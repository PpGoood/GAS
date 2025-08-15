--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--
--TODO 需要使用动画队列进行管理，让弹出更加顺滑，现在UI会挤在一起
---@type WBP_EffectMessage_C
local M = UnLua.Class()

function M:ShowMessage(Image,msg)
    if Image then        
        self.Image_Icon:SetBrushFromTexture(Image)
        self:PlayMessageAnim()
        self.Text_Message:SetText(msg)
    end
end
--function M:Initialize(Initializer)
--end

function M:PlayMessageAnim()
    local InAnimation = self.MessageAnimation  -- 
    local StartAtTime = 0.0  -- 从动画的开头开始播放
    local NumLoopsToPlay = 1  -- 播放一次
    local PlayMode = UE4.EUMGSequencePlayMode.Forward  -- 正向播放
    local PlaybackSpeed = 1.0  -- 正常播放速度
    local bRestoreState = true  -- 播放结束后恢复状态
    self:DelayRemoveFromParent(self.MessageAnimation:GetEndTime())
    -- 播放动画
    self:PlayAnimation(InAnimation, StartAtTime, NumLoopsToPlay, PlayMode, PlaybackSpeed, bRestoreState)
end

-- 延时移除
function M:DelayRemoveFromParent(Induration)
    coroutine.resume(coroutine.create(
        function(WorldContectObject,duration)    
            UE4.UKismetSystemLibrary.Delay(WorldContectObject,duration)
            self:RemoveFromParent()
        end
    ),
    self,Induration)
end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M
