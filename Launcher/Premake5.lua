project "Launcher"
	project_base()
	kind "ConsoleApp"
    
	include_copy_resources()
	include_copy_sfml_bin()
	include_script_core()
	include_application_core()
	include_imgui()
	include_json()
	include_sfml()
