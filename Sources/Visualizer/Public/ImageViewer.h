#pragma once
#include <string>
#include <cstdint>

class ImageViewer
{
public:
	ImageViewer();
	static void DisplayAll();
	void LoadFromFile(const std::string& FilePath);
	void UpdateBaseData(uint8_t* Data, int sX, int sY, int inChannels);

private:
	void Display();

	bool bIsTextureInitialized = false;
	uint32_t TextureID;
	uint8_t* ImageData = nullptr;
	uint8_t* TransformedData = nullptr;
	uint64_t Value;
	bool bDisplay = true;
public:

private:

	int SizeX = 0, SizeY = 0, Channels = 0;
	time_t LastUpdateTime = 0;
	
	void DrawMenuBar();
	void UpdateTransformedInfos();

	void ResetData();
	void ApplyTransformation();
	void UpdateHistogram();
	
	/**
	 * Infos
	 */
	uint64_t ValueSum = 0;
	uint8_t PixelMin = 0;
	uint8_t PixelMax = 0;
	double AverageGrayScale = 0.0;

	/**
	 * Settings
	 */
	bool bNegate = false;
	bool bClamp = false;
	bool bThreshold = false;
	bool bStretch = false;
	int ThresholdValue = 127;
	int MinRange = 0;
	int MaxRange = 255;
	int MinStretch = 0;
	int MaxStretch = 255;
	
	/**
	 * Histogram
	 */	
	void DrawHistogram();
	bool bShowHistogram = false;
	float* HistogramData = nullptr;
	float HistogramMax = 0;
};