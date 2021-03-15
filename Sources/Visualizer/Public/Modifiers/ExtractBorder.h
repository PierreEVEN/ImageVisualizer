#pragma once
#include "imageModifier.h"


class ExtractBorderFilter : public ImageModifier
{
public:
	void DrawUI() override;
	void ModifyImage(ImageData* Data) override;

private:

	bool is_8_extraction = false;
	
};


