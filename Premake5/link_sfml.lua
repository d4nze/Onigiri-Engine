function link_sfml()
    filter "platforms:Win32"
        libdirs { 
            "%{dependencies_dir}/SFML/Win32/lib"
        }
    filter "platforms:Win64"
        libdirs { 
            "%{dependencies_dir}/SFML/Win64/lib"
        }
    filter {}
        links {
            "sfml-audio.lib",
            "sfml-graphics.lib",
            "sfml-network.lib",
            "sfml-system.lib",
            "sfml-window.lib",
            "opengl32.lib",
            "winmm.lib",
            "gdi32.lib"
        }
end
