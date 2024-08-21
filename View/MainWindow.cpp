#include "MainWindow.h"

void MainWindow::setupFileSystemModel(QString& homePath)
{
    fileSystemModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    fileSystemModel->setRootPath(homePath);
}

void MainWindow::onSelectionChange(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    QModelIndex index = selected.indexes().constFirst();

    currentPath = fileSystemModel->filePath(index);

    this->statusBar()->showMessage("Выбранный путь: " + currentPath);

    QMap<QString, long long> countData = context.executeStrategy(currentPath);
    QMap<QString, double> data = countPrecent(countData, 1.0);
    emit pathChange(data);
}

void MainWindow::onStrategyChange(int index)
{
    if(strategy != nullptr){
        delete strategy;
        strategy = nullptr;
    }

    if(index == 0){
        strategy = new FolderTraversal();
    }else if(index == 1){
        strategy = new TypeTraversal();
    }
    context.setStrategy(strategy);

    QMap<QString, long long> countData = context.executeStrategy(currentPath);
    QMap<QString, double> data = countPrecent(countData, 1.0);
    emit pathChange(data);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    treeView = new QTreeView();
    tableView = new QTableView();
    viewSplitter = new QSplitter(this);

    viewSplitter->addWidget(treeView);
    viewSplitter->addWidget(tableView);

    currentPath = QDir::currentPath();

    fileSystemModel = new QFileSystemModel(this);
    setupFileSystemModel(currentPath);

    strategy = new FolderTraversal();
    context.setStrategy(strategy);

    QMap<QString, long long> countData = context.executeStrategy(currentPath);
    QMap<QString, double> data = countPrecent(countData, 1.0);
    statisticModel = new StatisticModel(data, this);

    tableView->setModel(statisticModel);

    treeView->setModel(fileSystemModel);
    treeView->expandAll();
    treeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    QItemSelectionModel* selectionModel = treeView->selectionModel();
    QModelIndex homeIndex = fileSystemModel->index(currentPath);
    QItemSelection toggleSelection;
    toggleSelection.select(homeIndex, homeIndex);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);

    QWidget* mainWindowWidget = new QWidget(this);
    strategyComboBox = new QComboBox(mainWindowWidget);
    strategyComboBox->addItems(
        {"By Folder", "By type"}
    );

    QVBoxLayout* layout = new QVBoxLayout(mainWindowWidget);
    layout->addWidget(strategyComboBox);
    layout-> addWidget(viewSplitter);

    mainWindowWidget->setLayout(layout);

    this->setCentralWidget(mainWindowWidget);
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Chosen Path: ");
    this->setGeometry(100, 100, 1500, 300);

    connect(
        selectionModel,
        &QItemSelectionModel::selectionChanged,
        this,
        &MainWindow::onSelectionChange
    );
    connect(
        this,
        &MainWindow::pathChange,
        statisticModel,
        &StatisticModel::onPathChange
    );
    connect(
        strategyComboBox,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this,
        &MainWindow::onStrategyChange
    );
}

MainWindow::~MainWindow()
{
    if(strategy != nullptr){
        delete strategy;
        strategy = nullptr;
    }
}


