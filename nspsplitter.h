#ifndef NSPSPLITTER_H
#define NSPSPLITTER_H

#define _FAT32PartSize 0xFFFF0000
#define _FAT32BlockSize 0x00008000

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <direct.h>
#include <QDebug>
#include <QDir>
#include <QString>


class NSPSplitter : public QObject
{
    Q_OBJECT

signals:
    void progress(int prog);
public:
    NSPSplitter();
    size_t nspCheckFilesize();
    int nspCalcParts(size_t size);

    int nspSplit();
    void setInPath(QString path);
    void setOutPath(QString path);
private:
    std::ifstream _nsp;
    QString _inPath;
    QString _outPath;

};

#endif // NSPSPLITTER_H
