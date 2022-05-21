#include <QtWidgets/QApplication>
#include "gui.h"
#include "teste.h"

void start(int argc, char* argv[])
{
    QApplication a(argc, argv);
    
    repo r;
    service srv{ r };
    gui G{ srv };
    G.show();

    a.exec();
}

int main(int argc, char *argv[])
{
    testAll();

    start(argc, argv);

    return 0;
}
