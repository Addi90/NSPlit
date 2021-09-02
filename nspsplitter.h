#ifndef NSPSPLITTER_H
#define NSPSPLITTER_H

#define _FAT32PartSize 0xFFFF0000
#define _FAT32BlockSize 0x00008000

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <direct.h>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QMessageBox>
#include <nsp.h>


class NSPSplitter : public QObject
{
    Q_OBJECT

signals:
    void progress(int prog);
public:
    NSPSplitter(QObject* parent);
    int nspCalcParts(size_t size);

    int nspSplit(NSP* nsp);

    int setOutPath(QString path);
private:
    std::ifstream _nsp;
    QString _inPath;
    QString _outPath;

};

#endif // NSPSPLITTER_H
