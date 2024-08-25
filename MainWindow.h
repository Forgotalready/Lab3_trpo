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
#include "View/ViewAdapter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void createNavigation();
    QWidget* createStatistic();
    void createStatusBar();
    void createStrategeBox();
    QMap<QString, double> calculateStatistic();
    void createViewBox();
private:
    QString currentPath;

    QTreeView* navigationView;
    QFileSystemModel* navigationModel;

    ViewAdapter* statisticView;
    StatisticModel* statisticModel;
    Context context;
    ITraversal* stratege;

    QComboBox* strategeBox;
    QComboBox* viewBox;

    QHBoxLayout* viewLayout;

private slots:
    void onSelectionChange(const QItemSelection& selected, const QItemSelection& deselected);
    void onStrategyChange(int index);
    void onViewChange(int index);
signals:
    void pathChange(QMap<QString, double>&);

};
#endif // MAINWINDOW_H
