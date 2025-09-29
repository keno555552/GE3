#pragma once
#include <vector>
#include <string>

class CsvLoader {
public:
	// static関数にすることで、インスタンスを作らずに「CsvLoader::Load」の形で呼び出せる
	static std::vector<std::vector<int>> Load(const std::string &filePath);
};