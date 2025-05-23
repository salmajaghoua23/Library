#include "signUp.h"
#include "Login.h"
#include "ui_signUp.h"
#include "digitalLibrary.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QSpacerItem>
#include <QGraphicsDropShadowEffect>
#include <QFontDatabase>
#include <QComboBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

signUp::signUp(QWidget *parent) : QDialog(parent)
{
    // Configuration de la fenêtre
    setWindowTitle("Bibliothèque - Création de compte");
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(900, 700); // Slightly taller to accommodate more fields

    // Couleurs et polices
    QString gradientStart = "#D16BA5"; // rose
    QString gradientEnd = "#86A8E7";   // violet
    QString textColor = "#2c3e50";
    QFont titleFont("Segoe UI", 26, QFont::Bold);
    QFont labelFont("Segoe UI", 12);
    QFont buttonFont("Segoe UI", 13, QFont::Bold);

    // Conteneur principal avec ombre
    QFrame *mainFrame = new QFrame(this);
    mainFrame->setStyleSheet("QFrame { background-color: white; border-radius: 20px; }");
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(35);
    shadow->setOffset(0, 5);
    shadow->setColor(QColor(0, 0, 0, 100));
    mainFrame->setGraphicsEffect(shadow);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(mainFrame);
    mainLayout->setContentsMargins(50, 40, 50, 40);
    mainLayout->setSpacing(20);

    // Titre et icône
    QLabel *title = new QLabel("📝 Créer un nouveau compte");
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: " + textColor + ";");
    mainLayout->addWidget(title);

    // Champ Nom complet
    QVBoxLayout *nameLayout = new QVBoxLayout();
    QLabel *nameLabel = new QLabel("Nom complet");
    nameLabel->setFont(labelFont);
    nameLabel->setStyleSheet("color: " + textColor + ";");
    nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("👤 Entrez votre nom complet");
    nameLineEdit->setMinimumHeight(45);
    nameLineEdit->setStyleSheet(
        "QLineEdit { padding: 10px 15px; font-size: 14px; border: 2px solid #ddd; border-radius: 10px; }"
        "QLineEdit:focus { border: 2px solid #D16BA5; }");
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLineEdit);
    mainLayout->addLayout(nameLayout);

    // Champ Nom d'utilisateur
    QVBoxLayout *userLayout = new QVBoxLayout();
    QLabel *userLabel = new QLabel("Nom d'utilisateur");
    userLabel->setFont(labelFont);
    userLabel->setStyleSheet("color: " + textColor + ";");
    usernameLineEdit = new QLineEdit();
    usernameLineEdit->setPlaceholderText("👤 Entre 8-30 caractères (lettres, chiffres, _)");
    usernameLineEdit->setMinimumHeight(45);
    usernameLineEdit->setStyleSheet(
        "QLineEdit { padding: 10px 15px; font-size: 14px; border: 2px solid #ddd; border-radius: 10px; }"
        "QLineEdit:focus { border: 2px solid #D16BA5; }");
    userLayout->addWidget(userLabel);
    userLayout->addWidget(usernameLineEdit);
    mainLayout->addLayout(userLayout);

    // Champ mot de passe
    QVBoxLayout *passLayout = new QVBoxLayout();
    QLabel *passLabel = new QLabel("Mot de passe");
    passLabel->setFont(labelFont);
    passLabel->setStyleSheet("color: " + textColor + ";");
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setPlaceholderText("🔒 Entrez un mot de passe sécurisé");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setMinimumHeight(45);
    passwordLineEdit->setStyleSheet(
        "QLineEdit { padding: 10px 15px; font-size: 14px; border: 2px solid #ddd; border-radius: 10px; }"
        "QLineEdit:focus { border: 2px solid #D16BA5; }");
    passLayout->addWidget(passLabel);
    passLayout->addWidget(passwordLineEdit);
    mainLayout->addLayout(passLayout);

    // Champ Rôle
    QVBoxLayout *roleLayout = new QVBoxLayout();
    QLabel *roleLabel = new QLabel("Rôle");
    roleLabel->setFont(labelFont);
    roleLabel->setStyleSheet("color: " + textColor + ";");
    roleComboBox = new QComboBox();
    roleComboBox->addItem("Student");
    roleComboBox->addItem("user");
    roleComboBox->addItem("admin");
    roleComboBox->setMinimumHeight(45);
    roleComboBox->setStyleSheet(
        "QComboBox { padding: 10px 15px; font-size: 14px; border: 2px solid #ddd; border-radius: 10px; }"
        "QComboBox:focus { border: 2px solid #D16BA5; }");
    roleLayout->addWidget(roleLabel);
    roleLayout->addWidget(roleComboBox);
    mainLayout->addLayout(roleLayout);

    // Bouton de création de compte
    QPushButton *createButton = new QPushButton("✨ Créer un compte");
    createButton->setFont(buttonFont);
    createButton->setCursor(Qt::PointingHandCursor);
    createButton->setStyleSheet(
        QString("QPushButton {"
                "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 %1, stop:1 %2);"
                "color: white; border: none; border-radius: 12px; padding: 14px;}"
                "QPushButton:hover { background-color: #b58edc; }")
            .arg(gradientStart, gradientEnd));
    mainLayout->addWidget(createButton);

    // Ligne de séparation
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("color: #ccc;");
    mainLayout->addWidget(line);

    // Bouton de retour
    QPushButton *backButton = new QPushButton("↩ Retour à la connexion");
    backButton->setFont(buttonFont);
    backButton->setCursor(Qt::PointingHandCursor);
    backButton->setStyleSheet(QString("QPushButton {"
                                      "background-color: white; color: %1;"
                                      "border: 2px solid %1; border-radius: 10px; padding: 12px;}"
                                      "QPushButton:hover { background-color: %2; color: white; }")
                                  .arg(gradientStart).arg(QColor(gradientStart).lighter(130).name()));
    mainLayout->addWidget(backButton);

    // Positionnement
    QHBoxLayout *containerLayout = new QHBoxLayout(this);
    containerLayout->addStretch();
    containerLayout->addWidget(mainFrame);
    containerLayout->addStretch();

    // Set validators
    setValidator();

    // Connexion des signaux
    connect(createButton, &QPushButton::clicked, this, &signUp::on_createButton_clicked);
    connect(backButton, &QPushButton::clicked, this, &signUp::on_backButton_clicked);
}

signUp::~signUp()
{
}

void signUp::setValidator()
{
    // Validator for username
    QRegularExpression rxUsername("^[A-Za-z][A-Za-z0-9_]{7,29}$");
    QRegularExpressionValidator *valUsername = new QRegularExpressionValidator(rxUsername, this);
    usernameLineEdit->setValidator(valUsername);

    // Validator for name
    QRegularExpression rxName("^[A-Za-z]{7,29}$");
    QRegularExpressionValidator *valName = new QRegularExpressionValidator(rxName, this);
    nameLineEdit->setValidator(valName);
}

void signUp::on_createButton_clicked()
{
    // Get the content
    QString username = usernameLineEdit->text();
    QString name = nameLineEdit->text();
    QString password = passwordLineEdit->text();
    QString role = roleComboBox->currentText();

    // Call the main Database
    digitalLibrary lib;
    auto db = lib.db;

    // Add name, password, username, and role to the db
    if (!username.isEmpty() && !name.isEmpty() && !password.isEmpty()) {
        // Check if the account already exists
        auto search = QSqlQuery(db);
        QString searchAcc = "SELECT * FROM accounts WHERE username='" + username + "'";
        if (!search.exec(searchAcc)) {
            qDebug() << "Cannot select: " << search.lastError().text();
            QMessageBox::warning(this, "Database Error", search.lastError().text());
            return;
        }

        if (search.next()) {
            QMessageBox::warning(this, "Failed", "Nom d'utilisateur existe déjà!");
            return;
        }

        // Insert the new account with the role (without specifying id)
        QSqlQuery query(db);
        query.prepare("INSERT INTO accounts (username, name, password, role) VALUES (:username, :name, :password, :role)");
        query.bindValue(":username", username);
        query.bindValue(":name", name);
        query.bindValue(":password", password);
        query.bindValue(":role", role);

        if (!query.exec()) {
            qDebug() << "Cannot add entry to the database: " << query.lastError().text();
            QMessageBox::warning(this, "Database Error", query.lastError().text());
        } else {
            QMessageBox::information(this, "SUCCÈS", "Compte créé avec succès!");
            this->hide();
            Login login;
            login.exec();
        }
    }
    else {
        QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs!");
    }
}

void signUp::on_backButton_clicked()
{
    this->hide();
    Login login;
    login.exec();
}
