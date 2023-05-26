#include "MainWindow.hpp"
#include "DetailsWindow.hpp"
#include <qstandarditemmodel.h>
#include <qbuttongroup.h>

MainWindow::MainWindow(ClientController& controller, QWidget* parent) : QMainWindow(parent), controller{ controller }
{
    this->ui.setupUi(this);

    connect(this->ui.scanButton, &QPushButton::clicked, this, &MainWindow::scanComputer);
    connect(this->ui.detailsView, &QPushButton::clicked, this, &MainWindow::onDetailsView);
    connect(this->ui.actionButton, &QPushButton::clicked, this, &MainWindow::takeAction);
    connect(&this->controller.GetWorker(), &ClientWorker::rescanComputer, this, &MainWindow::scanComputer);

    this->model->setColumnCount(2);
    this->model->setHeaderData(0, Qt::Horizontal, "Process Name");
    this->model->setHeaderData(1, Qt::Horizontal, "Process ID");

    this->ui.detailsView->setEnabled(false);

    this->ui.resultsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui.resultsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui.resultsView->setModel(this->model);

    connect(this->ui.resultsView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::viewDetails);
}

MainWindow::~MainWindow()
{
    if (this->model)
    {
        delete this->model;
    }
}

void MainWindow::scanComputer()
{
    this->model->removeRows(0, this->model->rowCount());

    const QList<Process>& processes = this->controller.scanComputer();
    for (const Process& process : processes)
    {
        QList<QStandardItem*> items{ };
        items.append(new QStandardItem(process.getName()));
        items.append(new QStandardItem(QString::number(process.getPID())));
        this->model->appendRow(items);
    }
    this->ui.resultsView->update();
}

void MainWindow::viewDetails()
{
    this->ui.detailsView->setEnabled(false);

    const QModelIndexList& selectedIndexes = this->ui.resultsView->selectionModel()->selectedIndexes();
    if (selectedIndexes.size() == 1)
    {
        this->ui.resultsView->selectionModel()->select(selectedIndexes.at(0), QItemSelectionModel::Select | QItemSelectionModel::Rows);
        return;
    }

    if (selectedIndexes.size() == 2)
    {
        this->selectedProcess.setName(selectedIndexes[0].data().toString());
        this->selectedProcess.setPID(selectedIndexes[1].data().toInt());

        this->ui.detailsView->setEnabled(true);
    }
}

void MainWindow::onDetailsView()
{
    const QModelIndexList& selectedIndexes = this->ui.resultsView->selectionModel()->selectedIndexes();
    const QString& processName = selectedIndexes[0].data().toString();
    qint32 processId = selectedIndexes[1].data().toInt();

    DetailsWindow* detailsWindow = new DetailsWindow(processId, this->controller, this);
    detailsWindow->setWindowTitle("Details for " + processName);
    detailsWindow->show();
}

void MainWindow::takeAction()
{
    QButtonGroup group{ };
    for (int i = 0; i < this->ui.actionBox->children().size() - 1; ++i)
    {
        group.addButton(reinterpret_cast<QAbstractButton*>(this->ui.actionBox->children().at(i)), i);
    }

    this->controller.takeAction(this->selectedProcess, group.checkedId());
}