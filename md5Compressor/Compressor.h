#pragma once
#include "BinaryFile.h"
class Compressor
{
public:
	Compressor();
	~Compressor();

	static bool CompressFile(char* input, char* outputA, char* outputB);
	static bool DecompressFiles(char* inputA, char* inputB, char* output);

private:
	static bool IsFileFirst(BinaryFile & b);
	static size_t GetFirstPair(BinaryFile & file, char value,size_t &currentIndex);
	static size_t GetNextOccurence(BinaryFile & file, char value, size_t& startFrom);
	static void SplitFile(BinaryFile &  file, size_t location, char* fileA, char* fileB);


};

