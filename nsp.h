#ifndef NSP_H
#define NSP_H

#include <QObject>
#include <QFileInfo>
#include <iostream>
#include <fstream>

class NSP : public QObject
{
    Q_OBJECT

public:
    NSP();
    NSP(QString path);
    size_t size();
    QString sourcePath();

    int setSourcePath(QString path);
    int setSize(QString path);

private:
    QString _nspSourcePath;
    size_t _nspSize; // size in bytes
    std::ifstream _nsp;

signals:

};

#endif // NSP_H
