-- Pie Script ====================================
project "PieScript"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.c",
        "src/**.h",
        "src/**.cpp",
        "src/**.hpp"
    }

    includedirs {
        "src"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "DIST"
        optimize "On"
-- ==========================================================