#pragma once
#include "Application/Application.hpp"
#include "Core/Scene.hpp"

class MainApplication : public Application
{
public:
	MainApplication();

protected:
	void update() override;

private:
	Scene m_scene;
};
