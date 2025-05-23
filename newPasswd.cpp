#include "newPasswd.h"
#include"Login.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QFont>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

newPasswd::newPasswd(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Réinitialisation du mot de passe");
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(900, 620);

    // Dégradés et polices
    QString gradientStart = "#D16BA5";
    QString gradientEnd = "#86A8E7";
    QString textColor = "#2c3e50";
    QFont titleFont("Segoe UI", 24, QFont::Bold);
    QFont labelFont("Segoe UI", 12);
    QFont buttonFont("Segoe UI", 13, QFont::Bold);

    // Conteneur avec ombre
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

    QLabel *title = new QLabel("🔐 Réinitialiser votre mot de passe");
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: " + textColor + ";");
    mainLayout->addWidget(title);

    // Champ nom d'utilisateur
    QLabel *userLabel = new QLabel("Nom d'utilisateur");
    userLabel->setFont(labelFont);
    userLabel->setStyleSheet("color: " + textColor + ";");
    usernameEdit = new QLineEdit();
    usernameEdit->setPlaceholderText("👤 Entrez votre nom d'utilisateur");
    usernameEdit->setMinimumHeight(45);
    usernameEdit->setStyleSheet("QLineEdit { padding: 10px; border: 2px solid #ddd; border-radius: 10px; }"
                                "QLineEdit:focus { border: 2px solid #D16BA5; }");
    mainLayout->addWidget(userLabel);
    mainLayout->addWidget(usernameEdit);

    // Champ nouveau mot de passe
    QLabel *newPassLabel = new QLabel("Nouveau mot de passe");
    newPassLabel->setFont(labelFont);
    newPassLabel->setStyleSheet("color: " + textColor + ";");
    newPassEdit = new QLineEdit();
    newPassEdit->setPlaceholderText("🔑 Nouveau mot de passe");
    newPassEdit->setEchoMode(QLineEdit::Password);
    newPassEdit->setMinimumHeight(45);
    newPassEdit->setStyleSheet("QLineEdit { padding: 10px; border: 2px solid #ddd; border-radius: 10px; }"
                               "QLineEdit:focus { border: 2px solid #D16BA5; }");
    mainLayout->addWidget(newPassLabel);
    mainLayout->addWidget(newPassEdit);

    // Bouton de confirmation
    QPushButton *resetBtn = new QPushButton("✅ Réinitialiser");
    resetBtn->setFont(buttonFont);
    resetBtn->setCursor(Qt::PointingHandCursor);
    resetBtn->setStyleSheet(
        QString("QPushButton {"
                "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 %1, stop:1 %2);"
                "color: white; border: none; border-radius: 12px; padding: 14px;}"
                "QPushButton:hover { background-color: #b58edc; }")
            .arg(gradientStart, gradientEnd));
    mainLayout->addWidget(resetBtn);

    // Layout général
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addStretch();
    layout->addWidget(mainFrame);
    layout->addStretch();
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

    // Connexion du bouton
    connect(resetBtn, &QPushButton::clicked, this, &newPasswd::resetPassword);
    connect(backButton, &QPushButton::clicked, this, &newPasswd::on_backButton_clicked);
}

void newPasswd::resetPassword()
{
    QString username = usernameEdit->text().trimmed();
    QString newPassword = newPassEdit->text().trimmed();

    if (username.isEmpty() || newPassword.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
        return;
    }

    // Connexion à la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "resetConn");
    db.setDatabaseName("C:/Users/Pc/OneDrive/Bureau/QT_PROJECT/library.db");

    if (!db.open()) {
        qDebug() << "Erreur d'ouverture BD:" << db.lastError().text();
        QMessageBox::critical(this, "Erreur", "Impossible d'accéder à la base de données.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE accounts SET password = :pass WHERE username = :user");
    query.bindValue(":pass", newPassword);
    query.bindValue(":user", username);

    if (query.exec() && query.numRowsAffected() > 0) {
        QMessageBox::information(this, "Succès", "Mot de passe mis à jour avec succès !");
        this->accept();  // Fermer la fenêtre
    } else {
        QMessageBox::warning(this, "Erreur", "Utilisateur introuvable ou mise à jour échouée.");
    }

    db.close();
    QSqlDatabase::removeDatabase("resetConn");
}
void newPasswd::on_backButton_clicked()
{
    this->hide();
    Login login;
    login.exec();
}
