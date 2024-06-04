workspace "PieScript"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

-- Directory final files will be placed into
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "PieScript" -- Main project