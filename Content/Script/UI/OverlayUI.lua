require("LuaPanda").start("127.0.0.1", 8818);
--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_Overlay_C
local M = UnLua.Class()

function M:WidgetControllerSet_Event()
    -- 设置所有需要的控件的 WidgetController
    local widgets = { self.WBP_HealthGlobe, self.WBP_ManaGlobe,self.WBP_SkillItem }
    for _, widget in ipairs(widgets) do
        widget:SetWidgetController(self.WidgetController)
    end

    if not self.WidgetController then return end
    self.WidgetController.MessageWidgetRowDelegate:Add(self, self.OnMessage)
    self.WidgetController.OnControllerChargeChanged:Add(self, self.OnChargeBarUpdate)
end

function M:OnChargeBarUpdate(CurCharge,MaxCharge)
    self.ChargeBar:SetPercent(CurCharge / MaxCharge)
end

function M:OnMessage(Row)
    --TODO 使用UI管理器，现在每次消息都会弹出

    -- 加载蓝图类，确保路径正确
    local UMG_C = UE4.UClass.Load("/Game/_Game/Blueprints/UI/Main/SubWidget/WBP_EffectMessage.WBP_EffectMessage_C")
    if UMG_C == nil then
        print("[PeiLuaLog] Failed to load UMG class!")
        return
    end

    -- 创建 UMG 实例
    local UMG_Message = UE4.UWidgetBlueprintLibrary.Create(self, UMG_C)
    if UMG_Message == nil then
        print("[PeiLuaLog] Failed to create UMG instance!")
        return
    end

    self.CanvasPanel.AddChild(self.CanvasPanel,UMG_Message)
    local CanvasSlot = UE4.UWidgetLayoutLibrary.SlotAsCanvasSlot(UMG_Message)
    if CanvasSlot then
        -- 锚定到左下角 (0,1) 的位置
        local Anchors = UE4.FAnchors()
        Anchors.Minimum = UE4.FVector2D(0.0, 1.0)
        Anchors.Maximum = UE4.FVector2D(0.0, 1.0)
        CanvasSlot.SetAnchors(CanvasSlot,Anchors) -- 锚点设置为左下
        CanvasSlot.SetSize(CanvasSlot,UE4.FVector2D(400.0, 75.0))
        CanvasSlot.SetAlignment(CanvasSlot,UE4.FVector2D(0.0, 1.0))  -- 设置对齐方式为左下
        CanvasSlot.SetPosition(CanvasSlot,UE4.FVector2D(50.0, 0.0))  -- 设置具体位置
    end

    -- 确保 UMG_TestMain_Ins 被成功转换为期望的蓝图类型
    local UMG_Message_Cast = UMG_Message:Cast(UE4.AWBP_EffectMessage_C)  -- 确保类名正确
    if UMG_Message_Cast == nil then
        print("[PeiLuaLog] Failed to cast UMG_TestMain_Ins to WBP_EffectMessage_C")
        return
    end
    
    -- 调用 WBP_EffectMessage_C 中的 ShowMessage 方法
    UMG_Message_Cast:ShowMessage(Row.Image, Row.Message)
end

--function M:Initialize(Initializer)
--end

--function M:PreConstruct(IsDesignTime)
--end

function M:Construct()
    self.Button_Attribute.OnClicked:Add(self,self.OnAttributeButtonClick)
end

function M:OnAttributeButtonClick()
    --打开ui
    -- local GameInstance = self:GetGameInstance()
    -- GameInstance:OpenUIByString("UI.Layer.GameMenu.AttributeMenuUI")
    local PlayerController = UE.UGameplayStatics.GetPlayerController(self,0)
    local HUD = PlayerController:GetHUD()
    HUD:OpenUIByString("UI.Layer.GameMenu.AttributeMenuUI")
end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M
