#include "nsp.h"

NSP::NSP(){

}

NSP::NSP(QString path){
    setSourcePath(path);
    setSize(path);
}

int NSP::setSourcePath(QString path)
{
    QFileInfo file(path);
    if(!file.exists() || !file.isFile()){
        return -3;
    }
    _nspSourcePath = path;
    return setSize(path);
}

size_t NSP::size()
{
    return _nspSize;
}

QString NSP::sourcePath()
{
    return _nspSourcePath;
}

int NSP::setSize(QString path){
    if(!path.isEmpty()){

        path.replace('/',"\\\\");
        _nsp.open(path.toStdString(),std::ios::ate | std::ios::binary);
        size_t size = _nsp.tellg();

        if(_nsp.is_open() && size){
            _nsp.close();
            _nspSize = size;
            return 0;
        }
        else return -1;
    }
    return -2;
}

