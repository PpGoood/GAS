--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_SpellGlobe_C
local M = UnLua.Class()


function M:WidgetControllerSet_Event()
    self.WidgetController.AbilityInfoDelegate:Add(self, self.OnAbilityInfoSignature)
end

function M:OnAbilityInfoSignature(info)
    -- UE.UKismetSystemLibrary.PrintString(WorldContectObject,"OnAbilityInfoSignature")
    self:SetAbilityIconInfo(info)
    self:SetDefaultState()
    local isMatch = UE.UBlueprintGameplayTagLibrary.MatchesTag(info.InputTag,self.InputTag,true)
    if isMatch then
    
        if self.ListenCooldownTask then
            self.ListenCooldownTask:EndTask()
        end
        self.ListenCooldownTask = UE.UListenCooldownChangeTask.ListenForCooldownChange(self.WidgetController.AbilitySystemComponent,info.CooldownTag)
        self.ListenCooldownTask.CooldownStart:Add(self,self.CooldownStart)
        self.ListenCooldownTask.CooldownEnd:Add(self,self.CooldownEnd)

    end
end

function M:CooldownStart(TimeRemaining)
    self:SetCooldownState()
    self.CooldownTime = TimeRemaining
    self.CooldownTime = math.max(0,self.CooldownTime)
    self.Text_Cooldown:SetText(UE.UKismetTextLibrary.Conv_DoubleToText(self.CooldownTime))
    self.Timer = UE.UKismetSystemLibrary.K2_SetTimerDelegate({self,self.UpdateText},self.FrequencyTimer,true)
end


function M:CooldownEnd()
    self:SetDefaultState()
    UE4.UKismetSystemLibrary.K2_ClearAndInvalidateTimerHandle(self,self.Timer)
end

function M:UpdateText(TimeRemaining)
    if self.CooldownTime <= 0 then
        return
    end

    self.CooldownTime = self.CooldownTime - self.FrequencyTimer
    self.CooldownTime = math.max(0,self.CooldownTime)
    self.Text_Cooldown:SetText(UE.UKismetTextLibrary.Conv_DoubleToText(self.CooldownTime))
end

function M:Destruct()
    if self.ListenCooldownTask then
        self.ListenCooldownTask:EndTask()
    end
    if self.Timer then
         UE.UKismetSystemLibrary.K2_ClearAndInvalidateTimerHandle(self,self.Timer)
    end
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
