#include "controller.h"
namespace s21 {
Controller::Controller(Calculator* calc, CreditCalc* credit)
    : calc_(calc), credit_(credit){};
Controller::~Controller() = default;
void Controller::Calc(std::string input_str) { calc_->Calc(input_str); }
double Controller::GetResult() { return calc_->GetResult(); }
bool Controller::GetError() { return calc_->GetError(); }
void Controller::SetInput(double sum, int deadline, double percent) {
  credit_->SetInput(sum, deadline, percent);
};
void Controller::AnnuityCalc() { credit_->AnnuityCalc(); }
void Controller::DifferentiatedCalc() { credit_->DifferentiatedCalc(); }
double Controller::GetMonthlyPayment() { return credit_->GetMonthlyPayment(); }
double Controller::GetOverpayment() { return credit_->GetOverpayment(); };
double Controller::GetTotalPayment() { return credit_->GetTotalPayment(); };
double Controller::GetMonthlyPaymentFromQueue() {
  return credit_->GetMonthlyPaymentFromQueue();
};
bool Controller::GetQueueEmpty() { return credit_->GetQueueEmpty(); };
}  // namespace s21
