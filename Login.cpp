#include "Login.h"
#include "ui_Login.h"
#include"studentlibrary.h"
#include <QMessageBox>
#include "digitalLibrary.h"
#include "signUp.h"
#include "newPasswd.h"
#include <QDebug>
#include  <QRegularExpression>
#include <QRegularExpressionValidator>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
    setValidator();
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{

    // Call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    // Get the username
    QString username = ui->username->text();

    // Get the password
    QString password = ui->password->text();

    // Check if the db is opened
    if (!db.isOpen()) {
        qDebug() << "Failed to open the database";
    }

    // Define the query
    auto query = QSqlQuery(db);

    if (!username.isEmpty() && !password.isEmpty()) {
        // Create the body of the query to include the role field
        QString checkLogin = "SELECT * FROM accounts WHERE username='" + username + "' AND password='" + password + "'";

        if (query.exec(checkLogin)) {
            int count = 0;
            QString role;

            // Retrieve the role from the query
            while (query.next()) {
                count++;
                role = query.value("role").toString();  // Assurez-vous que la colonne 'role' est présente dans la table
            }

            if (count == 1) {
                lib.setUsername(username);

                // Hide the current window
                this->hide();

                // Redirection en fonction du rôle
                if (role == "admin") {
                    // Show the main window for admin
                    lib.exec();  // Appel à la fenêtre principale pour l'admin
                } else if (role == "student") {
                    // Show a different window for students
                    // Exemple : une fenêtre différente pour l'étudiant
                    // studentWindow.exec();
                    studentLibrary *studentPage = new studentLibrary(this, db);
                    studentPage->show();
                    // this->close();
                    qDebug() << "Welcome Student!";
                }
            } else {
                QMessageBox msgBox;
                msgBox.setText("You are not registered or incorrect credentials!");
                msgBox.setStyleSheet("QMessageBox { color:  #FF69B4; }");  // Changer la couleur du texte en noir
                msgBox.exec();

               // QMessageBox::warning(this, "Failed", "You are not registered or incorrect credentials!");
            }
        } else {
            qDebug() << "Cannot execute the query";
        }
    } else {
        QMessageBox msgBox;
        msgBox.setText("Empty,Fields are empty!");
        msgBox.setStyleSheet("QMessageBox { color:  #FF69B4; }");  // Changer la couleur du texte en noir
        msgBox.exec();

    }
}


void Login::on_signUpButton_clicked()
{
    this->hide();
    signUp signUp;
    signUp.exec();
}

void Login::on_forgetPasswdBtn_clicked()
{
    this->hide();
    newPasswd newpass;
    newpass.exec();
}

void Login::setValidator()
{
    // Validator for username
    QRegularExpression rxName("^[A-Za-z][A-Za-z0-9_]{7,29}$");
    QRegularExpressionValidator *valName = new QRegularExpressionValidator(rxName, this);
    ui->username->setValidator(valName);
}
