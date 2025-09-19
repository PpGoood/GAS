--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_SpellGlobe_C
local M = UnLua.Class()


function M:WidgetControllerSet_Event()
    self.WidgetController.AbilityInfoDelegate:Add(self, self.OnAbilityInfoSignature)
end

function M:OnAbilityInfoSignature(info)
    self:SetAbilityIconInfo(info)
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
