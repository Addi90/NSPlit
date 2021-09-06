#ifndef NSPSPLITTER_H
#define NSPSPLITTER_H

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
#include <QThread>


class NSPSplitter : public QThread
{
    Q_OBJECT

signals:
    void progress(int prog);

public:
    NSPSplitter();
    int nspCalcParts(size_t size);


    int nspSplit(NSP* nsp);

    int setSavePath(QString path);
    int setNSPItem(NSP* nsp);
private:
    std::ifstream _nsp;
    QString _inPath;
    QString _outPath;

    QString makeSaveDir(QString filename);

    const size_t _FAT32PartSize = 0xFFFF0000;
    const size_t _FAT32BlockSize = 0x00008000;
};

#endif // NSPSPLITTER_H
