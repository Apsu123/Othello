#include "othello.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Othello othello;

    return app.exec();
}
