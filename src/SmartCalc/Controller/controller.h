#ifndef CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_

#include "../Model/model.h"

namespace s21 {
class Controller {
 public:
  Controller(Model *m) : model_(m){};

  double Calculator(const std::string &expression, double num, int *err);

  void Credit(double *total_paymnt, double *interest, double *monthly,
              double month_rate, double credit_sum, double percent, double term,
              int flag, double *res, double *month);
  void Deposit(double deposit_sum, int term, double interest, double tax_rate,
               int capitalization, int add_date, int part_date,
               double part_withdrawal, double additional, double *percents,
               double *end_sum, double *tax);

 private:
  Model *model_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_