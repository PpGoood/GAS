--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type BP_InteractiveObjectBase_C
local M = UnLua.Class()

-- function M:Initialize(Initializer)
-- end

-- function M:UserConstructionScript()
-- end

-- function M:ReceiveBeginPlay()
-- end

-- function M:ReceiveEndPlay()
-- end

-- function M:ReceiveTick(DeltaSeconds)
-- end

-- function M:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
-- end

function M:ReceiveActorBeginOverlap(OtherActor)
    self:OnOverlap(OtherActor)
end

function M:ReceiveActorEndOverlap(OtherActor)
    self:OnEndOverlap(OtherActor)
end

return M
