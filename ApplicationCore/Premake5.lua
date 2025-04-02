project "ApplicationCore"
	project_base()
	kind "StaticLib"

	include_imgui()
	include_sfml()

	link_imgui()
	link_sfml()
	links { "opengl32.lib" }

	defines "APPLICATION_CORE_EXPORTS"

function include_application_core()
	includedirs "%{wks.location}/ApplicationCore/Source/"
	links "ApplicationCore"
end
