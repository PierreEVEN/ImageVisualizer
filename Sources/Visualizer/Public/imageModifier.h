#pragma once

#include <string>

struct ImageData;
class ImageViewer;

class ImageModifier
{
	friend ImageViewer;
public:

	virtual void DrawUI() = 0;
	virtual void ModifyImage(ImageData* Data) = 0;

	virtual ~ImageModifier() {}

protected:

	void OnModified();
	size_t ModifierID = 0;

	void DragFloat(const std::string& name, double* value);
	void IntSlider(const std::string& name, int* Value, int Min, int Max);
	void Checkbox(const std::string& name, bool* Value);
	uint8_t GetPixelSafe(ImageData* Data, int64_t PosX, int64_t PosY);
	void MatrixView(double* Matrix, size_t SizeX, size_t SizeY);

private:
	void DrawUI_Internal();
	void ModifyImage_Internal(ImageData* Data);
	
	std::string Name;
	bool Enable = true;
	ImageViewer* Parent = nullptr;
};
