#include "stdafx.h"
#include "BinaryFile.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
BinaryFile::BinaryFile(char* filename)
{
	std::ifstream inFile(filename, std::ios::in | std::ios::binary | std::ios::ate);
	//File Opened. Read file into buffer
	fileSize = inFile.tellg();
	//inFile.close();
	bytes.resize(fileSize);
	inFile.seekg(std::ios::beg);
	inFile.read(&bytes[0], fileSize);

	inFile.close();
}


size_t BinaryFile::FindChar(size_t startFrom, char value)
{
	auto it = std::find(bytes.begin() + startFrom, bytes.end() - 1, value);
	if (it == bytes.end())
	{
		return -1;
	}
	size_t index = it - bytes.begin();
	return index;
}


std::vector<char> BinaryFile::GetChunk(size_t start, size_t size)
{
	if (start < 0)
	{
		throw std::out_of_range("Start index is less than 0.");
	}
	if (start + size > GetFileSize())
	{
		throw std::out_of_range("End index is out of bounds");
	}
	if (size <= 0)
	{
		throw std::out_of_range("Size less than 0");
	}
	std::vector<char> chunk;
	chunk.insert(chunk.begin(), bytes.begin() + start, bytes.begin() + start + size);
	return chunk;
}

size_t BinaryFile::GetFileSize()
{
	return bytes.size();
}

bool BinaryFile::IsIndexValid(size_t index)
{
	return (index >= 0 && index < fileSize);
}

char BinaryFile::GetCharAt(size_t index)
{
	if (index < 0 || index >= GetFileSize())
	{
		throw std::out_of_range("Index out of range of file");
	}

	return bytes[index];
}


BinaryFile::~BinaryFile()
{
	bytes.clear();
}
