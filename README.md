# SmartCalc v2.0

Реализация SmartCalc v2.0.

## Contents

1. [Introduction](#introduction)
2. [Information](#information)
    3.1. [Part 1](#part-1-реализация-smartcalc-v20) \
    3.2. [Part 2](#part-2-дополнительно-кредитный-калькулятор) \
    3.3. [Part 3](#part-3-дополнительно-депозитный-калькулятор) 

## Introduction

В данном проекте предстояло в парадигме объектно-ориентированного программирования реализовать на языке программирования С++ расширенную версию обычного калькулятора. Помимо базовых арифметических операций, как плюс-минус и умножить-поделить, калькулятор дополнен возможностью вычисления арифметических выражений с учетом приоритетов, а также некоторыми математическими функциями (синус, косинус, логарифм и т. д.). Помимо вычисления выражений калькулятор еще поддерживает использование переменной x и построение графика соответствующей функции. В качестве дополнительных улучшений реализованы кредитный и депозитный калькуляторы.

## Information
Для реализации калькулятора использован *алгоритм Дейкстры* для перевода выражений в *обратную польскую нотацию*. 


## Part 1. Реализация SmartCalc v2.0

- Программа разработана на языке C++ стандарта C++17.
- При написании кода придерживались Google Style.
- Классы реализованы внутри пространства имен `s21`.
- Подготовлено полное покрытие unit-тестами модулей, связанных с вычислением выражений, c помощью библиотеки GTest.
- Сборка программы настроена с помощью Makefile со стандартным набором целей для GNU-программ: all, install, uninstall, clean, dvi, dist, tests. 
- Реализация с графическим пользовательским интерфейсом, на базе любой GUI-библиотеки Qt.
- Программа реализована с использованием паттерна MVC, а также:
    - нет кода бизнес-логики в коде представлений;
    - нет кода интерфейса в контроллере и в модели;
    - контроллеры - тонкие.
- На вход программы могут подаваться как целые числа, так и вещественные числа, записанные и через точку, и в экспоненциальной форме записи.
- Вычисление производится после полного ввода вычисляемого выражения и нажатия на символ `=`.
- Вычисление произвольных скобочных арифметических выражений производится в инфиксной нотации.
- Вычисление произвольных скобочных арифметических выражений производится в инфиксной нотации с подстановкой значения переменной _x_ в виде числа.
- Есть возможность построения графика функции, заданной с помощью выражения в инфиксной нотации с переменной _x_ (с координатными осями, отметкой используемого масштаба и сеткой с адаптивным шагом).
    - Не требовалось предоставлять пользователю возможность менять масштаб.
- Область определения и область значения функций ограничиваются по крайней мере числами от -1000000 до 1000000.
- Проверяемая точность дробной части — минимум 7 знаков после запятой.
- У пользователя есть возможность ввода до 255 символов.
- Скобочные арифметические выражения в инфиксной нотации поддерживают следующие арифметические операции и математические функции:
    - **Арифметические операторы**:

        | Название оператора | Инфиксная нотация <br /> (Классическая) | Префиксная нотация <br /> (Польская нотация) |  Постфиксная нотация <br /> (Обратная польская нотация) |
        | ------ | ------ | ------ | ------ |
        | Скобки | (a + b) | (+ a b) | a b + |
        | Сложение | a + b | + a b | a b + |
        | Вычитание | a - b | - a b | a b - |
        | Умножение | a * b | * a b | a b * |
        | Деление | a / b | / a b | a b \ |
        | Возведение в степень | a ^ b | ^ a b | a b ^ |
        | Остаток от деления | a mod b | mod a b | a b mod |
        | Унарный плюс | +a | +a | a+ |
        | Унарный минус | -a | -a | a- |

    - **Функции**:
  
        | Описание функции | Функция |   
        | ---------------- | ------- |  
        | Вычисляет косинус | cos(x) |   
        | Вычисляет синус | sin(x) |  
        | Вычисляет тангенс | tan(x) |  
        | Вычисляет арккосинус | acos(x) | 
        | Вычисляет арксинус | asin(x) | 
        | Вычисляет арктангенс | atan(x) |
        | Вычисляет квадратный корень | sqrt(x) |
        | Вычисляет натуральный логарифм | ln(x) | 
        | Вычисляет десятичный логарифм | log(x) |

## Part 2. Дополнительно. Кредитный калькулятор

Предусмотрен специальный режим «кредитный калькулятор»:
 - Вход: общая сумма кредита, срок, процентная ставка, тип (аннуитетный, дифференцированный).
 - Выход: ежемесячный платеж, переплата по кредиту, общая выплата.

## Part 3. Дополнительно. Депозитный калькулятор

Предусмотрен специальный режим «калькулятор доходности вкладов»:
 - Вход: сумма вклада, срок размещения, процентная ставка, налоговая ставка, периодичность выплат, капитализация процентов, список пополнений, список частичных снятий.
 - Выход: начисленные проценты, сумма налога, сумма на вкладе к концу срока.
