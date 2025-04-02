function setup_app_kind()
    filter "configurations:Debug"
		kind "ConsoleApp"
	filter "configurations:Release"
		kind "WindowedApp"
	filter {}
end