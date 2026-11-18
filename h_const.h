#ifndef H_CONST_H
#define H_CONST_H

// Return values
const int UNKNOWN_OPTION = 1;
const int BAD_FILE = 2;
const int OK_FILE = 3;
const int ALREADY_COMPRESSED = 4;
const int ALREADY_DECOMPRESSED = 5;
const int EMPTY_FILE = 6;

// Magic for compressed files
const char* MAGIC_BYTES = "\x0\x0MAJED\x0X\x0HUFF\x0\x0"; // free this?
const int MAGIC_SIZE = 16;

// Modes which determine what file should be done with
const int UNKNOWN_MODE = 90;
const int COMPRESSION_MODE = 91;
const int DECOMPRESSION_MODE = 92;

// Actual ASCII is 128, instead we use 256 in case of a non-ASCII
const int POSSIBLE_CHARS = 256;

// Memory sizes for readability when setting buffer size
const size_t KB = 1024;
const size_t MB = 1024*KB;
const size_t GB = 1024*MB;
const size_t MAX_BUFFER = 0.5*GB;

#endif
