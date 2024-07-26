#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <QWidget>

#include "../controller/controller.h"

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget* parent, s21::Controller* controller);
  ~Graph();
  void Draw();
  void SetLine(QString line);
 private slots:
  void on_pushButton_clicked();

 private:
  void Clear();
  void Plot();
  Ui::Graph* ui;
  s21::Controller* controller_;
  QVector<double> x_, y_;
  QString line_;
};

#endif  // GRAPH_H
