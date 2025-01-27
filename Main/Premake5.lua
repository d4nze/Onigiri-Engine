function copyFile(sourcePath)
    return string.format("{COPYFILE} \"%s\" \"%%{wks.location}\\Main\\Build\\bin\\%%{outputdir}\"", sourcePath)
end

project "Main"
	language "C++"
	kind "ConsoleApp"
    cppdialect "C++17"
    
	location "Source/"
	targetdir "Build/bin/%{outputdir}"
    objdir "Build/obj/%{outputdir}"
	
	files {
		"Source/**.hpp",
		"Source/**.inl",
		"Source/**.cpp"
	}
    vpaths {
      ["Source"] = { "../**.hpp",  "../**.h", "../**.inl", "../**.cpp" }
    }
    
    includedirs {
		"Source",
		"../Core/Source",
		"../ScriptingEnvironment/Source"
	}
	libdirs {}
    links {}
	postbuildcommands {
		---copyFile("%{wks.location}ScriptingEnvironment\\Build\\bin\\%{outputdir}\\ScriptingEnvironment.dll")
	}
	
	filter "platforms:Win32"
		architecture "x86"
        defines "WIN32"
	filter "platforms:Win64"
		architecture "x86_64"
        defines "WIN64"	
	filter "configurations:Debug"
        symbols "On"
        defines "DEBUG"
	filter "configurations:Release"
        optimize "On"
        defines "RELEASE"
