#include "mainwindow.h"
#include "ui_graph.h"
Graph::Graph(QWidget* parent, s21::Controller* controller)
    : QWidget(parent), ui(new Ui::Graph), controller_(controller), line_("") {
  ui->setupUi(this);
  setWindowTitle("Graph");
  ui->widget->addGraph();
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->xAxis->setRange(-10, 10);
  ui->widget->yAxis->setRange(-10, 10);
}
Graph::~Graph() { delete ui; }

void Graph::Draw() {
  Clear();
  if (!line_.isEmpty()) {
    for (double i = -1000; i < 1000 && !controller_->GetError(); i += 0.1) {
      QString input_line = line_;
      input_line.replace("x", QString::number(i));
      controller_->Calc(input_line.toStdString());
      if (!controller_->GetError()) {
        x_.push_back(i);
        y_.push_back(controller_->GetResult());
      }
    }
  }
  Plot();
}

void Graph::on_pushButton_clicked() { Plot(); }

void Graph::SetLine(QString line) { line_ = line; }
void Graph::Clear() {
  x_.clear();
  y_.clear();
  ui->widget->graph(0)->data()->clear();
}
void Graph::Plot() {
  ui->widget->graph(0)->addData(x_, y_);
  ui->widget->xAxis->setRange(ui->x1->value(), ui->x2->value());
  ui->widget->yAxis->setRange(ui->y1->value(), ui->y2->value());
  ui->widget->replot();
}
