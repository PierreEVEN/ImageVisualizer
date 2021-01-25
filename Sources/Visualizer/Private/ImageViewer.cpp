

#include "ImageViewer.h"

#include "imgui.h"
#include "OpenGLContext.h"

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <filesystem>


#include "stb_image.h"
#include "GL/gl3w.h"
#include "ImageOperations.h"



std::vector <ImageViewer*> ImagesViewers;
uint64_t ImageID = 0;

void ImageViewer::DisplayAll() {
	// Draw all instances
	for (int i = ImagesViewers.size() - 1; i >= 0; --i)
	{
		if (!ImagesViewers[i]->bDisplay)
		{
			delete ImagesViewers[i];
			ImagesViewers.erase(ImagesViewers.begin() + i);
			continue;
		}
		ImagesViewers[i]->Display();
	}
}

ImageViewer::ImageViewer() {
	// Register instance
	ImagesViewers.push_back(this);
	Value = ImageID++;
}

void ImageViewer::DrawMenuBar() {
	bool bShow;
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Display")) {
			/* Histogram */
			bShow = bShowHistogram;
			ImGui::Checkbox("Histogram", &bShow);
			if (bShow != bShowHistogram) {
				bShowHistogram = bShow;
				ApplyTransformation();
			}
			
			/* Negate */
			bShow = bNegate;
			ImGui::Checkbox("Negate", &bShow);
			if (bShow != bNegate) {
				bNegate = bShow;
				ApplyTransformation();
			}
			ImGui::Checkbox("Clamp", &bClamp);
			ImGui::Checkbox("Threshold", &bThreshold);
			ImGui::Checkbox("Stretch contrast", &bStretch);
			
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

void ImageViewer::UpdateBaseData(uint8_t* Data, int sX, int sY, int inChannels) {
	if (ImageData) free(ImageData);

	ImageData = Data;
	SizeX = sX;
	SizeY = sY;
	Channels = inChannels;
	
	ApplyTransformation();
}

void ImageViewer::LoadFromFile(const std::string& FilePath) {	
	std::cout << "update image data" << std::endl;
	int sX, sY, newChannels;
	stbi_uc* NewImageData = stbi_load(FilePath.c_str(), &sX, &sY, &newChannels, 1);
	if (!NewImageData)	{
		std::cerr << "failed to load image from " << FilePath << std::endl;
		return;
	}
	
	UpdateBaseData(NewImageData, sX, sY, 1);
}


void ImageViewer::Display() {
	if (!bDisplay) return;
	
	if (ImGui::Begin(("Image " + std::to_string(Value)).c_str(), &bDisplay, ImGuiWindowFlags_MenuBar)) {

		DrawMenuBar();
		DrawHistogram();
		if (!TransformedData)	{
			ImGui::Text("No data");
		}
		else {
			if (bClamp) {
				{
					int Min = MinRange;
					ImGui::SliderInt("Range min", &Min, 0, 255);
					if (Min > MaxRange) MaxRange = Min;
					if (Min != MinRange) {
						MinRange = Min;
						ApplyTransformation();
					}
				}

				{
					int Max = MaxRange;
					ImGui::SliderInt("Range max", &Max, 0, 255);
					if (Max < MinRange) MinRange = Max;
					if (Max != MaxRange) {
						MaxRange = Max;
						ApplyTransformation();
					}
				}
			}

			if (bStretch) {
				{
					int Min = MinStretch;
					ImGui::SliderInt("Stretch contrast min", &Min, 0, 255);
					if (Min > MaxStretch) MaxStretch = Min;
					if (Min != MinStretch) {
						MinStretch = Min;
						ApplyTransformation();
					}
				}

				{
					int Max = MaxStretch;
					ImGui::SliderInt("Stretch contrast max", &Max, 0, 255);
					if (Max < MinStretch) MinStretch = Max;
					if (Max != MaxStretch) {
						MaxStretch = Max;
						ApplyTransformation();
					}
				}
			}
			
			if (bThreshold) {
				int Value = ThresholdValue;
				ImGui::SliderInt("Threshold", &Value, 0, 255);
				if (Value != ThresholdValue) {
					ThresholdValue = Value;
					ApplyTransformation();
				}
			}
			
			ImGui::Text("Size : %d x %d", SizeX, SizeY);
			ImGui::Text("Channels : %d", Channels);
			ImGui::Text("Value sum : %d", ValueSum);
			ImGui::Text("Average gray scale : %lf", AverageGrayScale);
			ImGui::Text("Color range : %d - %d", PixelMin, PixelMax);

			ImGui::Image(reinterpret_cast<ImTextureID>(TextureID), ImVec2(static_cast<float>(SizeX), static_cast<float>(SizeY)));
		}
	}
	ImGui::End();
}

void ImageViewer::ResetData() {
	if (TransformedData) free(TransformedData);
	TransformedData = nullptr;
	if (HistogramData) free(HistogramData);
	HistogramData = nullptr;
}

void ImageViewer::ApplyTransformation() {
	std::cout << "rebuild image" << std::endl;
	ResetData();

	if (!ImageData || SizeX * SizeY * Channels <= 0) return;

	TransformedData = new uint8_t[SizeX * SizeY * Channels];
	std::memcpy(TransformedData, ImageData, SizeX * SizeY * Channels);

	if (bNegate) ImageOperations::NegateImage(TransformedData, SizeX, SizeY, Channels);
	if (bClamp) ImageOperations::ClampImage(TransformedData, SizeX, SizeY, Channels, MinRange, MaxRange);
	if (bThreshold) ImageOperations::ThresholdImage(TransformedData, SizeX, SizeY, Channels, ThresholdValue);
	if (bStretch) ImageOperations::StretchContrast(TransformedData, SizeX, SizeY, Channels, MinStretch, MaxStretch);

	UpdateTransformedInfos();
	UpdateHistogram();

	uint8_t* TempData = new uint8_t[SizeX * SizeY * 4];
	for (size_t i = 0; i < SizeX * SizeY; ++i) {
		TempData[i * 4] = TransformedData[i];
		TempData[i * 4 + 1] = TransformedData[i];
		TempData[i * 4 + 2] = TransformedData[i];
	}

	if (!bIsTextureInitialized) glGenTextures(1, &TextureID);
	bIsTextureInitialized = true;
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SizeX, SizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, TempData);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if (TempData) free(TempData);
}

void ImageViewer::UpdateHistogram() {
	// Generate histogram data
	if (HistogramData) free(HistogramData);
	HistogramData = nullptr;
	
	if (!TransformedData) return;
	
	HistogramData = new float[255];
	HistogramMax = 0;
	std::memset(HistogramData, 0, sizeof(float) * 255);

	for (size_t i = 0; i < SizeX * SizeY * Channels; ++i) {
		HistogramData[TransformedData[i]]++;
		if (HistogramData[TransformedData[i]] > HistogramMax) HistogramMax = HistogramData[TransformedData[i]];
	}
}

void ImageViewer::UpdateTransformedInfos() {
	if (!TransformedData) return;
	ValueSum = 0;
	PixelMin = TransformedData[0];
	PixelMax = TransformedData[0];
	for (int i = 0; i < SizeX * SizeY * Channels; ++i)
	{
		ValueSum += TransformedData[i];
		if (TransformedData[i] > PixelMax) PixelMax = TransformedData[i];
		if (TransformedData[i] < PixelMin) PixelMin = TransformedData[i];
	}
	AverageGrayScale = (double)ValueSum / (SizeX * SizeY * Channels);
}

void ImageViewer::DrawHistogram() {
	if (!bShowHistogram || !HistogramData) return;
	
	ImGui::PlotHistogram("Color histogram", HistogramData, 255, 0, NULL, 0.0f, HistogramMax, ImVec2(550.f, 200.f));
}

