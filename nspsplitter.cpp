#include "nspsplitter.h"

NSPSplitter::NSPSplitter()
{

}

size_t NSPSplitter::nspCheckFilesize(){
    if(!_inPath.isEmpty()){
        _nsp.open(_inPath.toStdString(),std::ios::ate | std::ios::binary);
        size_t size = _nsp.tellg();

        if(_nsp.is_open() && size){
            _nsp.close();
            return size;
        }
        else return -1;
    }
    return -2;
}

int NSPSplitter::nspCalcParts(size_t size){
    if(size <= 0) return -1;
    int parts = (int) (size / _FAT32PartSize);
    return parts+1;
}



int NSPSplitter::nspSplit(){

    size_t filesize = nspCheckFilesize();
    int parts = nspCalcParts(filesize);

    if(parts <= 0) return -1;
    if(_outPath.isEmpty()) return -2;

    _nsp.open(_inPath.toStdString(),std::ios::in | std::ios::binary);
    _nsp.seekg(_nsp.beg);

    /* TODO: get filename, format to new splitted nsp-foldername (the new nsp file) */

    QStringList splittedPath = _inPath.split('/');
    QString sourceFileName = splittedPath.last().remove(".nsp");
    sourceFileName.append("_split.nsp");
    QString savePath = _outPath + '/' + sourceFileName;
    savePath.replace('/',"\\\\");

    //if(!QDir().exists()){
        QDir().mkdir(savePath);
    //}


    for(int i = 0; i < parts; i++){

        /* for every part, calculate read starting-pos. and create new file */
        size_t pos = i * _FAT32PartSize;
        char buf[_FAT32BlockSize];

        QString partSavePath(savePath);
        QString partName = QStringLiteral("/%1").arg(i,2,10,QLatin1Char('0'));
        partSavePath.append(partName);
        partSavePath.replace('/',"\\\\");

        std::ofstream outStream;
        outStream.open(partSavePath.toStdString(), std::ios::out | std::ios::binary);

        /* read sourcefile blockwise and copy to dest., stop at part-end/file-end */
        while(pos  < filesize && (pos < (i+1)*_FAT32PartSize)){

            if(filesize > pos+sizeof(buf)){
                _nsp.seekg(pos);
                _nsp.read(buf,sizeof(buf));
                outStream.write(buf,sizeof(buf));
                pos += sizeof(buf);
            }
            else{

                _nsp.seekg(pos);
                size_t leftover = filesize - pos+1;
                std::vector<char> buf2(leftover);

                _nsp.read(buf2.data(),leftover);
                outStream.write(buf2.data(),leftover);
                break;
            }
            int prog = std::lround(((double)pos / (double)filesize)*100);
            qDebug() << "current pos: " << pos << "prog.: "<< prog << "%";
            emit progress(prog);

        }
        outStream.close();
    }
    _nsp.close();
    return parts;

}

void NSPSplitter::setInPath(QString path){
    /* TODO: check if valid */
    _inPath = path;
}
void NSPSplitter::setOutPath(QString path){
    /* TODO: check if valid */
    _outPath = path;
}
