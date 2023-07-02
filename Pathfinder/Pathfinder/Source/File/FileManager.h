#pragma once

#include <vector>

class FileManager
{
public:
	static FileManager& Instance();

	std::vector<char> ReadBinaryFile(const char* _fileName);

private:
	FileManager();
	~FileManager();

	FileManager(const FileManager&) = delete;
	FileManager(FileManager&&) = delete;
	void operator=(const FileManager&) = delete;
	void operator=(FileManager&&) = delete;
};