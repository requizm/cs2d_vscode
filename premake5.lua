workspace "cs2d_vscode"
   configurations { "Release" }

project "cs2d_vscode"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "bin/%{cfg.buildcfg}"

   files { "src/**.hpp", "src/**.cpp" }
   removefiles { "src/Common.cpp", "src/Common.hpp" }
   
   libdirs { "lib/32"}
   includedirs { "include/" }
	
   links { "glew32", "glfw3", "opengl32", "gdi32", "freetype" }
   
   architecture "x86"
   optimize "Speed"

   filter "configurations:Release"
      defines { "NDEBUG" }
	  
	
	

	
	
	