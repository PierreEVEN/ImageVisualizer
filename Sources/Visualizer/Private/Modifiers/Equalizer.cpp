
#include "Modifiers/Equalizer.h"

#include "ImageViewer.h"

void Equalizer::ModifyImage(ImageData* Data)
{
	size_t Histogram[256];
	for (auto& Value : Histogram) Value = 0;

	size_t PixelCount = Data->SizeX * Data->SizeY * Data->Channels;
	
	for (size_t i = 0; i < PixelCount; ++i)	{
		const uint8_t Value = Data->Data[i];
		Histogram[Value]++;
	}

	uint8_t GrayLevels[256];	
	size_t Current = 0;
	
	for (int i = 0; i < 256; i++) {
		Current += Histogram[i];
		GrayLevels[i] = static_cast<uint8_t>(round((static_cast<double>(Current) * 255.0) / static_cast<double>(PixelCount)));
	}

	for (size_t i = 0; i < PixelCount; ++i) {
		Data->Data[i] = GrayLevels[Data->Data[i]];
	}
}
