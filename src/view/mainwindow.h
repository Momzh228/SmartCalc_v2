#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QWindow>

#include "../controller/controller.h"
#include "creditcalc.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent, s21::Controller* controller);
  ~MainWindow();

 private:
  Ui::MainWindow* ui;
  s21::Controller* controller_;
  CreditCalc credit_;
  Graph graph_;
  QLineEdit* line_edit_;
  bool x_;
 private slots:
  void Symbol();
  void Func();
  void Clear_all();
  void SetLineEdit();
  void on_pushButton_graph_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_equal_clicked();
  void on_pushButton_CE_clicked();
  void on_pushButton_clear_clicked();
};
#endif  // MAINWINDOW_H
