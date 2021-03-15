
#include "BinaryMask.h"

#include <fstream>
#include <iostream>
#include <string>

Binarymask::Binarymask(const std::filesystem::path& SourceFile)
{
	std::ifstream Input(SourceFile);

	if (!Input) return;

	int XPos = 0;
	int YPos = 0;

	int CenterX = 0;
	int CenterY = 0;
	
	char CurrentChar;

	std::cout << "import mask" << std::endl;
	
	while (Input.read(&CurrentChar, 1))
	{
		XPos += 1;

		if (CurrentChar == '\n')
		{
			XPos = 0;
			YPos++;
			continue;
		}
		int CharValue = std::atoi(std::to_string(CurrentChar).c_str());
		
		if (CharValue & 0x2)
		{
			CenterX = XPos;
			CenterY = YPos;

			std::cout << "center : " << CenterX << " : " << CenterY << std::endl;
			
		}

		if ((CharValue & 0x1) == 1)
		{
			mask.push_back({ XPos,YPos });
		}		
	}

	for (auto& elem : mask)
	{
		elem.first -= CenterX;
		elem.second -= CenterY;


		std::cout << elem.first << " x " << elem.second << std::endl;
		
	}
		
	Input.close();	
}
