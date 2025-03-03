project "SFMLLinker"
	language "C++"
	kind "StaticLib"
    cppdialect "C++17"
    
	location ""
	targetdir "%{outputdir}"
	objdir "%{outputdir}/obj"
	
	filter "platforms:Win32"
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
	