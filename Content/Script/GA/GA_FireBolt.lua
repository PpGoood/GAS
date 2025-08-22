--  
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type GA_FireBolt_C
local M = UnLua.Class()

-- function M:K2_ActivateAbility()
--     UE.UKismetSystemLibrary.PrintString(WorldContectObject,"准备播放动画ActivateTest")

--     local Proxy = UE.UGAS_PlayMontageAndWaitForEvent.PlayMontageAndWaitForEvent(
--         self, 
--         nil, 
--         self.FireAnim,
--         UE.UBlueprintGameplayTagLibraryUtil.GetTagFromString("Event.Montage.FireBolt"),
--         1, 
--         nil,
--         true, 
--         1.0)
    
--     Proxy.EventReceived:Add(self,self.OnEventReceived)
--     Proxy:ReadyForActivation()

-- end

-- eg
-- function M:K2_ActivateAbility()
--     if self:IsLocallyControlled() then
--         self:StartRangedWeaponTargeting()
--     end

--     local Proxy = UE.UAbilityTask_PlayMontageAndWait.CreatePlayMontageAndWaitProxy(self, nil, self.CharacterFireMontage, self.AutoRate, nil, false, 1.0, 0)
--     local Handler = function()
--         self:K2_EndAbility()
--     end
--     Proxy.OnCompleted:Add(self, Handler)
--     Proxy.OnInterrupted:Add(self, Handler)
--     Proxy.OnCancelled:Add(self, Handler)
--     Proxy:ReadyForActivation()

--     UE.UKismetSystemLibrary.K2_SetTimerDelegate({ self, self.FireComplete }, self.FireDelayTimeSecs, false, 0, 0)
-- end

-- function M:FireComplete()
--     self:K2_EndAbility()
-- end

function M:OnEventReceived()
    UE.UKismetSystemLibrary.PrintString(WorldContectObject,"收到了标签哦")
    self:SpawnProjectile()
    self:K2_EndAbility()
end
return M