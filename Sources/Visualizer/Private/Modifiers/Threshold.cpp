
#include "Modifiers/Threshold.h"

#include "ImageViewer.h"

void ThresholdModifier::DrawUI() {
	IntSlider("Threshold", &ThresholdValue, 0, 255);
}

void ThresholdModifier::ModifyImage(ImageData* Data) {
	for (size_t i = 0; i < Data->SizeX * Data->SizeY * Data->Channels; ++i) {
		Data->Data[i] = Data->Data[i] > ThresholdValue ? 255 : 0;
	}
}
