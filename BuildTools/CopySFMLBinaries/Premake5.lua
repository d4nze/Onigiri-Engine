project "CopySFMLBinaries"
    language "C++"
    cppdialect "C++17"
    kind "StaticLib"
    
	targetdir "%{output_dir}/"
	objdir "%{output_dir}/Obj/BuildTools/%{prj.name}/"
    
	postbuildcommands {
		copy_dir("%{wks.location}Dependencies\\SFML\\%{cfg.platform}\\bin\\")
	}

function include_copy_sfml_bin()
    dependson "CopySFMLBinaries"
end
