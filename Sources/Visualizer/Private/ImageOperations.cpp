#include "ImageOperations.h"

/**
 * TP 1
 */

void ImageOperations::NegateImage(uint8_t* ImageData, uint32_t SizeX, uint32_t SizeY, uint32_t Channels) {
	for (int i = 0; i < SizeX * SizeY * Channels; ++i) {
		ImageData[i] = 255 - ImageData[i];
	}	
}

void ImageOperations::ClampImage(uint8_t* ImageData, uint32_t SizeX, uint32_t SizeY, uint32_t Channels, int Min, int Max) {
	for (int i = 0; i < SizeX * SizeY * Channels; ++i) {
		if (ImageData[i] < Min) ImageData[i] = static_cast<uint8_t>(Min);
		if (ImageData[i] > Max) ImageData[i] = static_cast<uint8_t>(Max);
	}
}

void ImageOperations::ThresholdImage(uint8_t* ImageData, uint32_t SizeX, uint32_t SizeY, uint32_t Channels, int Threshold) {
	for (int i = 0; i < SizeX * SizeY * Channels; ++i) {
		ImageData[i] = ImageData[i] > Threshold ? 255 : 0;
	}
}

void ImageOperations::StretchContrast(uint8_t* ImageData, uint32_t SizeX, uint32_t SizeY, uint32_t Channels, int Min, int Max) {
	int ValMin = ImageData[0];
	int ValMax = ImageData[0];

	for (int i = 0; i < SizeX * SizeY * Channels; ++i) {
		if (ImageData[i] < ValMin) ValMin = ImageData[i];
		if (ImageData[i] > ValMax) ValMax = ImageData[i];
	}

	for (int i = 0; i < SizeX * SizeY * Channels; ++i) {
		ImageData[i] = (static_cast<double>(ImageData[i] - ValMin) / static_cast<double>(ValMax - ValMin)) * static_cast<double>(Max - Min) + Min;
	}
}

void ImageOperations::Normalize(uint8_t* ImageData, uint32_t SizeX, uint32_t SizeY, uint32_t Channels) {
	StretchContrast(ImageData, SizeX, SizeY, Channels, 0, 255);
}


