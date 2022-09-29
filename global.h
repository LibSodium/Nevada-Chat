#pragma once

#include <QDir>
#include <QFile>
#include <QObject>
#include <QDirIterator>
#include <QRandomGenerator>

class Files
{
public:
    static void copy(QString from, QString to, bool remove_after = false);
};

class Generators
{
public:
    static QString key(int length = 16);
};
