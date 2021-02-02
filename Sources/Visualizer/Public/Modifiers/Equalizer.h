#pragma once
#include "imageModifier.h"

class Equalizer : public ImageModifier
{
public:
	void DrawUI() override {}
	void ModifyImage(ImageData* Data) override;
};