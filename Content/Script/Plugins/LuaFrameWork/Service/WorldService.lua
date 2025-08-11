local WorldService = UnLua.Class()

function WorldService:LuaInit()
    print("WorldService:LuaInit")
end

function WorldService:LuaPostInit()
    print("WorldService:LuaPostInit")
end

function WorldService:LuaOnWorldBeginPlay()
    --声明path
    --调用GetWidgetByPath方法
    --添加到视口
    print("WorldService:LuaOnWorldBeginPlay")
end

function WorldService:LuaDeinit()
    print("WorldService:LuaDeinit")
end

return WorldService