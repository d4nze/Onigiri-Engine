project "ApplicationCore"
	language "C++"
	kind "StaticLib"
    cppdialect "C++17"
    
	location "Source/"
	targetdir "%{outputdir}"
	objdir "%{outputdir}/obj"
	
	files {
		"Source/**.hpp",
		"Source/**.inl",
		"Source/**.cpp"
	}
    vpaths {
      ["Source"] = { "../**.hpp",  "../**.h", "../**.inl", "../**.cpp" }
    }
    
    includedirs {
		"Source/%{prj.name}",
		"../Dependencies/ImGui/include"
	}
	libdirs {}
    links { "opengl32.lib" }
	
	filter "platforms:Win32"
		architecture "x86"
        defines "WIN32"
		includedirs { 
			"../Dependencies/SFML/Win32/include"
		}
		libdirs { 
			"../Dependencies/SFML/Win32/lib"
		}
		links {
			"sfml-audio.lib",
			"sfml-graphics.lib",
			"sfml-network.lib",
			"sfml-system.lib",
			"sfml-window.lib"
		}
	filter "platforms:Win64"
		architecture "x86_64"
        defines "WIN64"
		includedirs { 
			"../Dependencies/SFML/Win64/include"
		}
		libdirs { 
			"../Dependencies/SFML/Win64/lib"
		}
		links {
			"sfml-audio.lib",
			"sfml-graphics.lib",
			"sfml-network.lib",
			"sfml-system.lib",
			"sfml-window.lib"
		}
	filter "configurations:Debug"
        symbols "On"
        defines "DEBUG"
	filter "configurations:Release"
        optimize "On"
        defines "RELEASE"
	filter { "platforms:Win32", "configurations:Debug" }
		libdirs "../Dependencies/ImGui/lib/Debug/Win32"
		links "ImGui.lib"
	filter { "platforms:Win64", "configurations:Debug" }
		libdirs "../Dependencies/ImGui/lib/Debug/Win64"
		links "ImGui.lib"
	filter { "platforms:Win32", "configurations:Release" }
		libdirs "../Dependencies/ImGui/lib/Release/Win32"
		links "ImGui.lib"
	filter { "platforms:Win64", "configurations:Release" }
		libdirs "../Dependencies/ImGui/lib/Release/Win64"
		links "ImGui.lib"
	filter {}
		defines "APPLICATION_CORE_EXPORTS"
