#ifndef YAML_LOADER_H
#define YAML_LOADER_H

#include <vector>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"
#include "Globals.h"

struct levelData;
struct PlayerData;

class yamlLoader
{
public:
	yamlLoader() = default;

	static void loadSettings(std::string t_loadFileName, SettingsData& t_settings);
	static void WriteSettings(std::string t_loadFileName, SettingsData& t_settings);

	static void loadPlayerData(PlayerData& t_data);

	static void loadLevelData(levelData& t_levelData, int t_levelNum);

	static void loadNpcData(levelData& t_levelData, int t_levelNum);

	static void loadMedData(levelData& t_levelData, int t_levelNum);
};

#endif // !YAML_LOADER_H
