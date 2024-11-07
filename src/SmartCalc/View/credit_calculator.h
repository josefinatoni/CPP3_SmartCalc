#ifndef CREDIT_CALCULATOR_H
#define CREDIT_CALCULATOR_H

#include <QDialog>

#include "../Controller/controller.h"

namespace Ui {
class Credit_calculator;
}

class Credit_calculator : public QDialog {
  Q_OBJECT

 public:
  explicit Credit_calculator(s21::Controller &controller,
                             QWidget *parent = nullptr);
  ~Credit_calculator();

 private slots:
  void on_creditButton_clicked();

 private:
  Ui::Credit_calculator *ui;
  s21::Controller &controller;
};

#endif  // CREDIT_CALCULATOR_H
