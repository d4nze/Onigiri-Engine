function project_base()
	language "C++"
    cppdialect "C++17"
    
	location "Source/"
	targetdir "%{output_dir}/"
	objdir "%{output_dir}/Obj/%{prj.name}/"
    debugdir "%{output_dir}/"
	
	files {
		"Source/**.h",
		"Source/**.hpp",
		"Source/**.cpp",
		"Source/**.inl"
	}
    vpaths {
        ["Header Files"] = { "../**.h", "../**.hpp", "../**.inl" },
        ["Source Files"] = { "../**.cpp" }
    }

    includedirs "Source/%{prj.name}/"
    
    filter "platforms:Win32"
        architecture "x86"
        defines "WIN32"
    filter "platforms:Win64"
        architecture "x86_64"
        defines "WIN64"
    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"
    filter "configurations:Release"
        defines "RELEASE"
        optimize "On"
    filter {}
end
