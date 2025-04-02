function link_imgui()
	filter { "platforms:Win32", "configurations:Debug" }
		libdirs "../Dependencies/ImGui/lib/Debug/Win32"
	filter { "platforms:Win64", "configurations:Debug" }
		libdirs "../Dependencies/ImGui/lib/Debug/Win64"
	filter { "platforms:Win32", "configurations:Release" }
		libdirs "../Dependencies/ImGui/lib/Release/Win32"
	filter { "platforms:Win64", "configurations:Release" }
		libdirs "../Dependencies/ImGui/lib/Release/Win64"
    filter {}
		links "ImGui.lib"
end
