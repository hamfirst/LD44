
#include <QTimer>
#include <QKeyEvent>

#include <SDL2/SDL_keyboard.h>

#include "GameClientWidget.h"
#include "EditorContainer.h"

#include "Engine/Input/KeyboardState.h"


extern DelegateList<void> g_GlobalUpdate;

GameClientWidget::GameClientWidget(int client_index, QWidget *parent) :
  QOpenGLWidget(parent),
  m_ClientIndex(client_index)
{
  setFocusPolicy(Qt::ClickFocus);
  setAttribute(Qt::WA_InputMethodEnabled);
  setMouseTracking(true);
}

GameClientWidget::~GameClientWidget()
{

}

void GameClientWidget::initializeGL()
{

}

void GameClientWidget::resizeGL(int w, int h)
{
  if (m_FakeWindow)
  {
    m_FakeWindow->SetWindowSize(Vector2(w, h));
  }
}

void GameClientWidget::paintGL()
{
  if (m_GameContainer)
  {
    m_GameContainer->Render();
  }
}

void GameClientWidget::showEvent(QShowEvent * ev)
{
  auto window_geo = geometry();
  auto window_pos = mapToGlobal(QPoint(window_geo.x(), window_geo.y()));
  auto window_box = Box{ Vector2{ window_pos.x(), window_pos.y() }, Vector2{ window_pos.x() + window_geo.width(), window_pos.y() + window_geo.height() } };

  m_FakeWindow.Emplace(
    window_box,
    [this] {},
    [this] {},
    [this](int x, int y) { QCursor::setPos(x, y); },
    [this] { close(); },
    [this](NullOptPtr<Box> box) { m_ImeMode = true; },
    [this] { m_ImeMode = false; }
  );

  auto cursor_pos = mapFromGlobal(QCursor::pos());

  if (window_geo.contains(cursor_pos))
  {
    m_FakeWindow->SetWindowMouseFocused(true);
  }

  if (hasFocus())
  {
    m_FakeWindow->SetWindowKeyboardFocused(true);
  }

  auto init_settings = std::make_unique<GameContainerInitSettings>();
  init_settings->m_AutoConnect = true;
  init_settings->m_UserName = "Player" + std::to_string(m_ClientIndex + 1);

  m_FakeWindow->HandleMouseMoveMessage(cursor_pos.x(), cursor_pos.y());
  m_GameContainer.Emplace(m_FakeWindow->GetWindow(), std::move(init_settings));

  g_GlobalUpdate.AddDelegate();

  m_UpdateDelegate = g_GlobalUpdate.AddDelegate([this] { Update(); });

  setFocus();
}

void GameClientWidget::closeEvent(QCloseEvent * ev)
{

}

void GameClientWidget::keyPressEvent(QKeyEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  if (m_ImeMode)
  {
    auto text = event->text().toStdString();
    m_FakeWindow->HandleTextInputCommit(text.data());
    event->text();
  }

  auto scan_code = KeyboardState::ScanCodeFromQtCode(event->key());
  m_FakeWindow->HandleKeyPressMessage(SDL_GetKeyFromScancode((SDL_Scancode)scan_code), scan_code, true);
}

void GameClientWidget::keyReleaseEvent(QKeyEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  auto scan_code = KeyboardState::ScanCodeFromQtCode(event->key());
  m_FakeWindow->HandleKeyPressMessage(SDL_GetKeyFromScancode((SDL_Scancode)scan_code), scan_code, false);
}

void GameClientWidget::mousePressEvent(QMouseEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  int button;
  if (event->button() == Qt::LeftButton)
  {
    button = kMouseLeftButton;
  }
  else if (event->button() == Qt::MiddleButton)
  {
    button = kMouseMiddleButton;
  }
  else if (event->button() == Qt::RightButton)
  {
    button = kMouseRightButton;
  }
  else
  {
    return;
  }

  m_FakeWindow->HandleMouseButtonPressMessage(button, true);
}

void GameClientWidget::mouseMoveEvent(QMouseEvent *event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->HandleMouseMoveMessage(event->x(), event->y());
}

void GameClientWidget::mouseReleaseEvent(QMouseEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  int button;
  if (event->button() == Qt::LeftButton)
  {
    button = kMouseLeftButton;
  }
  else if (event->button() == Qt::MiddleButton)
  {
    button = kMouseMiddleButton;
  }
  else if (event->button() == Qt::RightButton)
  {
    button = kMouseRightButton;
  }
  else
  {
    return;
  }

  m_FakeWindow->HandleMouseButtonPressMessage(button, false);
}

void GameClientWidget::moveEvent(QMoveEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  auto pos = mapToGlobal(QPoint(0, 0));
  m_FakeWindow->SetWindowPos(Vector2(pos.x(), pos.y()));
}

void GameClientWidget::focusInEvent(QFocusEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowKeyboardFocused(true);
}

void GameClientWidget::focusOutEvent(QFocusEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowKeyboardFocused(false);
}

void GameClientWidget::enterEvent(QEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowMouseFocused(true);
}

void GameClientWidget::leaveEvent(QEvent * event)
{
  if (!m_FakeWindow)
  {
    return;
  }

  m_FakeWindow->SetWindowMouseFocused(false);
}

void GameClientWidget::Update()
{
  if (!m_FakeWindow)
  {
    return;
  }

  auto pos = mapToGlobal(QPoint(0, 0));
  m_FakeWindow->SetWindowPos(Vector2(pos.x(), pos.y()));

  m_GameContainer->Update();
  repaint();
}
