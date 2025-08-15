--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_EffectMessage_C
local M = UnLua.Class()

function M:ShowMessage(Image,msg)
    if Image then        
        self.Image_Icon:SetBrushFromTexture(Image)
    end
    self.Text_Message:SetText(msg)
end
--function M:Initialize(Initializer)
--end

function M:PreConstruct(IsDesignTime)
    print("[PeiLuaLog] 构造")
end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M
