font_pts = 8
chat_font_pts = 10
large_header_font_pts = 14
small_header_font_pts = 9

font_height = 0
chat_font_height = 0
large_header_font_height = 0
small_header_font_height = 0

font = loader:LoadFont("./Fonts/Centurion 8x8.ttf", font_pts, -2);
chat_font = loader:LoadFont("./Fonts/Montserrat-Bold.ttf", chat_font_pts, 0)

large_header_font = loader:LoadFont("./Fonts/FFF.ttf", large_header_font_pts, 0)
small_header_font = loader:LoadFont("./Fonts/FFF.ttf", small_header_font_pts, 0)

PushPostLoadFunc(function ()
  font_height = ui:GetLineHeight(font) + 4
  chat_font_height = ui:GetLineHeight(chat_font) + 2
  large_header_font_height = ui:GetLineHeight(large_header_font) + 2
  small_header_font_height = ui:GetLineHeight(small_header_font) + 2
end)
