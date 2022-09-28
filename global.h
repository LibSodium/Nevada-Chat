#pragma once

#include <QDir>
#include <QFile>
#include <QObject>
#include <QDirIterator>

class Files
{
public:
    static void copy(QString from, QString to, bool remove_after);
    static void remove(QString path);
};
