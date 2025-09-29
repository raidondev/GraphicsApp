workspace "GraphicsApp"
    architecture "x64"
    platforms { "Win64" }
    configurations { "Debug", "Release", "Dist" }
    startproject "Sandbox"

IncludeDir = {}
IncludeDir["Glad"] = "%{wks.location}/Engine/ThirdParty/glad/include"
IncludeDir["GLFW"] = "%{wks.location}/Engine/ThirdParty/glfw/include"
IncludeDir["ImGui"] = "%{wks.location}/Engine/ThirdParty/imgui"
IncludeDir["JoltPhysics"] = "%{wks.location}/Engine/ThirdParty/joltphysics/Jolt"

group "Dependencies"
    include "Engine/ThirdParty/glad" 
    include "Engine/ThirdParty/glfw"
    include "Engine/ThirdParty/imgui"
    include "Engine/ThirdParty/joltphysics"
group ""

include "Engine"
include "Sandbox"