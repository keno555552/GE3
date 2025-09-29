#include "CsvLoader.h"
#include <fstream>
#include <sstream>
#include <cassert>

std::vector<std::vector<int>> CsvLoader::Load(const std::string &filePath) {
	std::vector<std::vector<int>> data;
	std::ifstream file(filePath);
	assert(file.is_open()); // ファイルが開けなかったらプログラムを止める

	std::string line;
	while(std::getline(file, line)) {
		std::vector<int> row;
		std::stringstream ss(line);
		std::string cell;
		while(std::getline(ss, cell, ',')) {
			row.push_back(std::stoi(cell));
		}
		data.push_back(row);
	}
	return data;
}