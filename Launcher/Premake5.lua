project "Launcher"
	project_base()
	kind "ConsoleApp"
    
	include_script_core()
	include_application_core()
	include_imgui()
	include_json()
	include_sfml()
	
    links "opengl32.lib"
	postbuildcommands {
		copy_file("%{wks.location}Launcher\\Source\\vcrosdmonorus_vhsicons.ttf")
	}
	copy_sfml_dlls()
