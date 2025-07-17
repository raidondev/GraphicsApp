# Graphics Application

This project demonstrates a graphics application with OpenGL and [Jolt Physics](https://github.com/jrouwe/JoltPhysics), designed to help with learning and experimentation.

This project uses [Premake](https://premake.github.io/) for generating project files.

## Getting Started

Follow these steps to set up and build the project after downloading the `.zip` file.

---

## 1. Extract the Project

1. Download the `.zip` of this repository.
2. Extract it to a folder of your choice.

## 2. Generate Visual Studio solution

In the root directory of the extracted project files, run the `GenerateProjectFiles.bat` script:

```bash
GenerateProjectFiles.bat
```
This will create a Visual Studio solution using Premake.

## 3. Build & Run the Project

1. Open the solution file `GraphicsApp.sln` in **Visual Studio 2022** 1. or **JetBrains Rider**.
2. Select the desired build configuration (Debug or Release).
3. Build the project.
4. Run the `Sandbox` target to launch the application.

## Requirements

To successfully build and run this project, ensure you have the following installed:
- **Visual Studio 2022** (with the appropriate C++ development workload) or **JetBrains Rider** (Optional)
- **Premake 5** (already set up in the project)

## Library Versions
The following third-party libraries are bundled with this project:
- **OpenGL**: Version 4.6
- **GLFW**: Version 3.4
- **Jolt Physics**: Version 5.3.0
- **ImGui (Dear ImGui)**: Version 1.92.1

These libraries are included in the `ThirdParty` folder with only the necessary code.