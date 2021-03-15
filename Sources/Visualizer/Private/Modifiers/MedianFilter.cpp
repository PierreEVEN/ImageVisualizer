
#include "Modifiers/MedianFilter.h"

#include <array>
#include "algorithm"

#include "ImageViewer.h"

void MedianFilterModifier::DrawUI()
{
}


void MedianFilterModifier::ModifyImage(ImageData* Data)
{
	uint8_t* new_data = new uint8_t[Data->SizeX * Data->SizeY * Data->Channels];
	memcpy(new_data, Data->Data, Data->SizeX * Data->SizeY * Data->Channels);

	std::array<uint32_t, 9> map;
	
	for (size_t i = 0; i < Data->SizeX * Data->SizeY * Data->Channels; ++i) {

		for (int x = -1; x <= 1; ++x)
		{
			for (int y = -1; y <= 1; ++y)
			{
				map[(x + 1) + (y + 1) * 3] = GetPixelSafe(Data, (i % Data->SizeX + x), (i / Data->SizeX + y));
			}
		}

		std::sort(map.begin(), map.end(), [] (int a, int b)
			{
				return a > b;
			});
		
		new_data[i] = map[9 / 2];
	}

	memcpy(Data->Data, new_data, Data->SizeX * Data->SizeY * Data->Channels);

	delete new_data;
}
