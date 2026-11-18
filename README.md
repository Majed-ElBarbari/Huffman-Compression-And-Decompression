# Huffman Compression And Decompression
## What is this project?
This project offers a program that compresses files using Huffman code, as well as decompress files created in such way.\
Currently it is a W.I.P. and at this level just builds the Huffman tree and transverse it to find code for each symbol, and it prints a list of codes which I found to be correct (Sometimes it would differ from expected slightly but only in order, but the length of each code is completely correct, which is what is most important).

## Why does this project exist?
This project is made for a course of data structures using C++.

Needless to say this program cannot be compared with more advanced methods of lossless compression like LZ (or its variants like LZ77, which is what is used by gzip) which reduce files more than a plain Huffman algorithm as it does not go on a char by char basis.\
Of course it is even less related to other lossless compression algorithms like arithmetic compression, which uses a completely different idea than previously mentioned, or any lossy compression method.

This project is mostly to learn more about these ideas:
    - Data compression
    - Data structures
    - File IO
    - Memory management in C/C++

You can notice in code that almost no features of C++ is used and most of this project, not even strings or classes, and it could be easily transferred to C with some minor changes. This is limitation is by choice and it is to allow me to think more of how each data structure is implemented.\
Why not write it in C? Good question! No reason, I actually might do this in a later point of time and try seeing how much the code differs, and I might also see how the code would look if C++ features are used.

# Use of AI/LLMs
Note: No LLM/AI was used to write or read or review any code, and as much as possible avoided in searching and a list of references is seen, maybe only once used LLM to search something but I even later reviewed by searching it myself.

## To do list
### Phases of this project

1. Compression
    - Currently I want to make a decision between rewriting code to follow canonical Huffman code, or continue
    - I want to find solution to edge cases where input file includes chars not in ASCII (i.e. first bit is 1 not 0) which are currently ignored. I think wchar may fix this (?), if not an easy fix for now I will consider assuming all files are ASCII and change `POSSIBLE_CHARS` const to 128 not 256.
    - Also deal with files including EOF, this is an issue as I made the head to be EOF, maybe I could instead have a bool or a function to tell if a node in tree is a leaf or not (both children are null). A segmentation fault occurs for some reason when an EOF is entered.
    - Actually create an ofstream which would be the decompressed file, it should include metadata like the `MAGIC_BYTES` and the code book (how it is stored would depend if I make the code canonical or not)
    - Is 0.5GB too much RAM to take for buffering file?
2. Decompression
    - Write different function to read the decompressed file (this will depend on how the final compressed file implementation is)
3. Application
    - I am thinking of looking into an application of compression that studies language tree, this was made as a scientific research in 2002 I believe. A video made by 3Blue1Brown mentions it. I would like to see how it compares with results of the research, and see if a simpler compression like mine has any impact on the results. This will be done at a stage where the program is completely capable of compression and decompression with actual output.
    - Might try to see if there are any other applications like this. 
