#ifndef FILEPARSE_H
#define FILEPARSE_H
#include <QString>

class FileParse
{
public:
    FileParse(int w, int h, QString f);
    ~FileParse();
    const bool* get();
private:
    bool* p;
};

#endif // FILEPARSE_H
