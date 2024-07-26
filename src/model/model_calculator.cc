#include "model_calculator.h"

namespace s21 {
void Calculator::Calc(std::string input_str) {
  is_error_ = false;
  Clear();
  std::string::iterator it = input_str.begin();
  std::string::iterator prev_it;
  if (*it == '-' || *it == '+') {
    if (*it == '-') {
      rpn_ << *it;
    }
    ++it;
  }
  while (it != input_str.end() && !is_error_) {
    if (std::isdigit(*it)) {
      DigitProcessing(it, input_str.end());
    } else if (IsOperation(*it)) {
      if ((*it == '-' || *it == '+') && !std::isdigit(*prev_it) &&
          *prev_it != ')') {
        if (!std::isdigit(*(it + 1))) {
          stack_rpn_.push('~');
        } else if (*it == '-') {
          rpn_ << *it;
        } else {
          ++it;
          continue;
        }
      } else {
        OperationProcessing(it);
      }
    } else if (*it == '(') {
      stack_rpn_.push(*it);
    } else if (*it == ')') {
      if (*prev_it == '(' || (!std::isdigit(*prev_it) && *prev_it != ')')) {
        is_error_ = true;
        continue;
      }
      while (stack_rpn_.top() != '0' && stack_rpn_.top() != '(') {
        rpn_ << stack_rpn_.top() << ' ';
        stack_rpn_.pop();
      }
      if (stack_rpn_.top() == '(')
        stack_rpn_.pop();
      else {
        is_error_ = true;
        return;
      }
    } else {
      is_error_ = true;
    }
    prev_it = it;
    ++it;
  }

  if (!is_error_) {
    while (stack_rpn_.top() != '0') {
      rpn_ << stack_rpn_.top() << ' ';
      stack_rpn_.pop();
    }

    rpn_str_ = rpn_.str();
    PostfixProcessing();
  }
}
void Calculator::PostfixProcessing() {
  std::stack<double> result;
  std::istringstream expression(rpn_str_);
  std::string token;
  std::string::iterator it_begin;
  while (expression >> token && !is_error_) {
    it_begin = token.begin();
    if (std::isdigit(*it_begin)) {
      result.push(std::stod(token));
    } else if (*it_begin == '-' && std::isdigit(*(it_begin + 1))) {
      token.erase(it_begin);
      result.push(std::stod(token) * -1);
    } else {
      if (token == "(" || token == ")") {
        is_error_ = true;
        return;
      }
      Processing(result, token);
    }
  }
  if (!is_error_) {
    result_ = result.top();
    result.pop();
    if (!result.empty()) {
      is_error_ = true;
    }
  }
}
void Calculator::Processing(std::stack<double>& result, std::string token) {
  if (result.empty()) {
    is_error_ = true;
    return;
  }
  double num_1 = result.top(), num_2 = 0;
  result.pop();
  if (IsBinaryOperation(token)) {
    if (result.empty()) {
      is_error_ = true;
      return;
    }
    num_2 = result.top();
    result.pop();
  }
  if (token == "+") {
    result.push(num_2 + num_1);
  } else if (token == "-") {
    result.push(num_2 - num_1);
  } else if (token == "*") {
    result.push(num_2 * num_1);
  } else if (token == "/") {
    result.push(num_2 / num_1);
  } else if (token == "%" || token == "m") {
    result.push(fmodl(num_2, num_1));
  } else if (token == "^") {
    result.push(powl(num_2, num_1));
  } else if (token == "s") {
    result.push(sinl(num_1));
  } else if (token == "c") {
    result.push(cosl(num_1));
  } else if (token == "t") {
    result.push(tanl(num_1));
  } else if (token == "S") {
    result.push(asinl(num_1));
  } else if (token == "C") {
    result.push(acosl(num_1));
  } else if (token == "T") {
    result.push(atanl(num_1));
  } else if (token == "q") {
    result.push(sqrtl(num_1));
  } else if (token == "l") {
    result.push(logl(num_1));
  } else if (token == "L") {
    result.push(log10l(num_1));
  } else if (token == "~") {
    result.push((num_1 * -1));
  }
}
bool Calculator::IsOperation(char oper) {
  bool is_oper = false;
  std::string char_set = "+-*/sctaml^";
  if (std::find(char_set.begin(), char_set.end(), oper) != char_set.end()) {
    is_oper = true;
  }
  return is_oper;
}
bool Calculator::IsBinaryOperation(std::string token) {
  bool is_binary_oper = false;
  std::string char_set = "+-*/^%";
  if (std::find(char_set.begin(), char_set.end(), *token.begin()) !=
      char_set.end()) {
    is_binary_oper = true;
  }
  return is_binary_oper;
}
bool Calculator::IsBinaryOperation(char operation) {
  bool is_binary_oper = false;
  std::string char_set = "+-*/^";
  if (std::find(char_set.begin(), char_set.end(), operation) !=
      char_set.end()) {
    is_binary_oper = true;
  }
  return is_binary_oper;
}
int Calculator::GetPresedense(char ch) {
  int precedency = 0;
  if (ch == '+' || ch == '-' || ch == '~') {
    precedency = 1;
  } else if (ch == '*' || ch == '/' || ch == '%' || ch == 'm') {
    precedency = 2;
  } else if (strchr("sctlaSCTLq", ch)) {
    precedency = 5;
  } else if (ch == '^') {
    precedency = 4;
  } else if (ch == '(') {
    precedency = -1;
  }
  return precedency;
}
void Calculator::OperationProcessing(std::string::iterator& it) {
  while ((GetPresedense(stack_rpn_.top()) >= GetPresedense(*it) ||
          (stack_rpn_.top() == '~' && GetPresedense(*it) != 5)) &&
         GetPresedense(stack_rpn_.top()) != 0 &&
         (GetPresedense(*it) != 4 || GetPresedense(stack_rpn_.top()) != 4)) {
    rpn_ << stack_rpn_.top() << ' ';
    stack_rpn_.pop();
  }
  if (IsBinaryOperation(*it)) {
    stack_rpn_.push(*it);
  } else {
    int pos = 3;
    char operation = '0';
    if (!strncmp(it.base(), "ln(", pos)) {
      operation = 'l';
    } else if (!strncmp(it.base(), "mod", pos)) {
      ++pos;
      operation = '%';
    } else if (!strncmp(it.base(), "log(", ++pos)) {
      operation = 'L';
    } else if (!strncmp(it.base(), "sin(", pos)) {
      operation = 's';
    } else if (!strncmp(it.base(), "cos(", pos)) {
      operation = 'c';
    } else if (!strncmp(it.base(), "tan(", pos)) {
      operation = 't';
    } else if (!strncmp(it.base(), "asin(", ++pos)) {
      operation = 'S';
    } else if (!strncmp(it.base(), "acos(", pos)) {
      operation = 'C';
    } else if (!strncmp(it.base(), "atan(", pos)) {
      operation = 'T';
    } else if (!strncmp(it.base(), "sqrt(", pos)) {
      operation = 'q';
    } else {
      is_error_ = true;
    }
    stack_rpn_.push(operation);
    it += pos - 2;
  }
}
void Calculator::DigitProcessing(std::string::iterator& it,
                                 std::string::iterator it_end) {
  int dot = 0;
  int e_stopper = 0;
  while ((std::isdigit(*it) || *it == '.' || *it == 'e' || *it == '+' ||
          *it == '-') &&
         !is_error_ && it != it_end && dot != 2 && e_stopper != 2) {
    if (*it == '.') {
      ++dot;
      if (dot == 2 || e_stopper) {
        is_error_ = true;
        return;
      }
    } else if (*it == 'e') {
      if (!(std::isdigit(*(it - 1)))) {
        is_error_ = true;
        return;
      }
      ++e_stopper;
    } else if (*it == '+' || *it == '-') {
      if (!e_stopper || *(it - 1) != 'e') {
        break;
      }
    }
    rpn_ << *it;
    ++it;
  }
  --it;
  rpn_ << ' ';
}
void Calculator::Clear() {
  while (stack_rpn_.top() != '0') {
    stack_rpn_.pop();
  }
  rpn_.str("");
  rpn_.clear();
  rpn_str_.clear();
  result_ = 0;
}
double Calculator::GetResult() { return result_; }
bool Calculator::GetError() { return is_error_; }

}  // namespace s21
