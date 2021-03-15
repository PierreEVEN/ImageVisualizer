

#include "Modifiers/Open.h"

void OpenModifier::DrawUI()
{
	Checkbox("is 8 extraction", &is_8_extraction);
}

void OpenModifier::ModifyImage(ImageData* Data)
{
	Erode(Data, is_8_extraction);
	Dilate(Data, is_8_extraction);
}
