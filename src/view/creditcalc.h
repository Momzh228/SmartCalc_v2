#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QDateTime>
#include <QWidget>

#include "../controller/controller.h"
namespace Ui {
class CreditCalc;
}

class CreditCalc : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget* parent, s21::Controller* controller);
  ~CreditCalc();

 private slots:
  void on_pushButton_calculate_clicked();
  void on_year_or_month_activated(int index);

 private:
  enum Deadline { MONTH, YEAR };
  Ui::CreditCalc* ui;
  s21::Controller* controller_;
};

#endif  // CREDITCALC_H
