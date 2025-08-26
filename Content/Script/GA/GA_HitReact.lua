--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type GA_HitReact_C
local M = UnLua.Class()

function M:K2_ActivateAbility()
    self.GE = self:BP_ApplyGameplayEffectToOwner(self.GEClass,1,1)
    local character = self:GetAvatarActorFromActorInfo()
    local Montage = character:GetHitReactMontage()
    self:PlayAnim(Montage)
end

function M:PlayAnim(anim)
    local TaskAnim = UE.UAbilityTask_PlayMontageAndWait.CreatePlayMontageAndWaitProxy(self, 
    nil, 
    anim, 
    1, 
    nil, 
    false, 
    1.0, 
    0)
    TaskAnim.OnCompleted:Add(self,self.RemoveGE)
    TaskAnim.OnInterrupted:Add(self,self.RemoveGE)
    TaskAnim.OnCancelled:Add(self,self.RemoveGE)
    TaskAnim:ReadyForActivation()
end

function M:RemoveGE()
    self:BP_RemoveGameplayEffectFromOwnerWithHandle(self.GE,-1)
    self:K2_EndAbility()
end

return M