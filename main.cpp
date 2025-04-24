#include "Login.h"
#include "signUp.h"
#include "newPasswd.h"
#include "manageBooks.h"
#include "ManageAuthors.h"
#include "addMember.h"
#include "editMember.h"
#include "membersList.h"
#include "addBook.h"
#include"historique.h"
// #include "stats.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    // Historique historique;
    // historique.initReservationFile();
    w.show();
    return a.exec();
}
