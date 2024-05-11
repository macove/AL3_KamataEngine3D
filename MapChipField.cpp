#include "MapChipField.h"
#include <map>
#include <fstream>
#include <sstream>
#include <cassert>


namespace {
	//CSVの中身を読む
	std::map<std::string, MapChipType> MapChipTable = {
	    {"0", MapChipType::kBlank},
	    {"1", MapChipType::kBlock},
	};

}

void MapChipField::ResetMapChipData() {

	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVertical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {
		mapChipDataLine.resize(kNumBlockHorizontal);
	}

}

void MapChipField::LoadMapChipCsv(const std::string& filePath) {

    ResetMapChipData();

	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	std::stringstream mapChipCsv;

	mapChipCsv << file.rdbuf();

	file.close();

	for (uint32_t i = 0; i < kNumBlockVertical; ++i) {

		std::string line;

	    getline(mapChipCsv, line);

		std::istringstream line_stream(line);

		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
		
		
			std::string word;
			getline(line_stream, word, ',');

			if (MapChipTable.contains(word)) {
			
			mapChipData_.data[i][j] = MapChipTable[word];
			}

		
		}

	
	}

}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) { 

	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex) {
	
	return MapChipType::kBlank;
	}
	if (yIndex < 0 || kNumBlockVertical - 1 < yIndex) {
	
	return MapChipType::kBlank;
	}

	return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) { 
	return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVertical - 1 - yIndex), 0); 
}

uint32_t MapChipField::GetNumBlockVertical() { return kNumBlockVertical; }

uint32_t MapChipField::GetNumBlockHorizontal() { return kNumBlockHorizontal; }
