[![CodeFactor](https://www.codefactor.io/repository/github/requizm/cs2d_vscode/badge)](https://www.codefactor.io/repository/github/requizm/cs2d_vscode)

**WIP**
**Only avaible for Windows**  

### Mingw-w64 Configurations  

**32 bit:**  
Thread model: win32  
gcc version 8.1.0 (i686-win32-dwarf-rev0, Built by MinGW-W64 project)  


**64 bit:**  
Thread model: win32  
gcc version 8.1.0 (x86_64-win32-seh-rev0, Built by MinGW-W64 project)  
  
___
  
### How To Build  
- If you are going to use a different compiler than *Mingw64*, don't forget to download the [glfw lib](https://www.glfw.org/download) file and put it in *lib/32*. Then delete *libglfw3.a* and *libglfw3dll.a*
- You can use build tools such as [cmake](https://cmake.org/) or [premake](https://premake.github.io/). But i suggest [premake](https://premake.github.io/).
- Don't forget to put *freetype.dll* and *glew32.dll* files in *bin/Release* or *bin/Debug*.
- If you are going to use cmake, you should add `-A Win32` end of the cmake command. Example: `cmake -G "Visual Studio 16 2019" -A Win32`
  
___
  
### Used Libraries  
- [glfw 3.3.2](https://github.com/glfw/glfw)
- [glew 2.1.0](https://github.com/nigels-com/glew)
- [freetype 2.10.4](https://gitlab.freedesktop.org/freetype/freetype)
- [stb_image](https://github.com/nothings/stb)
- [rapidxml 1.13](http://rapidxml.sourceforge.net/)
