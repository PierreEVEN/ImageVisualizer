

#include "ImageViewer.h"
#include "OpenGLContext.h"
#include "imgui.h"
#include <filesystem>

int main(int argc, char** argv)
{
	OpenGLContext::Init();
	

	while (!OpenGLContext::ShouldClose()) {		
		OpenGLContext::BeginFrame();

		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Load")) {

				//std::
				std::filesystem::path Path = std::filesystem::path("Images");
				if (std::filesystem::exists(Path)) {
					for (auto& File : std::filesystem::directory_iterator(Path))
					{
						if (ImGui::MenuItem(File.path().string().c_str())) {
							if (File.is_directory()) continue;
							ImageViewer* Image = new ImageViewer;
							Image->LoadFromFile(File.path().string().c_str());
						}
					}
				}
				
				ImGui::EndMenu();
			}			
			ImGui::EndMainMenuBar();
		}
		
		ImageViewer::DisplayAll();
		OpenGLContext::EndFrame();
	}

	OpenGLContext::Shutdown();
}
