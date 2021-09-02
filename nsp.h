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

    size_t size();
    QString sourcePath();

    int setSourcePath(QString path);

private:
    QString _nspSourcePath;
    size_t _nspSize; // size in bytes

    int setSize(QString path);

signals:

};

#endif // NSP_H
