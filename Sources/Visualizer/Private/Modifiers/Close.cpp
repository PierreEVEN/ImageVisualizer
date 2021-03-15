

#include "Modifiers/Close.h"

void CloseModifier::DrawUI()
{
	Checkbox("is 8 extraction", &is_8_extraction);
}

void CloseModifier::ModifyImage(ImageData* Data)
{
	Dilate(Data, is_8_extraction);
	Erode(Data, is_8_extraction);
}
