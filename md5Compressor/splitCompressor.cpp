// md5Compressor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Compressor.h"
#include <iostream>
#include <string>


void explainD(std::string prog)
{
	std::cout << "Decompressor Usage: " << prog << "-d [input file A] [input file B] [output file]" << std::endl;
	std::cout << "Decompressed file will be automatically generated." << std::endl;

}

void explainC(std::string prog)
{
	std::cout << "Compressor Usage: " << prog << "-c [filename]" << std::endl;
	std::cout << "Compressed files will be automatically generated." << std::endl;
}


void processD(int argc, char** args)
{

	if (argc != 5)
	{
		explainD(std::string(args[0]));
		return;
	}

	std::string fileA(args[2]);
	std::string fileB(args[3]);
	std::string outputFile(args[4]);
	bool decompress = Compressor::DecompressFiles((char*)fileA.c_str(), (char*)fileB.c_str(), (char*)outputFile.c_str());
	if (decompress)
	{
		std::cout << "Decompression Successful!" << std::endl;
	}
	else
	{
		std::cout << "Decompression Failed!" << std::endl;
	}
}

void processC(int argc, char* args[])
{
	if (argc != 3)
	{
		explainC(std::string(args[0]));
		return;
	}

	std::string inFile(args[2]);
	std::string outA = inFile + ".001.comp";
	std::string outB = inFile + ".002.comp";
	bool compress = Compressor::CompressFile((char*)inFile.c_str(), (char*)outA.c_str(), (char*)outB.c_str());
	if (compress)
	{
		std::cout << "Compression Successful!" << std::endl;
	}
	else
	{
		std::cout << "Compression Failed!" << std::endl;
	}
}

int main(int argc, char* argv[])
{
	//Parse arguments

	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << "  -d/-c files (type -d or -c for explanations of each)";
		return 0;
	}
	
	if (argc >= 2)
	{
		if (strcmp(argv[1],"-d") == 0)
		{

			processD(argc, argv);
			return 0;
		}

		if (strcmp(argv[1], "-c") == 0)
		{
			processC(argc, argv);
			return 0;
		}
		std::cerr << "Usage: " << argv[0] << "-d/-c files (type -d or -c for explanations of each)";
		return 0;
	}
	int a = 1;
	std::cin >> a;
	return 0;
}

