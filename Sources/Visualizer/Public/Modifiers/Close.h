#pragma once
#include "MorphModifiers.h"


class CloseModifier : public MorphModifier
{
public:
	void DrawUI() override;
	void ModifyImage(ImageData* Data) override;

	bool is_8_extraction = false;
};

