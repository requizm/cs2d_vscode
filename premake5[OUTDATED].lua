workspace "cs2d_vscode"
   configurations { "Release" }

project "cs2d_vscode"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "bin/%{cfg.buildcfg}"
   debugdir "bin/%{cfg.buildcfg}"

   files { "src/**.hpp", "src/**.cpp" }
   removefiles { "src/Common.cpp", "src/Common.hpp" }
   
   
   includedirs { "include" }
   architecture "x86"
    
   filter "system:Windows"
	  filter "action:vs2017"
	     libdirs { "lib/32", "lib/32/vs2017"}
		  
	  filter "action:vs2019"
		 libdirs { "lib/32", "lib/32/vs2019"}

	  filter "action:gmake2"
	     libdirs { "lib/32", "lib/32/mingw"}
		 linkoptions { "-static-libstdc++", "-static-libgcc" }
		  
		
		
   filter {}
      filter "system:Windows"
	     filter "configurations:Release"
	        optimize "Speed"
	        links { "glew32", "glfw3", "opengl32", "gdi32", "freetype"}