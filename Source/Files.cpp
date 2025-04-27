#include "Files.h"
#include <fstream>
#include <iostream>

std::vector<std::string> ReadCsvLine(const std::string& line, const char separator) {
	std::vector<std::string> items;
	std::string temp = "";
	for (size_t i = 0; i < line.length(); i++) {
		if (line[i] != separator) {
			temp += line[i];
		}
		else {
			items.emplace_back(temp);
			temp.clear();
		}
	}
	items.emplace_back(temp);
	return items;
}

std::vector<std::vector<std::string>> ReadCsv(const std::string& path, const char separator) {
    std::vector<std::vector<std::string>> csvVec;
    std::ifstream csvFile(path);
    std::string line;
    if (csvFile.is_open()) {
        while (std::getline(csvFile, line)) {
            csvVec.emplace_back(ReadCsvLine(line, separator));
        }
        csvFile.close();
    }
    else {
        std::cout << "error reading file\n";
    }

    return csvVec;
}