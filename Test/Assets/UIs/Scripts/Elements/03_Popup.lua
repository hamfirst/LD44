
Popup = Elem:construct()
Popup.alpha = 0


function Popup:setup(o)
  Elem:setup(o)
  o:SetClip(false)
  o:SetEnabled(false)

  o.children = {}
  o.next_child_id = 0
end

function Popup:Draw()
  ui:DrawFilledRectangle(0 - 10, 0 - 10, self.width, self.height, 0, 0, 0, self.alpha - 0.7)
  ui:DrawFilledRectangle(0, 0, self.width - 1, self.height - 1, 1, 1, 1, self.alpha)
  ui:DrawRectangle(0, 0, self.width, self.height, 0.8, 0.8, 0.8, self.alpha)
  ui:FlushGeometry()
end

function Popup:PushChild(elem)
  elem:SetParent(self)
  self.children[self.next_child_id] = elem
  self.next_child_id = self.next_child_id + 1
  return elem
end

function Popup:FadeIn()
  for k, v in pairs(self.children) do
    v:destroy()
  end

  self.children = {}
  self.next_child_id = 0
  self:CreateChildren()

  for k, v in pairs(self.children) do

    if v.parent_alpha ~= nil then
      v.parent_alpha = 0
      AddLerp(v, "parent_alpha", 1, 0.3, nil, EaseInCubic)
    end
  end

  self.alpha = 0
  AddLerp(self, "alpha", 1, 0.2, nil, EaseInCubic)
  self:SetEnabled(true)

  popup_fader:FadeToSolid()
end

function Popup:FadeOut()
  for k, v in pairs(self.children) do
    v.pressable = false

    if v.parent_alpha ~= nil then
      AddLerp(v, "parent_alpha", 0, 0.3, nil, EaseInCubic)
    end
  end

  AddLerp(self, "alpha", 0, 0.6, function() self:SetEnabled(false) end, EaseInCubic)

  popup_fader:FadeToClear()
end

function CreatePopupFader()
  popup_fader = PushMenuElement(Fader:new())
  popup_fader.target_alpha = 0.5

  popup_fader:SetAlpha(0)
end