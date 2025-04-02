function include_sfml()
    filter "platforms:Win32"
        includedirs "%{dependencies_dir}/SFML/Win32/include"
    filter "platforms:Win64"
        includedirs "%{dependencies_dir}/SFML-3.0.0/Win64/include"
    filter {}
end
