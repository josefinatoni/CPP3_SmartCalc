#include "controller.h"

namespace s21 {
double Controller::Calculator(const std::string &expression, double num,
                              int *err) {
  return model_->Calculator(expression, num, err);
}

void Controller::Credit(double *total_paymnt, double *interest, double *monthly,
                        double month_rate, double credit_sum, double percent,
                        double term, int flag, double *res, double *month) {
  model_->CreditCalculator(total_paymnt, interest, monthly, month_rate,
                           credit_sum, percent, term, flag, res, month);
}

void Controller::Deposit(double deposit_sum, int term, double interest,
                         double tax_rate, int capitalization, int add_date,
                         int part_date, double part_withdrawal,
                         double additional, double *percents, double *end_sum,
                         double *tax) {
  model_->DepositCalculator(
      deposit_sum, term, interest, tax_rate, capitalization, add_date,
      part_date, part_withdrawal, additional, percents, end_sum, tax);
}

}  // namespace s21
