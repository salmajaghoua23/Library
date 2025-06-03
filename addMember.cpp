#include "addMember.h"
#include "ui_addMember.h"
#include "digitalLibrary.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

#include "addMember.h"
#include "ui_addMember.h"
#include "digitalLibrary.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QLinearGradient>

addMember::addMember(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addMember)
{
    ui->setupUi(this);

    // Configuration de base
    this->setWindowTitle("Nouveau Membre • Bibliothèque Digitale");
    this->setFixedSize(800, 650);
    this->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f0f4ff, stop:1 #f8f0ff);");

    // Conteneur principal
    QFrame *mainContainer = new QFrame(this);
    mainContainer->setGeometry(25, 25, 750, 600);
    mainContainer->setStyleSheet(
        "background: white;"
        "border-radius: 15px;"
        "border: 1px solid #e0d4ff;"
        );

    // Effet d'ombre
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(mainContainer);
    shadow->setBlurRadius(25);
    shadow->setOffset(0, 5);
    shadow->setColor(QColor(106, 90, 205, 100));
    mainContainer->setGraphicsEffect(shadow);

    // Header avec dégradé
    QFrame *header = new QFrame(mainContainer);
    header->setGeometry(0, 0, 750, 80);
    header->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #6a5acd, stop:1 #9575cd);"
        "border-top-left-radius: 15px;"
        "border-top-right-radius: 15px;"
        );

    // Titre
    QLabel *title = new QLabel("Ajouter un Membre", header);
    title->setGeometry(30, 20, 690, 40);
    title->setStyleSheet(
        "color: white;"
        "font-family: 'Segoe UI';"
        "font-size: 22px;"
        "font-weight: bold;"
        );

    // Style des champs
    QString fieldStyle =
        "QLineEdit, QComboBox {"
        "   border: 2px solid #d1c4e9;"
        "   border-radius: 8px;"
        "   padding: 10px 15px;"
        "   font-size: 14px;"
        "   background: #fafaff;"
        "   font-family: 'Segoe UI';"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #7e57c2;"
        "   background: white;"
        "}";

    // Positionnement des champs
    int yPos = 120;
    const int fieldHeight = 45;
    const int margin = 30;

    // ID
    ui->id->setParent(mainContainer);
    ui->id->setGeometry(margin, yPos, 690, fieldHeight);
    ui->id->setStyleSheet(fieldStyle + "border-color: #9fa8da;");

    // Prénom
    yPos += fieldHeight + margin;
    ui->firstName->setParent(mainContainer);
    ui->firstName->setGeometry(margin, yPos, 690, fieldHeight);
    ui->firstName->setStyleSheet(fieldStyle + "border-color: #b39ddb;");

    // Nom
    yPos += fieldHeight + margin;
    ui->lastName->setParent(mainContainer);
    ui->lastName->setGeometry(margin, yPos, 690, fieldHeight);
    ui->lastName->setStyleSheet(fieldStyle + "border-color: #9575cd;");

    // Téléphone
    yPos += fieldHeight + margin;
    ui->phone->setParent(mainContainer);
    ui->phone->setGeometry(margin, yPos, 690, fieldHeight);
    ui->phone->setStyleSheet(fieldStyle + "border-color: #7e57c2;");

    // Genre
    yPos += fieldHeight + margin;
    ui->gender->setParent(mainContainer);
    ui->gender->setGeometry(margin, yPos, 690, fieldHeight);
    ui->gender->setStyleSheet(
        "QComboBox {"
        "   border: 2px solid #d1c4e9;"
        "   border-radius: 8px;"
        "   padding: 10px 15px;"
        "   font-size: 14px;"
        "   background: #fafaff;"
        "   font-family: 'Segoe UI';"
        "}"
        "QComboBox::drop-down {"
        "   subcontrol-origin: padding;"
        "   subcontrol-position: right center;"
        "   width: 30px;"
        "   border-left: 1px solid #d1d5db;"
        "}"
        );

    // Bouton d'ajout
    ui->addMemberButton->setParent(mainContainer);
    ui->addMemberButton->setGeometry(550, 500, 180, 50);
    ui->addMemberButton->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #6a5acd, stop:1 #9575cd);"
        "   border-radius: 8px;"
        "   color: white;"
        "   font-weight: bold;"
        "   font-size: 16px;"
        "   padding: 10px;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #7e57c2, stop:1 #a188d6);"
        "}"
        "QPushButton:pressed {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #5e35b1, stop:1 #7e57c2);"
        "}"
        );

    // Bouton de retour
    QPushButton *backBtn = new QPushButton(mainContainer);
    backBtn->setGeometry(30, 500, 120, 50);
    backBtn->setText("Retour");
    backBtn->setStyleSheet(
        "QPushButton {"
        "   background: transparent;"
        "   border-radius: 8px;"
        "   color: #6a5acd;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "   padding: 10px;"
        "   border: 2px solid #6a5acd;"
        "}"
        "QPushButton:hover {"
        "   background: rgba(106, 90, 205, 0.1);"
        "}"
        "QPushButton:pressed {"
        "   background: rgba(106, 90, 205, 0.2);"
        "}"
        );

    // Connecter le bouton de retour
    connect(backBtn, &QPushButton::clicked, this, &addMember::reject);

    // Initialisation des validateurs
    setValidator();
}

// Les autres méthodes (destructeur, setValidator, etc.) restent identiques
addMember::~addMember()
{
    delete ui;
    qDebug() << "addMember destroyed";  // Optionnel : pour le débogage
}
void addMember::on_addMemberButton_clicked()
{
    // Récupération des valeurs
    QString id = ui->id->text().trimmed();
    QString firstName = ui->firstName->text().trimmed();
    QString lastName = ui->lastName->text().trimmed();
    QString phone = ui->phone->text().trimmed();
    QString gender = ui->gender->currentText();

    // Vérification des champs avec ET logique (&&)
    if(id.isEmpty() ||firstName.isEmpty() || lastName.isEmpty() || phone.isEmpty() || gender.isEmpty())
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
    query.prepare("INSERT INTO accounts (username, name, password, role,ID) "
                  "VALUES (:firstname, :lastname, :phone, :gender,:id)");
    query.bindValue(":ID", id);
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
