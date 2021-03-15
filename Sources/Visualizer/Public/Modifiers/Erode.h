#pragma once
#include "MorphModifiers.h"


class ErodeFilter : public MorphModifier
{
public:
	void DrawUI() override;
	void ModifyImage(ImageData* Data) override;

	bool is_8_extraction = false;
};
