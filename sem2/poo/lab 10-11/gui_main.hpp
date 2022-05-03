#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_gui_main.h"

class gui_main : public QMainWindow
{
    Q_OBJECT

    public:
        gui_main(QWidget *parent = Q_NULLPTR);

    private:
        Ui::gui_mainClass ui;
};
