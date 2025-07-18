project "ImGui"
    kind "StaticLib"
    language "C++"
    staticruntime "off"
    
    targetdir ("%{wks.location}/Binaries/" .. OutputDir .. "/ThirdParty/%{prj.name}")
    objdir ("%{wks.location}/Intermediate/Build/" .. OutputDir .. "/%{prj.name}")
    
    files
    {
        "backends/imgui_impl_glfw.cpp",
        "backends/imgui_impl_glfw.h",
        "backends/imgui_impl_opengl3.cpp",
        "backends/imgui_impl_opengl3.h",
        "backends/imgui_impl_opengl3_loader.h",

        "imconfig.h",
        "imgui.cpp",
        "imgui.h",
        "imgui_draw.cpp",
        "imgui_internal.h",
        "imgui_tables.cpp",
        "imgui_widgets.cpp",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
    }

    includedirs
    {
        ".",
        "backends",
        "%{IncludeDir.GLFW}"
    }

    filter "system:windows"
        systemversion "latest"
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        runtime "Release"
        optimize "on"
        
    filter "configurations:Dist"
        runtime "Release"
        optimize "on"
        symbols "off"