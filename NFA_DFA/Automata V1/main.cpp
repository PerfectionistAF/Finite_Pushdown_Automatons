#include "index.h"
#include <QApplication>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Widget window;
    window.show();
    return app.exec();
}


