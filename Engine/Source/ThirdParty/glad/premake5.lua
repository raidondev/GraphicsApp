project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "Off"
    
    targetdir ("%{wks.location}/Engine/Binaries/ThirdParty")
    objdir ("%{wks.location}/Engine/Intermediate/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}")
    
    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        
        "src/glad.c"
    }

    includedirs
    {
        "include",
        "src"
    }

    filter "system:windows"
        systemversion "latest"
        
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        
    filter "configurations:Development"
        runtime "Release"
        optimize "On"
        symbols "On"
        
    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "On"
