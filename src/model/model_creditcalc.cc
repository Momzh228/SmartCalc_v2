#include "model_creditcalc.h"
namespace s21 {
CreditCalc::CreditCalc()
    : sum_(0),
      deadline_(0),
      percent_(0),
      monthly_payment_(0),
      overpayment_(0),
      total_payment_(0){};
CreditCalc::~CreditCalc() = default;
void CreditCalc::SetInput(double sum, int deadline, double percent) {
  sum_ = sum;
  deadline_ = deadline;
  percent_ = percent;
};
void CreditCalc::AnnuityCalc() {
  double p = percent_ / 100 / 12;
  monthly_payment_ = sum_ * (p + (p / (powl(1 + p, deadline_) - 1)));
  total_payment_ = monthly_payment_ * deadline_;
  overpayment_ = total_payment_ - sum_;
};
void CreditCalc::DifferentiatedCalc() {
  total_payment_ = 0;
  double p = percent_ / 100 / 12;
  monthly_payment_ = sum_ / deadline_ + sum_ * p;
  double sum_cpy = sum_;
  for (int i = 1; i <= deadline_; ++i) {
    double payment = sum_ / deadline_ + sum_cpy * p;
    monthly_payment_queue_.push(payment);
    total_payment_ += payment;
    sum_cpy = sum_ - i * sum_ / deadline_;
  }
  overpayment_ = total_payment_ - sum_;
}
double CreditCalc::GetMonthlyPayment() { return monthly_payment_; }
double CreditCalc::GetOverpayment() { return overpayment_; };
double CreditCalc::GetTotalPayment() { return total_payment_; };
double CreditCalc::GetMonthlyPaymentFromQueue() {
  double monthly_payment = monthly_payment_queue_.front();
  monthly_payment_queue_.pop();
  return monthly_payment;
};
bool CreditCalc::GetQueueEmpty() { return monthly_payment_queue_.empty(); };

}  // namespace s21