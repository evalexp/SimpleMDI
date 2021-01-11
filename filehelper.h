#ifndef FILEHELPER_H
#define FILEHELPER_H

#include "QString"
#include "QFile"
#include "QDebug"

class FileHelper
{
public:
    FileHelper();
    static bool write(const QString& path, const QString& content);
    static bool read(const QString& path, QString& contentRef);
};

#endif // FILEHELPER_H
