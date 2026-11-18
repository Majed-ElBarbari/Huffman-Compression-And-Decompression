#include <bits/stdc++.h>
#include "h_const.h"
#include "h_file.h"
using namespace std;

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		cerr << "Not enough arguments!\n";
		exit(1);
	}
	else
	{
		if (argv[1][0] == '-')
		{
			switch (argv[1][1])
			{
			case 'h':
				cout << "This program can compress and decompress files using huffman code\n\n" <<
					"\tTo parse file(s):\t" << argv[0] << " [file(s)]\n" <<
					"\tTo compress file(s):\t"<< argv[0] << " -c [file(s)]\n" <<
					"\tTo decompress file(s):\t"<< argv[0] << " -d [file(s)]\n" <<
					"\tTo show this message:\t" << argv[0] << " -h\n\n" <<
					"(Parsing detects if file is compressed or not, and accordingly compress or decompress)\n\n";
			case 'c':
				for (int i = 2; i < argc; i++)
					h_file h = h_file(argv[i]);
					// 
				break;
			case 'd':
				for (int i = 2; i < argc; i++)
					h_file h = h_file(argv[i]);
					// 
				break;
			default:
				cerr << "Unknown option: '" << argv[1] << "'\n";
				return UNKNOWN_OPTION;
			}
		}
		else
		{
			for (int i = 1; i < argc; i++);
				// 
		}
	}
}
