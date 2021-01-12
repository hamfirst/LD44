

book = loader:LoadTexture("./Images/book_png_processed.png")

gun_icon = loader:LoadTexture("./Images/WesternIcons_21_png_processed.png")
ammo_icon = loader:LoadTexture("./Images/WesternIcons_24_png_processed.png")
life_up_icon = loader:LoadTexture("./Images/WesternIcons_28_png_processed.png")
health_icon = loader:LoadTexture("./Images/WesternIcons_105_png_processed.png")
hand_icon = loader:LoadTexture("./Images/WesternIcons_52_png_processed.png")
move_icon = loader:LoadTexture("./Images/WesternIcons_13_png_processed.png")


heart_cost_icon = loader:LoadTexture("./Images/HeartCost.png")
half_heart_cost_icon = loader:LoadTexture("./Images/HalfHeartCost.png")

Cost = Elem:construct()
Cost.hearts = 1

function Cost:Draw()

  ui:DrawText(font, "Cost", 0, 0, 0.15, 0.12, 0.08, 1, kNormal)

  local heart_x = 33
  local hearts = self.hearts

  while hearts > 0 do
    if hearts > 1 then
      ui:DrawTexture(heart_cost_icon, heart_x, -5)
      hearts = hearts - 2
      heart_x = heart_x + 10  
    else
      ui:DrawTexture(half_heart_cost_icon, heart_x, -5)
      hearts = hearts - 1
      heart_x = heart_x + 10
    end
  end
end

Purchase = Elem:construct()

function Purchase:Init(icon, cost, description, purchase_callback)
  self.icon = Texture:new(self)
  self.icon:SetTexture(icon)
  self.icon.y = 15

  self.cost = Cost:new(self)
  self.cost.x = 50
  self.cost.y = 20
  self.cost.width = 100
  self.cost.height = 32
  self.cost.hearts = cost

  self.description = Label:new(self)
  self.description.x = 50
  self.description.y = 20
  self.description.width = 100
  self.description.height = 20
  self.description.text = description
  self.description.r = 0.15
  self.description.g = 0.12
  self.description.b = 0.07
  self.description.centered = false

  if cost ~= 0 then
    self.purchase = Button:new(self)
    self.purchase.x = 10
    self.purchase.y = 0
    self.purchase.width = 100
    self.purchase.height = 15
    self.purchase.text = "Buy"
    self.purchase.fade = false
    
    self.purchase.presssed = purchase_callback
  end
end



Currency = Elem:construct()
function Currency:Draw()
  ui:DrawTexture(plank1, screen_start_x + 25, screen_end_y - 33)

  local heart_x = screen_start_x + 35
  while hud_info.health > 0 do
    if hud_info.health > 1 then
      ui:DrawTexture(heart, heart_x, screen_end_y - 26)
      hud_info.health = hud_info.health - 2
      heart_x = heart_x + 16
    else
      ui:DrawTexture(half_heart, heart_x, screen_end_y - 26)
      hud_info.health = hud_info.health - 1
      heart_x = heart_x + 16
    end
  end

  ui:DrawTexture(plank3, 119, screen_end_y - 33)

  local life_x = 135
  local lives = hud_info.lives
  while lives > 0 do
    ui:DrawTexture(life_icon, life_x, screen_end_y - 26)
    lives = lives - 1
    life_x = life_x + 20
  end

  if hud_info.timer ~= "" then
    ui:DrawCenteredTextScaled(large_header_font, hud_info.timer, 0, screen_end_y - large_header_font_height + 10, 
      1, 1, 1, 1, kOutlined, 1);      
  end
end


upgrade_info = { damage = 2, ammo = 3, health = 4, speed = 1, life = 2, rate = 3 }

function InitStoreMenu()

  local book_bkg = PushMenuElement(Texture:new())
  book_bkg:SetTexture(book)
  book_bkg.x = screen_start_x + 15
  book_bkg.y = screen_start_y

  local currency = PushMenuElement(Currency:new())
  currency:SetClip(false)

  local label1 = PushMenuElement(Label:new())
  label1.text = "Upgrades"
  label1.font = large_header_font
  label1.r = 0.15
  label1.g = 0.12
  label1.b = 0.08
  label1.a = 1
  label1.x = -140
  label1.y = 30
  label1.width = 100
  label1.height = 100

  local label2 = PushMenuElement(Label:new())
  label2.text = "For Sale"
  label2.font = large_header_font
  label2.r = 0.15
  label2.g = 0.12
  label2.b = 0.08
  label2.a = 1
  label2.x = 40
  label2.y = 30
  label2.width = 100
  label2.height = 100

  local damage_upgrade = PushMenuElement(Purchase:new())
  damage_upgrade:Init(gun_icon, upgrade_info.damage, "Damage+", function() game:BuyDamage() end)
  damage_upgrade.x = -160
  damage_upgrade.y = 20
  damage_upgrade.width = 200
  damage_upgrade.height = 50

  local ammo_upgrade = PushMenuElement(Purchase:new())
  ammo_upgrade:Init(ammo_icon, upgrade_info.ammo, "Ammo+", function() game:BuyAmmo() end)
  ammo_upgrade.x = -160
  ammo_upgrade.y = -30
  ammo_upgrade.width = 200
  ammo_upgrade.height = 50

  local health_upgrade = PushMenuElement(Purchase:new())
  health_upgrade:Init(health_icon, upgrade_info.health, "Health+", function() game:BuyHealth() end)
  health_upgrade.x = -160
  health_upgrade.y = -80
  health_upgrade.width = 200
  health_upgrade.height = 50

  local speed_upgrade = PushMenuElement(Purchase:new())
  speed_upgrade:Init(move_icon, upgrade_info.speed, "Speed+", function() game:BuySpeed() end)
  speed_upgrade.x = 40
  speed_upgrade.y = 20
  speed_upgrade.width = 200
  speed_upgrade.height = 50

  local life_upgrade = PushMenuElement(Purchase:new())
  life_upgrade:Init(life_up_icon, upgrade_info.life, "Life+", function() game:BuyLife() end)
  life_upgrade.x = 40
  life_upgrade.y = -30
  life_upgrade.width = 200
  life_upgrade.height = 50

  local rate_upgrade = PushMenuElement(Purchase:new())
  rate_upgrade:Init(hand_icon, upgrade_info.rate, "Rate+", function() game:BuyRate() end)
  rate_upgrade.x = 40
  rate_upgrade.y = -80
  rate_upgrade.width = 200
  rate_upgrade.height = 50
end

