#pragma once
#include "MorphModifiers.h"


class DilateModifier : public MorphModifier
{
public:
	void DrawUI() override;
	void ModifyImage(ImageData* Data) override;

	bool is_8_extraction = false;
};

