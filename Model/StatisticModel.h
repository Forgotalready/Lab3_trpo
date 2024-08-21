#ifndef STATISTICMODEL_H
#define STATISTICMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QString>

class StatisticModel : public QAbstractTableModel
{
public:
    StatisticModel(QMap<QString, double>&, QObject* parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
public slots:
    void onPathChange(QMap<QString, double>& newData);
private:
    QVector<QVector<QString>> m_data;
    int columnAmount = 2;
};

#endif // STATISTICMODEL_H
