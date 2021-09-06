#include "nsp.h"

NSP::NSP(){

}

NSP::NSP(QString path){
    setPath(path);
    setSize(path);
}

int NSP::setPath(QString path)
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

QString NSP::path()
{
    return _nspSourcePath;
}

QString NSP::name()
{
    QStringList splittedPath = _nspSourcePath.split('/');
    return splittedPath.last();
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

