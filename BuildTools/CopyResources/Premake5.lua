project "CopyResources"
    language "C++"
    cppdialect "C++17"
    kind "StaticLib"
    
	targetdir "%{output_dir}/"
	objdir "%{output_dir}/Obj/BuildTools/%{prj.name}/"
    
    postbuildcommands {
        copy_dir("%{wks.location}\\Resources\\")
    }

function include_copy_resources()
    dependson "CopyResources"
end
