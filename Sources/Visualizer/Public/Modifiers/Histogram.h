#pragma once
#include "imageModifier.h"

class Histogram : public ImageModifier
{
public:
	Histogram()
	{
		Values = new float[256];
	}

	~Histogram()
	{
		delete Values;
	}
	
	void DrawUI() override;
	void ModifyImage(ImageData* Data) override;

private:
	float* Values;

	float Max = 0;

};