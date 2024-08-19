#ifndef ITRAVERSAL_H
#define ITRAVERSAL_H

#include <QMap>
#include <QDir>

QMap<QString, double> countPrecent(QMap<QString, long long>&, double);

class ITraversal
{
public:
    virtual QMap<QString, long long> execute(QString& path) = 0;

    virtual ~ITraversal(){}
};

class FolderTraversal : public ITraversal{
    void traversal(QDir&, QMap<QString, long long>&);
public:
    QMap<QString, long long> execute(QString &path) override;
};

class TypeTraversal : public ITraversal{
    void traversal(QDir&, QMap<QString, long long>&);
public:
    QMap<QString, long long> execute(QString& path) override;
};

#endif // ITRAVERSAL_H
