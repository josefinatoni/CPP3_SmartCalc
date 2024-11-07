#include "deposit_calculator.h"

#include "ui_deposit_calculator.h"

Deposit_calculator::Deposit_calculator(s21::Controller &controller,
                                       QWidget *parent)
    : QDialog(parent), ui(new Ui::Deposit_calculator), controller(controller) {
  ui->setupUi(this);
}

Deposit_calculator::~Deposit_calculator() { delete ui; }

void Deposit_calculator::on_calc_clicked() {
  double deposit_sum = ui->line_sum->text().toDouble();
  int term = ui->line_term->text().toInt();
  double interest = ui->interest_rate->text().toDouble();
  double tax_rate = ui->tax_rate->text().toDouble();
  int period = 0;

  int capitalization = 0;
  double additional = 0;
  int add_date = 0;
  int part_date = 0;
  double percents = 0;
  double end_sum = 0;
  double tax = 0;
  double part_withdrawal = 0;

  if (ui->capitalization->isChecked()) {
    capitalization = 1;
  } else {
    period = ui->pmnt_period->currentIndex();
    if (period == 0)
      period = 1;
    else if (period == 1)
      period = 6;
    else if (period == 2)
      period = term;
  }
  if (ui->add_check->isChecked()) {
    additional = ui->addition->text().toDouble();
    add_date = ui->addition_when->currentIndex() * 3;
    if (add_date == 9)
      add_date = 12;
    else if (add_date == 0)
      add_date = 1;
  }
  if (ui->partial_check->isChecked()) {
    part_withdrawal = ui->partial->text().toDouble();
    part_date = ui->partial_when->currentIndex() * 3;
    if (part_date == 9)
      part_date = 12;
    else if (part_date == 0)
      part_date = 1;
  }
  controller.Deposit(deposit_sum, term, interest, tax_rate, capitalization,
                     add_date, part_date, part_withdrawal, additional,
                     &percents, &end_sum, &tax);
  ui->percents->setText(QString::number(percents, 'f', 2));
  ui->end_sum->setText(QString::number(end_sum, 'f', 2));
  ui->tax->setText(QString::number(tax, 'f', 2));
}
