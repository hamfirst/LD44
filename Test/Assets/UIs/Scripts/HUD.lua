
hud_info = {}

tutorial_atlas = loader:LoadAtlas("./UIs/Tutorial.atlas")
ui_atlas = loader:LoadAtlas("./UIs/UI.atlas")
alert_img = loader:LoadTexture("./Images/NoiseIndicator.png")

heart = loader:LoadTexture("./Images/Heart.png")
half_heart = loader:LoadTexture("./Images/HeartHalf.png")
bullet = loader:LoadTexture("./Images/Bullet.png")
life_icon = loader:LoadTexture("./Images/BatIcon.png")
alert_img = loader:LoadTexture("./Images/NoiseIndicator.png")

plank1 = loader:LoadTexture("./Images/UI/plank_16_png_processed.png")
plank2 = loader:LoadTexture("./Images/UI/plank_17_png_processed.png")
plank3 = loader:LoadTexture("./Images/UI/plank_18_png_processed.png")

function DrawHud()

  --i:DrawAtlas(ui_atlas, "TopBar", screen_start_x, screen_end_y - 25, screen_width, 35)
  ui:DrawTexture(plank1, screen_start_x + 25, screen_end_y - 33)

  local heart_x = screen_start_x + 35
  local health = hud_info.health
  while health > 0 do
    if health > 1 then
      ui:DrawTexture(heart, heart_x, screen_end_y - 26)
      health = health - 2
      heart_x = heart_x + 16
    else
      ui:DrawTexture(half_heart, heart_x, screen_end_y - 26)
      health = health - 1
      heart_x = heart_x + 16
    end
  end

  ui:DrawTexture(plank2, 30, screen_end_y - 33)
  ui:DrawTexture(bullet, 45, screen_end_y - 26)
  ui:DrawTextScaled(large_header_font, math.floor(hud_info.ammo) .. " / " .. math.floor(hud_info.max_ammo), 75, screen_end_y - 21, 1, 1, 1, 1, kNormal, 0.5)
  
  ui:DrawTexture(plank3, 119, screen_end_y - 33)

  local life_x = 135
  local life = hud_info.lives
  while life > 0 do
    ui:DrawTexture(life_icon, life_x, screen_end_y - 26)
    life = life - 1
    life_x = life_x + 20
  end


  if hud_info.timer ~= "" then

    if hud_info.timer_pre_round then
      ui:DrawCenteredTextScaled(large_header_font, hud_info.timer, 0, screen_height / 4 + 10, 
        1, 1, 1, 1 - hud_info.timer_scale, kNormal, 1 + hud_info.timer_scale);
    else
      ui:DrawCenteredTextScaled(large_header_font, hud_info.timer, 0, screen_end_y - large_header_font_height + 10, 
        1, 1, 1, 1, kOutlined, 1);      
    end
  end


  for i = 1, hud_info.num_alerts do

    local s = math.sin(hud_info.alerts[i].angle)
    local c = math.cos(hud_info.alerts[i].angle)

    local max_extent_x = screen_width / 2 - 30
    local max_extent_y = screen_height / 2 - 30

    local max_extent = math.max(max_extent_x, max_extent_y)

    if s ~= 0 then
      max_extent = math.min(math.abs(max_extent_y / s), max_extent)
    end

    if c ~= 0 then
      max_extent = math.min(math.abs(max_extent_x / c), max_extent)
    end

    local oa = math.random() * math.pi * 2
    local o_alpha = hud_info.alerts[i].alpha * hud_info.alerts[i].alpha
    local os = math.sin(oa) * 6 * o_alpha
    local oc = math.cos(oa) * 6 * o_alpha

    ui:DrawTextureTint(alert_img, c * max_extent + oc, s * max_extent + os, 1, 1, 1, hud_info.alerts[i].alpha)
  end

  if hud_info.timer_post_round then
    ui:DrawFilledRectangle(screen_start_x, screen_start_y, screen_width, screen_height, 0, 0, 0, 1)
  end


  if hud_info.tutorial_hint ~= "" then
    local width, height = ui:MeasureText(font, hud_info.tutorial_hint)

    ui:DrawAtlas(tutorial_atlas, "Bubble", hud_info.tutorial_hint_x, hud_info.tutorial_hint_y, 64 + width, 64 + height)
    ui:DrawText(font, hud_info.tutorial_hint, hud_info.tutorial_hint_x + 32, hud_info.tutorial_hint_y + 38, 0, 0, 0, 1, kNormal)
  end

end

