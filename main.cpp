extern "C" {
#include "utils.h"
#include "DList.h"
#include "LOGFILES.h"
}
#include <stdio.h>
#include <QApplication>
#include <QTextEdit>
#include <QVBoxLayout>


//#define MY_QTDBG
#define DBG4

#define LOOPSIZE 1000000
#define TESTFILE "/home/ilian/QT5/UtilitiesinC/testfile"
char* striput(const char*, char);
char* striput(const char* str, char delimiter) {
                  char* newstr = (char*) malloc(sizeof(char) * strlen(str)+1);
                  char* begin = newstr;
                  do {

                    if ( *str == delimiter ) {
                        str++;
                    }
                  } while ( *newstr++  = *str++ );
                  return begin;
              }
int main(int argc, char** argv)
{
#ifdef DBG1
    const char* str1 = "Some really big big string to be splitet by whitespaces";
    fprintf(stdout, "Demo1: strip()\n[%s]\n[result]:%s\n",
            str1, Utils.strip(str1, ' '));

    fprintf(stdout, "Demo2: getTimeString()\n%s\n", Utils.getTimeString());

    const char* str2 = "THis is some /home/ilian/directories/to/whatever/ and I expect 6 slashes";
    fprintf(stdout, "Demo3: unstrip() leave only delimiters for string %s\nResult:[%s]\n",
            str2, Utils.unstrip(str2, '/'));

    const char* str3 = "Some completely random string with some bla bla bla";
    fprintf(stdout, "Demo4: charAt()\nGet some random chars from %s\nresult[2][%c]\n[22][%c]\n[999][%c]\n[12][%c]\n",
            str3, Utils.charAt(str3, 2), Utils.charAt(str3, 22),
            Utils.charAt(str3,999), Utils.charAt(str3, 12));

    const char* str4 = "Looooooooooooooooooooong string";
    fprintf(stdout, "Demo5: getCharsInStr()\nShow the number of char %c in %s\n#:%d\n",
            'o', str4, Utils.getNumberOfCharAtString(str4, 'o'));

    const char* line = "This is  some line with \t tabs \n and newnewlines";
    fprintf(stdout, "Demo6: readLineByDelimiter()\nReads a line by delimiter.(Not only newlines)\nString:%s\nLine:%s",
            line, Utils.readLine(line, '\n'));

    const char* str5 = "Now is the time for all good men to come and their party(with newline at end)\n";
    fprintf(stdout, "Demo7: reverseStrring()\nReverse the string:%s\nResult:[%s]\n",
            str5, Utils.reverseString(str5));

    char *buffer1 = "Some string to xor";
    const char* k = "abc";
    fprintf(stdout,"Demo 8 XOR: %s before\n", buffer1 );
    buffer1 = Utils.XOR_buffer(buffer1, k);
    fprintf(stdout,"Demo 8 XOR: %s after\n", buffer1 );
    buffer1 = Utils.XOR_buffer(buffer1, "abc");
    fprintf(stdout,"Demo 8 XOR: %s restore\n", buffer1 );

    fprintf(stdout, "Demo 9 get slice of a string\n %s slice from %d to %d\n%s slice\n",
            "Some big big shittty string", 5,10,
            Utils.getStringFromTo("Some big big shittty string",5,10));
    return 0;

#elif defined (DBG2)
    FILE* fp = fopen(TESTFILE, "w");
    if ( ! fp ) return;
    time_t stime;
    time_t etime;
    time(&stime);
    int loop=LOOPSIZE;
    while ( loop-- > 0 ) {
        fprintf(fp,"%s\n",Utils.strip("bla bla bla bla",' '));
    }
    time(&etime);
    printf("Time elapsed %d\n", etime-stime);
    fclose(fp);

#elif defined (DBG3)
    LOG_setNorm("/home/ilian/blablabla1");
    LOG_setErr("/home/ilian/blablabla2");
    LOG_setOther("/home/ilian/blablabla3");

    Utils.writeToFile("Blalalalal",LOG_getLogName(1),"w");
#elif defined (DBG4)
    /* UPdated - now have a working split */

    char *buf = "Now is the time for all good men to came and aid their party\nThe quick brown fox jumpped iver the lazy dog\
                sasdasdsadsds \nasdasd  OOOOOOOOOOOOOOOOOOOOpppp ooooooooooooooooo \
                hereeee wwwww goooo long one looong and\n\n\n\n\t many many testing garbage strings\
                11111111111111111112222222222222 \t\b\n";
    printf("\n\nBEFORE XOR:%s\n\n", buf);
    buf = Utils.XOR_buffer(buf, "abc");
    printf("\n\nAFTER XOR:%s\n\n", buf);
    buf = Utils.XOR_buffer(buf, "abc");
    printf("\n\nAGAIN XOR:%s\n\n", buf);

    char *readfile = Utils.readFileToBuffer("/home/ilian/Downloads/test.html", "rb");

    Utils.writeToFile(Utils.replace(readfile, "a","BBB"),"/home/ilian/t.html", "w");

    Utils_ClearHeap();


//[1]    char* readbuff = Utils.readFileToBuffer("/home/ilian/testcopy.mkv", "rb");

//[2]    char* newbuff = Utils.XOR_buffer(readbuff, "abc");
//[3]    char* dexor = Utils.XOR_buffer(newbuff, "abc");

//[4]    Utils.writeToFile(newbuff, "/home/ilian/test1.mkv", "wb");

#elif defined MY_QTDBG


        QApplication a(argc, argv);
        QWidget qwd;

        QTextEdit te;
        QVBoxLayout qvb;
        te.append(QString("Ilian C Utils Demo"));
        te.append("-----------------------------");
        te.append("1.Strip a delimiter from a buffer");
        te.append("Some foo bar shitz");
        te.append(Utils.strip("Some foo bar shitz", ' '));
        te.append("-----------------------------");

        te.append("2.Get a char at index");
        te.append("Show the 3rd char");
        te.append(QString(QChar(Utils.charAt("Show the 3rd char", 2))));
        te.append("-----------------------------");

        te.append("3. Unstrip by a delimiter");
        te.append("/home/ilian/downloads/sth/ ( expect 5 slashes)");
        te.append(Utils.unstrip(" /home/ilian/downloads/sth/ ( expect 5 slashes)", '/'));
        te.append("-----------------------------");

        te.append("4.Reverse this string");
        te.append(Utils.reverseString("Reverse this string"));
        te.append("-----------------------------");


        te.append("5.Show C time string");
        te.append(Utils.getTimeString());
        te.append("-----------------------------");


        char* buffer = "The quick brown fox jumped over the lazy dog\nand now is the time for all good men to came to aid their party";
        te.append("6.XOR char buffer");
        buffer = Utils.XOR_buffer(buffer, "abc");
        buffer = Utils.XOR_buffer(buffer, "abc");

        te.append(buffer);
        te.append("-----------------------------");


        te.append("7.Get part of string from index to index");
        te.append(Utils.getStringFromTo("Some long long string randomly cut",
                                        7, 22));
        te.append("-----------------------------");

        te.append("8.Read by a newline or other delimter");
        char* somebuff = "Some buffer with newline here[\n] and other buffer";
        te.append(somebuff);
        te.append(Utils.readLine(somebuff,'\n'));
        te.append("-----------------------------");
        te.append("9. XOR and DEXOR a buffer by key");
        char* xorr = "Now is the time for all good men to came and aid their party\nwhile the quick brown fox jumped over the lazy dog";
        te.append(xorr);
        te.append("-----------------------------------------");
        xorr = Utils.XOR_buffer(xorr,"123");
        te.append(xorr);
        te.append("-----------------------------------------");
        xorr = Utils.XOR_buffer(xorr,"123");
        te.append(xorr);
        te.append("-----------------------------------------");
        te.append("10. Split and return array of strings");
        char** splitted = Utils.split("This will be split by a whitespace ", ' ',1);
        te.append(splitted[0]);
        te.append(splitted[1]);
        te.append(splitted[2]);
        te.append(splitted[3]);
        te.append(splitted[4]);

        LOG_setNorm("/home/ilian/UtilsinC.log");

        te.append("11. Replace a pattern in a string");
        char *readfile = Utils.readFileToBuffer("/home/ilian/Downloads/test.html", "rb");

        Utils.writeToFile(Utils.replace(readfile, "div", "p"), "/home/ilian/t.html", "w");


        qwd.setMinimumHeight(480);
        qvb.addWidget(&te);
        qwd.setLayout(&qvb);
        qwd.show();
        /* Must call Clear_UtilsHeap() from signal/slot or some class ~() */


        return a.exec();
#endif

}
