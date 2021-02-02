#pragma once
#include "imageModifier.h"

class NegateModifier : public ImageModifier
{
public:
	void DrawUI() override {}
	virtual void ModifyImage(ImageData* Data);
};