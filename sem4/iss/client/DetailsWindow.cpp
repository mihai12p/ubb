#include "DetailsWindow.hpp"

DetailsWindow::DetailsWindow(qint32 PID, ClientController& controller, QWidget* parent) : QMainWindow(parent), controller{ controller }
{
    ui.setupUi(this);

    this->ui.detailsList->addItems(this->controller.getProcessDetails(PID));
}