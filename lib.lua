-- lua/lua.lua

premake.modules.lua = {}
local m = premake.modules.lua

local p = premake

newoption {
    trigger = "lib",
    description = "Set the type of library to shared or static",
    allowed = {
        { "shared", "Shared library" },
        { "static", "Static library" }
    },
    default = "static"
}

return m