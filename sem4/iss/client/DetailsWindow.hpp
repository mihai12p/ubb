#pragma once

#include <QtWidgets/QMainWindow>
#include <ui_DetailsWindow.h>
#include "ClientController.hpp"

class DetailsWindow : public QMainWindow
{
    Q_OBJECT

public:
    DetailsWindow(qint32 PID, ClientController& controller, QWidget* parent = nullptr);

private:
    Ui::Form ui;
    ClientController& controller;
};