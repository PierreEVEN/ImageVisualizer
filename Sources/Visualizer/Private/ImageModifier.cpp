

#include <iostream>

#include "imageModifier.h"
#include "ImageViewer.h"
#include "imgui.h"

void ImageModifier::DrawUI_Internal()
{
	ImGui::Separator();
	ImGui::Text((Name + " : ").c_str());
	ImGui::SameLine();
	Checkbox("Enable", &Enable);
	if (Enable) DrawUI();
}

void ImageModifier::DragFloat(const std::string& name, double* value)
{
	float OldValue = static_cast<float>(*value);
	float NewValue = OldValue;
	ImGui::DragFloat((name + "_##" + std::to_string(ModifierID)).c_str(), &NewValue);

	if (NewValue != OldValue) {
		*value = static_cast<double>(NewValue);
		OnModified();
	}
	
}

void ImageModifier::IntSlider(const std::string& name, int* Value, int Min = 0, int Max = 255) {
	int CurrentValue = *Value;
	ImGui::SliderInt((name + "_##" + std::to_string(ModifierID)).c_str(), &CurrentValue, Min, Max);
	if (CurrentValue != *Value) {
		*Value = CurrentValue;
		OnModified();
	}	
}

void ImageModifier::Checkbox(const std::string& name, bool* Value)
{
	bool CurrentValue = *Value;
	ImGui::Checkbox((name + "_##" + std::to_string(ModifierID)).c_str(), &CurrentValue);
	if (CurrentValue != *Value)
	{
		*Value = CurrentValue;
		OnModified();
	}
}


uint8_t ImageModifier::GetPixelSafe(ImageData* Data, int64_t PosX, int64_t PosY)
{
	PosX = PosX < 0 ? -PosX : PosX > Data->SizeX ? Data->SizeX * 2 - PosX : PosX;
	PosY = PosY < 0 ? -PosY : PosY > Data->SizeY ? Data->SizeY * 2 - PosY : PosY;


	return Data->Data[PosX + PosY * Data->SizeX];
}


void ImageModifier::MatrixView(double* Matrix, size_t SizeX, size_t SizeY)
{
	ImGui::Columns(static_cast<int>(SizeX));
	for (size_t X = 0; X < SizeX; ++X)
	{
		for (size_t Y = 0; Y < SizeY; ++Y)
		{
			DragFloat("##" + std::to_string(X + Y * SizeX), &Matrix[X + Y * SizeX]);
			ImGui::NextColumn();
		}
	}
	ImGui::Columns(1);
}

void ImageModifier::ModifyImage_Internal(ImageData* Data) {
	if (Enable) ModifyImage(Data);
}

void ImageModifier::OnModified() {
	Parent->ApplyTransformation();
}
