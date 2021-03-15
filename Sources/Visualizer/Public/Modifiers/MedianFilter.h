#pragma once
#include "imageModifier.h"


class MedianFilterModifier : public ImageModifier
{
public:
	void DrawUI() override;
	void ModifyImage(ImageData* Data) override;
};

