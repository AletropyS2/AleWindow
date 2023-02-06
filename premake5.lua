workspace "AleWindow"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.configuration}-%{cfg.architecture}"

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