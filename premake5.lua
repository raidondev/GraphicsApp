workspace "GraphicsApp"
    architecture "x64"
    platforms { "Win64" }
    configurations { "Debug", "Release", "Dist" }
    startproject "Sandbox"

OutputDir = "%{cfg.platform}/%{cfg.buildcfg}"

group "Dependencies"
    include "Engine/Src/ThirdParty/GLFW"
    include "Engine/Src/ThirdParty/JoltPhysics"
group ""

include "Engine/Engine.lua"
include "Sandbox/Sandbox.lua"