#pragma once
#include <iostream>
#include <vector>

class BinaryFile
{
public:
	BinaryFile(char* filename);
	~BinaryFile();

	size_t GetFileSize();
	char GetCharAt(size_t index);
	size_t FindChar(size_t startFrom, char value);
	std::vector<char> GetChunk(size_t start, size_t size);
	bool IsIndexValid(size_t);

private:
	std::vector<char> bytes;
	char* fileData;
	size_t fileSize = 0;
	//Private Methods
	
};

