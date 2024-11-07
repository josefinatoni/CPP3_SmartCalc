#include "calculator.h"

#include "./ui_calculator.h"
#include "credit_calculator.h"
#include "deposit_calculator.h"

Calculator::Calculator(s21::Controller &controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator), controller(controller) {
  ui->setupUi(this);

  connect(ui->oneButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->twoButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->threeButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->fourButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->fiveButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->sixButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->sevenButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->eightButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->nineButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->nullButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->xButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->lBracketButton, SIGNAL(clicked()), this, SLOT(buttons()));
  connect(ui->rBracketButton, SIGNAL(clicked()), this, SLOT(buttons()));

  connect(ui->powerButton, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->minusButton, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->plusButton, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->divButton, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->mulButton, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->modButton, SIGNAL(clicked()), this, SLOT(operations()));

  connect(ui->unaryButton, SIGNAL(clicked()), this, SLOT(unary()));

  connect(ui->sqrtButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->sinButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->cosButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->tanButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->asinButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->acosButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->atanButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->logButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->lnButton, SIGNAL(clicked()), this, SLOT(functions()));

  ui->widget->setBackground(QColor(112, 128, 144));
  ui->widget->xAxis->setBasePen(QPen(QColor(217, 217, 217)));
  ui->widget->yAxis->setBasePen(QPen(QColor(217, 217, 217)));
  ui->widget->xAxis->setTickLabelColor(QColor(217, 217, 217));
  ui->widget->yAxis->setTickLabelColor(QColor(217, 217, 217));
  ui->widget->xAxis->setTickPen(QPen(QColor(217, 217, 217)));
  ui->widget->yAxis->setTickPen(QPen(QColor(217, 217, 217)));
  ui->widget->xAxis->setSubTickPen(QPen(QColor(217, 217, 217)));
  ui->widget->yAxis->setSubTickPen(QPen(QColor(217, 217, 217)));
  ui->widget->xAxis->grid()->setPen(QPen(Qt::gray));
  ui->widget->yAxis->grid()->setPen(QPen(Qt::gray));

  ui->widget->xAxis->setRange(-5, 5);
  ui->widget->yAxis->setRange(-5, 5);
}

Calculator::~Calculator() { delete ui; }

void Calculator::buttons() {
  QPushButton *button = (QPushButton *)sender();

  if (ui->calcScreen->text().isEmpty() || ui->calcScreen->text() == "Error" ||
      ui->calcScreen->text() == "0" || ui->calcScreen->text() == "inf") {
    ui->calcScreen->setText(button->text());
  } else {
    ui->calcScreen->setText(ui->calcScreen->text() + button->text());
  }
}

void Calculator::operations() {
  QPushButton *button = (QPushButton *)sender();
  QString currentText = ui->calcScreen->text();
  int flag = 1;
  if (currentText.endsWith("*") || currentText.endsWith("/") ||
      currentText.endsWith("+") || currentText.endsWith("-") ||
      currentText.endsWith("mod") || currentText.endsWith("^"))
    flag = 0;

  if (button->text() == "mod" && currentText.isEmpty()) {
    ui->calcScreen->setText("Error");
    return;
  }

  if (ui->calcScreen->text().isEmpty() || ui->calcScreen->text() == "Error" ||
      ui->calcScreen->text() == "inf") {
    ui->calcScreen->setText("0" + button->text());
  } else if (flag == 1) {
    ui->calcScreen->setText(ui->calcScreen->text() + button->text());
  }
}

void Calculator::unary() {
  QPushButton *button = (QPushButton *)sender();
  double all_numbers;
  QString new_label;

  if (button->text() == "+/-") {
    all_numbers = (ui->calcScreen->text()).toDouble();
    all_numbers = all_numbers * -1;
    new_label = QString::number(all_numbers, 'g', 15);
    ui->calcScreen->setText(new_label);
  }
}

void Calculator::on_dotButton_clicked() {
  QString screen = ui->calcScreen->text();
  if (screen.endsWith('+') || screen.endsWith('-') || screen.endsWith('*') ||
      screen.endsWith('/') || screen.isEmpty()) {
    ui->calcScreen->setText(screen + "0.");
  } else {
    int len = screen.length();
    bool canAddDot = true;
    for (int i = len - 1; i >= 0; i--) {
      QChar ch = screen.at(i);
      if (!ch.isDigit() && ch != '.') {
        canAddDot = false;
        break;
      }
      if (ch == '.') {
        canAddDot = false;
        break;
      }
    }
    if (canAddDot) {
      ui->calcScreen->setText(screen + ".");
    }
  }
}

void Calculator::functions() {
  QPushButton *button = (QPushButton *)sender();

  if (ui->calcScreen->text().isEmpty() || ui->calcScreen->text() == "Error" ||
      ui->calcScreen->text() == "0" || ui->calcScreen->text() == "inf") {
    ui->calcScreen->setText(button->text() + "(");
  } else {
    ui->calcScreen->setText(ui->calcScreen->text() + button->text() + "(");
  }
}

void Calculator::on_equalButton_clicked() {
  int error = 0;
  double res = 0.0;
  double number_x = 0.0;
  if (ui->enter_x->text() != "Enter x") {
    number_x = ui->enter_x->text().toDouble();
  }
  std::string expression = ui->calcScreen->text().toStdString();

  res = controller.Calculator(expression, number_x, &error);
  if (error == 0) ui->calcScreen->setText(QString::number(res, 'g', 15));
  if (error == 1 || std::isnan(res)) ui->calcScreen->setText("Error");
}

void Calculator::on_ACButton_clicked() { ui->calcScreen->setText(""); }

void Calculator::on_CButton_clicked() {
  QString new_label = ui->calcScreen->text();
  if (new_label.isEmpty()) return;
  QStringList functions = {"asin", "acos", "atan", "sin", "cos",   "tan",
                           "sqrt", "log",  "ln",   "mod", "Error", "inf"};
  for (const QString &func : functions) {
    if (new_label.endsWith(func)) {
      new_label.chop(func.length());
      ui->calcScreen->setText(new_label);
      return;
    }
  }
  new_label.chop(1);
  ui->calcScreen->setText(new_label);
}

void Calculator::on_graphButton_clicked() {
  ui->widget->clearGraphs();
  std::string str1 = ui->calcScreen->text().toStdString();
  double x_begin = ui->min_x->text().toDouble();
  double x_end = ui->max_x->text().toDouble();
  double y_begin = ui->min_y->text().toDouble();
  double y_end = ui->max_y->text().toDouble();
  ui->widget->xAxis->setRange(x_begin, x_end);
  ui->widget->yAxis->setRange(y_begin, y_end);
  if (x_begin < x_end && y_begin < y_end) {
    double h = 0.01;
    int N = (x_end - x_begin) / h + 2;
    QVector<double> x(N), y(N);
    int i = 0;
    int err = 0;
    float X = 0.0;
    if (str1.empty() || ui->calcScreen->text() == "Error") {
      ui->widget->clearGraphs();
      ui->calcScreen->setText("Error");
      return;
    }
    for (X = x_begin; X <= x_end; X += h) {
      double res = 0.0;
      res = controller.Calculator(str1, X, &err);
      if (err == 0) {
        x[i] = X;
        y[i] = res;
        i++;
      }
    }
    if (err == 0) {
      ui->widget->addGraph();
      ui->widget->graph(0)->setData(x, y);
      ui->widget->graph(0)->setPen(QColor(217, 217, 217));
      ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
      ui->widget->graph(0)->setScatterStyle(
          QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
      ui->widget->replot();
      x.clear();
      y.clear();
    } else {
      ui->calcScreen->setText("Error");
    }
  }
}

void Calculator::on_creditButton_clicked() {
  Credit_calculator window(controller);
  window.setModal(true);
  window.exec();
}

void Calculator::on_depositButton_clicked() {
  Deposit_calculator window(controller);
  window.setModal(true);
  window.exec();
}
