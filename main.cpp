#include <QCoreApplication>

#include <QDir>
#include <QMap>
#include <QTextStream>

#include "Traversal/ITraversal.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ITraversal* strat = new TypeTraversal();
    QString path = QDir::currentPath();
    QMap<QString, long long> map = *(strat->execute(path));

    QTextStream cout(stdout);

    foreach(auto x, map.keys()){
        cout << x << " " << map[x] << Qt::endl;
        cout.flush();
    }

    return a.exec();
}
