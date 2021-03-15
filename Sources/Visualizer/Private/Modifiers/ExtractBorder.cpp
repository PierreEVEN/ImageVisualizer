
#include "Modifiers/ExtractBorder.h"

#include "ImageViewer.h"


void ExtractBorderFilter::DrawUI()
{
	Checkbox("is 8 extraction", &is_8_extraction);
}

void ExtractBorderFilter::ModifyImage(ImageData* Data)
{
	auto* new_data = new uint8_t[Data->SizeX * Data->SizeY * Data->Channels];

	for (int64_t PosX = 0; PosX < Data->SizeX; ++PosX)
	{
		for (int64_t PosY = 0; PosY < Data->SizeY; ++PosY)
		{
			const uint8_t px = GetPixelSafe(Data, PosX, PosY);

			if (px == 0) {
				new_data[PosX + PosY * Data->SizeX] = 0;
				continue;
			}
			
			if (is_8_extraction)
			{
				new_data[PosX + PosY * Data->SizeX] =
					(GetPixelSafe(Data, PosX + 1, PosY - 1) != px ||
						GetPixelSafe(Data, PosX + 1, PosY) != px ||
						GetPixelSafe(Data, PosX + 1, PosY + 1) != px ||
						GetPixelSafe(Data, PosX, PosY + 1) != px ||
						GetPixelSafe(Data, PosX - 1, PosY + 1) != px ||
						GetPixelSafe(Data, PosX - 1, PosY) != px ||
						GetPixelSafe(Data, PosX - 1, PosY - 1) != px ||
						GetPixelSafe(Data, PosX, PosY - 1) != px
						) ? UINT8_MAX : 0;
			}
			else
			{
				new_data[PosX + PosY * Data->SizeX] =
					(GetPixelSafe(Data, PosX + 1, PosY) != px ||
						GetPixelSafe(Data, PosX - 1, PosY) != px ||
						GetPixelSafe(Data, PosX, PosY + 1) != px ||
						GetPixelSafe(Data, PosX, PosY - 1) != px
						) ? UINT8_MAX : 0;
			}
		}
	}
	
	memcpy(Data->Data, new_data, Data->SizeX * Data->SizeY * Data->Channels);
	delete[] new_data;
}
