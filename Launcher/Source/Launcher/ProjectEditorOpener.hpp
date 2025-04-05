#include <nlohmann/json.hpp>
#include <fstream>

namespace Launcher
{
namespace ProjectSelection
{
struct Project;
}

class ProjectEditorOpener
{
public:
	ProjectEditorOpener(const ProjectSelection::Project& selectedProject);

private:
	bool openReader();
	void updateProject(const ProjectSelection::Project& selectedProject);
	bool openWriter();
	
private:
	std::ifstream mSettingsReader;
	std::ofstream mSettingsWriter;
	nlohmann::json mSettings;
};
}
