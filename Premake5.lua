workspace "Sandbox Engine"
    startproject "Main"
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

group "Linkers"
	include "SFMLLinker"
group ""
	include "Core"
	include "Main"
