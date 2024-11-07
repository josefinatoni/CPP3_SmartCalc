#include "./View/calculator.h"
#include "./Controller/controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Model model;
    s21::Controller controller(&model);
    Calculator w(controller);
    w.show();
    return a.exec();
}
