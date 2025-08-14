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
    local widgets = { self.WBP_HealthGlobe, self.WBP_ManaGlobe }
    for _, widget in ipairs(widgets) do
        widget:SetWidgetController(self.WidgetController)
    end

    if not self.WidgetController then return end
    self.WidgetController.MessageWidgetRowDelegate:Add(self, self.OnMessage)
    
end

function M:OnMessage(Row)
    -- 打印消息，检查是否接收到正确的消息内容
    print("[PeiLuaLog] OnMessage", Row.Message)

    -- 加载蓝图类，确保路径正确
    local UMG_C = UE4.UClass.Load("/Game/_Game/Blueprints/UI/Main/SubWidget/WBP_EffectMessage.WBP_EffectMessage_C")
    if UMG_C == nil then
        print("[PeiLuaLog] Failed to load UMG class!")
        return
    end

    -- 创建 UMG 实例
    local UMG_TestMain_Ins = UE4.UWidgetBlueprintLibrary.Create(self, UMG_C)
    if UMG_TestMain_Ins == nil then
        print("[PeiLuaLog] Failed to create UMG instance!")
        return
    end

    -- 获取视口大小并进行调整
    local vector = UE4.UWidgetLayoutLibrary.GetViewportSize(self)

    -- 将 UMG 实例添加到视口
    UMG_TestMain_Ins:AddToViewport()

    -- 确保 UMG_TestMain_Ins 被成功转换为期望的蓝图类型
    local castUI = UMG_TestMain_Ins:Cast(UE4.AWBP_EffectMessage_C)  -- 确保类名正确
    if castUI == nil then
        print("[PeiLuaLog] Failed to cast UMG_TestMain_Ins to WBP_EffectMessage_C")
        return
    end
    -- 调用 WBP_EffectMessage_C 中的 ShowMessage 方法
    castUI:ShowMessage(Row.Image, Row.Message)
end


--function M:Initialize(Initializer)
--end

--function M:PreConstruct(IsDesignTime)
--end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M
