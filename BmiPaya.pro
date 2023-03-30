QT       += core gui sql widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
include(./QXlsx/QXlsx.pri)

SOURCES += \
    aboutdialog.cpp \
    chequeprint.cpp \
    helpdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    num2str.cpp \
    numberformatdelegate.cpp \
    qdatejalali.cpp

HEADERS += \
    aboutdialog.h \
    chequeprint.h \
    helpdialog.h \
    mainwindow.h \
    num2str.h \
    numberformatdelegate.h \
    qdatejalali.h

FORMS += \
    aboutdialog.ui \
    chequeprint.ui \
    helpdialog.ui \
    mainwindow.ui
RC_ICONS = favicon.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
