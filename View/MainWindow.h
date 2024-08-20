#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QTableView>
#include <QSplitter>
#include <QFileSystemModel>
#include <QAbstractTableModel>
#include <QDir>
#include <QHeaderView>
#include <QStatusBar>

#include "Context.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void setupFileSystemModel();
private:
    // View
    QTreeView* treeView;
    QTableView* tableView;

    QSplitter* viewSplitter;
    // Model
    QFileSystemModel* fileSystemModel;
    QAbstractTableModel* statisticModel;
    // ComboBox

    // Calculation Contex
    Context contex;
};
#endif // MAINWINDOW_H
