project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    files
    {
        "Src/Runtime/**.h",
        "Src/Runtime/**.cpp"
    }

    includedirs
    {
        "Src/Runtime",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.JoltPhysics}",
    }

    links
    {
        "GLFW",
        "ImGui",
        "JoltPhysics",
        "opengl32.lib"
    }

    targetdir ("%{wks.location}/Binaries/" .. OutputDir)
    objdir ("%{wks.location}/Intermediate/Build/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines {}

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