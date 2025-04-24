#include "editMember.h"
#include "ui_editMember.h"
#include "digitalLibrary.h"
#include <QSqlError>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDebug>

editMember::editMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editMember)
{
    ui->setupUi(this);

    this->setWindowTitle("Edit Member Info");
    setValidator();
}

editMember::~editMember()
{
    delete ui;
}

void editMember::on_searchMemberBtn_clicked()
{
    // Reset counter
    count = 0;

    // Get username from input
    QString username = ui->ID->text().trimmed();

    if(username.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a username");
        return;
    }

    // Initialize variables
    QString firstName, lastName, phone, gender;

    // Connect to database
    digitalLibrary lib;
    auto db = lib.db;

    if(!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database not connected!");
        return;
    }

    // Prepare and execute query
    QSqlQuery query(db);
    query.prepare("SELECT username, name, password, role FROM accounts WHERE username = ?");
    query.addBindValue(username);

    if(!query.exec()) {
        QMessageBox::critical(this, "Query Error",
                              "Failed to search member: " + query.lastError().text());
        return;
    }

    // Process results
    if(query.next()) {
        count = 1;
        firstName = query.value("username").toString();
        lastName = query.value("name").toString();
        phone = query.value("password").toString();
        gender = query.value("role").toString();

        // Update UI
        ui->firstName->setText(firstName);
        ui->lastName->setText(lastName);
        ui->phone->setText(phone);
        ui->gender->setCurrentText(gender);
    } else {
        QMessageBox::information(this, "Not Found", "No member found with this username");
        ui->ID->clear();
    }
}

void editMember::on_editMemberBtn_clicked()
{
    // Verify we have search results
    if(count != 1) {
        QMessageBox::warning(this, "Error", "Please search for a member first");
        return;
    }

    // Get input values
    QString username = ui->ID->text().trimmed();
    QString firstName = ui->firstName->text().trimmed();
    QString lastName = ui->lastName->text().trimmed();
    QString phone = ui->phone->text().trimmed();
    QString gender = ui->gender->currentText();

    // Validate inputs
    if(firstName.isEmpty() || lastName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "First and last names cannot be empty");
        return;
    }

    // Connect to database
    digitalLibrary lib;
    auto db = lib.db;

    // Prepare update query
    QSqlQuery query(db);
    query.prepare("UPDATE accounts SET "
                  "username = ?, "
                  "name = ?, "
                  "password = ?, "
                  "role = ? "
                  "WHERE username = ?");

    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(phone);
    query.addBindValue(gender);
    query.addBindValue(username);

    // Execute update
    if(!query.exec()) {
        QMessageBox::critical(this, "Update Error",
                              "Failed to update member: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Member updated successfully");
        count = 0; // Reset search status
    }
}

void editMember::setValidator()
{
    // Validator for username (alphanumeric, 5-20 chars)
    QRegularExpression username("^[A-Za-z0-9_]{5,20}$");
    ui->ID->setValidator(new QRegularExpressionValidator(username, this));

    // Validator for names (letters only, 2-29 chars)
    QRegularExpression name("^[A-Za-zÀ-ÿ\\s]{2,29}$");
    ui->firstName->setValidator(new QRegularExpressionValidator(name, this));
    ui->lastName->setValidator(new QRegularExpressionValidator(name, this));

    // Validator for phone (10 digits)
    QRegularExpression phone("^[0-9]{10}$");
    ui->phone->setValidator(new QRegularExpressionValidator(phone, this));
}
