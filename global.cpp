#include "global.h"

QString possible_chars = "11223344556677889900qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

void Files::copy(QString from, QString to, bool remove_after)
{
    QDirIterator it(from, QDirIterator::Subdirectories);
    QDir dir(from);
    int path_length = dir.absoluteFilePath(from).length();
    while(it.hasNext())
    {
        it.next();
        auto file_info = it.fileInfo();
        if(!file_info.isHidden())
        {
            QString sub_path = file_info.absoluteFilePath().mid(path_length);
            QString sub_path_after_copy = to + sub_path;
            if(file_info.isDir())
            {
                dir.mkpath(sub_path_after_copy);
            }
            else if(file_info.isFile())
            {
                QFile::remove(sub_path_after_copy);
                QFile::copy(file_info.absoluteFilePath(), sub_path_after_copy);
                QFile::setPermissions(sub_path_after_copy, QFileDevice::ReadOwner | QFileDevice::WriteOwner);
            }
        }
    }
    if(remove_after) dir.removeRecursively();
}

QString Generators::key(int length)
{
    QString out;
    for(int i = 0; i < length; i++)
        out += possible_chars.at(QRandomGenerator::global()->bounded(possible_chars.size()));
    return out;
}
