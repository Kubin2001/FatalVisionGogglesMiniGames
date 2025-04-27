#pragma once
#include <vector>
#include <string>

std::vector<std::string> ReadCsvLine(const std::string& line, const char separator = ',');

std::vector<std::vector<std::string>> ReadCsv(const std::string& path, const char separator = ',');