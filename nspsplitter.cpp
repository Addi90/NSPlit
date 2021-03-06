#include "nspsplitter.h"

NSPSplitter::NSPSplitter()
{

}

int NSPSplitter::nspCalcParts(size_t size){
    if(size <= 0) return -1;
    int parts = (int) (size / _FAT32PartSize);
    return parts+1;
}


int NSPSplitter::nspSplit(NSP* nsp){

    size_t filesize = nsp->size();
    int parts = nspCalcParts(filesize);

    if(parts <= 1) return -1;

    _nsp.open(nsp->path().toStdString(),std::ios::in | std::ios::binary);
    _nsp.seekg(_nsp.beg);

    /* make new nsp-folder/container for splitted files */
    QString sourceFileName = nsp->name().remove(".nsp");
    sourceFileName.append("_split.nsp");   
    QString savePath = makeSaveDir(sourceFileName);

    for(int i = 0; i < parts; i++){

        /* for every part, calculate read starting-pos. and create new file */
        size_t pos = i * _FAT32PartSize;
        char buf[_FAT32BlockSize];

        QString partSavePath(savePath);
        QString partName = QStringLiteral("/%1").arg(i,2,10,QLatin1Char('0'));
        partSavePath.append(partName);

        std::ofstream outStream;
        outStream.open(partSavePath.toStdString(), std::ios::out | std::ios::binary);

        /* read sourcefile blockwise and copy to dest., stop at part-end/file-end */
        while((pos  < filesize) && (pos < (i+1)*_FAT32PartSize)){

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
            //qDebug() << "current pos: " << pos << "prog.: "<< prog << "%";
            emit progress(prog);

        }
        outStream.close();
    }
    _nsp.close();
    return 0;

}


int NSPSplitter::setSavePath(QString path){

    if(!QDir(path).exists()){
        return -1;
    }
    _outPath = path;
    return 0;
}

QString NSPSplitter::makeSaveDir(QString name)
{
    QString savePath = _outPath + '/' + name;
    QDir().mkdir(savePath);
    return savePath;
}
