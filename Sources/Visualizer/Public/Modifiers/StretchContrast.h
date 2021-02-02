
#include "imageModifier.h"

class NormalizerModifier : public ImageModifier
{
public:
	void DrawUI() override;
	void ModifyImage(ImageData* Data) override;

private:
	int NormMin = 0;
	int NormMax = 255;

	bool Normalize = true;;
};