QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_item_window.cpp \
    cartwindow.cpp \
    checkout.cpp \
    items.cpp \
    main.cpp \
    mainwindow.cpp \
    manageproducts.cpp \
    registrationwindow.cpp \
    shelf.cpp \
    userwindow.cpp

HEADERS += \
    add_item_window.h \
    cartwindow.h \
    checkout.h \
    items.h \
    mainwindow.h \
    manageproducts.h \
    registrationwindow.h \
    shelf.h \
    userwindow.h

FORMS += \
    add_item_window.ui \
    cartwindow.ui \
    checkout.ui \
    mainwindow.ui \
    manageproducts.ui \
    registrationwindow.ui \
    userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    AUC Logo.png
