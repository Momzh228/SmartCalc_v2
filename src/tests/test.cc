#include "../controller/controller.h"
#include "../model/model_calculator.h"
#include "../model/model_creditcalc.h"
#include "gtest/gtest.h"
using namespace s21;

TEST(S21_Smart_Calc, test_1) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  ;
  std::string input_str = "2+2*2-2";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), 4, 1e-7);
}

TEST(S21_Smart_Calc, test_2) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  ;
  std::string input_str = "sin(5)^2+cos(5)^2";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), 1, 1e-7);
}

TEST(S21_Smart_Calc, test_3) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "acos(-1)*2^2^2";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), 50.2654824, 1e-7);
}

TEST(S21_Smart_Calc, test_4) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "2/6*5mod3+10-9";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), 2.6666666, 1e-7);
}

TEST(S21_Smart_Calc, test_5) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "-5+cos(10)*sin(1)/tan(1)";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), -5.4533522, 1e-7);
}

TEST(S21_Smart_Calc, test_6) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "((ln(10)*2)+2)/2";
  controller.Calc(input_str);

  EXPECT_NEAR(controller.GetResult(), 3.3025850, 1e-7);
}

TEST(S21_Smart_Calc, test_7) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "5mod3*10/15+6+atan(5)";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), 8.7067341, 1e-7);
}

TEST(S21_Smart_Calc, test_8) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "sin()";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_9) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "sin(5";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_10) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "asin(1)";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), 1.5707963, 1e-7);
}

TEST(S21_Smart_Calc, test_11) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "sqrt(4)";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), 2, 1e-7);
}

TEST(S21_Smart_Calc, test_12) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "log(10)";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), 1, 1e-7);
}

TEST(S21_Smart_Calc, test_13) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "2.2.2+1";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_14) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "(2e+2)";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), 200, 1e-7);
}

TEST(S21_Smart_Calc, test_15) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "(2ee2)";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_16) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "123 123";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_17) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "1+1)+1";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_18) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "e7";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_19) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "(+)";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_20) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "2(2+2)";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_21) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "2ee2";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_22) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "son(5)";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_23) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "2+";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_24) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "2+2*sin(2).";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
  input_str = "2+2*sin(2).";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_25) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "1+6)+3";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
  input_str = "1+6)+3";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_26) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "(*)";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_27) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "(+5-4)";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), 1, 1e-7);
}

TEST(S21_Smart_Calc, test_28) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "(-sqrt(4))";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), -2, 1e-7);
}

TEST(S21_Smart_Calc, test_29) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "(*/2)";
  controller.Calc(input_str);
  EXPECT_TRUE(controller.GetError());
}

TEST(S21_Smart_Calc, test_30) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string input_str = "(-sqrt(9)^2)";
  controller.Calc(input_str);
  EXPECT_NEAR(controller.GetResult(), 9, 1e-7);
}

TEST(S21_Smart_Calc, Credit_1) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetInput(100000, 12, 5);
  controller.AnnuityCalc();
  EXPECT_NEAR(controller.GetMonthlyPayment(), 8560.75, 1e-2);
  EXPECT_NEAR(controller.GetOverpayment(), 2728.98, 1e-2);
  EXPECT_NEAR(controller.GetTotalPayment(), 102728.98, 1e-2);
}

TEST(S21_Smart_Calc, Credit_2) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetInput(100000, 12, 5);
  std::queue<double> check_monthly_payment(
      {8750.00, 8715.28, 8680.56, 8645.83, 8611.11, 8576.39, 8541.67, 8506.94,
       8472.22, 8437.50, 8402.78, 8368.06});
  controller.DifferentiatedCalc();
  while (!controller.GetQueueEmpty()) {
    EXPECT_NEAR(controller.GetMonthlyPaymentFromQueue(),
                check_monthly_payment.front(), 1e-2);
    check_monthly_payment.pop();
  }
  EXPECT_NEAR(controller.GetOverpayment(), 2708.33, 1e-2);
  EXPECT_NEAR(controller.GetTotalPayment(), 102708.33, 1e-2);
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
