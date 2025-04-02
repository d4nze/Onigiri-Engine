function copy_file(sourcePath)
    return string.format("{COPYFILE} \"%s\" \"%%{wks.location}Build\\%%{config_dir}\"", sourcePath)
end

function copy_dir(sourcePath)
	return string.format("{COPYDIR} \"%s\" \"%%{wks.location}Build\\%%{config_dir}\"", sourcePath)
end
