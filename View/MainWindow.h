#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QTableView>
#include <QSplitter>
#include <QFileSystemModel>
#include <QDir>
#include <QHeaderView>
#include <QStatusBar>
#include <QComboBox>
#include <QVBoxLayout>

#include "Context.h"
#include "Model/StatisticModel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void setupFileSystemModel(QString& homePath);
private slots:
    void onSelectionChange(const QItemSelection& selected, const QItemSelection& deselected);
    void onStrategyChange(int index);
private:
    QString currentPath;

    // View
    QTreeView* treeView;
    QTableView* tableView;

    QSplitter* viewSplitter;
    // Model
    QFileSystemModel* fileSystemModel;
    StatisticModel* statisticModel;
    // ComboBox
    QComboBox* strategyComboBox;
    // Calculation Contex
    Context context;
    ITraversal* strategy;
signals:
    void pathChange(QMap<QString, double>&);

};
#endif // MAINWINDOW_H
