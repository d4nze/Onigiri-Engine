workspace "Onigiri Engine"
    startproject "Launcher"
	configurations {
		"Debug",
		"Release"
	}
	platforms {
		"Win32",
		"Win64"
	}

config = "%{cfg.buildcfg}-%{cfg.platform}"
output_dir = "%{wks.location}/Build/%{config}"
dependencies_dir = "%{wks.location}/Dependencies"

include "Premake5/copy.lua"

include "Premake5/include_imgui.lua"
include "Premake5/include_json.lua"
include "Premake5/include_sfml.lua"

include "Premake5/link_imgui.lua"
include "Premake5/link_sfml.lua"

include "Premake5/project_base.lua"
include "Premake5/setup_app_kind.lua"

group "BuildTools"
	include "BuildTools/CopyResources"
	include "BuildTools/CopySFMLBinaries"
group ""
	include "ScriptCore"
	include "ApplicationCore"
	include "ProjectEditor"
	include "Launcher"
