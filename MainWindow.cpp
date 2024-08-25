#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    currentPath = QDir::currentPath();
    QWidget* mainWindowWidget = new QWidget(this);

    createNavigation();
    QWidget* statistic = createStatistic();
    createStrategeBox();
    createViewBox();

    QVBoxLayout* vLayout = new QVBoxLayout(mainWindowWidget);

    viewLayout = new QHBoxLayout(mainWindowWidget);

    viewLayout->addWidget(navigationView);
    viewLayout->addWidget(statistic);

    QHBoxLayout* comboBoxLayout = new QHBoxLayout(mainWindowWidget);
    comboBoxLayout->addWidget(strategeBox);
    comboBoxLayout->addWidget(viewBox);

    vLayout->addLayout(comboBoxLayout);
    vLayout->addLayout(viewLayout);

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
    if(statisticView != nullptr)
    {
        delete statisticView;
        statisticView = nullptr;
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

void MainWindow::createViewBox()
{
    viewBox = new QComboBox(this);
    viewBox->addItems(
        {"Table", "Pie Chart", "Bar Chart"}
    );

    connect(
        viewBox,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this,
        &MainWindow::onViewChange
    );
}

void MainWindow::createStatusBar()
{
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Выбраный путь: " + currentPath);
}

QWidget* MainWindow::createStatistic()
{
    statisticView = new TableView();
    stratege = new FolderTraversal();
    context.setStrategy(stratege);

    QMap<QString, double> data = calculateStatistic();

    statisticModel = new StatisticModel(data, this);

    QWidget* statistic = statisticView->updateView(statisticModel);

    connect(
        this,
        &MainWindow::pathChange,
        statisticModel,
        &StatisticModel::onPathChange
    );
    return statistic;
}

void MainWindow::onSelectionChange(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    QModelIndex selectedItem = selected.indexes().constFirst();

    currentPath = navigationModel->filePath(selectedItem);

    QMap<QString, double> data = calculateStatistic();

    emit pathChange(data);

    viewLayout->addWidget(statisticView->updateView(statisticModel));
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

    viewLayout->addWidget(statisticView->updateView(statisticModel));
}

void MainWindow::onViewChange(int index)
{
    if(statisticView != nullptr)
    {
        delete statisticView;
        statisticView = nullptr;
    }

    switch(index)
    {
        case 0:
            statisticView = new TableView();
            break;
        case 1:
            statisticView = new PieChart();
            break;
        case 2:
            statisticView = new BarChart();
            break;
    }
    viewLayout->addWidget(statisticView->updateView(statisticModel));
}
