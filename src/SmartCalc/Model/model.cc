#include "model.h"

namespace s21 {

double Model::Calculator(std::string str, double num, int *err) {
  double res = 0.0;
  std::string exit_str;
  if (str.length() < 256) *err = StringCheck(str, exit_str);
  if (*err == 0) {
    std::string pol;
    RPolNotation(exit_str, pol);
    if (*err == 0) {
      *err = Calculate(pol, res, num);
    }
  }
  return res;
}

int Model::BracketsCheck(const std::string &str) {
  int flag = 1;
  int count = 0;
  for (char ch : str) {
    if (ch == '(') ++count;
    if (ch == ')') --count;
  }
  if (count == 0) flag = 0;
  return flag;
}

int Model::StringCheck(const std::string &str, std::string &exit) {
  int flag = 1;
  if (BracketsCheck(str) == 0) {
    Validator(str, exit);
    flag = 0;
  }
  if (!exit.empty()) {
    std::string functions = "sctnoaqglm";
    for (size_t i = 0; i < exit.length(); ++i) {
      if ((exit[i] >= '0' && exit[i] <= '9') || exit[i] == 'x') flag = 0;
      if (exit[0] == ')') flag = 1;
      if ((functions.find(exit[i]) != std::string::npos) &&
          exit[i + 1] == '(' && (exit[i + 2] == '\0' || exit[i + 2] == ')')) {
        flag = 1;
        break;
      }
    }
    char last_char = exit.back();
    if (!((last_char >= '0' && last_char <= '9') || last_char == '.' ||
          last_char == ')' || last_char == 'x')) {
      flag = 1;
    }
  }
  return flag;
}

void Model::Validator(const std::string &str, std::string &exit_str) {
  exit_str.clear();
  for (size_t i = 0; i < str.length(); ++i) {
    if (str.compare(i, 3, "sin") == 0) {
      exit_str += 's';
      i += 2;
    } else if (str.compare(i, 3, "cos") == 0) {
      exit_str += 'c';
      i += 2;
    } else if (str.compare(i, 3, "tan") == 0) {
      exit_str += 't';
      i += 2;
    } else if (str.compare(i, 4, "asin") == 0) {
      exit_str += 'n';
      i += 3;
    } else if (str.compare(i, 4, "acos") == 0) {
      exit_str += 'o';
      i += 3;
    } else if (str.compare(i, 4, "atan") == 0) {
      exit_str += 'a';
      i += 3;
    } else if (str.compare(i, 4, "sqrt") == 0) {
      exit_str += 'q';
      i += 3;
    } else if (str.compare(i, 3, "log") == 0) {
      exit_str += 'g';
      i += 2;
    } else if (str.compare(i, 2, "ln") == 0) {
      exit_str += 'l';
      ++i;
    } else if (str.compare(i, 3, "mod") == 0) {
      exit_str += 'm';
      i += 2;
    } else if (i == 0 && str[i] == '-') {
      exit_str += "0-";
    } else if (str[i] == '(' && str[i + 1] == '-') {
      exit_str += "(0";
    } else if ((((str[i] >= '0' && str[i] <= '9') || str[i] == ')') &&
                (str[i + 1] == '(' || str[i + 1] == 'a' || str[i + 1] == 'c' ||
                 str[i + 1] == 's' || str[i + 1] == 't' || str[i + 1] == 'm' ||
                 str[i + 1] == 'l')) ||
               (str[i] == 'x' && (str[i + 1] >= '0' && str[i + 1] <= '9')) ||
               ((str[i] >= '0' && str[i] <= '9') && str[i + 1] == 'x')) {
      exit_str += str[i];
      exit_str += '*';
    } else {
      exit_str += str[i];
    }
  }
}

int Model::Priority(char ch) {
  if (ch >= '0' && ch <= '9') {
    return 0;
  } else if (ch == 'x' || ch == '.') {
    return 0;
  } else if (ch == '(' || ch == ')') {
    return 1;
  } else if (ch == '+' || ch == '-') {
    return 2;
  } else if (ch == '*' || ch == '/' || ch == 'm') {
    return 3;
  } else if (ch == 'c' || ch == 's' || ch == 't' || ch == 'g' || ch == 'q' ||
             ch == 'l' || ch == '^' || ch == 'a' || ch == 'o' || ch == 'n') {
    return 4;
  } else {
    return -1;
  }
}

void Model::RPolNotation(const std::string &str, std::string &output) {
  std::stack<char> stack;
  for (size_t i = 0; i < str.size(); ++i) {
    char c = str[i];
    if (Priority(c) == 0) {
      output += c;
      if (i < str.size() - 1 && Priority(str[i + 1]) != 0) {
        output += ' ';
      }
    } else if (Priority(c) > 1) {
      if (stack.empty() || Priority(stack.top()) < Priority(c)) {
        stack.push(c);
      } else if (Priority(stack.top()) >= Priority(c)) {
        while (!stack.empty() && Priority(stack.top()) >= Priority(c)) {
          output += stack.top();
          stack.pop();
        }
        stack.push(c);
      }
    } else if (c == 'x') {
      output += c;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.empty() && stack.top() != '(') {
        output += stack.top();
        stack.pop();
      }
      stack.pop();
    }
  }
  while (!stack.empty()) {
    output += stack.top();
    stack.pop();
  }
}

int Model::Calculate(const std::string &pol, double &res, double num) {
  int flag = 0;
  std::stack<double> stack;
  for (size_t i = 0; i < pol.size(); ++i) {
    if (pol[i] == 'x') {
      stack.push(num);
    } else if ((pol[i] >= '0' && pol[i] <= '9') || pol[i] == '.') {
      size_t j = i;
      while (j < pol.size() &&
             ((pol[j] >= '0' && pol[j] <= '9') || pol[j] == '.')) {
        ++j;
      }
      std::string numbers = pol.substr(i, j - i);
      stack.push(std::stod(numbers));
      i = j - 1;
    } else if (flag == 0 &&
               !((pol[i] == '-' || pol[i] == '*' || pol[i] == '/') &&
                 stack.size() == 1)) {
      flag = FuncsCount(pol, i, stack);
    }
  }
  if (!stack.empty()) {
    res = stack.top();
    stack.pop();
  }
  return flag;
}

int Model::FuncsCount(const std::string &sign, size_t index,
                      std::stack<double> &nums) {
  int flag = 0;
  char op = sign[index];

  if (IsBinaryOperator(op)) {
    flag = PerformBinaryOperation(op, nums);
  } else if (IsUnaryOperator(op)) {
    flag = PerformUnaryOperation(op, nums);
  }
  return flag;
}

bool Model::IsBinaryOperator(char op) {
  return op == '+' || op == '-' || op == '*' || op == '/' || op == 'm' ||
         op == '^';
}

bool Model::IsUnaryOperator(char op) {
  return op == 's' || op == 'c' || op == 't' || op == 'n' || op == 'o' ||
         op == 'a' || op == 'l' || op == 'g' || op == 'q';
}

int Model::PerformBinaryOperation(char op, std::stack<double> &nums) {
  double num2 = nums.top();
  nums.pop();
  double num1 = nums.top();
  nums.pop();
  int flag = 0;

  switch (op) {
    case '+':
      nums.push(num1 + num2);
      break;
    case '-':
      nums.push(num1 - num2);
      break;
    case '*':
      nums.push(num1 * num2);
      break;
    case '/':
      if (num2 != 0) {
        nums.push(num1 / num2);
      } else {
        flag = 1;
      }
      break;
    case 'm':
      if (num1 != 0 && num2 != 0) {
        nums.push(fmod(num1, num2));
      } else {
        flag = 1;
      }
      break;
    case '^':
      nums.push(pow(num1, num2));
  }
  return flag;
}

int Model::PerformUnaryOperation(char op, std::stack<double> &nums) {
  double num = nums.top();
  nums.pop();

  switch (op) {
    case 's':
      nums.push(sin(num));
      break;
    case 'c':
      nums.push(cos(num));
      break;
    case 't':
      nums.push(tan(num));
      break;
    case 'n':
      nums.push(asin(num));
      break;
    case 'o':
      nums.push(acos(num));
      break;
    case 'a':
      nums.push(atan(num));
      break;
    case 'l':
      nums.push(log(num));
      break;
    case 'g':
      nums.push(log10(num));
      break;
    case 'q':
      nums.push(sqrt(num));
      break;
  }
  return 0;
}

void Model::CreditCalculator(double *total_paymnt, double *interest,
                             double *monthly, double month_rate,
                             double credit_sum, double percent, double term,
                             int flag, double *res, double *month) {
  if (credit_sum > 0 && percent > 0 && term > 0) {
    month_rate = percent / 12 / 100;
    if (flag == 0) {
      *monthly =
          credit_sum *
          (month_rate + (month_rate / (pow((1 + month_rate), term) - 1)));
      *total_paymnt = *monthly * term;
    } else if (flag == 1) {
      for (int i = 0; i < term; ++i) {
        *month = credit_sum / term +
                 (credit_sum - (credit_sum / term) * i) * month_rate;
        if (i == 0) *res = *month;
        *total_paymnt += *month;
      }
    }
    *interest = *total_paymnt - credit_sum;
  }
}

void Model::DepositCalculator(double deposit_sum, int term, double interest,
                              double tax_rate, int capitalization, int add_date,
                              int part_date, double part_withdrawal,
                              double additional, double *percents,
                              double *end_sum, double *tax) {
  double cap_account = deposit_sum;
  double account = 0;
  double period_paymnt = 0;
  for (int i = 1; i <= term; ++i) {
    if (capitalization) {
      *percents += cap_account * (interest / 12 / 100);
      *tax += *percents * (tax_rate / 12 / 100);
      cap_account += cap_account * (interest / 12 / 100) - *tax;
      if (additional && !fmod(i, add_date) && (i != term)) {
        cap_account += additional;
      }
      if (part_withdrawal && !fmod(i, part_date) && (i != term)) {
        cap_account -= part_withdrawal;
      }
    } else {
      account = deposit_sum * (interest / 12 / 100);
      *tax += account * (tax_rate / 12 / 100);
      if (additional && !fmod(i, add_date) && (i != term)) {
        deposit_sum += additional;
      }
      if (part_withdrawal && !fmod(i, part_date) && (i != term)) {
        deposit_sum -= part_withdrawal;
      }
      period_paymnt += account;
      *percents = period_paymnt;
    }
  }
  if (capitalization) {
    *end_sum = cap_account;
  } else {
    *end_sum = deposit_sum + period_paymnt - *tax;
  }
}

}  // namespace s21
