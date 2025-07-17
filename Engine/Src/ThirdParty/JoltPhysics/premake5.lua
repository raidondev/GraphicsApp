project "JoltPhysics"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/Binaries/" .. OutputDir .. "/ThirdParty/%{prj.name}")
    objdir ("%{wks.location}/Intermediate/Build/" .. OutputDir .. "/%{prj.name}")

    files
    {
        "Jolt/**.cpp",
        "Jolt/**.h",
        "Jolt/**.inl",
        "Jolt/**.gliffy"
    }

    includedirs { ".", "Jolt" }

    filter "system:windows"
        systemversion "latest"

        files 
        {
           "Jolt/Jolt.natvis"
        }

    filter "configurations:Debug"
        runtime "Debug"    
        symbols "on"
        optimize "off"

        defines
        {
            "_DEBUG",
            "JPH_DEBUG_RENDERER",
            "JPH_FLOATING_POINT_EXCEPTIONS_ENABLED",
            "JPH_EXTERNAL_PROFILE",
            "JPH_ENABLE_ASSERTS"
        }

    filter "configurations:Release"
        runtime "Release"    
        optimize "on"
        vectorextensions "AVX2"
        isaextensions { "BMI", "POPCNT", "LZCNT", "F16C" }

        defines
        {
            "JPH_DEBUG_RENDERER",
            "JPH_FLOATING_POINT_EXCEPTIONS_ENABLED",
            "JPH_EXTERNAL_PROFILE"
        }

    filter "configurations:Dist"
        runtime "Release"
        optimize "on"
        symbols "off"
        vectorextensions "AVX2"
        isaextensions { "BMI", "POPCNT", "LZCNT", "F16C" }