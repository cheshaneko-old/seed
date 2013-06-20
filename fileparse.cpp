#include "fileparse.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QStringList>

FileParse::FileParse(int w, int h, QString f)
{
    p = new bool[w*h];
    for(int i=0; i<w*h; ++i)
        p[i]=false;

    QRegExp rx("(\\d+ \\d+.*)");
    QFile file(f);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    int x, y;
    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
        if(rx.exactMatch(line))
        {
            x = line.split(" ").at(0).toInt();
            y = line.split(" ").at(1).toInt();
            if(x<w && y<h)
                p[y*w+x]=true;
        }
        line = in.readLine();
    }

}

const bool* FileParse::get()
{
    return p;
}

FileParse::~FileParse()
{
    delete[] p;
}
