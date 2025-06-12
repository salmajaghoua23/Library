#include "Login.h"
#include "ui_Login.h"
#include"studentlibrary.h"
#include <QMessageBox>
#include "digitalLibrary.h"
#include"historique.h"
#include "signUp.h"
#include "newPasswd.h"
#include <QDebug>
#include  <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QSpacerItem>
#include <QGraphicsDropShadowEffect>
#include <QFontDatabase>
#include <QMessageBox>
#include<QSqlError>
Login::Login(QWidget *parent) : QDialog(parent)
{  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Pc/OneDrive/Bureau/QT_PROJECT/library.db");
    if (!db.open()) {
        qDebug() << "Error opening database:" << db.lastError().text();
        return;
    }
    // Configuration de la fenêtre
    setWindowTitle("Bibliothèque - Connexion");
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(900, 620);

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
    mainLayout->setContentsMargins(50, 50, 50, 50);
    mainLayout->setSpacing(25);

    // Titre et icône
    QLabel *title = new QLabel("🔐 Connexion à la bibliothèque");
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: " + textColor + ";");
    mainLayout->addWidget(title);

    // Champ Nom d'utilisateur
    QVBoxLayout *userLayout = new QVBoxLayout();
    QLabel *userLabel = new QLabel("Nom d'utilisateur");
    userLabel->setFont(labelFont);
    userLabel->setStyleSheet("color: " + textColor + ";");
    usernameLineEdit = new QLineEdit();
    usernameLineEdit->setPlaceholderText("👤 Entrez votre nom d'utilisateur");
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
    passwordLineEdit->setPlaceholderText("🔒 Entrez votre mot de passe");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setMinimumHeight(45);
    passwordLineEdit->setStyleSheet(
        "QLineEdit { padding: 10px 15px; font-size: 14px; border: 2px solid #ddd; border-radius: 10px; }"
        "QLineEdit:focus { border: 2px solid #D16BA5; }");
    passLayout->addWidget(passLabel);
    passLayout->addWidget(passwordLineEdit);
    mainLayout->addLayout(passLayout);

    // Bouton de connexion
    QPushButton *loginButton = new QPushButton("🚪 Se connecter");
    loginButton->setFont(buttonFont);
    loginButton->setCursor(Qt::PointingHandCursor);
    loginButton->setStyleSheet(
        QString("QPushButton {"
                "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 %1, stop:1 %2);"
                "color: white; border: none; border-radius: 12px; padding: 14px;}"
                "QPushButton:hover { background-color: #b58edc; }")
            .arg(gradientStart, gradientEnd));
    mainLayout->addWidget(loginButton);

    // Lien mot de passe oublié
    QPushButton *forgotBtn = new QPushButton("🔑 Mot de passe oublié ?");
    forgotBtn->setFont(labelFont);
    forgotBtn->setCursor(Qt::PointingHandCursor);
    forgotBtn->setStyleSheet("QPushButton { border: none; background: transparent; color: #3498db; }"
                             "QPushButton:hover { text-decoration: underline; }");
    mainLayout->addWidget(forgotBtn, 0, Qt::AlignCenter);

    // Ligne de séparation
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("color: #ccc;");
    mainLayout->addWidget(line);

    // Création de compte
    QLabel *signupLabel = new QLabel("Vous n'avez pas de compte ?");
    signupLabel->setFont(labelFont);
    signupLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(signupLabel);

    QPushButton *signupBtn = new QPushButton("📝 Créer un compte");
    signupBtn->setFont(buttonFont);
    signupBtn->setCursor(Qt::PointingHandCursor);
    signupBtn->setStyleSheet(QString("QPushButton {"
                                     "background-color: white; color: %1;"
                                     "border: 2px solid %1; border-radius: 10px; padding: 12px;}"
                                     "QPushButton:hover { background-color: %2; color: white; }")
                                 .arg(gradientStart).arg(QColor(gradientStart).lighter(130).name()));
    mainLayout->addWidget(signupBtn);

    // Positionnement
    QHBoxLayout *containerLayout = new QHBoxLayout(this);
    containerLayout->addStretch();
    containerLayout->addWidget(mainFrame);
    containerLayout->addStretch();

    // Connexion des signaux
  connect(loginButton, &QPushButton::clicked, this, &Login::on_loginButton_clicked);
    connect(signupBtn, &QPushButton::clicked, this, &Login::on_signUpButton_clicked);
   connect(forgotBtn, &QPushButton::clicked, this, &Login::on_forgetPasswdBtn_clicked);
}

Login::~Login()
{
}

void Login::mousePressEvent(QMouseEvent *event)
{
    // Pour déplacer la fenêtre sans bordure
    if(event->button() == Qt::LeftButton) {
        m_dragging = true;
        m_lastMousePosition = event->globalPos();
    }
}

void Login::mouseMoveEvent(QMouseEvent *event)
{
    if(m_dragging) {
        this->move(this->pos() + (event->globalPos() - m_lastMousePosition));
        m_lastMousePosition = event->globalPos();
    }
}

void Login::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        m_dragging = false;
    }
}

void Login::on_loginButton_clicked()
{
    digitalLibrary lib;
    auto db = lib.db;

    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if (!db.isOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    QSqlQuery query(db);

    if (!username.isEmpty() && !password.isEmpty()) {
        QString checkLogin = "SELECT * FROM accounts WHERE username='" + username + "' AND password='" + password + "'";

        if (query.exec(checkLogin)) {
            int count = 0;
            QString role;
            int userId = -1;

            while (query.next()) {
                count++;
                role = query.value("role").toString();
                userId = query.value("id").toInt();
            }

            if (count == 1) {
                lib.setUsername(username);

                // Enregistrer la connexion dans la table historique_connexions
                Historique historique(userId,db);                      // Instancie ton objet Historique
                historique.enregistrerConnexion(userId, db); // Enregistre la connexion dans la base

                this->hide();

                if (role == "admin") {
                    digitalLibrary lib(nullptr, userId); // Ajoute userId comme paramètre
                    lib.setUsername(username);
                    lib.exec();
                } else if (role == "student") {
                    studentLibrary *studentPage = new studentLibrary(this, db);
                    studentPage->setCurrentUserId(userId);
                    studentPage->exec();
                }
            } else {
                QMessageBox::warning(this, "Failed", "You are not registered or incorrect credentials!");
            }
        } else {
            qDebug() << "Cannot execute the query";
        }
    } else {
        QMessageBox::warning(this, "Empty Fields", "Fields cannot be empty!");
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
