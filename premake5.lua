workspace "AleWindow"
    architecture "x64"
    startproject "Sandbox"
    configurations 
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "AleWindow"
    location "AleWindow"
    cppdialect "C++17"
    kind "StaticLib"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
    }

    includedirs
    {
        "%{prj.name}/src"
    }

    filter "configurations:Debug"
        defines
        {
            "ALE_DEBUG"
        }
        symbols "On"
    filter "configurations:Release"
        defines
        {
            "ALE_RELEASE"
        }
        optimize "On"


project "Sandbox"
    location "Sandbox"
    cppdialect "C++17"
    kind "ConsoleApp"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
    }

    includedirs
    {
        "%{prj.name}/src",
        "AleWindow/src"
    }

    links
    {
        "AleWindow"
    }

    filter "system:linux"
        links { "X11" }

    filter "configurations:Debug"
        symbols "On"
    filter "configurations:Release"
        optimize "On"
