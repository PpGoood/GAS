--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_GlobeProgressBar_C
local M = UnLua.Class()

--function M:Initialize(Initializer)
--end

function M:PreConstruct(IsDesignTime)
    self.Image_Background:SetBrush(self.BackgroundBrush)
    self.Image_Glass:SetBrush(self.GlassBrush)
    self.ProgressBarStyle.FillImage = self.ProgressBarFillmage
    self.ProgressBar_Globe.WidgetStyle = self.ProgressBarStyle
end

return M
