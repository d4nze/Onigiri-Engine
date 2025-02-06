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

include "Core"
include "Main"
