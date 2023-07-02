#include "FileManager.h"
#include <fstream>

FileManager::FileManager()
{}

FileManager::~FileManager()
{}

FileManager& FileManager::Instance()
{
	static FileManager s_FileManager{};
	return s_FileManager;
}

std::vector<char> FileManager::ReadBinaryFile(const char* _filePath)
{
	std::ifstream inputFile(_filePath, std::ios::binary | std::ios::ate);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("ERROR: Failed to read binary file");
	}

	const size_t fileSize = static_cast<size_t>(inputFile.tellg());
	std::vector<char> buffer(fileSize);

	inputFile.seekg(0);
	inputFile.read(buffer.data(), fileSize);
	inputFile.close();

	return buffer;
}