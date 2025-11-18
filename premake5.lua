workspace "GraphicsEngine"
    architecture "x64"
    platforms { "Win64" }
    configurations { "Debug", "Release", "Dist" }
    startproject "Sandbox"

    IncludeDir = {}
    IncludeDir["Glad"] = "%{wks.location}/Engine/Source/ThirdParty/glad/include"
    IncludeDir["GLFW"] = "%{wks.location}/Engine/Source/ThirdParty/glfw/include"
    IncludeDir["ImGui"] = "%{wks.location}/Engine/Source/ThirdParty/imgui"
--     IncludeDir["JoltPhysics"] = "%{wks.location}/Engine/Source/ThirdParty/joltphysics/Jolt"
    IncludeDir["STB"] = "%{wks.location}/Engine/Source/ThirdParty/stb"
    
    group "Dependencies"
        include "Engine/Source/ThirdParty/glad" 
        include "Engine/Source/ThirdParty/glfw"
        include "Engine/Source/ThirdParty/imgui"
--         include "Engine/Source/ThirdParty/joltphysics"
    group ""
    
    include "Engine"
    include "Sandbox"