#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::Calculator calc;
  s21::CreditCalc credit_calc;
  s21::Controller controller(&calc, &credit_calc);
  MainWindow w(nullptr, &controller);
  w.show();
  return a.exec();
}
