
#include "GameClient/GameModeLogo.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameContainer.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"


void GameModeLogo::Initialize(GameContainer & container)
{
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(0, 0, 0, 255));

  GetAssets().LoadAsset<TextureAsset>("./Images/stormbrewers_logo.png", "logo");
}

void GameModeLogo::OnAssetsLoaded(GameContainer & container)
{
  m_Timer.Start();
}

void GameModeLogo::Update(GameContainer & container)
{
  if (m_Timer.GetTimeSinceStart() > 1.0 && container.AllGlobalResourcesLoaded())
  {
    container.StartNetworkClient("127.0.0.1", 47815);
    container.SwitchMode(GameModeDef<GameModeConnecting>{});
    return;
  }
}

void GameModeLogo::Render(GameContainer & container)
{
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.Clear();
  
  render_state.EnableBlendMode();

  auto texture = GetAssets().GetTexture("logo");
  if (texture && texture->IsLoaded())
  {
    auto window_size = container.GetWindow().GetSize();
    auto texture_size = texture->GetSize();
   
    render_util.DrawTexturedQuad(window_size / 2 - texture_size / 2, Color(255, 255, 255, 255), texture->GetTexture(), window_size);
  }
}
