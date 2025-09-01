--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_AttributeMenu_C
local M = UnLua.Class()
--TODO应该用对象池生成,错误示范
function M:WidgetControllerSet_Event()
    local ChildWiget = {self.WBP_TextValueRow_Point,
    self.WBP_TextValueButtonRow_1,
    self.WBP_TextValueButtonRow_2,
    self.WBP_TextValueButtonRow_3,
    self.WBP_TextValueButtonRow_4,
    self.WBP_TextValueRow_1,
    self.WBP_TextValueRow_2,
    self.WBP_TextValueRow_3,
    self.WBP_TextValueRow_4,
    self.WBP_TextValueRow_5,
    self.WBP_TextValueRow_6,
    self.WBP_TextValueRow_7,
    self.WBP_TextValueRow_8,
    self.WBP_TextValueRow_9,
    self.WBP_TextValueRow_10, 
    self.WBP_TextValueRow_11,
    self.WBP_TextValueRow_12,
    self.WBP_TextValueRow_13,
    self.WBP_TextValueRow_14 
    }
    for _, widget in ipairs(ChildWiget) do
        widget:SetWidgetController(self.WidgetController)
    end
end

--function M:Initialize(Initializer)
--end

--function M:PreConstruct(IsDesignTime)
--end

function M:Construct()
    self.Button_Close.OnClicked:Add(self,self.OnCloseButtonClick)
end

function M:OnCloseButtonClick()
    -- local GameInstance = self:GetGameInstance()
    -- GameInstance:CloseUIByString("UI.Layer.GameMenu.AttributeMenuUI")
    --TODO应该抽成蓝图库静态全局方法
    local PlayerController = UE.UGameplayStatics.GetPlayerController(self,0)
    local HUD = PlayerController:GetHUD()
    HUD:CloseUIByString("UI.Layer.GameMenu.AttributeMenuUI")
end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M
