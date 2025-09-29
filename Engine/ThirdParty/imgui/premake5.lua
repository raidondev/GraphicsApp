project "ImGui"
    kind "StaticLib"
    language "C++"
    staticruntime "Off"

    targetdir ("%{wks.location}/Engine/Binaries/ThirdParty")
    objdir ("%{wks.location}/Engine/Intermediate/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}")

    files
    {
        "backends/imgui_impl_glfw.cpp",
        "backends/imgui_impl_opengl3.cpp",
        "backends/imgui_impl_opengl3_loader.h",

        "imconfig.h",
        "imgui.h",
        "imgui.cpp",
        "imgui_draw.cpp",
        "imgui_internal.h",
        "imgui_tables.cpp",
        "imgui_widgets.cpp",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
        "imgui_demo.cpp",
    }

    includedirs
    {
        ".",
        "backends",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.GLFW}"
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
