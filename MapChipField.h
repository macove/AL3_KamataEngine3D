#pragma once
#include <cmath>
#include <vector>
#include "Vector3.h"
#include "DirectXCommon.h"
#include "Input.h"

enum class MapChipType {
	kBlank, //blank
	kBlock, //block
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};



class MapChipField {

public: 

	void ResetMapChipData();
	
	void LoadMapChipCsv(const std::string& filePath);
	
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVertical() { return kNumBlockVertical; }
	uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; }



private:
	//size per block
	static inline const float kBlockWidth = 2.0f;
	static inline const float kBlockHeight = 2.0f;
	//number of blocks
	static inline const uint32_t kNumBlockVertical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

};
