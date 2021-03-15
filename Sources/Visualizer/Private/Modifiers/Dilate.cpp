

#include "Modifiers/Dilate.h"

void DilateModifier::DrawUI()
{
	Checkbox("is 8 extraction", &is_8_extraction);
}

void DilateModifier::ModifyImage(ImageData* Data)
{
	Dilate(Data, is_8_extraction);
}
