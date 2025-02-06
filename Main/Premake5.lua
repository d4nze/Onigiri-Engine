function copyFile(sourcePath)
    return string.format("{COPYFILE} \"%s\" \"%%{wks.location}Build\\%%{config}\\Main\"", sourcePath)
end

project "Main"
	language "C++"
	kind "ConsoleApp"
    cppdialect "C++17"
    
	location "Source/"
	targetdir "%{outputdir}/%{prj.name}"
	objdir "%{outputdir}/%{prj.name}/obj"
	
	files {
		"Source/**.hpp",
		"Source/**.inl",
		"Source/**.cpp"
	}
    vpaths {
      ["Source"] = { "../**.hpp",  "../**.h", "../**.inl", "../**.cpp" }
    }
    
    includedirs {
		"Source",
		"../Core/Source",
		"../Dependencies/JSON"
	}
	libdirs {}
    links { "Core" }
	
	postbuildcommands {
		copyFile("%{wks.location}Build\\%{config}\\Core\\Core.dll")
	}
	
	filter "platforms:Win32"
		architecture "x86"
        defines "WIN32"
		includedirs { 
			"../Dependencies/SFML/Win32/include",
			"../Dependencies/ImGui/Win32/include"
		}
		libdirs { 
			"../Dependencies/SFML/Win32/lib",
			"../Dependencies/ImGui/Win32/lib"
		}
		links {
			"sfml-audio.lib",
			"sfml-graphics.lib",
			"sfml-network.lib",
			"sfml-system.lib",
			"sfml-window.lib",
			"ImGui.lib"
		}
		postbuildcommands {
			copyFile("%{wks.location}Dependencies\\SFML\\Win32\\bin\\sfml-audio-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win32\\bin\\sfml-graphics-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win32\\bin\\sfml-network-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win32\\bin\\sfml-system-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win32\\bin\\sfml-window-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win32\\bin\\sfml-graphics-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win32\\bin\\sfml-network-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win32\\bin\\sfml-system-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win32\\bin\\sfml-window-d-3.dll")
		}
	filter "platforms:Win64"
		architecture "x86_64"
        defines "WIN64"
		includedirs { 
			"../Dependencies/SFML/Win64/include",
			"../Dependencies/ImGui/Win64/include"
		}
		libdirs { 
			"../Dependencies/SFML/Win64/lib",
			"../Dependencies/ImGui/Win64/lib"
		}
		links {
			"sfml-audio.lib",
			"sfml-graphics.lib",
			"sfml-network.lib",
			"sfml-system.lib",
			"sfml-window.lib",
			"ImGui.lib"
		}
		postbuildcommands {
			copyFile("%{wks.location}Dependencies\\SFML\\Win64\\bin\\sfml-audio-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win64\\bin\\sfml-graphics-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win64\\bin\\sfml-network-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win64\\bin\\sfml-system-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win64\\bin\\sfml-window-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win64\\bin\\sfml-graphics-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win64\\bin\\sfml-network-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win64\\bin\\sfml-system-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\Win64\\bin\\sfml-window-d-3.dll")
		}
	filter "configurations:Debug"
        symbols "On"
        defines "DEBUG"
	filter "configurations:Release"
        optimize "On"
        defines "RELEASE"
