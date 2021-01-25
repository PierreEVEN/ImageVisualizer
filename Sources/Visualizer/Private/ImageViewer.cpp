

#include "ImageViewer.h"

#include "imgui.h"
#include "OpenGLContext.h"

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <filesystem>

#include "stb_image.h"
#include "GL/gl3w.h"

std::vector <ImageViewer*> Images;

ImageViewer::ImageViewer()
{
	Images.push_back(this);
}

void ImageViewer::LoadFromFile(const std::string& newPath) {
	Path = newPath;	
	
	std::cout << "update image data" << std::endl;
	
	stbi_uc* NewImageData = stbi_load(Path.c_str(), &SizeX, &SizeY, &Channels, 4);
	if (!NewImageData)	{
		std::cerr << "failed to load image from " << Path << std::endl;
		return;
	}
	UpdateData(NewImageData, SizeX, SizeY, Channels);
}

void ImageViewer::DisplayAll() {
	for (const auto& Image : Images)	{
		Image->CheckFileUpdate();
		Image->Display();
	}
}

void ImageViewer::Display() {
	if (ImGui::Begin(("Image : " + Path).c_str())) {
		if (!ImageData)	{
			ImGui::Text("No data");
		}
		else {
			ImGui::Image(reinterpret_cast<ImTextureID>(TextureID), ImVec2(static_cast<float>(SizeX), static_cast<float>(SizeY)));

			ImGui::Text("Size : %d x %d", SizeX, SizeY);
			ImGui::Text("Channels : %d", Channels);
			ImGui::Text("Value sum : %d", ValueSum);
			ImGui::Text("Average gray scale : %lf", AverageGrayScale);
			ImGui::Text("Rage : %d - %d", PixelMin, PixelMax);
		}
	}
	ImGui::End();
}

void ImageViewer::UpdateData(uint8_t* Data, uint8_t sX, uint8_t sY, uint8_t Channels) {
	UpdateImageInfos(Data, SizeX, SizeY, Channels);


	if (!bAreTextureDataBuilt) {
		bAreTextureDataBuilt = true;
		glGenTextures(1, &TextureID);
	}
	
	if (ImageData) free(ImageData);
	ImageData = Data;	

	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SizeX, SizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, static_cast<unsigned char*>(ImageData));
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	bAreTextureDataBuilt = true;
}

void ImageViewer::CheckFileUpdate() {
	if (Path.empty()) return;

	std::filesystem::path FilePath(Path.c_str());
	if (!std::filesystem::exists(FilePath)) {
		std::cerr << Path << "does not exists " << std::endl;
		return;
	}

	std::filesystem::file_time_type file_time = std::filesystem::last_write_time(FilePath);
	time_t FileTime = std::chrono::system_clock::to_time_t(
		std::chrono::time_point_cast<std::chrono::system_clock::duration>(
			file_time - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
			));
	
	if (LastUpdateTime == FileTime) return;
	LastUpdateTime = FileTime;
	LoadFromFile(Path);
}

void ImageViewer::UpdateImageInfos(uint8_t* data, int sizeX, int sizeY, int channels) {
	if (!data) return;
	ValueSum = 0;
	PixelMin = data[0];
	PixelMax = data[0];
	for (int i = 0; i < sizeX * sizeY * channels; ++i)
	{
		ValueSum += data[i];
		if (data[i] > PixelMax) PixelMax = data[i];
		if (data[i] < PixelMin) PixelMin = data[i];
	}
	AverageGrayScale = ValueSum / (sizeX * sizeY * channels);
}

