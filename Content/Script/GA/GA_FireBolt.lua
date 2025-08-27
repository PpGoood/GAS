-- --  
-- -- DESCRIPTION
-- --
-- -- @COMPANY **
-- -- @AUTHOR **
-- -- @DATE ${date} ${time}
-- --

-- ---@type GA_FireBolt_C
-- local M = UnLua.Class()

-- function M:K2_ActivateAbility()
--     UE.UKismetSystemLibrary.PrintString(WorldContectObject,"准备播放动画ActivateTest")

--     local TaskMouse = UE.UUnderMouseDataAbilityTask.CreateUnderMouseDataAbilityTask(self)
--     TaskMouse.OnMouseDataAbilityTask:Add(self,self.OnDelegateTrgger)
--     TaskMouse:ReadyForActivation()

-- end

-- function M:OnDelegateTrgger(data)
--     self:GetMouseTargetLocation(data)
--     self:SetPlayerFacingTarget(self.Location)
--     self:PlayAnim()
-- end

-- function M:GetMouseTargetLocation(data)
--     local data = UE.UAbilitySystemBlueprintLibrary.GetHitResultFromTargetData(data)
--     self.Location = data.Location
-- end

-- --用于MotionWarping改变转向
-- function M:SetPlayerFacingTarget(Location)
--     local character = self:GetAvatarActorFromActorInfo()
--     character:UpdateFacingTarget(Location)
-- end

-- function M:PlayAnim()
--     local TaskAnim = UE.UGAS_PlayMontageAndWaitForEvent.PlayMontageAndWaitForEvent(
--         self, 
--         nil, 
--         self.FireAnim,
--         UE.UBlueprintGameplayTagLibraryUtil.GetTagFromString("Event.Montage.FireBolt"),
--         1, 
--         nil,
--         true, 
--         1.0)
    
--     TaskAnim.EventReceived:Add(self,self.OnEventReceived)
--     TaskAnim:ReadyForActivation()
-- end

-- function M:OnEventReceived()
--     UE.UKismetSystemLibrary.PrintString(WorldContectObject,"收到了标签哦")
--     self:SpawnProjectile(self.Location)
--     self:DelayEndAbility(0.5)
-- end

-- function M:DelayEndAbility(Induration)
--     coroutine.resume(coroutine.create(
--         function(WorldContectObject,duration)    
--            self:K2_EndAbility()
--         end
--     ),
--     self,Induration)
-- end
-- return M


-- -- eg
-- -- function M:K2_ActivateAbility()
-- --     if self:IsLocallyControlled() then
-- --         self:StartRangedWeaponTargeting()
-- --     end

-- --     local Proxy = UE.UAbilityTask_PlayMontageAndWait.CreatePlayMontageAndWaitProxy(self, nil, self.CharacterFireMontage, self.AutoRate, nil, false, 1.0, 0)
-- --     local Handler = function()
-- --         self:K2_EndAbility()
-- --     end
-- --     Proxy.OnCompleted:Add(self, Handler)
-- --     Proxy.OnInterrupted:Add(self, Handler)
-- --     Proxy.OnCancelled:Add(self, Handler)
-- --     Proxy:ReadyForActivation()

-- --     UE.UKismetSystemLibrary.K2_SetTimerDelegate({ self, self.FireComplete }, self.FireDelayTimeSecs, false, 0, 0)
-- -- end

-- -- function M:FireComplete()
-- --     self:K2_EndAbility()
-- -- end