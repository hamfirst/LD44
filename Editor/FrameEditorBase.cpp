
#include <QPainter>
#include <QWheelEvent>
#include <QApplication>

#include "StormData/StormDataPath.h"

#include "Engine/Shader/ShaderManager.h"
#include "Engine/Shader/DefaultShader.h"
#include "Engine/Sprite/SpriteEngineData.h"

#include "FrameEditorBase.h"
#include "FrameEditorUtil.h"
#include "FrameEditorShader.h"
#include "SpriteEditor.h"

FrameEditorBase::FrameEditorBase(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  uint64_t frame_id,
  QWidget * parent) :
  QOpenGLWidget(parent),
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_FrameId(frame_id),
  m_VertexBuffer(true)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);
}

void FrameEditorBase::SyncMouse()
{
  bool should_have_mouse = m_Panning || m_Dragging;
  if (should_have_mouse && m_HasMouse == false)
  {
    grabMouse();
    m_HasMouse = true;
  }
  else if (should_have_mouse == false && m_HasMouse)
  {
    releaseMouse();
    m_HasMouse = false;
  }
}

void FrameEditorBase::SyncDraw()
{
  auto p = QCursor::pos();
  Vector2 pos = Vector2(p.x(), p.y());

  if (m_Dragging)
  {
    DrawMove(pos,
      (QApplication::keyboardModifiers() & Qt::AltModifier) != 0,
      (QApplication::keyboardModifiers() & Qt::ShiftModifier) != 0,
      (QApplication::keyboardModifiers() & Qt::ControlModifier) != 0);
  }
  else
  {
    DrawPreview(pos,
      (QApplication::keyboardModifiers() & Qt::AltModifier) != 0,
      (QApplication::keyboardModifiers() & Qt::ShiftModifier) != 0,
      (QApplication::keyboardModifiers() & Qt::ControlModifier) != 0);
  }
}

Vector2 FrameEditorBase::TransformScreenToFrame(const Vector2 & pos)
{
  auto p = pos;

  auto half_window_size = Vector2(width() / 2, height() / 2);
  p -= half_window_size;
  
  p.y *= -1;
  p /= m_Magnification;
  p.x += (int)m_Center.x;
  p.y += (int)m_Center.y;
  return p;
}

Vector2 FrameEditorBase::TransformFrameToScreen(const Vector2 & pos)
{
  auto p = pos;

  p.x -= (int)m_Center.x;
  p.y -= (int)m_Center.y;

  p *= m_Magnification;
  p.y *= -1;

  auto half_window_size = Vector2(width() / 2, height() / 2);
  p += half_window_size;
  return p;
}

void FrameEditorBase::DrawBox(const Box & box)
{
  m_GeometryBuidler->FilledRectangle(box.m_Start, box.m_End + Vector2(1,1), Color(0, 0, 0, 200));
}

void FrameEditorBase::DrawEdge(const FrameEditorEdge & edge)
{
  auto offset = FrameEditorByteArray::GetOffsetForEdgeType(edge.m_Type);
  m_GeometryBuidler->Line(edge.m_P1 + offset, edge.m_P2 + offset, 3.0f / m_Magnification, Color(250, 12, 250, 255));
}

void FrameEditorBase::DrawHighlightedEdge(const FrameEditorEdge & edge)
{
  auto offset = FrameEditorByteArray::GetOffsetForEdgeType(edge.m_Type);
  m_GeometryBuidler->Line(edge.m_P1 + offset, edge.m_P2 + offset, 7.0f / m_Magnification, Color(128, 128, 250, 255));
}

void FrameEditorBase::DrawLine(const Vector2 & a, const Vector2 & b)
{
  m_GeometryBuidler->Line(a, b, 5.0f / m_Magnification, Color(0, 0, 0, 255));
  m_GeometryBuidler->Line(a, b, 3.0f / m_Magnification, Color(255, 255, 255, 255));
}

void FrameEditorBase::DrawCornerControl(const Vector2 & pos)
{
  m_GeometryBuidler->FilledCircle(pos, 7.0f / m_Magnification, Color(255, 255, 10, 255), 20);
  m_GeometryBuidler->Circle(pos, 7.0f / m_Magnification, 2.0f / m_Magnification, Color(0, 0, 0, 255), 20);
  m_GeometryBuidler->Circle(pos, 2.0f / m_Magnification, 1.0f / m_Magnification, Color(0, 0, 0, 255), 20);
}

void FrameEditorBase::DrawHighlightedCornerControl(const Vector2 & pos)
{
  m_GeometryBuidler->FilledCircle(pos, 7.0f / m_Magnification, Color(255, 255, 10, 255), 20);
  m_GeometryBuidler->Circle(pos, 7.0f / m_Magnification, 3.0f / m_Magnification, Color(128, 128, 255, 250), 20);
  m_GeometryBuidler->Circle(pos, 2.0f / m_Magnification, 1.0f / m_Magnification, Color(0, 0, 0, 255), 20);
}

void FrameEditorBase::DrawData()
{

}

void FrameEditorBase::DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void FrameEditorBase::DrawLeave()
{

}

bool FrameEditorBase::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  return false;
}

void FrameEditorBase::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void FrameEditorBase::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{

}

void FrameEditorBase::DrawCancel()
{

}

void FrameEditorBase::StopDrawing()
{
  if (m_Dragging)
  {
    DrawCancel();
    m_Dragging = false;
    SyncMouse();
  }
}

void FrameEditorBase::initializeGL()
{
  m_RenderState.InitRenderState(width(), height());
  m_RenderUtil.LoadShaders();

  m_Shader = MakeQuickShaderProgram(kDefaultVertexShader, kFrameEditorFragmentShader);
}

void FrameEditorBase::resizeGL(int w, int h)
{
  m_RenderState.SetScreenSize(Vector2(w, h));
}

void FrameEditorBase::paintGL()
{
  QColor clear_color_qt = palette().color(QPalette::Window);
  Color color(clear_color_qt.red(), clear_color_qt.green(), clear_color_qt.blue(), 255);

  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);

  if (m_Sprite.m_Textures.HighestIndex() == -1)
  {
    return;
  }

  auto & first_texture = m_Sprite.m_Textures.begin();
  auto texture = m_TextureAccess.GetTexture(first_texture->first);

  if (texture == nullptr)
  {
    return;
  }

  Vector2 frame_size = { first_texture->second.m_FrameWidth, first_texture->second.m_FrameHeight };
  Vector2 texture_size = texture->GetSize();

  if (frame_size.x == 0 || frame_size.y == 0 || texture_size.x == 0 || texture_size.y == 0)
  {
    return;
  }

  m_RenderState.EnableBlendMode();

  Box frame_box = Box::FromFrameCenterAndSize(Vector2{}, frame_size);

  RenderVec2 resolution{ width(), height() };
  resolution /= m_Magnification;

  auto screen_start = TransformScreenToFrame(Vector2(0, 0));
  auto screen_end = TransformScreenToFrame(Vector2(width() - 1, height() - 1));

  LineVertexBufferBuilder line_builder;
  LineVertexBuilderInfo line;
  line.m_TextureSize = Vector2(1, 1);

  RenderVec4 matrix = RenderVec4{ 1.0f, 0.0f, 0.0f, 1.0f };
  if (m_MirrorX)
  {
    matrix.x *= -1.0f;
  }

  if (m_MirrorY)
  {
    matrix.w *= -1.0f;
  }

  auto & default_shader = g_ShaderManager.GetDefaultShader();
  default_shader.Bind();
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 200));
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), resolution);
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ m_Center } *-1.0f);
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), matrix);

  texture->GetTexture().BindTexture(0);

  QuadVertexBufferBuilder builder;
  builder.AddFrame(frame_box, texture_size, frame_size, 0, Color(255, 255, 255, 255));
  builder.FillVertexBuffer(m_VertexBuffer);


  m_VertexBuffer.Bind();
  m_VertexBuffer.CreateDefaultBinding(default_shader);
  m_VertexBuffer.Draw();

  frame_box.m_End += Vector2(1, 1);
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  default_shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0f, 0.0f, 0.0f, 1.0f });

  if (m_Magnification >= 4)
  {
    for (int x = screen_start.x - 1; x <= screen_end.x + 1; x++)
    {
      line.m_Start.x = x;
      line.m_Start.y = screen_start.y + 1;
      line.m_End.x = x;
      line.m_End.y = screen_end.y - 1;
      line.m_Color = Color(128, 128, 128, 50);
      line_builder.AddLine(line);
    }

    for (int y = screen_end.y - 1; y <= screen_start.y + 1; y++)
    {
      line.m_Start.x = screen_start.x - 1;
      line.m_Start.y = y;
      line.m_End.x = screen_end.x + 1;
      line.m_End.y = y;
      line.m_Color = Color(128, 128, 128, 50);
      line_builder.AddLine(line);
    }


    for (int x = frame_box.m_Start.x; x <= frame_box.m_End.x; x++)
    {
      line.m_Start.x = x;
      line.m_Start.y = frame_box.m_Start.y;
      line.m_End.x = x;
      line.m_End.y = frame_box.m_End.y;
      line.m_Color = Color(0, 0, 0, 128);
      line_builder.AddLine(line);
    }

    for (int y = frame_box.m_Start.y; y <= frame_box.m_End.y; y++)
    {
      line.m_Start.x = frame_box.m_Start.x;
      line.m_Start.y = y;
      line.m_End.x = frame_box.m_End.x;
      line.m_End.y = y;
      line.m_Color = Color(0, 0, 0, 128);
      line_builder.AddLine(line);
    }


    m_RenderUtil.GetDefaultTexture().BindTexture(0);

    line_builder.FillVertexBuffer(m_VertexBuffer);
    m_VertexBuffer.Bind();
    m_VertexBuffer.CreateDefaultBinding(default_shader);
    m_VertexBuffer.Draw();
  }

  m_Shader.Bind();
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), resolution);
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ActualScreenSize"), RenderVec2(width(), height()));
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ m_Center } *-1.0f);
  m_Shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0f, 0.0f, 0.0f, 1.0f });

  m_GeometryBuidler.Emplace();
  m_GeometryBuidler->Rectangle(frame_box.m_Start, frame_box.m_End, 3.0f / m_Magnification, Color(0, 0, 0, 255));

  DrawData();

  m_RenderUtil.GetDefaultTexture().BindTexture(0);

  m_GeometryBuidler->FillVertexBuffer(m_VertexBuffer);
  m_VertexBuffer.Bind();
  m_VertexBuffer.CreateDefaultBinding(m_Shader);
  m_VertexBuffer.Draw();

  m_GeometryBuidler.Clear();
}

void FrameEditorBase::tick()
{
  repaint();
}

void FrameEditorBase::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_X)
  {
    m_MirrorX = !m_MirrorX;
    repaint();
  }

  if (event->key() == Qt::Key_Y)
  {
    m_MirrorY = !m_MirrorY;
    repaint();
  }

  if (event->key() == Qt::Key_Alt || event->key() == Qt::Key_Shift || event->key() == Qt::Key_Control)
  {
    SyncDraw();
  }
}

void FrameEditorBase::keyReleaseEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Alt || event->key() == Qt::Key_Shift || event->key() == Qt::Key_Control)
  {
    SyncDraw();
  }
}

void FrameEditorBase::mousePressEvent(QMouseEvent * event)
{
  bool alt = (bool)(event->modifiers() & Qt::AltModifier);
  bool shift = (bool)(event->modifiers() & Qt::ShiftModifier);
  bool ctrl = (bool)(event->modifiers() & Qt::ControlModifier);

  auto p = QCursor::pos();
  p = mapFromGlobal(p);

  if (event->button() == Qt::LeftButton)
  {

    Vector2 pos = Vector2(p.x(), p.y());

    if (DrawStart(pos, alt, shift, ctrl))
    {
      m_Dragging = true;
      SyncMouse();
    }
  }
  else if (event->button() == Qt::MiddleButton)
  {
    m_CursorPos = p;

    m_Panning = true;
    SyncMouse();
    return;
  }
  else if(event->button() == Qt::RightButton)
  {
    if (m_Dragging)
    {
      StopDrawing();
    }
  }
}

void FrameEditorBase::mouseMoveEvent(QMouseEvent *event)
{
  auto p = QCursor::pos();
  p = mapFromGlobal(p);
  Vector2 pos = Vector2(p.x(), p.y());

  bool alt = (bool)(event->modifiers() & Qt::AltModifier);
  bool shift = (bool)(event->modifiers() & Qt::ShiftModifier);
  bool ctrl = (bool)(event->modifiers() & Qt::ControlModifier);

  if (m_Dragging)
  {
    DrawMove(pos, alt, shift, ctrl);
  }
  else
  {
    DrawPreview(pos, alt, shift, ctrl);
  }

  if (m_Panning)
  {
    auto diff_pos = p - m_CursorPos;

    m_Center.x -= (float)diff_pos.x() / m_Magnification;
    m_Center.y += (float)diff_pos.y() / m_Magnification;
    repaint();
  }

  m_CursorPos = p;
}

void FrameEditorBase::mouseReleaseEvent(QMouseEvent * event)
{
  auto p = QCursor::pos();
  p = mapFromGlobal(p);

  bool alt = (bool)(event->modifiers() & Qt::AltModifier);
  bool shift = (bool)(event->modifiers() & Qt::ShiftModifier);
  bool ctrl = (bool)(event->modifiers() & Qt::ControlModifier);

  if (event->button() == Qt::LeftButton)
  {
    if (m_Dragging)
    {
      Vector2 pos = Vector2(p.x(), p.y());
      DrawEnd(pos, alt, shift, ctrl);
      m_Dragging = false;
      SyncMouse();
    }
  }

  if (event->button() == Qt::MiddleButton)
  {
    m_Panning = false;
    SyncMouse();
    return;
  }
}

void FrameEditorBase::wheelEvent(QWheelEvent *event)
{
  if (event->delta() < 0)
  {
    if (m_Magnification > 1)
    {
      m_Magnification -= m_Magnification / 6 + 1;
    }
  }
  else
  {
    m_Magnification += m_Magnification / 6 + 1;
  }

  repaint();
}

void FrameEditorBase::leaveEvent(QEvent * event)
{
  DrawLeave();
}