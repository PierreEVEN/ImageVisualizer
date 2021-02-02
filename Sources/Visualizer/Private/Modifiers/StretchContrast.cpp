#pragma once
#include "Modifiers/StretchContrast.h"

#include "ImageViewer.h"

void NormalizerModifier::DrawUI()
{
	Checkbox("Normalize", &Normalize);
	if (!Normalize) {
		IntSlider("Min", &NormMin, 0, 255);
		if (NormMin > NormMax) NormMax = NormMin;
		IntSlider("Max", &NormMax, 0, 255);
		if (NormMax < NormMin) NormMin = NormMax;		
	}
	
}

void NormalizerModifier::ModifyImage(ImageData* Data)
{
	int ValMin = Data->Data[0];
	int ValMax = Data->Data[0];

	const int DesiredMin = Normalize ? 0 : NormMin;
	const int DesiredMax = Normalize ? 255 : NormMax;

	for (size_t i = 0; i < Data->SizeX * Data->SizeY * Data->Channels; ++i) {
		if (Data->Data[i] < ValMin) ValMin = Data->Data[i];
		if (Data->Data[i] > ValMax) ValMax = Data->Data[i];
	}

	for (size_t i = 0; i < Data->SizeX * Data->SizeY * Data->Channels; ++i) {
		Data->Data[i] = static_cast<uint8_t>((static_cast<double>(Data->Data[i] - ValMin) / static_cast<double>(ValMax - ValMin)) * static_cast<double>(DesiredMax - DesiredMin) + DesiredMin);
	}
}
