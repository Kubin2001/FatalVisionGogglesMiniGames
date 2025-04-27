#include "Logger.h"
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include "SceneManager.h"

std::string Logger::currentPath = "";

//void Logger::SetFilePath(std::string& path) {
//	this->currentPath = path;
//}

int LogFileCount(const std::string& path) {
	int counter = 1;
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
		std::string name = entry.path().stem().string();
		if (entry.is_regular_file()) {
			counter++;
		}
	}
	return counter++;
}

void Logger::SetUpNewSession(const std::string& playerName, int gameType) {
	if (playerName == "") {
		std::cout << "NameEmpty Logging Not possible\n";
		return;
	}
	std::string directory = "";
	switch (gameType){
		case 1:
			directory = "Logs/GameOne";
			break;
		case 2:
			directory = "Logs/GameTwo";
			break;
		case 3:
			directory = "Logs/GameThree";
			break;
		case 4:
			directory = "Logs/GameFour";
			break;
		case 5:
			directory = "Logs/GameFive";
			break;
		case 6:
			directory = "Logs/GameSix";
			break;
	}

	int counter = 0;

    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory)) {
        std::string name = entry.path().stem().string();
		if (entry.is_directory()) {
			if (name == playerName) {
				currentPath = entry.path().string() + "/" + std::to_string(LogFileCount(entry.path().string())) + ".txt";
				std::ofstream logFile(currentPath);
				Logger::Log(std::to_string(SceneMan::GetData<bool>("UsesGoogles")) + "\n");
				return;
			}
		}
    }
	std::filesystem::path newFolder = directory +"/" + playerName;
	if (std::filesystem::create_directory(newFolder)) {
		currentPath = newFolder.string() + "/1.txt";
		std::ofstream logFile(currentPath);
		Logger::Log(std::to_string(SceneMan::GetData<bool>("UsesGoogles")) + "\n");

	}
	else {
		std::cerr << "Failed to create folder: " << newFolder << "\n";
	}
}

void Logger::Log(const std::string& massage) {
	if (SceneMan::GetData<std::string>("PlayerName") == "") {
		std::cout << "NameEmpty Logging Not possible\n";
		return;
	}
	std::ofstream logFile(currentPath,std::ios::app);

	if (logFile.is_open()) {
		logFile << massage + "\n";
		logFile.close();
	}
	else{
		std::cout << "Error file: " << currentPath << " does not exist\n";
	}
}