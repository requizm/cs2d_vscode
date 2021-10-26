[![CodeFactor](https://www.codefactor.io/repository/github/requizm/cs2d_vscode/badge)](https://www.codefactor.io/repository/github/requizm/cs2d_vscode)
[![Codacy](https://app.codacy.com/project/badge/Grade/c6e13fcd32764c3a9a1094a736d8d991)](https://www.codacy.com/gh/requizm/cs2d_vscode/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=requizm/cs2d_vscode&amp;utm_campaign=Badge_Grade)
![Build](https://github.com/requizm/cs2d_vscode/workflows/build/badge.svg)
[![Build status](https://ci.appveyor.com/api/projects/status/7qjq7a7vhsh5cbow?svg=true)](https://ci.appveyor.com/project/requizm/cs2d-vscode)
![GitHub repo size](https://img.shields.io/github/repo-size/requizm/cs2d_vscode)
![GitHub last commit](https://img.shields.io/github/last-commit/requizm/cs2d_vscode)
[![Visits Badge](https://badges.pufler.dev/visits/requizm/cs2d_vscode)](https://badges.pufler.dev)


**WIP**  
**Cross Platform(Windows, Linux and MacOS)**  
  
___
  
### Available Compilers  
- Mingw-w64
- MSVC
- GCC
- Clang
  
___
  
### Tested Platforms  
- Visual Studio 2017 (Windows)
- Visual Studio 2019 (Windows)
- MinGW (Windows)
- GCC (Ubuntu)
  
___
  
### How To Build  
*Windows*
```
git clone https://github.com/requizm/cs2d_vscode
cd cs2d_vscode
cmake -BBuild
cd Build
make
```
  
*Linux*
```
sudo apt-get install cmake libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev
git clone https://github.com/requizm/cs2d_vscode
cd cs2d_vscode
cmake -BBuild -G "Unix Makefiles"
cd Build
make
```
  
___
  
### Used Libraries  
- [glfw dep](https://github.com/glfw/glfw)
- [glew dep](https://github.com/Perlmint/glew-cmake)
- [freetype dep](https://github.com/aseprite/freetype2)
- [spdlog dep](https://github.com/gabime/spdlog)
- [stb_image](https://github.com/nothings/stb)
- [rapidxml 1.13](http://rapidxml.sourceforge.net/)
- [nlohmann/json 3.9.1](https://github.com/nlohmann/json)
