#include "MainWindow.h"

void MainWindow::setupFileSystemModel()
{
    fileSystemModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    QString homePath = QDir::currentPath();
    fileSystemModel->setRootPath(homePath);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    treeView = new QTreeView();
    tableView = new QTableView();
    viewSplitter = new QSplitter(this);

    viewSplitter->addWidget(treeView);
    viewSplitter->addWidget(tableView);

    fileSystemModel = new QFileSystemModel(this);
    setupFileSystemModel();

    treeView->setModel(fileSystemModel);
    treeView->expandAll();
    treeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    this->setCentralWidget(viewSplitter);
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Chosen Path: ");
    this->setGeometry(100, 100, 1500, 300);
}

MainWindow::~MainWindow()
{
}


