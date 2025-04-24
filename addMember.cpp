#include "addMember.h"
#include "ui_addMember.h"
#include "digitalLibrary.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

addMember::addMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addMember)
{
    ui->setupUi(this);
    this->resize(350, 400);
    this->setWindowTitle("Add Member");

    // Style optionnel pour meilleure visibilité
    this->setStyleSheet(
        "QLineEdit { padding: 5px; border: 1px solid #ccc; border-radius: 3px; }"
        "QPushButton { padding: 8px; background-color: #4CAF50; color: white; border: none; border-radius: 4px; }"
        );

    setValidator();
}
addMember::~addMember()
{
    delete ui;
    qDebug() << "addMember destroyed";  // Optionnel : pour le débogage
}
void addMember::on_addMemberButton_clicked()
{
    // Récupération des valeurs
    QString firstName = ui->firstName->text().trimmed();
    QString lastName = ui->lastName->text().trimmed();
    QString phone = ui->phone->text().trimmed();
    QString gender = ui->gender->currentText();

    // Vérification des champs avec ET logique (&&)
    if(firstName.isEmpty() || lastName.isEmpty() || phone.isEmpty() || gender.isEmpty())
    {
        QMessageBox::warning(this, "Empty Fields", "All fields are required!");
        return;
    }

    digitalLibrary lib;
    auto db = lib.db;

    // Vérifier la connexion à la base
    if(!db.isOpen())
    {
        QMessageBox::critical(this, "Database Error", "Database connection failed!");
        return;
    }

    // Requête préparée (plus sécurisée)
    QSqlQuery query(db);
    query.prepare("INSERT INTO accounts (username, name, password, role) "
                  "VALUES (:firstname, :lastname, :phone, :gender)");

    query.bindValue(":firstname", firstName);
    query.bindValue(":lastname", lastName);
    query.bindValue(":phone", phone);
    query.bindValue(":gender", gender);

    if(!query.exec())
    {
        qDebug() << "SQL Error:" << query.lastError().text();
        QMessageBox::critical(this, "Error",
                              "Failed to add member:\n" + query.lastError().text());
    }
    else
    {
        QMessageBox::information(this, "Success", "Member added successfully!");
        this->accept(); // Ferme la fenêtre après succès
    }
}

void addMember::setValidator()
{
    // Validation pour les noms (7-29 caractères alphabétiques)
    QRegularExpression nameRegex("^[A-Za-z]{7,29}$");
    ui->firstName->setValidator(new QRegularExpressionValidator(nameRegex, this));
    ui->lastName->setValidator(new QRegularExpressionValidator(nameRegex, this));

    // Validation pour le téléphone (10 chiffres)
    QRegularExpression phoneRegex("^[0-9]{10}$");
    ui->phone->setValidator(new QRegularExpressionValidator(phoneRegex, this));

    // Activer la validation en temps réel
    ui->firstName->setProperty("valid", true);
    ui->lastName->setProperty("valid", true);
    ui->phone->setProperty("valid", true);
}
