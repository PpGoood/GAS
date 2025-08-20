--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type GA_Test_C
local M = UnLua.Class()

function M:K2_ActivateAbility()
    print("[PeiLuaLog]测试GA开始")
    UE4.UKismetSystemLibrary.PrintString(WorldContectObject,"测试GA开始ActivateTest")
    self:DelayF(2);

end

function M:K2_OnEndAbility(bWasCancelled)
    print("[PeiLuaLog]测试GA结束")
    UE4.UKismetSystemLibrary.PrintString(WorldContectObject,"测试GA结束EndTest")
end

function M:DelayF(Induration)
    coroutine.resume(coroutine.create(
        function(WorldContectObject,duration)    
            UE4.UKismetSystemLibrary.Delay(WorldContectObject,duration)
            self:K2_EndAbility()
        end
    ),
    self,Induration)
end

return M
