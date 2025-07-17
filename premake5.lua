workspace "GraphicsApp"
    architecture "x64"
    platforms { "Win64" }
    configurations { "Debug", "Release", "Dist" }
    startproject "Sandbox"

OutputDir = "%{cfg.platform}/%{cfg.buildcfg}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Engine/Src/ThirdParty/GLFW/include"
IncludeDir["ImGui"] = "%{wks.location}/Engine/Src/ThirdParty/ImGui"
IncludeDir["JoltPhysics"] = "%{wks.location}/Engine/Src/ThirdParty/JoltPhysics/Jolt"

group "Dependencies"
    include "Engine/Src/ThirdParty/GLFW"
    include "Engine/Src/ThirdParty/ImGui"
    include "Engine/Src/ThirdParty/JoltPhysics"
group ""

include "Engine/Engine.lua"
include "Sandbox/Sandbox.lua"