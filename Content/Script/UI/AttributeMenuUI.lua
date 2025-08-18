--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_AttributeMenu_C
local M = UnLua.Class()

--function M:Initialize(Initializer)
--end

--function M:PreConstruct(IsDesignTime)
--end

function M:Construct()
    self.Button_Close.OnClicked:Add(self,self.OnCloseButtonClick)
end

function M:OnCloseButtonClick()
    local GameInstance = self:GetGameInstance()
    GameInstance:CloseUIByString("UI.Layer.GameMenu.AttributeMenuUI")
end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M
