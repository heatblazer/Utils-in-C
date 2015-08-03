#ifndef UTILS_H
#define UTILS_H
#define Utils _getUtils()

#define XORVER1

#ifdef __gnu_linux__
#include  <unistd.h> //for unlink
#include <fnmatch.h> //remove it later
#define copyOverwriteFile(FN, CR, INT_O) copyOverwriteFileWithCryptOption(FN, CR, INT_O);
#else
#endif

#include <stdio.h>
#include <time.h>

#define HASH_SIZE 127
/* unoversal swap macro */
#define SWAP(Typo, x1, x2) do { \
    Typo tm = x1; \
    x1 = x2; \
    x2 = tm; \
   } while (0); \

typedef void (*_crypt)(const char* key);
/*return a hashval */
unsigned int hash(const char*);
typedef unsigned int (*_hash)(const char*);

typedef void* (*_writeToFile)(const char* string, const char* fname, const char* opts );

typedef char* (*_getTimeString)();

typedef int (*_charCount)(const char* string, char delimiter);

typedef int (*_countNewLines)(FILE*);

typedef char* (*_strip)(const char*, char); //new added on 13.09.2014

typedef char* (*_unstrip)(const char*, char); //leave only delimiter

typedef int (*_matchChar)(const char* string, char matched);

typedef char (*_charAt)(const char*, int);

//char** split(const char* string, char delimiter, int size);
typedef char** (*_split)(const char* string, char delimiter, int size);

typedef int (*_getLengtToChar)(const char*, char);

typedef int (*_getCharIndex)(const char* string, char delimiter);

typedef char* (*_getStringFromTo)(const char* string, int from, int to);

typedef int (*_getNumberOfCharAtString)(const char* string, char delimiter);

typedef int* (*_fromCharToInt)(char*);

typedef void (*_copyFile)(const char* from, const char* to, int link);

typedef void* (*_copyOverwriteFileWithCryptOption)(const char*, char* , int );

typedef int (*_getFileSize)(const char*, const char*);
/* read a line by default by \n or by a delimiter */
typedef char* (*_readLine)(const char* line, char delimiter);

typedef char* (*_reverseString)(const char*);

typedef char* (*_getKey)(void);
#ifdef XORVER1
typedef char* (*_xorbuffer)(char*, const char*);
#else
typedef char* (*_xorbuffer)(char*, size_t, const char*, size_t);
#endif

/* special options */
typedef void* (*callbacks)(void*, void*); //universall call to XOR
/* new unction */
typedef void* (*_write_to_file_w_callback)
(const char* string, const char* fname, const char* opts, const char*,callbacks cbs);


typedef char* (*_replace)(char const* original, const char* patternOld, const char* patterNew);

typedef char* (*_read_file_to_buffer)(const char*, const char*);
struct  Utilz {
    _writeToFile writeToFile;
    _getTimeString getTimeString;
    _charCount charCount;
    _charAt charAt;
    _fromCharToInt fromCharToInt;
    _countNewLines countNewLines;
    _strip strip;
    _unstrip unstrip;
    _matchChar matchChar;
    _getCharIndex getCharIndex;
    _getFileSize getFileSize;
    _getNumberOfCharAtString getNumberOfCharAtString;
    _getStringFromTo getStringFromTo;
    _readLine readLine;
    _reverseString reverseString;
    _copyOverwriteFileWithCryptOption copyOverwriteFileWithCryptOption;
    _getKey getKey ;
    _xorbuffer XOR_buffer;
    _split split;
    _write_to_file_w_callback writeToFileWCallback;
    _read_file_to_buffer readFileToBuffer;
    _replace replace;
} ;

/*public function - clear heap */
int Utils_ClearHeap();


#ifdef __cplusplus
extern "C" {
#endif
struct Utilz _getUtils();
#ifdef __cplusplus
}
#endif

#endif // UTILS_H
