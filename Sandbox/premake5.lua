project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    targetdir ("%{wks.location}/Engine/Binaries/ThirdParty")
    objdir ("%{wks.location}/Engine/Intermediate/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}")

    files
    {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs
    {
        "Source",
        "%{wks.location}/Engine/Source/Runtime",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.JoltPhysics}"
    }

    links
    {
        "Engine"
    }

    filter "system:windows"
        systemversion "latest"
        defines { "GA_PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "on"
        symbols "on"

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "on"
        symbols "off"