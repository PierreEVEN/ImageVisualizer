

#include "Modifiers/Clamp.h"
#include "ImageViewer.h"
#include "imgui.h"

void ClampModifier::DrawUI() {
	IntSlider("Range min", &Min, 0, 255);
	if (Min > Max) Max = Min;
	IntSlider("Range max", &Max, 0, 255);
	if (Max > Min) Min = Max;
}

void ClampModifier::ModifyImage(ImageData* Data) {
	for (size_t i = 0; i < Data->SizeX * Data->SizeY * Data->Channels; ++i) {
		if (Data->Data[i] < Min) Data->Data[i] = static_cast<uint8_t>(Min);
		if (Data->Data[i] > Max) Data->Data[i] = static_cast<uint8_t>(Max);
	}	
}
