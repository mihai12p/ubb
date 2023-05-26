#pragma once

#include <QtWidgets/QMainWindow>
#include <ui_MainWindow.h>
#include "ClientController.hpp"
#include <qstandarditemmodel.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ClientController& controller, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void scanComputer();
    void viewDetails();
    void onDetailsView();
    void takeAction();

private:
    Ui::MainWindow ui;
    ClientController& controller;

    QStandardItemModel* model = new QStandardItemModel(this);

    Process selectedProcess{ };
};