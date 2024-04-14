#include "YamlLoader.h"
#include "playerStats.h"
#include "levelData.h"

// read
void operator >> (const YAML::Node& t_node, SettingsData& t_settingsData)
{
	t_settingsData.vsync = t_node["vsync"].as<int>();
	t_settingsData.ScreenSize.x = t_node["Screen"]["x"].as<int>();
	t_settingsData.ScreenSize.y = t_node["Screen"]["y"].as<int>();
}

// write
void operator << (YAML::Node& t_node, const SettingsData& t_settingsData)
{
	t_node["vsync"] = static_cast<int>(t_settingsData.vsync);
	t_node["Screen"]["x"] = t_settingsData.ScreenSize.x;
	t_node["Screen"]["y"] = t_settingsData.ScreenSize.y;
}

// read player data
void operator >> (const YAML::Node& t_node, PlayerData& t_data)
{
	for (unsigned i = 0; i < t_node.size(); ++i)
	{
		if (t_data.m_name == t_node[i]["name"].as<std::string>())
		{
			t_data.m_speed = t_node[i]["speed"].as<float>();
			t_data.m_size = sf::Vector2f(t_node[i]["size"]["x"].as<float>(), t_node[i]["size"]["y"].as<float>());
			t_data.m_color = sf::Color(t_node[i]["colour"]["r"].as<int>(),
									   t_node[i]["colour"]["g"].as<int>(), 
									   t_node[i]["colour"]["b"].as<int>(),
									   t_node[i]["colour"]["a"].as<int>());
			t_data.m_sprintSpeed = t_node[i]["sprintSpeed"].as<int>();
			t_data.m_sprintTime = t_node[i]["sprintTime"].as<float>();
		}
	}
}

//read npc data
void operator >> (const YAML::Node& t_node, npcData& t_npc)
{
	// npc start position
	t_npc.position.x = t_node["position"]["x"].as<float>();
	t_npc.position.y = t_node["position"]["y"].as<float>();

	//npc size
	t_npc.size.x = t_node["size"]["x"].as<float>();
	t_npc.size.y = t_node["size"]["y"].as<float>();

	// npc colour
	t_npc.color.r = t_node["colour"]["r"].as<int>();
	t_npc.color.g = t_node["colour"]["g"].as<int>();
	t_npc.color.b = t_node["colour"]["b"].as<int>();
	t_npc.color.a = t_node["colour"]["a"].as<int>();

	// npc speed
	t_npc.speed = t_node["speed"].as<float>();

	// patrol points
	for (unsigned i = 0; i < t_node["paths"].size(); ++i)
	{
		sf::Vector2f newPoint;
		newPoint.x = t_node["paths"][i]["point"]["x"].as<float>();
		newPoint.y = t_node["paths"][i]["point"]["y"].as<float>();

		t_npc.patrolPoints.push_back(newPoint);
	}
}

//read the room data
void operator >> (const YAML::Node& t_node, RoomData& t_room)
{
	t_room.m_roomType = t_node["type"].as<std::string>();
	t_room.m_sizeX = t_node["size"]["x"].as<float>();
	t_room.m_sizeY = t_node["size"]["y"].as<float>();
	t_room.m_positionX = t_node["position"]["x"].as<float>();
	t_room.m_positionY = t_node["position"]["y"].as<float>();
}

//read the door data
void operator >> (const YAML::Node& t_node, DoorData& t_door)
{
	t_door.m_doorType = t_node["type"].as<std::string>();
	t_door.m_positionX = t_node["position"]["x"].as<float>();
	t_door.m_positionY = t_node["position"]["y"].as<float>();
	t_door.m_rotation = t_node["rotation"].as<float>();
}

//read the Medication data
void operator >> (const YAML::Node& t_node, MedData& t_med)
{
	t_med.type = t_node["type"].as<std::string>();
	t_med.position.x = t_node["position"]["x"].as<float>();
	t_med.position.y = t_node["position"]["y"].as<float>();
}

// read level data
void operator >> (const YAML::Node& t_node, levelData& t_data)
{
	const YAML::Node& npcNode = t_node["npc"].as<YAML::Node>();
	for (unsigned i = 0; i < npcNode.size(); ++i)
	{
		npcData newNpc;

		npcNode[i] >> newNpc;

		t_data.m_npcs.push_back(newNpc);
	}

	const YAML::Node& roomNode = t_node["rooms"].as<YAML::Node>();
	for (unsigned i = 0; i < roomNode.size(); i++)
	{
		RoomData newRoom;
		roomNode[i] >> newRoom;
		t_data.m_rooms.push_back(newRoom);
	}

	const YAML::Node& doorNode = t_node["doors"].as<YAML::Node>();
	for (unsigned i = 0; i < doorNode.size(); i++)
	{
		DoorData newDoor;
		doorNode[i] >> newDoor;
		t_data.m_doors.push_back(newDoor);
	}

	const YAML::Node& medNode = t_node["medication"].as<YAML::Node>();
	for (unsigned i = 0; i < medNode.size(); i++)
	{
		MedData newMed;
		medNode[i] >> newMed;
		t_data.m_meds.push_back(newMed);
	}
}

/// <summary>
/// @brief try to load the settings data
///    this can be used as a simple template for more yaml loading
/// </summary>
/// <param name="t_loadFileName">files name</param>
/// <param name="t_settings">settings data struct</param>
void yamlLoader::loadSettings(std::string t_loadFileName, SettingsData& t_settings)
{
	std::string filename = ".\\ASSETS\\DATA\\SETTINGS\\" + t_loadFileName + ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);
		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> t_settings;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}

/// <summary>
/// @brief dumps new settings into the yaml file
/// 
/// </summary>
/// <param name="t_loadFileName">file to dump into</param>
/// <param name="t_settings">settings data struct</param>
void yamlLoader::WriteSettings(std::string t_loadFileName, SettingsData& t_settings)
{
	std::string filename = ".\\ASSETS\\DATA\\SETTINGS\\" + t_loadFileName + ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);
		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}
		baseNode << t_settings;

		std::ofstream fout(filename);
		fout << baseNode; // dump it back into the file
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}

void yamlLoader::loadPlayerData(PlayerData& t_data)
{
	std::string filename = ".\\ASSETS\\DATA\\LEVEL\\player.yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);
		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> t_data;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}

void yamlLoader::loadLevelData(levelData& t_levelData, int t_levelNum)
{
	std::string filename = ".\\ASSETS\\DATA\\LEVEL\\level" + std::to_string(t_levelNum) + ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);
		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> t_levelData;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}
