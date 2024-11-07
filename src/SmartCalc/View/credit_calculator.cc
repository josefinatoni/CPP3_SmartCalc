#include "credit_calculator.h"

#include "ui_credit_calculator.h"

Credit_calculator::Credit_calculator(s21::Controller &controller,
                                     QWidget *parent)
    : QDialog(parent), ui(new Ui::Credit_calculator), controller(controller) {
  ui->setupUi(this);
}

Credit_calculator::~Credit_calculator() { delete ui; }

void Credit_calculator::on_creditButton_clicked() {
  double total_paymnt = 0.0;
  double interest = 0.0;
  double monthly = 0.0;
  if (ui->annuity->isChecked() || ui->differentiated->isChecked()) {
    if (ui->loan_sum->text() != "" && ui->interest_rate->text() != "" &&
        ui->loan_term->text() != "") {
      double month_rate = 0.0;
      double credit_sum = ui->loan_sum->text().toDouble();
      double percent = ui->interest_rate->text().toDouble();
      double term = ui->loan_term->text().toDouble();
      if (ui->annuity->isChecked()) {
        int flag = 0;
        controller.Credit(&total_paymnt, &interest, &monthly, month_rate,
                          credit_sum, percent, term, flag, 0, 0);
        ui->mnth_paymnt->setText(QString::number(monthly, 'f', 2));
        ui->debt_interest->setText(QString::number(total_paymnt, 'f', 2));
        ui->charged_interest->setText(QString::number(interest, 'f', 2));
      }
      if (ui->differentiated->isChecked()) {
        int flag = 1;
        double res = 0.0;
        double month = 0.0;
        controller.Credit(&total_paymnt, &interest, &monthly, month_rate,
                          credit_sum, percent, term, flag, &res, &month);
        ui->mnth_paymnt->setText(QString::number(res, 'f', 2) + "..." +
                                 QString::number(month, 'f', 2));
        ui->debt_interest->setText(QString::number(total_paymnt, 'f', 2));
        ui->charged_interest->setText(QString::number(interest, 'f', 2));
      }
    }
  }
}
