#ifndef STATISTICMODEL_H
#define STATISTICMODEL_H

#include <QAbstractTableModel>

class StatisticModel : public QAbstractTableModel
{
public:
    StatisticModel(QMap<QString, double> Data, QObject* parent);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
public slots:
    void onPathChange(QMap<QString, double>& newData);
private:
    QVector<QVector<QString>> m_data;
    int column = 2;
};

#endif // STATISTICMODEL_H
