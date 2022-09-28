#include "global.h"

void Files::copy(QString from, QString to, bool remove_after)
{
//    QDirIterator it(from, QDirIterator::Subdirectories);
//    QDir dir(from);
//    int path_length = dir.absoluteFilePath(from).length();
//    while(it.hasNext())
//    {
//        it.next();
//        auto fileInfo = it.fileInfo();
//        if(!fileInfo.isHidden())
//        {
//            QString subPathStructure = fileInfo.absoluteFilePath().mid(absSourcePathLength);
//            QString constructedAbsolutePath = toDir + subPathStructure;
//            if(fileInfo.isDir())
//            {
//                dir.mkpath(constructedAbsolutePath);
//            }
//            else if(fileInfo.isFile())
//            {
//                QFile::remove(constructedAbsolutePath);
//                QFile::copy(fileInfo.absoluteFilePath(), constructedAbsolutePath);
//            }
//        }
//    }
//    if(remove_after) dir.removeRecursively();
}

void Files::remove(QString path)
{
    
}
