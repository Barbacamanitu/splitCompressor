#include "stdafx.h"
#include "Compressor.h"
#include <fstream>
Compressor::Compressor()
{
}


Compressor::~Compressor()
{
}

bool Compressor::DecompressFiles(char* inputA, char* inputB, char* output)
{
	BinaryFile a(inputA);
	BinaryFile b(inputB);

	BinaryFile * firstFile = nullptr;
	BinaryFile * secondFile = nullptr;

	int counter = 0;
	if (IsFileFirst(a))
	{
		firstFile = &a;
		secondFile = &b;
		counter++;
	}
	if (IsFileFirst(b))
	{
		counter++;
		firstFile = &b;
		secondFile = &a;
	}

	//Counter should be exactly 1. If it isn't, the files were unable to be decompressed.

	if (counter != 1)
	{
		return false;
	}

	//Now join the files, and add in the missing char!
	std::vector<char> newFile;
	std::vector<char> aF = firstFile->GetChunk(0, firstFile->GetFileSize());
	std::vector<char> bF = secondFile->GetChunk(0, secondFile->GetFileSize());

	newFile.insert(newFile.begin(), aF.begin(), aF.end());
	newFile.push_back(0);
	newFile.insert(newFile.end(), bF.begin(), bF.end());


	std::ofstream outFile(output, std::ios::binary);
	outFile.write((char*)&newFile[0], newFile.size());
	outFile.close();
}

bool Compressor::IsFileFirst(BinaryFile & b)
{
	char f = b.GetCharAt(0);
	char l = b.GetCharAt(b.GetFileSize()-1);
	return (f == l);
}


bool Compressor::CompressFile(char* input, char* outputA, char* outputB)
{
	size_t currentIndex = 0;

	BinaryFile inputFile(input);


	size_t firstPair = GetFirstPair(inputFile,0,currentIndex);

	if (firstPair <= 0)
	{
		return false;
	}

	SplitFile(inputFile,firstPair,outputA,outputB);
	return true;
}


size_t Compressor::GetNextOccurence(BinaryFile & file, char value, size_t& startFrom)
{
	if (startFrom < 0 || startFrom >= file.GetFileSize() - 1)
	{
		return -1;
	}
	size_t index = file.FindChar(startFrom, value);
	startFrom = index + 1;
	return index;
}

void Compressor::SplitFile(BinaryFile &  file, size_t location, char* fileA, char* fileB)
{

	//Location is the index of the pair. Go to the one before the index, and the one after.

	size_t chunkA_start = 0;
	size_t chunkA_size = location;
	size_t chunkB_start = location + 1;
	size_t chunkB_size = file.GetFileSize() - chunkB_start;
	std::vector<char> chunkA = file.GetChunk(chunkA_start, chunkA_size);
	std::vector<char> chunkB = file.GetChunk(chunkB_start, chunkB_size);




	std::ofstream aF(fileA, std::ios::binary);
	std::ofstream bF(fileB, std::ios::binary);
	aF.write((char*)&chunkA[0], chunkA.size());
	bF.write((char*)&chunkB[0], chunkB.size());
	aF.close();
	bF.close();

}


size_t Compressor::GetFirstPair(BinaryFile & file, char value,size_t & currentIndex)
{
	size_t fileSize = file.GetFileSize();
	char lastChar = file.GetCharAt(fileSize-1);
	char firstChar = file.GetCharAt(0);
	while (currentIndex < fileSize - 1)
	{
		size_t next = GetNextOccurence(file, value, currentIndex);
		if (next <= 0)
		{
			return -1;
		}

		size_t before = next - 1;
		size_t after = next + 1;

		 
		if (!file.IsIndexValid(before) || !file.IsIndexValid(after))
		{
			continue;
		}

		char befChar = file.GetCharAt(before);
		char afterChar = file.GetCharAt(after);

		if (befChar == firstChar)
		{
			if (afterChar != lastChar)
			{
				return next;
			}
			else

			{
				//Almost missed one.
				//Let algorithm keep going.
			}
			//Make sure only the FIRST half has matching first and last characters.		
			//This ensures proper decompression is possible.
		}
	}
	return -1;
}

