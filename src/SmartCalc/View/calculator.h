#ifndef CPP3_SMARTCALC_V2_0_1_SRC_VIEW_CALCULATOR_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_VIEW_CALCULATOR_H_

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <regex>

#include "../Controller/controller.h"
#include "credit_calculator.h"
#include "deposit_calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow {
  Q_OBJECT

 public:
  explicit Calculator(s21::Controller &controller, QWidget *parent = nullptr);
  ~Calculator();

 private slots:

  void buttons();
  void unary();
  void functions();
  void operations();

  void on_ACButton_clicked();
  void on_CButton_clicked();
  void on_creditButton_clicked();
  void on_depositButton_clicked();
  void on_graphButton_clicked();
  void on_equalButton_clicked();
  void on_dotButton_clicked();

 private:
  Ui::Calculator *ui;
  s21::Controller &controller;
};

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_VIEW_CALCULATOR_H_
