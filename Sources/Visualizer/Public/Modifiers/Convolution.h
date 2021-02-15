#pragma once
#include <memory>
#include <vector>

#include "imageModifier.h"

class ConvolutionModifier : public ImageModifier
{
public:

	ConvolutionModifier();
	
	void DrawUI() override;
	virtual void ModifyImage(ImageData* Data);

private:

	struct Preset
	{
		Preset(const std::string& inName, const std::vector<double>& inConvolutionMatrix) : Name(inName), Radius(static_cast<int>(sqrt(static_cast<int>(inConvolutionMatrix.size()))) - 2), ConvolutionMatrix(inConvolutionMatrix) {}
		const int Radius;
		const std::string Name;
		const std::vector<double> ConvolutionMatrix;
	};
	
	int Radius = 1;
	bool bNormalize = true;

	double* ConvolutionMatrix = nullptr;

	int PresetID = 0;

	void ApplyPreset(const Preset& inPreset);
	
	std::vector<Preset> Presets;
};