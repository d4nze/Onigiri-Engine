workspace "Script Engine"
    startproject "Main"
	configurations {
		"Debug",
		"Release"
	}
	platforms {
		"Win32",
		"Win64"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.platform}"

include "Main"
