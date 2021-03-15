
#include "Modifiers/Erode.h"



void ErodeFilter::DrawUI()
{
	Checkbox("is 8 extraction", &is_8_extraction);
}


void ErodeFilter::ModifyImage(ImageData* Data)
{
	Erode(Data, is_8_extraction);	
}