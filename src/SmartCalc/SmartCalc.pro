QT       += core gui
QT += printsupport
ICON = icon/icon.icns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/controller.cc \
    Model/model.cc \
    View/credit_calculator.cc \
    View/deposit_calculator.cc \
    main.cc \
    View/calculator.cc \
    qcustomplot.cpp

HEADERS += \
    Controller/controller.h \
    Model/model.h \
    View/calculator.h \
    View/credit_calculator.h \
    View/deposit_calculator.h \
    qcustomplot.h

FORMS += \
    View/calculator.ui \
    View/credit_calculator.ui \
    View/deposit_calculator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
