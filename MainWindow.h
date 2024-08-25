#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QFileSystemModel>
#include <QTableView>
#include <QDir>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QComboBox>
#include <QVBoxLayout>

#include "Traversal/ITraversal.h"
#include "Context.h"
#include "Model/StatisticModel.h"
#include "View/ChartCreator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void createNavigation();
    void createStatistic();
    void createStatusBar();
    void createStrategeBox();
    QMap<QString, double> calculateStatistic();
private:
    QString currentPath;

    QTreeView* navigationView;
    QFileSystemModel* navigationModel;

    QTableView* statisticView;
    StatisticModel* statisticModel;
    Context context;
    ITraversal* stratege;

    QComboBox* strategeBox;
private slots:
    void onSelectionChange(const QItemSelection& selected, const QItemSelection& deselected);
    void onStrategyChange(int index);
signals:
    void pathChange(QMap<QString, double>&);

};
#endif // MAINWINDOW_H
