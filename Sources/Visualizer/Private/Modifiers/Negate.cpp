

#include "Modifiers/Negate.h"

#include "ImageViewer.h"

void NegateModifier::ModifyImage(ImageData* Data) {
	for (size_t i = 0; i < Data->SizeX * Data->SizeY * Data->Channels; ++i) {
		Data->Data[i] = 255 - Data->Data[i];
	}
}
