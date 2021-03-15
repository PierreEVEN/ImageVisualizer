
#include "Modifiers/MorphModifiers.h"


#include "BinaryMask.h"
#include "ImageViewer.h"

void MorphModifier::Dilate(ImageData* Data, bool is_8_detection)
{

	auto* new_data = new uint8_t[Data->SizeX * Data->SizeY * Data->Channels];

	for (int64_t PosX = 0; PosX < Data->SizeX; ++PosX)
	{
		for (int64_t PosY = 0; PosY < Data->SizeY; ++PosY)
		{
			uint8_t px = GetPixelSafe(Data, PosX, PosY);

			if (px != 0) {
				new_data[PosX + PosY * Data->SizeX] = UINT8_MAX;
				continue;
			}

			if (Binarymask::DEFAULT_MASK)
			{
				for (const auto& elem : Binarymask::DEFAULT_MASK->mask)
				{
					const uint8_t new_px = GetPixelSafe(Data, PosX + elem.first, PosY + elem.second);
					if (new_px > px)
					{
						new_data[PosX + PosY * Data->SizeX] = new_px;
						px = new_px;
					}
				}
			}
			{
				if (is_8_detection)
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
	}

	memcpy(Data->Data, new_data, Data->SizeX * Data->SizeY * Data->Channels);
	delete[] new_data;


	
}

void MorphModifier::Erode(ImageData* Data, bool is_8_detection)
{

	auto* new_data = new uint8_t[Data->SizeX * Data->SizeY * Data->Channels];

	for (int64_t PosX = 0; PosX < Data->SizeX; ++PosX)
	{
		for (int64_t PosY = 0; PosY < Data->SizeY; ++PosY)
		{
			uint8_t px = GetPixelSafe(Data, PosX, PosY);

			if (px == 0) {
				new_data[PosX + PosY * Data->SizeX] = 0;
				continue;
			}

			if (Binarymask::DEFAULT_MASK)
			{
				for (const auto& elem : Binarymask::DEFAULT_MASK->mask)
				{
					const uint8_t new_px = GetPixelSafe(Data, PosX + elem.first, PosY + elem.second);
					if (new_px < px)
					{
						new_data[PosX + PosY * Data->SizeX] = new_px;
						px = new_px;
						break;
					}
				}
			}
			else {
				if (is_8_detection)
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
							) ? 0 : UINT8_MAX;
				}
				else
				{
					new_data[PosX + PosY * Data->SizeX] =
						(GetPixelSafe(Data, PosX + 1, PosY) != px ||
							GetPixelSafe(Data, PosX - 1, PosY) != px ||
							GetPixelSafe(Data, PosX, PosY + 1) != px ||
							GetPixelSafe(Data, PosX, PosY - 1) != px
							) ? 0 : UINT8_MAX;
				}
			}
		}
	}

	memcpy(Data->Data, new_data, Data->SizeX * Data->SizeY * Data->Channels);
	delete[] new_data;

	
}
