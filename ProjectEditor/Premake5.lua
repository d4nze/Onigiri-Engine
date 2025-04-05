project "ProjectEditor"
	project_base()
	kind "ConsoleApp"

	include_script_core()
	include_application_core()
	include_imgui()
	include_json()
	include_sfml()

function include_project_editor()
    dependson "ProjectEditor"
end
