#ifndef S21_SMART_CALC_V_2_0_SRC_MODEL_MODEL_H_
#define S21_SMART_CALC_V_2_0_SRC_MODEL_MODEL_H_

#include <algorithm>
#include <cmath>
#include <cstring>
#include <sstream>
#include <stack>
#include <string>

namespace s21 {
class Calculator {
 public:
  Calculator()
      : stack_rpn_({'0'}),
        rpn_(""),
        rpn_str_(""),
        result_(0),
        is_error_(false){};
  ~Calculator() = default;
  void Calc(std::string input_str);
  double GetResult();
  bool GetError();

 private:
  void DigitProcessing(std::string::iterator& it, std::string::iterator it_end);
  void OperationProcessing(std::string::iterator& it);
  void PostfixProcessing();
  void Processing(std::stack<double>& result, std::string token);
  int GetPresedense(char ch);
  bool IsOperation(char oper);
  bool IsBinaryOperation(std::string token);
  bool IsBinaryOperation(char operation);
  void Clear();

  std::stack<char> stack_rpn_;
  std::ostringstream rpn_;
  std::string rpn_str_;
  double result_;
  bool is_error_;
};
}  // namespace s21
#endif  // S21_SMART_CALC_V_2_0_SRC_MODEL_MODEL_H_
