
audio_on_texture = loader:LoadTexture("./Images/UI/MuteOff.png")
audio_off_texture = loader:LoadTexture("./Images/UI/Mute.png")

AudioControl = Elem:construct()

function AudioControl:setup(o)
  Elem:setup(o)
  o.width, o.height = ui:GetTextureSize(audio_on_texture)
end

function AudioControl:Draw()

  local texture_id = 0
  if ui:GetAudioVolume() > 0 then
    texture_id = audio_on_texture
  else
    texture_id = audio_off_texture
  end

  self.width, self.height = ui:GetTextureSize(texture_id)
  ui:DrawTexture(texture_id, 0, 0)
end

function AudioControl:Clicked()
  if ui:GetAudioVolume() > 0 then
    texture_id = ui:SetAudioVolume(0)
  else
    texture_id = ui:SetAudioVolume(0.85)
  end
end
