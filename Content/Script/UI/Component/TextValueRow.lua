--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_TextValueRow_C
local M = UnLua.Class()

--function M:Initialize(Initializer)
--end

-- function M:PreConstruct(IsDesignTime)
--     self.SizeBox_Root.WidthOverride = self.BoxWidth
--     self.SizeBox_Root.HeightOverride = self.BoxHeight
-- end

function M:WidgetControllerSet_Event()
    self.WidgetController.AttributeInfoDelegate:Add(self,self.UpdateWiget)
end

function M:UpdateWiget(Info)
    if(self.AttributeTag == Info.AttributeTag)then
        local Value = math.floor(Info.AttributeValue)
        self.WBP_FramedValue.Text_Value:SetText(UE.UKismetTextLibrary.Conv_IntToText(Value))
        self.Text_Name:SetText(Info.AttributeName)
    end
end
-- function M:Construct()
--     local PlayerController = UE.UGameplayStatics.GetPlayerController(self,0)
--     local HUD = PlayerController:GetHUD()
--     HUD:CloseUIByString("UI.Layer.GameMenu.AttributeMenuUI")
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M
