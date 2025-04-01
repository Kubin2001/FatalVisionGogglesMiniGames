#pragma once

#include <string>
class Logger {
	private:
		static std::string currentPath;

	public:
		//static void SetFilePath(std::string& path);


		static void SetUpNewSession(const std::string& playerName, int gameType);

		static void Log(const std::string& massage);
		



};