--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_ManaGlobe_C
local M = UnLua.Class("UI.Component.GlobeProgress")

function M:WidgetControllerSet_Event()
    self.WidgetController.OnManaChanged:Add(self,self.SetProgressMana)
    self.WidgetController.OnMaxManaChanged:Add(self,self.SetProgressMaxMana)
end

function M:SetProgressMana(NewMana)
    self.Mana = NewMana
    self.ProgressBar_Globe:SetPercent(self.Mana / self.MaxMana)
end

function M:SetProgressMaxMana(NewMaxMana)
    self.MaxMana = NewMaxMana
    self.ProgressBar_Globe:SetPercent(self.Mana / self.MaxMana)
end

return M
