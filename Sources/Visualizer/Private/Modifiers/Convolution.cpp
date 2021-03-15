

#include "Modifiers/Convolution.h"

#include <iostream>



#include "ImageViewer.h"
#include "imgui.h"

ConvolutionModifier::ConvolutionModifier()
{

	
	Presets.push_back(Preset("test", {
			1, 2, 3,
			3 ,2 ,1,
			1 ,2 ,3
		}));

	Presets.push_back(Preset("test2", {
			1, 2, 20,
			3 ,2 ,1,
			1 ,2 ,3
		}));
	
}

void ConvolutionModifier::DrawUI() {
	int LastRadius = Radius;
	IntSlider("Radius", &Radius, 0, 3);
	Checkbox("Normalize", &bNormalize);

	if (!ConvolutionMatrix || LastRadius != Radius) {
		if (ConvolutionMatrix) {
			free(ConvolutionMatrix);
		}

		size_t MatSize = Radius * 2 + 1;
		MatSize *= MatSize;

		ConvolutionMatrix = new double[MatSize];

		for (size_t i = 0; i < MatSize; ++i) {
			ConvolutionMatrix[i] = 1;
		}
		OnModified();
	}

	std::string PresetName = PresetID == 0 ? "custom" : Presets[PresetID - 1].Name.c_str();

	if (ImGui::BeginCombo(("Mask##" + std::to_string(ModifierID)).c_str(), PresetName.c_str())) {


		if (ImGui::Selectable("custom", PresetID == 0))
			PresetID = 0;
		for (int i = 1; i < Presets.size() + 1; ++i)
			if (ImGui::Selectable(Presets[i - 1].Name.c_str(), PresetID == i)) {
				PresetID = i;
				ApplyPreset(Presets[i - 1]);
				OnModified();
			}
		
		ImGui::EndCombo();
	}
	
	if (!PresetID) {
		MatrixView(ConvolutionMatrix, Radius * 2 + 1, Radius * 2 + 1);
	}
}


uint8_t GetPixelValue(int64_t PosX, int64_t PosY, ImageData* Data)
{
	if (PosX < 0) PosX = -PosX;
	if (PosY < 0) PosY = -PosY;
	if (PosX >= Data->SizeX) PosX = -PosX + Data->SizeX * 2 - 1;
	if (PosY >= Data->SizeY) PosX = -PosY + Data->SizeY * 2 - 1;

	return Data->Data[PosX + PosY * Data->SizeX];
}


void ConvolutionModifier::ModifyImage(ImageData* Data) {
	if (!ConvolutionMatrix) return;

	size_t Length = Radius * 2 + 1;
	int64_t MatSize = Length * Length;
	size_t Offset = Radius;

	double Sum = 0;
	if (bNormalize) {
		for (int i = 0; i < MatSize; ++i) {
			Sum += ConvolutionMatrix[i];
		}
	}
	else Sum = 1;

	uint8_t* newData = new uint8_t[Data->SizeX * Data->SizeY * Data->Channels];
	std::memcpy(newData, Data->Data, Data->SizeX * Data->SizeY * Data->Channels);
	
	for (int64_t X = 0; X < Data->SizeX; ++X)
	{
		for (int64_t Y = 0; Y < Data->SizeY; ++Y)
		{

			double Total = 0;
			for (int64_t i = 0; i < MatSize; ++i)
			{
				Total += GetPixelValue(X + i % Length - Offset, Y + i / Length - Offset, Data) * ConvolutionMatrix[i];
			}
			if (bNormalize) Total /= Sum;

			newData[X + Y * Data->SizeX] = static_cast<uint8_t>(Total);
		}
	}

	memcpy(Data->Data, newData, Data->SizeX * Data->SizeY * Data->Channels);	
	std::free(newData);
}

void ConvolutionModifier::ApplyPreset(const Preset& inPreset)
{
	Radius = inPreset.Radius;
	if (ConvolutionMatrix) free(ConvolutionMatrix);

	size_t S = (inPreset.Radius * 2 + 1) * (inPreset.Radius * 2 + 1);
	
	ConvolutionMatrix = new double[S];

	for (size_t i = 0; i < inPreset.ConvolutionMatrix.size(); ++i) {
		ConvolutionMatrix[i] = inPreset.ConvolutionMatrix[i];
	}
}
