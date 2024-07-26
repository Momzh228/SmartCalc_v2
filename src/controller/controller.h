#ifndef S21_SMART_CALC_V_2_0_SRC_CONTROLLER_CONTROLLER_H_
#define S21_SMART_CALC_V_2_0_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model_calculator.h"
#include "../model/model_creditcalc.h"
namespace s21 {
class Controller {
 public:
  Controller(Calculator* calc, CreditCalc* credit);
  ~Controller();
  void Calc(std::string input_str);
  double GetResult();
  bool GetError();
  void SetInput(double sum, int deadline, double percent);
  void AnnuityCalc();
  void DifferentiatedCalc();
  double GetMonthlyPayment();
  double GetOverpayment();
  double GetTotalPayment();
  double GetMonthlyPaymentFromQueue();
  bool GetQueueEmpty();

 private:
  Calculator* calc_;
  CreditCalc* credit_;
};
}  // namespace s21

#endif  // S21_SMART_CALC_V_2_0_SRC_CONTROLLER_CONTROLLER_H_
