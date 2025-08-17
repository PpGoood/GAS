--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_GlobeProgressBar_C
local M = UnLua.Class()

--function M:Initialize(Initializer)
--end

function M:PreConstruct(IsDesignTime)
    self.Image_Background:SetBrush(self.BackgroundBrush)
    self.Image_Glass:SetBrush(self.GlassBrush)
    self.ProgressBar_Globe.WidgetStyle.FillImage = self.GlobeFillBrush
    self.ProgressBar_Ghost.WidgetStyle.FillImage = self.GhostFillBrush
    self:InitProgressBar()
end

function M:InitProgressBar()
    self.ProgressBar_Globe:SetPercent(0)
    self.ProgressBar_Ghost:SetPercent(0)
end

function M:UpdateProgressBar(Value,MaxValue)
    self.ProgressBar_Globe:SetPercent(Value / MaxValue)
    self:DelayUpdateGhostProgressBar(0.5,Value,MaxValue)
end

function M:DelayUpdateGhostProgressBar(Induration,Value,MaxValue)
    coroutine.resume(coroutine.create(
        function(WorldContectObject,duration,InValue,InMaxValue)    
            UE4.UKismetSystemLibrary.Delay(WorldContectObject,duration)
            -- UE4.UKismetSystemLibrary.PrintString(WorldContectObject,InValue)
            self.ProgressBar_Ghost:SetPercent(InValue / InMaxValue)
        end
    ),
    self,Induration,Value,MaxValue)
end

return M
