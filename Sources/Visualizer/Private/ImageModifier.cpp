

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

void ImageModifier::IntSlider(const std::string& name, int* Value, int Min, int Max) {
	int CurrentValue = *Value;
	ImGui::SliderInt((name + "_##" + std::to_string(ModifierID)).c_str(), &CurrentValue, 0, 255);
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

void ImageModifier::ModifyImage_Internal(ImageData* Data) {
	if (Enable) ModifyImage(Data);
}

void ImageModifier::OnModified() {
	Parent->ApplyTransformation();
}
