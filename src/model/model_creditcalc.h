#ifndef S21_SMART_CALC_V_2_0_SRC_MODEL_CREDITCALC_H_
#define S21_SMART_CALC_V_2_0_SRC_MODEL_CREDITCALC_H_

#include <queue>

#include "model_calculator.h"
namespace s21 {
class CreditCalc {
 public:
  CreditCalc();
  ~CreditCalc();
  void SetInput(double sum, int deadline, double percent);
  void AnnuityCalc();
  void DifferentiatedCalc();
  double GetMonthlyPayment();
  double GetOverpayment();
  double GetTotalPayment();
  double GetMonthlyPaymentFromQueue();
  bool GetQueueEmpty();

 private:
  std::queue<double> monthly_payment_queue_;
  double sum_;
  int deadline_;
  double percent_;
  double monthly_payment_;
  double overpayment_;
  double total_payment_;
};
}  // namespace s21
#endif  // S21_SMART_CALC_V_2_0_SRC_MODEL_CREDITCALC_H_