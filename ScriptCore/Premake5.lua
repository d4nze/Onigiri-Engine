project "ScriptCore"
	project_base()
	kind "SharedLib"
    
	include_imgui()
	include_json()
	include_sfml()

	link_imgui()
	link_sfml()
	
	defines "SCRIPT_CORE_EXPORTS"

function include_script_core()
	includedirs "%{wks.location}/ScriptCore/Source/"
	links "ScriptCore"
end
	