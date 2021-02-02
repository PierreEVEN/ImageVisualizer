#pragma once
#include "imageModifier.h"

class ThresholdModifier : public ImageModifier
{
public:
	void DrawUI() override;
	void ModifyImage(ImageData* Data) override;

private:
	int ThresholdValue = 127;
};

