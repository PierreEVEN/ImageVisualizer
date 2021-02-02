#pragma once
#include "imageModifier.h"

class ClampModifier : public ImageModifier
{
public:
	void DrawUI() override;
	virtual void ModifyImage(ImageData* Data);

private:
	int Min = 0;
	int Max = 255;
	
};