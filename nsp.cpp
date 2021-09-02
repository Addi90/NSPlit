#include "nsp.h"

NSP::NSP(){

}

int NSP::setSourcePath(QString path)
{
    QFileInfo file(path);
    if(!file.exists() || !file.isFile()){
        return -1;
    }
    _nspSourcePath = path;
    return 0;
}

size_t NSP::size()
{
    if(_nspSize) setSize(_nspSourcePath);
    return _nspSize;
}

QString NSP::sourcePath()
{
    return _nspSourcePath;
}

int NSP::setSize(QString path){
    if(!path.isEmpty()){
        std::ifstream _nspDataStream;
        _nspDataStream.open(path.toStdString(),std::ios::ate | std::ios::binary);
        size_t size = _nspDataStream.tellg();

        if(_nspDataStream.is_open() && size){
            _nspDataStream.close();
            _nspSize = size;
            return 0;
        }
        else return -1;
    }
    return -2;
}

