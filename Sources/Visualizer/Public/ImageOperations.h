#pragma once
#include <cstdint>

namespace ImageOperations
{


	void NegateImage(uint8_t* ImageData, uint32_t SizeX, uint32_t SizeY, uint32_t Channels);
	void ClampImage(uint8_t* ImageData, uint32_t SizeX, uint32_t SizeY, uint32_t Channels, int Min, int Max);
	void ThresholdImage(uint8_t* ImageData, uint32_t SizeX, uint32_t SizeY, uint32_t Channels, int Threshold);
	void StretchContrast(uint8_t* ImageData, uint32_t SizeX, uint32_t SizeY, uint32_t Channels, int Min, int Max);
	void Normalize(uint8_t* ImageData, uint32_t SizeX, uint32_t SizeY, uint32_t Channels);
	


	
}
