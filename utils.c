#include "utils.h"
#include "LOGFILES.h"
#include "DList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* help for the log files - K&R Приложение А. - кратък наръчник */

#define mycat(x, y) "\"" #x #y "\""
#define myXcat(x,y) mycat(x,y)


#ifdef __gnu_linux__
#include <unistd.h>
#include <fcntl.h>
#endif
#define XORVER1
#define PRESERVE_HEADER //needed to save the first 3 bytes of the header

/*[TODO] must implement as DList */
#define HSIZE 512000
static char* myHeap[HSIZE];  //DList here!
static int hIterator = 0;

#define XORDBG
#define BUFFSIZE1 1

static char* line = "---------------------------------\n";

static int fsize =0 ;  //Stack for calls to fsize


static inline void privateSetFileSize(int fs) {
    fsize = fs;
}
static inline int privateGetFileSize(void) {
    return fsize;
}

/* STATICS SECTION */
/* IMPORTANT CRYPTED TEST FILES WITH THIS KEY! DO NOT FORGET*/
static char* cryptKey = "abc123";

/* TODO - add it to H file */
static inline void setKey(const char* k) {
    cryptKey = k;
}

static inline char* getKey(void) {
    return cryptKey;
}

//static int* _cryptKey = fromCharToInt("abc123");
//TODO create key for the program and free it after
/* END OF STATIC SECTION */
static  inline int charCount(const char* string, char delimiter) {
    int occs=0;
    while ( *string ) {
        if ( *string == delimiter) occs++;
        string++;
    }
    return occs;
}

static inline void* writeToFile(const char* string, const char* fname, const char* opts) {
    FILE* fp = fopen(fname, opts);
    if ( !fp ) return NULL;
	int lfsize = privateGetFileSize() <= 0 ? strlen(string) : privateGetFileSize();

    int i=0;
    while ( i < lfsize ) {
        fputc(string[i++], fp);
    }
    fclose(fp);
}

static inline void* writeToFileWCallback
(const char* string, const char* fname, const char* opts, const char* key, callbacks cbs) {

    FILE* fp = fopen(fname, opts);
    if ( !fp ) return NULL;
    /* TODO FIX */
    fclose(fp);
}


unsigned int hash(const char *s) {
    unsigned int retval=0;
    while ( *s ) {
        retval = *s+31*retval;
        s++;
    }
    return retval % HASH_SIZE;
}

static  inline char charAt(const char *s, int i) {
    if ( i >= strlen(s) ) return -1;
    else {
        return s[i];
    }
}

static  inline int countNewLines(FILE* fp) {
    char nl ;
    int occs = 0;
    while ( (nl = fgetc(fp)) != EOF ) {
        if ( nl == '\n') occs++;
    }
    printf("NEWLINES: %d \n", occs);
    rewind(fp);
    return occs;
}
/* strips any delimiter character from a string then return a new string */
static inline char*  strip(const char* str, char delimiter) {
    char* newstr = (char*) malloc(sizeof(char) * strlen(str)+1);
    myHeap[hIterator++] = newstr;
    char* begin = newstr;
    while ( *str ) {
      if ( *str == delimiter ) {
          str++;
          continue;
      }
      *newstr++ = *str++;
    }
    *newstr++ = 0;
    return begin;
}

static inline char* unstrip(const char *str, char delimiter) {
    char* newstr = (char*) malloc(sizeof(char) *
                                  charCount(str, delimiter)+1);
    myHeap[hIterator++] = newstr;

    char* begin = newstr;
    do {
        if ( *str++ == delimiter ) *newstr++ = delimiter;
    } while ( *str != '\0' );
    *newstr++ = '\0';
    return begin;
}

/* [1]copy of C header strlen with option to get lenght to a delimiter */
static inline int getLengthToChar(const char* string, char delimiter) {
    int len=0;
    while ( *string++ != delimiter) len++;
    return len;
}
/* [2]cuts a string from to and returns a copy that
 * must be freed on terminate
 * */

static  inline char* getStringFromTo(const char *string, int from, int to) {
    // better check - if to > from and if to is > length of str - terminate
    if ( (from > to) ||
         getLengthToChar(string, '\0') < to ) return NULL;
    char* retstring = (char*) malloc(sizeof(char) * (to-from)+1);
    myHeap[hIterator++] = retstring;

    char* begin = retstring;
    int sizer = to-from;
    const char* sourceBegin = &string[from];
    while ( sizer-- > 0 ) {
       *retstring++ = *sourceBegin++;
    }
    /*
    while ( (*retstring++ = *sourceBegin++)  != delimiter ) ; */
    *retstring++ = '\0';
    return begin;
}

/* [3]returns the index the char is first met in the string */
static  inline int getCharIndex(const char *string, char delimiter) {
    int begin = 0;
    do {
        if ( *string == '\0') return -1; //no delimiter found in string
        if ( *string == delimiter ) break;
        else begin++;
    } while ( *string++ );
    return begin;
}


static  inline int matchChar(const char *string, char matched) {
    int n = 0;
    while ( *string++ ) {
        if ( *string == matched ) n++;
    }
    if (strlen(string) == n) return 0;
    return n;
}

/*[4] this returns 2 arrays of strings splitted by delimiter,
 * delimiter itself is not returned */
/* TODO */
//customize logic to return N elements splitted
//TODO rework logics
// [1] count occs of delimiter
// [2] alloc char** of occs-1 size
// [3] start to walk:
// [3.1] begin - 1st occ
// [3.2] 1st occ - 2nd occ
// [3.3] 2nd occ -3rd occ etc.
// return the splts

/*[SPLIT] */
static inline char** split(const char* string, char delimiter, int size) {

    const char* beginStr = string;
    int* indexes = (int*)malloc(sizeof(int)*strlen(string));
    myHeap[hIterator++] = (char*) indexes;

    char** splitStrings =
            (char**) malloc(sizeof(char*) * charCount(string, delimiter)+1);

    int from, to, i,j ;
    from=to=i=j=0;
    int matches=0;
    while ( string[j++] != '\0') {
        if ( string[j] == delimiter ) {
            indexes[matches++] = j;
        }
    }
    if ( matches < 0 ) return 0x00;
    if ( matches == 1 ) {
        splitStrings[0] = Utils.getStringFromTo(beginStr, 0, indexes[0]);
        myHeap[hIterator] = splitStrings[0];
        return splitStrings;
    }
    i = 0;
    from = 0;
    to = indexes[0];
    while ( i < matches ) {
        to = indexes[i];
        splitStrings[i] = Utils.getStringFromTo(beginStr, from, to);
        myHeap[hIterator] = splitStrings[i++];
        from = to+1;
    }
    return splitStrings;
}

/*[5] get occurencies of a char in string */
static  inline int getNumberOfCharAtString(const char *string, char delimiter) {
    int occs=0;
    do {
        if ( *string == delimiter) occs++;
    } while (*string++);
    return occs;
    /*note to be used for bigger split and creating a huge 2d array */
}
/* optional not part of utils.h*/

//[6] copy file
static inline void copyFile(const char* from, const char* to, int link) {
    FILE* fp = fopen(from, "r");
    FILE* ft = fopen(to, "w");
    if ( !ft || !fp) return;
    else {
        char cp;
        while ( 1 ) {
            if ( feof(fp)) break;
            cp = fgetc(fp);
            fputc(cp, ft);
        }
        printf("#### file copied suxass\n");

       if ( link > 0 ) unlink(from);
    }
    fclose(fp); fclose(ft);
}

static  inline int* fromCharToInt(char* carr) {
    int* arr = (int*) malloc(sizeof(int) * strlen(carr));
    myHeap[hIterator++] = (char*) arr;
    int *begin = arr;
    while ( *arr++ = *carr++ ) ;
    return begin;
}

/*[TODO] Must implement private stack to push/pop latest */


static inline char* XOR_buffer(const char* d,const char* k) {
    int stringl= fsize <= 0 ? strlen(d) : fsize;
    const int klen = strlen(k);
    printf("### len is %d\n", stringl);
    char* privateXorBuff = (char*) malloc(sizeof(char)* stringl+1);
    char* begin = privateXorBuff;
    myHeap[hIterator++] = privateXorBuff;
    int i; char c;
    for (i=0; i < stringl; i++) {
#ifdef PRESERVE_HEADER
        if (i==0 || i==1 || i==2) c = d[i];
#endif
        c = d[i] ^ k[i%klen];
       if ( c == '\0' ) c ^= k[i%klen];
        privateXorBuff[i] = c;
    }
    privateXorBuff[i++]=0;
    return begin;
}

static inline char* XOR_buffer2(char* d, size_t sl1, const char* k, size_t sl2) {
    const int stringl = sl1;
    const int klen = sl2;
    char* begin=d;
    int i;
    char c;
    for(i=0; i < stringl; i++) {
        if ( (d[i] ^ k[i%klen] == '\0') ) d[i] ^= k[i%klen];
        d[i] ^= k[i%klen];
    }
    return d;
}


#ifdef __gnu_linux__
static  inline void* copyOverwriteFileWithCryptOption(const char* fname, char* key, int tocrypt) {
    printf("%s", line);
    printf("called copyOverwriteFileWithCryptOpt() on %s\n", fname);
    int len = strlen(key);
    int i =0;
 //[11]   int size= getFileSize(fname, "r");
 //[12]   printf("Size is %d bytes. \n", size);
//    char* ch = (char*) malloc(sizeof(char) * BUFFSIZE1);
    char ch[1];
    char name[1024] = "";
    strcat(name, fname);
    strcat(name, "~");
    name[strlen(name)+1] = '\0';
#ifdef __gnu_linux__
    int f1 ;
    int f2 ;
    char c;
    if ( !(f1 = open(fname, O_RDONLY, 0)) ) exit(1);
    if ( !( f2 = creat(name, 0666) ) ) exit(1) ;
    int n;
    while ( (n = read(f1, ch, 1)) > 0 ) {
       ch[0] ^= cryptKey[i++%len];
       write(f2, ch , n);
    }
    unlink(fname);
    if ( !(f2 = open(name, O_RDONLY, 0)) ) exit(1);
    if ( !(f1 = creat(fname, 0666) ) ) exit(1);
    while ( (n = read(f2, ch, 1)) > 0) {
        write(f1, ch, n);
    }
    unlink(name);
    writeToFile("[UNIX] call to copyOverwriteFile()", LOG_getLogName(NORMAL), "a+");
#else
    FILE* f1 = fopen(fname, "r");
    FILE* f2 = fopen(name, "w");
    /* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
    /* damn :( */
    if ( f1 == NULL || f2 == NULL ) {
        writeToFile("[utils] could not open file to read or write",
                    LOG_getLogName(ERRORR), "a+");
    } else {
        char ch;
        char crypted;
        while ( (ch=fgetc(f1)) != EOF ) {
            crypted = ch ^ cryptKey[i++%len];
            fputc(crypted, f2);
        }
        remove(f1);
        fclose(f1); fclose(f2);
        fopen(f1, "w"); fopen(f2, "r");
        while ( (ch=fgetc(f2) != EOF)) {
            fputc(ch, f1);
        }
        remove(f2);
        fclose(f1); fclose(f2);
        writeToFile("[WIN32] call to copyOverwriteFile()",
                    LOG_getLogName(OTHER), "a+");
    } //endif
#endif
}
#else
static inline void* copyOverwriteFileWithCryptOption(const char* fname, char* key, int tocrypt) {
    printf("Not on UNIX OS - implement later\n");
    exit(1);
}
#endif

static inline char* getTimeString() {
    time_t raw_time;
    struct tm* timeinfo;
    time(&raw_time);
    timeinfo = localtime(&raw_time);
    return asctime(timeinfo);
}


static  inline int getFileSize(const char *fname, const char* mode) {
    FILE* fp = fopen(fname, mode);
    int fs=0;
    while ( 1 ) {
        char c = getc(fp);
        if ( feof(fp ) ) break;
        fs++;
    }
    fclose(fp);
    return fs;
}


static inline char* readLine(const char *line, char delimiter) {
    char* newstr = (char*)malloc(sizeof(char*) * strlen(line)+1);
    myHeap[hIterator++] = newstr;
    char* begin = newstr;
    while ( (*newstr++ = *line++) != delimiter ) {
        if ( *line == '\0') {
            free(newstr);
            return 0x00;
        }
    }
    *newstr++ = '\0';
    return begin;
}


static inline char* reverseString(const char* str) {
    char* news = (char*) malloc(strlen(str)+1);
    myHeap[hIterator++] = news;
    char* newBeg = news;
    const char* end = &str[strlen(str)-1];

    while ( end >= str) {
        *news++ = *end--;
    }
    *news++ = '\0';
    return newBeg;
}

#define READFILETOBUFF_VER1
static inline char* readFileToBuffer(const char* fname, const char* opts) {
    FILE* fp = fopen(fname, opts);
    if ( !fp ) return 0x00;
    fseek(fp, 0, SEEK_END);
    privateSetFileSize(ftell(fp));
    if ( privateGetFileSize() <= 0 ) return 0x00;

    char *buff = (char*) malloc((sizeof(char)* privateGetFileSize()));
    char* begin= buff;
    myHeap[hIterator++] =  buff;
    fseek(fp, 0, SEEK_SET);
    int i=0;
#ifdef READFILETOBUFF_VER1
    for (; i < privateGetFileSize(); i++) buff[i] = fgetc(fp);
#else
    fread(buff, fsize, 1, fp);
#endif
    buff[i]=0;
    fclose(fp);
    return begin;
}

static inline void privateCopy(char* to, char* from) {
   // printf("#[1]dbg entry privateCopy()");
    if ( strlen(to) != strlen(from)) return;
    int len = strlen(from);
    int i =0;
    while ( i < len) {
        to[i] = from[i];
        i++;
    }
   // printf("#[2]dbg end privateCopy() %s \n", to);

}

static inline void privatePlaceStringFromTo(char* src, const char* data,
                                            int beginoffset, int endoffset) {
  //  printf("#[1]dbg end privatePlaceStringFromTo()");
    int i=beginoffset;
    int j=endoffset;
    while ( i < j ) {
        src[i] = data[i];
        i++;
    }
    printf("#[2]dbg end privatePlaceStringFromTo()%s\n", src);

}

/* this function will use aux functions getSlice() and  getFromTo() */
static inline char* privateGetSlice(const char* str, int begin, int offset) {

    char* tmp = (char*) malloc(sizeof(char)*offset);
    char* beg = tmp; //optional
    int i,j;
    i=begin;
    for(j=0; j < offset; j++, i++) tmp[j] = str[i];
    tmp[j]=0; // IMPORTANT!!!
    return beg;
} //end slice

static inline char* privateGetFromTo(const char* str, int beginOff, int endOff) {
    if ( beginOff > endOff) return 0x00;
    char *tmp = (char*)malloc(sizeof(char)* endOff);
    myHeap[hIterator++] = tmp;
    char* begin = tmp;
    int i=beginOff;
    int j=0;
    while ( j <= endOff ) {
        tmp[j++] = str[i++];
    }
    tmp[j]=0;
    return begin;
}

/* Aux replace if 1:1 chars */
static inline char* aux_replace(const char* original, char pat, char newpat) {
    printf("## using aux_replace()\n");
    int osize   = strlen(original);
    char* retbuff, head;
    retbuff = (char*) malloc(sizeof(char)* osize+1);
    myHeap[hIterator++] = head = retbuff;
    int i=0;
    while ( (*retbuff++ = *original++) != 0 );
    while ( i < osize ) {
        if ( retbuff[i] == pat ) retbuff[i] = newpat;
        i++;
    }
    retbuff[i]=0;
    return head;
}

static inline char* replace(const char*  original, const char* oldPattern, const char* newPattern) {
    /* I`ll add more readability to understand the algorithm */
    int originalLength  = strlen(original);
    int oldPatternLen   = strlen(oldPattern);
    int newPatternLen   = strlen(newPattern);

    int i;
    char* newbuffer= 0x00; /* the returning buffer */

    int additionalBytes = newPatternLen ; /* allocate more buffers after the loop */

    for(i=0; i < originalLength; i++) {
        /* memory safe due to the heap */
        char* tmp = privateGetSlice(original, i, oldPatternLen) ;
        if ( strcmp(oldPattern, tmp) == 0 ) {
            additionalBytes += newPatternLen; /* prepare the buffer for the new strings */
        }
    } // end for 1()
        int newLength = originalLength + ( additionalBytes*2); /* reserve more memory just in case*/
    printf("#### oroginal len %d\n", originalLength);
    printf("Allocated %d bytes for new\n", newLength);


    newbuffer = (char*) malloc(sizeof(char)* newLength);
    char* beginbuff = newbuffer;
    int j;

    /* the for loop with the algorithm */
    for (i=0, j=0; i < originalLength; j++, i++) {
        char* tmp = privateGetSlice(original, i, oldPatternLen);
        if ( strcmp(tmp, oldPattern) == 0) {
            int auxi;
            for (auxi=0; auxi < newPatternLen; auxi++) {
                newbuffer[j++] = privateGetSlice(newPattern, auxi, 1)[0]; /* this is ugly code*/
            }
            i= i+oldPatternLen; /* this is needed to move to next unchecked
                                 in the old buffer */
        }
        newbuffer[j] = privateGetSlice(original, i, 1)[0]; /* get the first char form the sliced
                                                      string */
    }    // END for 2
    newbuffer[i]='\0';
    return beginbuff;

} // END REPLACE

/* test passed - will lost bytes from crypt key */
//////////////////////////////////////////////////////////////////////////////////
/*
int main(int argc, char** argv) {
   // char* empty;
   // split("somefoo:barshitz", ':', 10);
   // getStringFromTo("some ofofoff", 1,2);
   // printf("%d is index of %c \n", getCharIndex("someffooo", ':'), ':');
   // char **splitz = split("this will be:splitted hard", ':',2312);
   // printf("%s SPLITED %s\n", splitz[0], splitz[1]);
    FILE* fp = fopen("Log.txt", "r");
    char line[256];
    while ( ( fgets(line, sizeof(line), fp) ) ) {
        fprintf(stdout, "%s", readLine(line, '\n'));
    }
} */
///////////////////////////////////////////////////////////////////////////////////


static struct Utilz __U  = {
        writeToFile,
        getTimeString,
        charCount,
        charAt,
        fromCharToInt,
        countNewLines,
        strip,
        unstrip,
        matchChar,
        getCharIndex,
        getFileSize,
        getNumberOfCharAtString,
        getStringFromTo,
        readLine,
        reverseString,
        copyOverwriteFileWithCryptOption,
        getKey,
        XOR_buffer,
        split,                      /* added 10.01.2015 */
        writeToFileWCallback,       /* added 12.01.2015 */
        readFileToBuffer,           /* added 13.01.2015 */
        replace                     /*  added 15.01.2015 */
    };


struct Utilz _getUtils() {
    return __U;
}

/* test unit */
/*
int main(void ) {

}*/


int Utils_ClearHeap()
{
    /* this will be returned from the main
     * in user implementation this myst be called
     * from the last constructor call or
     * at the end of the program
     * */
    int i;
    for (i=0; i < hIterator; i++) {

        printf("%p occupined\n", myHeap[i]);
        free(myHeap[i]);

    }
    return 0;
}
