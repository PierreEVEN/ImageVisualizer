#pragma once

#include "imageModifier.h"

class MorphModifier : public ImageModifier
{
protected:

	void Dilate(ImageData* Data, bool is_8_detection);
	void Erode(ImageData* Data, bool is_8_detection);

	
};

