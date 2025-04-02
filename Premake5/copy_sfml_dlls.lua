function copy_sfml_dlls()
	filter "platforms:Win32"
		postbuildcommands {
			copy_dir("%{wks.location}Dependencies\\SFML\\Win32\\bin\\")
		}
	filter "platforms:Win64"
		postbuildcommands {
			copy_dir("%{wks.location}Dependencies\\SFML\\Win64\\bin\\")
		}
	filter {}
end
