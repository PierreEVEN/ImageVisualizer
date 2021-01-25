#pragma once
#include <string>
#include <cstdint>

class ImageViewer
{
public:
	ImageViewer();

	void LoadFromFile(const std::string& newPath);

	static void DisplayAll();

	void UpdateData(uint8_t* Data, uint8_t sX, uint8_t sY, uint8_t Channels);

private:

	void Display();
	bool bAreTextureDataBuilt = false;
	std::string Path = "";
	uint32_t TextureID = -1;
	int SizeX = 0, SizeY = 0, Channels = 0;
	time_t LastUpdateTime = 0;

	void CheckFileUpdate();
	void UpdateImageInfos(uint8_t* data, int sizeX, int sizeY, int channels);
	
	/**
	 * Infos
	 */
	uint8_t* ImageData = nullptr;
	uint64_t ValueSum = 0;
	uint8_t PixelMin = 0;
	uint8_t PixelMax = 0;
	double AverageGrayScale = 0.0;
};