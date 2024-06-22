#include <QCoreApplication>

#include <QDir>
#include <QMap>
#include <QTextStream>

void directoryTraversalByFolder(QDir &directory, QMap<QString, long long> &statistic){
    QString path = directory.absolutePath();

    statistic[path] = 0;

    foreach(QFileInfo file, directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)){
        if(file.isDir()){
            QDir folder(file.absoluteFilePath());
            directoryTraversalByFolder(folder, statistic);
            continue;
        }
        statistic[path] += ((long long) file.size());
    }
}

void directoryTraversalByType(QDir &directory, QMap<QString, long long> &statistic){

    foreach(QFileInfo file, directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)){
        if(file.isDir()){
            QDir folder(file.absoluteFilePath());
            directoryTraversalByType(folder, statistic);
            continue;
        }

        QString extension = file.suffix();
        if(statistic.count(extension) != 0) statistic[extension] += ((long long) file.size());
        else statistic[extension] = ((long long) file.size());
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDir directory = QDir::currentPath();

    QMap<QString, long long> map;

    directoryTraversalByType(directory, map);

    QTextStream cout(stdout);

    foreach(auto x, map.keys()){
        cout << x << " " << map[x] << Qt::endl;
        cout.flush();
    }

    return a.exec();
}
