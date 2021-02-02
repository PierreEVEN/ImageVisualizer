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

	void IntSlider(const std::string& name, int* Value, int Min, int Max);
	void Checkbox(const std::string& name, bool* Value);

private:
	void DrawUI_Internal();
	void ModifyImage_Internal(ImageData* Data);
	
	std::string Name;
	bool Enable = true;
	ImageViewer* Parent = nullptr;
};
