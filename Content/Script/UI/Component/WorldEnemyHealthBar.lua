--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_EnemyWorldBar_C
local M = UnLua.Class()

function M:WidgetControllerSet_Event()
    self.WidgetController.OnHealthChanged:Add(self,self.SetProgressHealth)
    self.WidgetController.OnMaxHealthChanged:Add(self,self.SetProgressMaxHealth)
    self:InitProgressBar()
end

function M:InitProgressBar()
    self.ProgressBar:SetPercent(0)
    self.ProgressBar:SetPercent(0)
end

function M:SetProgressHealth(SetValue)
    self.CurValue = SetValue
    self.ProgressBar:SetPercent(self.CurValue/self.MaxValue)
end

function M:SetProgressMaxHealth(SetValue)
    self.MaxValue = SetValue
    self.ProgressBar:SetPercent(self.CurValue/self.MaxValue)
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
