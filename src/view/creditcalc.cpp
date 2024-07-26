#include "mainwindow.h"
#include "ui_creditcalc.h"
CreditCalc::CreditCalc(QWidget* parent, s21::Controller* controller)
    : QWidget(parent), ui(new Ui::CreditCalc), controller_(controller) {
  ui->setupUi(this);
  setWindowTitle("Credit");
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_pushButton_calculate_clicked() {
  double sum = ui->sum_credit->value();
  int deadline = ui->deadline_credit->value();
  double percent = ui->percent_credit->value();
  ui->list_monhtly_pay->clear();
  if (ui->year_or_month->currentIndex() == YEAR) deadline *= 12;
  controller_->SetInput(sum, deadline, percent);
  if (ui->radioButton_ann->isChecked()) {
    controller_->AnnuityCalc();
    ui->label_monthly_pay_result->setText(
        QString::number(controller_->GetMonthlyPayment(), 'f', 2));
  } else {
    controller_->DifferentiatedCalc();
    ui->label_monthly_pay_result->clear();
    QDateTime current_date_time = QDateTime::currentDateTime();
    int current_year = current_date_time.date().year();
    int current_month = current_date_time.date().month();
    int count_month = 1;
    while (!controller_->GetQueueEmpty()) {
      QString current_yearMonth =
          QString("Payment %1 : %2-%3 = %4")
              .arg(count_month)
              .arg(current_year)
              .arg(current_month)
              .arg(QString::number(controller_->GetMonthlyPaymentFromQueue(),
                                   'f', 2));
      ui->list_monhtly_pay->addItem(current_yearMonth);
      current_date_time = current_date_time.addMonths(1);
      current_year = current_date_time.date().year();
      current_month = current_date_time.date().month();
      ++count_month;
    }
  }
  ui->label_overpayment_result->setText(
      QString::number(controller_->GetOverpayment(), 'f', 2));
  ui->label_total_sum_result->setText(
      QString::number(controller_->GetTotalPayment(), 'f', 2));
}

void CreditCalc::on_year_or_month_activated(int index) {
  if (index == YEAR)
    ui->deadline_credit->setMaximum(50);
  else if (index == MONTH)
    ui->deadline_credit->setMaximum(600);
}
