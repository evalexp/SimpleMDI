#include "filehelper.h"

FileHelper::FileHelper()
{

}

/**
 * @brief FileHelper::write
 * @param path  file's path
 * @param content   the content to write
 * @return if write successful
 */
bool FileHelper::write(const QString &path, const QString &content){
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)){
        file.write(content.toStdString().data());
        return true;
    }
    return false;
}

/**
 * @brief FileHelper::read
 * @param path  file's path
 * @param contentRef    the contentRef will be set as file's content
 * @return if read successful
 */
bool FileHelper::read(const QString &path, QString &contentRef){
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        contentRef = QString::fromStdString(file.readAll().toStdString());
        return true;
    }
    return false;
}
