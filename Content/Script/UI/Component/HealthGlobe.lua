--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_HealthGlobe_C
local M = UnLua.Class("UI.Component.GlobeProgress")

function M:WidgetControllerSet_Event()
    self.WidgetController.OnHealthChanged:Add(self,self.SetProgressHealth)
    self.WidgetController.OnMaxHealthChanged:Add(self,self.SetProgressMaxHealth)
end

function M:SetProgressHealth(NewHealth)
    self.Health = NewHealth
    self:UpdateProgressBar(self.Health,self.MaxHealth)
end

function M:SetProgressMaxHealth(NewMaxHealth)
    self.MaxHealth = NewMaxHealth
    self:UpdateProgressBar(self.Health,self.MaxHealth)
end

return M
