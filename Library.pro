QT       += core gui sql
QT += widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += charts sql
QT += core gui sql charts printsupport  # Ajoutez printsupport
CONFIG += c++17
QT += core gui widgets sql charts
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_CHARTS_USE_NAMESPACE
SOURCES += \
    Login.cpp \
    ManageAuthors.cpp \
    addBook.cpp \
    addMember.cpp \
    authorsList.cpp \
    bookList.cpp \
    deleteMember.cpp \
    deletebook.cpp \
    digitalLibrary.cpp \
    editBook.cpp \
    editMember.cpp \
    genreList.cpp \
    main.cpp \
    manageBooks.cpp \
    membersList.cpp \
    newPasswd.cpp \
    signUp.cpp \
    stats.cpp \
    studentlibrary.cpp

HEADERS += \
    Login.h \
    ManageAuthors.h \
    addBook.h \
    addMember.h \
    authorsList.h \
    bookList.h \
    deleteMember.h \
    deletebook.h \
    digitalLibrary.h \
    editBook.h \
    editMember.h \
    genreList.h \
    manageBooks.h \
    membersList.h \
    newPasswd.h \
    signUp.h \
    stats.h \
    studentlibrary.h

FORMS += \
    Login.ui \
    ManageAuthors.ui \
    addBook.ui \
    addMember.ui \
    authorsList.ui \
    bookList.ui \
    deleteMember.ui \
    deletebook.ui \
    digitalLibrary.ui \
    editBook.ui \
    editMember.ui \
    genreList.ui \
    manageBooks.ui \
    membersList.ui \
    newPasswd.ui \
    signUp.ui \
    stats.ui \
    studentlibrary.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES +=
# Pour le style moderne
QT += concurrent
QT -= core5compat

