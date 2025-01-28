function copyFile(sourcePath)
    return string.format("{COPYFILE} \"%s\" \"%%{wks.location}\\Main\\Build\\bin\\%%{outputdir}\"", sourcePath)
end

project "Main"
	language "C++"
	kind "ConsoleApp"
    cppdialect "C++17"
    
	location "Source/"
	targetdir "Build/bin/%{outputdir}"
    objdir "Build/obj/%{outputdir}"
	
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
		"../ScriptingEnvironment/Source"
	}
	libdirs {}
    links { "Core" }
	
	postbuildcommands {
		copyFile("%{wks.location}Core\\Build\\bin\\%{outputdir}\\Core.dll"),
		copyFile("%{wks.location}ScriptingEnvironment\\Build\\bin\\%{outputdir}\\ScriptingEnvironment.dll")
	}
	
	filter "platforms:Win32"
		architecture "x86"
        defines "WIN32"
		includedirs { 
			"../Dependencies/SFML/x86/include"
		}
		libdirs { 
			"../Dependencies/SFML/x86/lib"
		}
		links {
			"sfml-audio.lib",
			"sfml-graphics.lib",
			"sfml-network.lib",
			"sfml-system.lib",
			"sfml-window.lib"
		}
		postbuildcommands {
			copyFile("%{wks.location}Dependencies\\SFML\\x86\\bin\\sfml-audio-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x86\\bin\\sfml-graphics-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x86\\bin\\sfml-network-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x86\\bin\\sfml-system-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x86\\bin\\sfml-window-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x86\\bin\\sfml-graphics-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x86\\bin\\sfml-network-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x86\\bin\\sfml-system-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x86\\bin\\sfml-window-d-3.dll")
		}
	filter "platforms:Win64"
		architecture "x86_64"
        defines "WIN64"
		includedirs { 
			"../Dependencies/SFML/x64/include"
		}
		libdirs { 
			"../Dependencies/SFML/x64/lib"
		}
		links {
			"sfml-audio.lib",
			"sfml-graphics.lib",
			"sfml-network.lib",
			"sfml-system.lib",
			"sfml-window.lib"
		}
		postbuildcommands {
			copyFile("%{wks.location}Dependencies\\SFML\\x64\\bin\\sfml-audio-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x64\\bin\\sfml-graphics-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x64\\bin\\sfml-network-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x64\\bin\\sfml-system-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x64\\bin\\sfml-window-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x64\\bin\\sfml-graphics-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x64\\bin\\sfml-network-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x64\\bin\\sfml-system-d-3.dll"),
			copyFile("%{wks.location}Dependencies\\SFML\\x64\\bin\\sfml-window-d-3.dll")
		}
	filter "configurations:Debug"
        symbols "On"
        defines "DEBUG"
	filter "configurations:Release"
        optimize "On"
        defines "RELEASE"
