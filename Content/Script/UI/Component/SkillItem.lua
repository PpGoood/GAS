--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_SkillItem_C
local M = UnLua.Class()

function M:WidgetControllerSet_Event()
    self.ListenTask = UE.UListenCooldownChangeTask.ListenForCooldownChange(self.WidgetController.AbilitySystemComponent,self.CooldownTag)
    self.ListenTask.CooldownStart:Add(self,self.CooldownStart)
    self.ListenTask.CooldownEnd:Add(self,self.CooldownEnd)
end

function M:CooldownStart(TimeRemaining)
    self:SetCooldownState()
    self.CooldownTime = TimeRemaining
    self:UpdateText()
    self.Timer = UE.UKismetSystemLibrary.K2_SetTimerDelegate({self,self.UpdateText},self.FrequencyTimer,true)
end

function M:UpdateText(TimeRemaining)
    self.CooldownTime = self.CooldownTime - self.FrequencyTimer
    self.CooldownTime = math.max(0,self.CooldownTime)
    self.Text_Cooldown:SetText(UE.UKismetTextLibrary.Conv_DoubleToText(self.CooldownTime))
end

function M:CooldownEnd()
    self:SetDefaultState()
    UE4.UKismetSystemLibrary.K2_ClearAndInvalidateTimerHandle(self,self.Timer)
end
--function M:Initialize(Initializer)
--end

--function M:PreConstruct(IsDesignTime)
--end

function M:Construct()
    self:SetDefaultState()
    self:UpdateText()
    self.FrequencyTimer = 0.1
end

function M:Destruct()
    self.ListenTask:EndTask()
    UE4.UKismetSystemLibrary.K2_ClearAndInvalidateTimerHandle(self,self.Timer)
end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M
