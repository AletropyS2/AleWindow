project "AleWindow"
    cppdialect "C++17"
    kind "StaticLib"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.cpp",
        "src/**.h"
    }

    includedirs
    {
        "src/"
    }

    
    filter "options:lib=shared"
        kind "SharedLib"
        defines
        {
            "ALE_BUILD_DLL"
        }

    filter "system:linux"
        links { "X11", "GL" }

    filter "system:windows"
        links { "opengl32.lib" }

    filter "configurations:Debug"
        defines
        {
            "ALE_DEBUG"
        }
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        defines
        {
            "ALE_RELEASE"
        }
        runtime "Release"
        optimize "On"
