#pragma once

#include <Application.h>

int main()
{
    auto App = GraphicsEngine::CreateApplication();
    App->Run();
    delete App;
}