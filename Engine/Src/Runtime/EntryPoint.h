#pragma once

#include <Application.h>

int main()
{
    auto App = GraphicsApp::CreateApplication();
    App->Run();
    delete App;
}