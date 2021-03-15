#pragma once
#include <filesystem>

class Binarymask final
{
public:
	Binarymask(const std::filesystem::path& SourceFile);

	std::vector<std::pair<int32_t, int32_t>> mask;


	inline static std::shared_ptr<Binarymask> DEFAULT_MASK = nullptr;
};

