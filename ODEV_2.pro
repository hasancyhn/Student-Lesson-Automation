QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    frm_ders.cpp \
    frm_notlar.cpp \
    frm_ogrenci.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    frm_ders.h \
    frm_notlar.h \
    frm_ogrenci.h \
    mainwindow.h

FORMS += \
    frm_ders.ui \
    frm_notlar.ui \
    frm_ogrenci.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
