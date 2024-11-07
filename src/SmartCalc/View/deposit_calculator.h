#ifndef DEPOSIT_CALCULATOR_H
#define DEPOSIT_CALCULATOR_H

#include <QDialog>

#include "../Controller/controller.h"

namespace Ui {
class Deposit_calculator;
}

class Deposit_calculator : public QDialog {
  Q_OBJECT

 public:
  explicit Deposit_calculator(s21::Controller &controller,
                              QWidget *parent = nullptr);
  ~Deposit_calculator();

 private slots:
  void on_calc_clicked();

 private:
  Ui::Deposit_calculator *ui;
  s21::Controller &controller;
};

#endif  // DEPOSIT_CALCULATOR_H
