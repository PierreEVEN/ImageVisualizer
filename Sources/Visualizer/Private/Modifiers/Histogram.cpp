

#include "Modifiers/Histogram.h"


#include "ImageViewer.h"
#include "imgui.h"

void Histogram::DrawUI()
{


	ImGui::PlotHistogram("Color histogram", Values, 255, 0, nullptr, 0.0f, Max, ImVec2(550.f, 200.f));
	
}

void Histogram::ModifyImage(ImageData* Data)
{
	Max = Data->Data[0];
	
	for (int i = 0; i < 256; ++i) Values[i] = 0.f;

	for (size_t i = 0; i < Data->SizeX * Data->SizeY * Data->Channels; ++i)
	{
		uint8_t Value = Data->Data[i];
		Values[Value]++;
		if (Values[Value] > Max) Max = Values[Value];
	}
}
