#include "ITraversal.h"


void FolderTraversal::traversal(QDir &directory, QMap<QString, long long> *statistic)
{
    QString path = directory.absolutePath();

    foreach(QFileInfo file, directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)){
        if(file.isDir()){
            QDir folder(file.absoluteFilePath());
            traversal(folder, statistic);
            continue;
        }

        long long fileSize = ((long long) file.size());

        if((*statistic).count(path) != 0)
            (*statistic)[path] += fileSize;
        else
            (*statistic)[path] = fileSize;
    }
}

QMap<QString, long long>* FolderTraversal::execute(QString &path)
{
    QDir dir(path);
    QMap<QString, long long> *map = new QMap<QString, long long>();

    traversal(dir, map);

    return map;
}

void TypeTraversal::traversal(QDir &directory, QMap<QString, long long> *statistic)
{
    foreach(QFileInfo file, directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)){
        if(file.isDir()){
            QDir folder(file.absoluteFilePath());
            traversal(folder, statistic);
            continue;
        }

        QString extension = file.suffix();
        if((*statistic).count(extension) != 0) (*statistic)[extension] += ((long long) file.size());
        else (*statistic)[extension] = ((long long) file.size());
    }
}

QMap<QString, long long> *TypeTraversal::execute(QString &path)
{
    QDir dir(path);
    QMap<QString, long long> *map = new QMap<QString, long long>();

    traversal(dir, map);

    return map;
}

QMap<QString, double>* countPrecent(QMap<QString, long long> &stat, double border)
{
    QMap<QString, double> *newMap = new QMap<QString, double>();
    if(stat.count() == 0) return newMap;

    double sum = 0.0;
    foreach(long long x, stat)
        sum += (double) x;

    foreach(QString str, stat.keys()){
        double precent = ((double) stat[str]) / sum * 100.0;
        if(precent < border){
            if((*newMap).count("Other") != 0) (*newMap)["Other"] += precent;
            else (*newMap)["Other"] = precent;
        }else
            (*newMap)[str] = precent;
    }
    return newMap;
}
