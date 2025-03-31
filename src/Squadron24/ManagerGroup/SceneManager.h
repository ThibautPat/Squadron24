#pragma once
#include <map>
#include "../SceneComponent/Scene.h"
#include "../SceneComponent/Decor.h"


class SceneManager 
{

public:

	std::map<int, Scene*> m_SceneMap{};
	Scene* m_CurrentScene;
	std::map<int, std::string> m_sceneName{};

	SceneManager();

	Scene* GetCurrentScene();
	void ChangeScene(int GameState); 
	void NewScene(std::string Name, int GameState);

};