#include "mainwindow.h"

#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent, s21::Controller *controller)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_(controller),
      credit_(nullptr, controller),
      graph_(nullptr, controller),
      line_edit_(nullptr),
      x_(false) {
  ui->setupUi(this);
  setWindowTitle("Calculator");
  setFixedSize(643, 360);
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_zero, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_one, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_two, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_three, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_four, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_five, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_six, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_seven, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_eight, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_nine, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_bracker_1, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_bracket_2, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_E, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(Symbol()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(Func()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(Func()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::Symbol() {
  SetLineEdit();
  QPushButton *button = (QPushButton *)sender();
  QRegularExpression operations("[+-/*^d]");
  QRegularExpression first_Symbol("[0-9x(]");
  QString current_text = line_edit_->text();
  QString Symbol_button = button->text();
  if (!ui->result_show->text().isEmpty()) {
    if (ui->result_show->text().front() == 'E' ||
        ui->result_show->text().front() == 'i' ||
        ui->result_show->text().front() == 'n') {
      Clear_all();
      current_text.clear();
    }
  }
  if (Symbol_button == 'x') {
    x_ = true;
  }
  if (current_text.isEmpty()) {
    if (first_Symbol.match(Symbol_button).hasMatch())
      line_edit_->setText(Symbol_button);
  } else if ((!(operations.match(QString(current_text.back())).hasMatch() &&
                operations.match(QString(Symbol_button.back())).hasMatch()) &&
              !(operations.match(QString(Symbol_button.back())).hasMatch() &&
                current_text.back() == '(') &&
              !((Symbol_button == "x" && (current_text.back().isDigit() ||
                                          current_text.back() == '.')) ||
                (current_text.back() == 'x' &&
                 (Symbol_button.back().isDigit() ||
                  Symbol_button.back() == '.')) ||
                (Symbol_button == 'x' && current_text.back() == 'x') ||
                (Symbol_button == 'e' && current_text.back() == 'e'))) ||
             (current_text.back() == '(' &&
              (Symbol_button == "-" || Symbol_button == "+"))) {
    QString set_text = current_text + Symbol_button;
    line_edit_->setText(set_text);
  }
}

void MainWindow::Func() {
  SetLineEdit();
  QPushButton *button = (QPushButton *)sender();
  QRegularExpression operations("[+-/*d^(]");
  QString text_result_show = line_edit_->text();
  if (ui->result_show->text() == "ERROR") {
    Clear_all();
    text_result_show.clear();
  }
  if (!text_result_show.isEmpty()) {
    if (operations.match(QString(text_result_show.back())).hasMatch()) {
      QString text = text_result_show + button->text() + '(';
      line_edit_->setText(text);
    }
  } else {
    QString text = text_result_show + button->text() + '(';
    line_edit_->setText(text);
  }
}
void MainWindow::on_pushButton_equal_clicked() {
  if (!ui->result_show->text().isEmpty()) {
    QString str = ui->result_show->text();
    QRegularExpression symbol_back("[0-9)x]");
    if (!symbol_back.match(QString(str.back())).hasMatch() ||
        (x_ && ui->x_field->text().isEmpty())) {
      ui->result_show->setText("ERROR");
    } else {
      QString x = ui->x_field->text();
      str.replace("x", x);
      std::string input_str = str.toStdString();
      controller_->Calc(input_str);
      if (!controller_->GetError()) {
        ui->result_show->setText(
            QString::number(controller_->GetResult(), 'g', 8));
      } else {
        ui->result_show->setText("ERROR");
      }
    }
  }
}

void MainWindow::on_pushButton_graph_clicked() {
  QString line = ui->result_show->text();
  if (x_ && !ui->x_field->text().isEmpty()) {
    QString x = ui->x_field->text();
    line.replace("x", x);
  }
  graph_.SetLine(line);
  graph_.Draw();
  graph_.show();
}

void MainWindow::on_pushButton_credit_clicked() { credit_.show(); }

void MainWindow::on_pushButton_CE_clicked() {
  SetLineEdit();
  QString text = line_edit_->text();
  if (!text.isEmpty()) {
    text.chop(1);
    line_edit_->setText(text);
  }
}

void MainWindow::on_pushButton_clear_clicked() { Clear_all(); }

void MainWindow::Clear_all() {
  ui->result_show->clear();
  ui->x_field->clear();
  x_ = false;
}

void MainWindow::SetLineEdit() {
  if (ui->radioButton_main_show->isChecked()) {
    line_edit_ = ui->result_show;
  } else {
    line_edit_ = ui->x_field;
  }
}
