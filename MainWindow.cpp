#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    currentPath = QDir::currentPath();
    QWidget* mainWindowWidget = new QWidget(this);

    createNavigation();
    createStatistic();
    createStrategeBox();

    QVBoxLayout* vLayout = new QVBoxLayout(this);

    QHBoxLayout* horLayout = new QHBoxLayout(this);
    horLayout->addWidget(navigationView);
    horLayout->addWidget(statisticView);

    vLayout->addWidget(strategeBox);
    vLayout->addLayout(horLayout);

    mainWindowWidget->setLayout(vLayout);

    this->setCentralWidget(mainWindowWidget);
    createStatusBar();
    this->setGeometry(100, 100, 1500, 500);
}

void MainWindow::createStrategeBox()
{
    strategeBox = new QComboBox(this);
    strategeBox->addItems(
        {"Folder", "Type"}
    );

    connect(
        strategeBox,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this,
        &MainWindow::onStrategyChange
    );
}

MainWindow::~MainWindow() {
    if(stratege != nullptr){
        delete stratege;
        stratege = nullptr;
    }
}

void MainWindow::createNavigation()
{
    navigationView = new QTreeView(this);
    navigationModel = new QFileSystemModel(this);

    navigationModel->setRootPath(currentPath);
    navigationModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);

    navigationView->setModel(navigationModel);
    navigationView->expandAll();
    navigationView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    QItemSelectionModel* selectionModel = navigationView->selectionModel();
    QItemSelection selection;
    QModelIndex currentPathIndex = navigationModel->index(currentPath);
    selection.select(currentPathIndex, currentPathIndex);
    selectionModel->select(currentPathIndex, QItemSelectionModel::Toggle);

    connect(
        selectionModel,
        &QItemSelectionModel::selectionChanged,
        this,
        &MainWindow::onSelectionChange
    );
}

QMap<QString, double> MainWindow::calculateStatistic()
{
    QMap<QString, long long> rawData = context.executeStrategy(currentPath);
    QMap<QString, double> data = countPrecent(rawData, 1.0f);

    return data;
}

void MainWindow::createStatusBar()
{
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Выбраный путь: " + currentPath);
}

void MainWindow::createStatistic()
{
    statisticView = new QTableView(this);

    stratege = new FolderTraversal();
    context.setStrategy(stratege);

    QMap<QString, double> data = calculateStatistic();

    statisticModel = new StatisticModel(data, this);
    statisticView->setModel(statisticModel);

    connect(
        this,
        &MainWindow::pathChange,
        statisticModel,
        &StatisticModel::onPathChange
    );
}

void MainWindow::onSelectionChange(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    QModelIndex selectedItem = selected.indexes().constFirst();

    currentPath = navigationModel->filePath(selectedItem);

    QMap<QString, double> data = calculateStatistic();

    emit pathChange(data);
}

void MainWindow::onStrategyChange(int index)
{
    if(stratege != nullptr){
        delete stratege;
        stratege = nullptr;
    }
    switch(index)
    {
        case 0:
            stratege = new FolderTraversal();
            break;
        case 1:
            stratege = new TypeTraversal();
            break;
    }
    context.setStrategy(stratege);
    QMap<QString, double> data = calculateStatistic();
    emit pathChange(data);
}
