#include "signUp.h"
#include "Login.h"
#include "ui_signUp.h"
#include "digitalLibrary.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

signUp::signUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signUp)
{
    ui->setupUi(this);
    this->setWindowTitle("New Account");
    setValidator();

    // Étape 1 : Test de suppression des données et ajout de la colonne 'role'
   // testDatabase();
}

signUp::~signUp()
{
    delete ui;
}

void signUp::testDatabase()
{
    // Appeler la base de données
    digitalLibrary lib;
    auto db = lib.db;

    // 1. Supprimer toutes les données de la table accounts
    QString deleteData = "DELETE FROM accounts";
    auto query = QSqlQuery(db);

    if (!query.exec(deleteData)) {
        qDebug() << "SQL Error: " << query.lastError().text();  // Affiche l'erreur SQL détaillée
        QMessageBox::warning(this, "Database Error", query.lastError().text());  // Affiche un message avec l'erreur SQL
    } else {
        qDebug() << "Data deleted successfully!";
    }

    // 2. Ajouter une colonne 'role' à la table accounts
    QString addRoleColumn = "ALTER TABLE accounts ADD COLUMN role VARCHAR(20)";
    if (!query.exec(addRoleColumn)) {
        qDebug() << "SQL Error: " << query.lastError().text();  // Affiche l'erreur SQL détaillée
        QMessageBox::warning(this, "Database Error", query.lastError().text());  // Affiche un message avec l'erreur SQL
    } else {
        qDebug() << "Column 'role' added successfully!";
    }
}

void signUp::on_createButton_clicked()
{
    // Get the content
    QString username = ui->username->text();
    QString name = ui->name->text();
    QString password = ui->password->text();
    QString role = ui->roleComboBox->currentText(); // Récupérer le rôle sélectionné dans le QComboBox

    // Call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    // Add name, password, username, and role to the db
    if (!username.isEmpty() && !name.isEmpty() && !password.isEmpty()) {
        // Check if the account already exists
        auto search = QSqlQuery(db);
        QString searchAcc = {"SELECT * FROM accounts WHERE username='" + username + "' AND name='" + name + "' AND password='" + password + "'"};
        if (!search.exec(searchAcc)) {
            qDebug() << "Cannot select";
        }
        int count = 0;
        while (search.next()) {
            count++;
        }

        if (count >= 1)
            QMessageBox::warning(this, "Failed", "Account Already Exist!");
        else {
            // Insert the new account with the role
            QString addEntry = "INSERT INTO accounts (username, name, password, role) VALUES ('%1', '%2', '%3', '%4')";
            auto query = QSqlQuery(db);

            if (!query.exec(addEntry.arg(username).arg(name).arg(password).arg(role)))
                qDebug() << "Cannot add entry to the database: " << query.lastError().text();
            else
                QMessageBox::information(this, "SUCCESS", "You registered successfully!");
        }
    }
    else
        QMessageBox::warning(this, "Empty", "Fields are empty!");
}

void signUp::on_backButton_clicked()
{
    this->hide();
    Login login;
    login.exec();
}

void signUp::setValidator()
{
    // Validator for username
    QRegularExpression rxUsername("^[A-Za-z][A-Za-z0-9_]{7,29}$");
    QRegularExpressionValidator *valUsername = new QRegularExpressionValidator(rxUsername, this);
    ui->username->setValidator(valUsername);

    // Validator for name
    QRegularExpression rxName("^[A-Za-z]{7,29}$");
    QRegularExpressionValidator *valName = new QRegularExpressionValidator(rxName, this);
    ui->name->setValidator(valName);
}
