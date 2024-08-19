#include <QCoreApplication>

#include <QDir>
#include <QMap>
#include <QTextStream>

#include "Traversal/ITraversal.h"
#include "Context.h"

void getStatistic(Context& context){
    ITraversal* strat = new FolderTraversal();

    context.setStrategy(strat);

    //QString path = QDir::currentPath();
    QString path = "D:/project/Lab3_trpo/Test2Folder";

    QMap<QString, long long> statistic = context.executeStrategy(path);

    QMap<QString, double> map = countPrecent(statistic, 1.0); // Правильнее использовать всё по значению, конечно не будет копирования, компилятор не дурак.
    QTextStream cout(stdout);

    foreach(const QString& key, map.keys())
        cout << key << " " << map[key] << Qt::endl;

    cout.flush();

    delete strat;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Context context;
    getStatistic(context);

    return a.exec();
}
