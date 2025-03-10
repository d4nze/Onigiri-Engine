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
outputdir = "..//Build/%{config}"

function copyFile(sourcePath)
    return string.format("{COPYFILE} \"%s\" \"%%{wks.location}Build\\%%{config}\"", sourcePath)
end

group "Linkers"
	include "SFMLLinker"
group ""
	include "ScriptCore"
	include "ApplicationCore"
	include "Launcher"
