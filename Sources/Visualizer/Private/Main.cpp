

#include "ImageViewer.h"
#include "OpenGLContext.h"

int main(int argc, char** argv)
{
	OpenGLContext::Init();

	ImageViewer Image1;
	ImageViewer Image;
	if (argc > 1) {
		Image.LoadFromFile(argv[1]);
	}
	else
	{
		Image.LoadFromFile("Images/baboon.pgm");
	}

	while (!OpenGLContext::ShouldClose()) {		
		OpenGLContext::BeginFrame();
		ImageViewer::DisplayAll();
		OpenGLContext::EndFrame();
	}

	OpenGLContext::Shutdown();
}
