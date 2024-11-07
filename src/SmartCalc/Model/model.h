#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_H_

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>

namespace s21 {
class Model {
 public:
  Model(){};
  ~Model() = default;

  double Calculator(std::string str, double num, int *err);

  void CreditCalculator(double *total_paymnt, double *interest, double *monthly,
                        double month_rate, double credit_sum, double percent,
                        double term, int flag, double *res, double *month);
  void DepositCalculator(double deposit_sum, int term, double interest,
                         double tax_rate, int capitalization, int add_date,
                         int part_date, double part_withdrawal,
                         double additional, double *percents, double *end_sum,
                         double *tax);

 private:
  void Validator(const std::string &str, std::string &exit_str);
  int Priority(char ch);
  int BracketsCheck(const std::string &str);
  int StringCheck(const std::string &str, std::string &exit);

  void RPolNotation(const std::string &str, std::string &output);
  int FuncsCount(const std::string &sign, size_t index,
                 std::stack<double> &nums);
  int Calculate(const std::string &pol, double &res, double num);

  bool IsBinaryOperator(char op);
  bool IsUnaryOperator(char op);
  int PerformBinaryOperation(char op, std::stack<double> &nums);
  int PerformUnaryOperation(char op, std::stack<double> &nums);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_H_