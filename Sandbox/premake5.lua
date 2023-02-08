project "Sandbox"
    cppdialect "C++17"
    kind "ConsoleApp"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.cpp",
        "src/**.h"
    }

    includedirs
    {
        "src/",
        "%{wks.location}/AleWindow/src"
    }

    links
    {
        "AleWindow"
    }

    filter "system:linux"
        links { "X11", "GL" }
    
    filter "system:windows"
        links { "opengl32.lib" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    filter "configurations:Release"
        runtime "Release"
        optimize "On"
