[![CodeFactor](https://www.codefactor.io/repository/github/requizm/cs2d_vscode/badge)](https://www.codefactor.io/repository/github/requizm/cs2d_vscode)
[![Codacy](https://app.codacy.com/project/badge/Grade/c6e13fcd32764c3a9a1094a736d8d991)](https://www.codacy.com/gh/requizm/cs2d_vscode/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=requizm/cs2d_vscode&amp;utm_campaign=Badge_Grade)
![Build](https://github.com/requizm/cs2d_vscode/workflows/build/badge.svg)
![GitHub repo size](https://img.shields.io/github/repo-size/requizm/cs2d_vscode)
![GitHub last commit](https://img.shields.io/github/last-commit/requizm/cs2d_vscode)


**WIP**  
  
___
  
### Available Compilers  
- Mingw-w64
- GCC
  
___
  
### Tested Platforms  
- MinGW (Windows)
- GCC (Linux)
  
___
  
### How To Build  
*Windows*
```
git clone https://github.com/requizm/cs2d_vscode
cd cs2d_vscode
cmake -Bbuild
cmake --build build
```
  
*Linux*
```
sudo apt-get install cmake libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev
git clone https://github.com/requizm/cs2d_vscode
cd cs2d_vscode
cmake -Bbuild -G "Unix Makefiles"
cmake --build build
```
  
___
  
### Used Libraries  
- [glfw](https://github.com/glfw/glfw)
- [glew](https://github.com/Perlmint/glew-cmake)
- [freetype](https://github.com/aseprite/freetype2)
- [spdlog](https://github.com/gabime/spdlog)
- [stb_image](https://github.com/nothings/stb)
- [rapidxml 1.13](http://rapidxml.sourceforge.net/)
- [nlohmann/json 3.9.1](https://github.com/nlohmann/json)