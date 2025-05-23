#include "digitalLibrary.h"
#include "ui_digitalLibrary.h"
#include "Login.h"
#include "statistic.h"
#include "manageBooks.h"
#include "ManageAuthors.h"
#include "addMember.h"
#include "editMember.h"
#include "deleteMember.h"
#include "membersList.h"
#include "addBook.h"
#include "editBook.h"
#include "deletebook.h"
#include "bookList.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QtConcurrent/QtConcurrent>
#include <QSqlQuery>
#include "digitalLibrary.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QSpacerItem>
#include <QGraphicsDropShadowEffect>
#include <QFontDatabase>
#include <QStackedWidget>
digitalLibrary::digitalLibrary(QWidget *parent) :
    QDialog(parent),
    m_usernameLabel(new QLabel(this)),
    booksBtn(nullptr),
    membersBtn(nullptr)
{
    connectDB(); // Assurez-vous que la base est connectée
    m_usernameLabel->setAlignment(Qt::AlignCenter);
    m_usernameLabel->setStyleSheet("font-weight: bold; color: #2c3e50;");

    // Configuration de la fenêtre
    setWindowTitle("Bibliothèque Digitale");
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(900, 700);

    // Couleurs (violet/bleu)
    QString primaryColor = "#6a5acd";
    QString secondaryColor = "#9370db";
    QString darkColor = "#483d8b";
    QString lightColor = "#e6e6fa";
    QString accentColor = "#4169e1";

    // Police
    QFont titleFont("Segoe UI", 24, QFont::Bold);
    QFont headerFont("Segoe UI", 18, QFont::Bold);
    QFont normalFont("Segoe UI", 12);

    // Conteneur principal
    QFrame *mainFrame = new QFrame(this);
    mainFrame->setStyleSheet("QFrame { background-color: white; border-radius: 15px; }");
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(30);
    shadow->setOffset(0, 5);
    shadow->setColor(QColor(0, 0, 0, 100));
    mainFrame->setGraphicsEffect(shadow);

    // Layout principal (horizontal)
    QHBoxLayout *mainLayout = new QHBoxLayout(mainFrame);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // ========== SIDEBAR ==========
    QFrame *sidebar = new QFrame();
    sidebar->setFixedWidth(250);
    sidebar->setStyleSheet(QString("QFrame { background-color: %1; border-top-left-radius: 15px; border-bottom-left-radius: 15px; }").arg(darkColor));

    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(20, 30, 20, 30);
    sidebarLayout->setSpacing(20);

    // Logo et titre
    QLabel *logo = new QLabel("📚");
    logo->setStyleSheet("font-size: 40px;");
    logo->setAlignment(Qt::AlignCenter);

    QLabel *sidebarTitle = new QLabel("Bibliothèque Digitale");
    sidebarTitle->setFont(titleFont);
    sidebarTitle->setStyleSheet(QString("color: %1;").arg(lightColor));
    sidebarTitle->setAlignment(Qt::AlignCenter);

    sidebarLayout->addWidget(logo);
    sidebarLayout->addWidget(sidebarTitle);
    sidebarLayout->addSpacing(30);

    // Style des boutons
    // Style des boutons
    QString buttonStyle = QString(
                              "QPushButton { "
                              "text-align: left; padding: 15px 20px; border-radius: 8px; "
                              "font-size: 14px; color: %1; background-color: transparent; "
                              "}"
                              "QPushButton:hover { background-color: rgba(255,255,255,0.1); }"
                              ).arg(lightColor);
    // Boutons sidebar
    QPushButton *dashboardBtn = createSidebarButton("📊 Tableau de bord", buttonStyle);
    booksBtn = createSidebarButton("📚 Gestion Livres", buttonStyle);
    membersBtn = createSidebarButton("👥 Gestion Membres", buttonStyle);
    QPushButton *authorsBtn = createSidebarButton("✍ Gestion Auteurs", buttonStyle);
    QPushButton *statsBtn = createSidebarButton("📈 Statistiques", buttonStyle);

    // Sous-menu pour les livres
    QVBoxLayout *booksSubMenu = new QVBoxLayout();
    booksSubMenu->setContentsMargins(20, 5, 5, 5);
    booksSubMenu->setSpacing(5);
    QString subButtonStyle =
        "QPushButton {"
        "   background-color: #584d8b;"
        "   color: white;"
        "   border: none;"
        "   padding: 10px 15px;"
        "   border-radius: 6px;"
        "   font-size: 13px;"
        "   text-align: left;"
        "}"
        "QPushButton:hover {"
        "   background-color: #6a5acd;"
        "}";

    QPushButton *addBookSubBtn = createSubMenuButton("➕ Ajouter livre");
    QPushButton *editBookSubBtn = createSubMenuButton("✏ Modifier livre");
    QPushButton *deleteBookSubBtn = createSubMenuButton("🗑 Supprimer livre");
    QPushButton *listBooksSubBtn = createSubMenuButton("📋 Liste des livres");
    QPushButton *issueBookSubBtn = createSubMenuButton("📥 Emprunter livre");
    QPushButton *returnBookSubBtn = createSubMenuButton("📤 Retourner livre");
    QPushButton *manageGenreSubBtn = createSubMenuButton("🏷 Gérer genres");

    booksSubMenu->addWidget(addBookSubBtn);
    booksSubMenu->addWidget(editBookSubBtn);
    booksSubMenu->addWidget(deleteBookSubBtn);
    booksSubMenu->addWidget(listBooksSubBtn);
    booksSubMenu->addWidget(issueBookSubBtn);
    booksSubMenu->addWidget(returnBookSubBtn);
    booksSubMenu->addWidget(manageGenreSubBtn);

    QWidget *booksSubMenuWidget = new QWidget();
    booksSubMenuWidget->setLayout(booksSubMenu);
    booksSubMenuWidget->hide();

    // Sous-menu pour les membres
    QVBoxLayout *membersSubMenu = new QVBoxLayout();
    membersSubMenu->setContentsMargins(20, 5, 5, 5);
    membersSubMenu->setSpacing(5);

    QPushButton *addMemberSubBtn = createSubMenuButton("➕ Ajouter membre");
    QPushButton *editMemberSubBtn = createSubMenuButton("✏ Modifier membre");
    QPushButton *deleteMemberSubBtn = createSubMenuButton("🗑 Supprimer membre");
    QPushButton *listMembersSubBtn = createSubMenuButton("📋 Liste des membres");

    membersSubMenu->addWidget(addMemberSubBtn);
    membersSubMenu->addWidget(editMemberSubBtn);
    membersSubMenu->addWidget(deleteMemberSubBtn);
    membersSubMenu->addWidget(listMembersSubBtn);

    QWidget *membersSubMenuWidget = new QWidget();
    membersSubMenuWidget->setLayout(membersSubMenu);
    membersSubMenuWidget->hide();

    // Ajout des éléments à la sidebar
    sidebarLayout->addWidget(dashboardBtn);
    sidebarLayout->addWidget(booksBtn);
    sidebarLayout->addWidget(booksSubMenuWidget);
    sidebarLayout->addWidget(membersBtn);
    sidebarLayout->addWidget(membersSubMenuWidget);
    sidebarLayout->addWidget(authorsBtn);
    sidebarLayout->addWidget(statsBtn);
    sidebarLayout->addStretch();

    // Bouton déconnexion
    QPushButton *logoutBtn = new QPushButton("🚪 Déconnexion");
    logoutBtn->setStyleSheet(
        "QPushButton { "
        "text-align: left; padding: 15px 20px; border-radius: 8px; "
        "font-size: 14px; color: #e74c3c; background-color: rgba(231, 76, 60, 0.2); "
        "}"
        "QPushButton:hover { background-color: rgba(231, 76, 60, 0.3); }"
        );
    sidebarLayout->addWidget(logoutBtn);

    // ========== MAIN CONTENT ==========
    QFrame *contentFrame = new QFrame();
    QVBoxLayout *contentLayout = new QVBoxLayout(contentFrame);
    contentLayout->setContentsMargins(30, 30, 30, 30);
    contentLayout->setSpacing(20);

    // Header
    QHBoxLayout *headerLayout = new QHBoxLayout();

    QLabel *welcomeLabel = new QLabel("Bonjour, Admin");
    welcomeLabel->setFont(headerFont);
    welcomeLabel->setStyleSheet(QString("color: %1;").arg(darkColor));

    QLabel *userLabel = new QLabel("👤 Admin");
    userLabel->setFont(normalFont);
    userLabel->setStyleSheet(
        "background-color: #f5f5f5; padding: 8px 15px; "
        "border-radius: 15px; color: #7f8c8d;"
        );

    headerLayout->addWidget(welcomeLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(userLabel);
    contentLayout->addLayout(headerLayout);

    // Cartes statistiques
    QHBoxLayout *statsLayout = new QHBoxLayout();
    statsLayout->setSpacing(20);

    QFrame *bookCard = createStatCard("📚", "Livres", "0", primaryColor);
    QFrame *memberCard = createStatCard("👥", "Membres", "0", secondaryColor);
    QFrame *authorCard = createStatCard("✍", "Auteurs", "0", "#8a2be2");
    QFrame *loanCard = createStatCard("🔄", "Emprunts", "0", "#4169e1");

    statsLayout->addWidget(bookCard);
    statsLayout->addWidget(memberCard);
    statsLayout->addWidget(authorCard);
    statsLayout->addWidget(loanCard);
    contentLayout->addLayout(statsLayout);

    // Section récentes activités
    QLabel *activityTitle = new QLabel("Activités Récentes");
    activityTitle->setFont(headerFont);
    activityTitle->setStyleSheet(QString("color: %1; margin-top: 20px;").arg(darkColor));
    contentLayout->addWidget(activityTitle);

    QFrame *activityFrame = new QFrame();
    activityFrame->setStyleSheet(
        "QFrame { background-color: white; border-radius: 10px; "
        "border: 1px solid #e0e0e0; }"
        );
    activityFrame->setFixedHeight(200);
    contentLayout->addWidget(activityFrame);

    // Section rapide actions
    QLabel *quickActionsTitle = new QLabel("Actions Rapides");
    quickActionsTitle->setFont(headerFont);
    quickActionsTitle->setStyleSheet(QString("color: %1; margin-top: 20px;").arg(darkColor));
    contentLayout->addWidget(quickActionsTitle);

    QHBoxLayout *quickActionsLayout = new QHBoxLayout();
    quickActionsLayout->setSpacing(15);

    QPushButton *addBookBtn = createQuickActionButton("➕ Ajouter Livre", primaryColor);
    QPushButton *addMemberBtn = createQuickActionButton("➕ Ajouter Membre", secondaryColor);
    QPushButton *addAuthorBtn = createQuickActionButton("➕ Ajouter Auteur", "#e67e22");
    QPushButton *viewAllBtn = createQuickActionButton("👁 Voir Tout", "#9b59b6");

    quickActionsLayout->addWidget(addBookBtn);
    quickActionsLayout->addWidget(addMemberBtn);
    quickActionsLayout->addWidget(addAuthorBtn);
    quickActionsLayout->addWidget(viewAllBtn);
    contentLayout->addLayout(quickActionsLayout);
     membersSubMenuWidget->setStyleSheet("background-color: #584d8b;");
     booksSubMenuWidget->setStyleSheet("background-color: #584d8b;");

    // Ajout des sections au layout principal
    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(contentFrame);

    // Positionnement final
    QHBoxLayout *containerLayout = new QHBoxLayout(this);
    containerLayout->addWidget(mainFrame);

    // Connexions
    connect(booksBtn, &QPushButton::clicked, [booksSubMenuWidget]() {
        booksSubMenuWidget->setVisible(!booksSubMenuWidget->isVisible());
    });

    connect(membersBtn, &QPushButton::clicked, [membersSubMenuWidget]() {
        membersSubMenuWidget->setVisible(!membersSubMenuWidget->isVisible());
    });

    connect(addBookSubBtn, &QPushButton::clicked, this, &digitalLibrary::on_addBookBtn_clicked);
    connect(editBookSubBtn, &QPushButton::clicked, this, &digitalLibrary::on_editBookBtn_clicked);
    connect(deleteBookSubBtn, &QPushButton::clicked, this, &digitalLibrary::on_deleteBookBtn_clicked);
    connect(listBooksSubBtn, &QPushButton::clicked, this, &digitalLibrary::on_booksListBtn_clicked);
    connect(issueBookSubBtn, &QPushButton::clicked, this, &digitalLibrary::on_issueBookBtn_clicked);
    connect(returnBookSubBtn, &QPushButton::clicked, this, &digitalLibrary::on_returnBookBtn_clicked);
    connect(manageGenreSubBtn, &QPushButton::clicked, this, &digitalLibrary::on_manageGenre_clicked);

    connect(addMemberSubBtn, &QPushButton::clicked, this, &digitalLibrary::on_addMemberBtn_clicked);
    connect(editMemberSubBtn, &QPushButton::clicked, this, &digitalLibrary::on_editMemberBtn_clicked);
    connect(deleteMemberSubBtn, &QPushButton::clicked, this, &digitalLibrary::on_deleteMemberBtn_clicked);
    connect(listMembersSubBtn, &QPushButton::clicked, this, &digitalLibrary::on_membersListBtn_clicked);

    connect(addBookBtn, &QPushButton::clicked, this, &digitalLibrary::on_addBookBtn_clicked);
    connect(addMemberBtn, &QPushButton::clicked, this, &digitalLibrary::on_addMemberBtn_clicked);
    connect(addAuthorBtn, &QPushButton::clicked, this, &digitalLibrary::on_manageAuthorButton_clicked);
    connect(viewAllBtn, &QPushButton::clicked, this, &digitalLibrary::on_booksListBtn_clicked);
    connect(statsBtn, &QPushButton::clicked, this, &digitalLibrary::on_statsButton_clicked);
    connect(logoutBtn, &QPushButton::clicked, this, &digitalLibrary::close);
}
QPushButton* digitalLibrary::createSidebarButton(const QString &text, const QString &style)
{
    QPushButton *btn = new QPushButton(text);
    btn->setStyleSheet(style);
    return btn;
}
QPushButton* digitalLibrary::createSubMenuButton(const QString &text)
{
    QPushButton *btn = new QPushButton(text);
    btn->setStyleSheet(
        "QPushButton { "
        "text-align: left; padding: 10px 15px 10px 30px; border-radius: 5px; "
        "font-size: 13px; color: #f0f0f0; background-color: transparent; "
        "border: none;"
        "}"
        "QPushButton:hover { background-color: rgba(255,255,255,0.1); }"
        );
    return btn;
}
QFrame* digitalLibrary::createStatCard(const QString &icon, const QString &title, const QString &value, const QString &color)
{
    QFrame *card = new QFrame();
    card->setMinimumHeight(120);
    card->setStyleSheet(
        QString("QFrame { background-color: %1; border-radius: 10px; color: white; }").arg(color)
        );

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(20, 20, 20, 20);

    QLabel *iconLabel = new QLabel(icon);
    iconLabel->setStyleSheet("font-size: 24px;");

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("font-size: 14px; font-weight: bold;");

    QLabel *valueLabel = new QLabel(value);
    valueLabel->setStyleSheet("font-size: 28px; font-weight: bold; margin-top: 10px;");

    cardLayout->addWidget(iconLabel);
    cardLayout->addWidget(titleLabel);
    cardLayout->addWidget(valueLabel);
    cardLayout->addStretch();

    return card;
}

QPushButton* digitalLibrary::createQuickActionButton(const QString &text, const QString &color)
{
    QPushButton *btn = new QPushButton(text);
    btn->setFixedHeight(50);
    btn->setStyleSheet(
        QString("QPushButton { "
                "background-color: %1; color: white; border-radius: 8px; "
                "font-size: 14px; font-weight: bold; padding: 0 15px; }"
                "QPushButton:hover { background-color: %2; }"
                "QPushButton:pressed { background-color: %3; }")
            .arg(color,
                 QColor(color).lighter(120).name(),
                 QColor(color).darker(120).name())
        );
    btn->setCursor(Qt::PointingHandCursor);
    return btn;
}

void digitalLibrary::connectDB()
{
    //Add the database with the SQLITE driver
    db = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
    //Set the database path
    db.setDatabaseName("C:/Users/Pc/OneDrive/Bureau/QT_PROJECT/library.db");

    //check if the database is opened
    if(!db.open())
        QMessageBox::critical(this, "FAILED", "DB is not opened");

    //définir la requete sur la base de données
    auto query = QSqlQuery(db);

    //Create a table named accounts
    QString accountTable{"CREATE TABLE IF NOT EXISTS accounts"
                         "(username VARCHAR(20), name VARCHAR(20),"
                         "password VARCHAR(20),ID INTEGER PRIMARY KEY, role varchar(255) )"};

    if(!query.exec(accountTable))
        QMessageBox::critical(this,"Info","Cannot create accounts");

    //Create a table named genres
    QString genreTable{"CREATE TABLE IF NOT EXISTS genres"
                       "(ID INTEGER, name VARCHAR(20))"};
    if(!query.exec(genreTable))
        QMessageBox::critical(this,"Info","Cannot create genre Table");

    //Create a table named authors
    QString authorTable{"CREATE TABLE IF NOT EXISTS authors"
                        "(ID INTEGER, firstName VARCHAR(20), lastName VARCHAR(20),"
                        "expertise VARCHAR(20), about VARCHAR(40))"};
    if(!query.exec(authorTable))
        QMessageBox::critical(this,"Info","Cannot create authors Table");

    //Create a table named members
    QString memberTable{"CREATE TABLE IF NOT EXISTS members"
                        "(ID INTEGER PRIMARY KEY, firstName VARCHAR(20), lastName VARCHAR(20),"
                        "phone VARCHAR(20), email VARCHAR(40), gender VARCHAR(10))"};
    if(!query.exec(memberTable))
        QMessageBox::critical(this,"Info","Cannot create members Table");
    QString member{"CREATE TABLE IF NOT EXISTS accounts"
                   "(ID INTEGER PRIMARY KEY AUTOINCREMENT, firstName VARCHAR(20), lastName VARCHAR(20),"
                   "password varchar(255))"};
    if(!query.exec(member))
        QMessageBox::critical(this,"Info","Cannot create accounts Table");
    //Create a table named books
    QString bookTable{"CREATE TABLE IF NOT EXISTS books"
                      "(ID INTEGER PRIMARY KEY, ISBN VARCHAR(20), name VARCHAR(20),"
                      "author VARCHAR(20), genre VARCHAR(20), quantity INT,"
                      "publisher VARCHAR(20), price REAL, date VARCHAR(10),"
                      "description VARCHAR(80), cover VARCHAR(50))"};
    if(!query.exec(bookTable))
        QMessageBox::critical(this,"Failed","Cannot create books Table");
    query.exec("SELECT COUNT(*) FROM accounts");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO accounts (username, name, password, ID, role) VALUES "
                   "('admin', 'Admin Name', 'admin123', 1, 'admin'),"
                   "('salma', 'Salma Yassine', 'pass123', 2, 'user'),"
                   "('amine', 'Amine El', '1234', 3, 'user'),"
                   "('sara', 'Sara K.', 'azerty', 4, 'user'),"
                   "('yassir', 'Yassir R.', 'yassir2024', 5, 'user'),"
                   "('fatima', 'Fatima Zahra', 'fatpass', 6, 'user'),"
                   "('khalid', 'Khalid M.', 'khalidpass', 7, 'user'),"
                   "('nora', 'Nora B.', 'norapass', 8, 'user'),"
                   "('zineb', 'Zineb K.', 'z123', 9, 'user'),"
                   "('hassan', 'Hassan A.', 'haspass', 10, 'user')");
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS historique_connexions ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "utilisateur_id INTEGER NOT NULL,"
                    "date_connexion DATETIME NOT NULL,"
                    "FOREIGN KEY (utilisateur_id) REFERENCES utilisateur(id))")) {
        qDebug() << "Erreur création table historique_connexions:" << query.lastError().text();
    }

    // Création de la table emprunt si elle n'existe pas
    if (!query.exec("CREATE TABLE IF NOT EXISTS emprunt ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "utilisateur_id INTEGER NOT NULL,"
                    "livre_id INTEGER NOT NULL,"
                    "date_emprunt DATETIME NOT NULL,"
                    "date_retour DATETIME,"
                    "FOREIGN KEY (utilisateur_id) REFERENCES utilisateur(id),"
                    "FOREIGN KEY (livre_id) REFERENCES livre(id))")) {
        qDebug() << "Erreur création table emprunt:" << query.lastError().text();
    }

    // Vérification des colonnes (pour les éventuelles mises à jour)
    QSqlQuery columnsQuery;
    if (!columnsQuery.exec("PRAGMA table_info(emprunt)")) {
        qDebug() << "Erreur vérification colonnes:" << columnsQuery.lastError().text();
    } else if (!columnsQuery.next()) {
        // Si la colonne date_retour n'existe pas, l'ajouter
        if (!query.exec("ALTER TABLE emprunt ADD COLUMN date_retour DATETIME")) {
            qDebug() << "Erreur ajout colonne date_retour:" << query.lastError().text();
        }
    }
    query.exec("SELECT COUNT(*) FROM accounts");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO accounts (username, name, password, ID, role) VALUES "
                   "('admin', 'Admin Name', 'admin123', 1, 'admin'),"
                   "('salma', 'Salma Yassine', 'pass123', 2, 'student'),"
                   "('amine', 'Amine El', '1234', 3, 'student'),"
                   "('sara', 'Sara K.', 'azerty', 4, 'student'),"
                   "('yassir', 'Yassir R.', 'yassir2024', 5, 'student'),"
                   "('fatima', 'Fatima Zahra', 'fatpass', 6, 'student'),"
                   "('khalid', 'Khalid M.', 'khalidpass', 7, 'student'),"
                   "('nora', 'Nora B.', 'norapass', 8, 'student'),"
                   "('zineb', 'Zineb K.', 'z123', 9, 'student'),"
                   "('hassan', 'Hassan A.', 'haspass', 10, 'student')");
    }
    query.exec("SELECT COUNT(*) FROM authors");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO authors (ID, firstName, lastName, expertise, about) VALUES "
                   "(1, 'Victor', 'Hugo', 'Littérature', 'Auteur de classiques'),"
                   "(2, 'Marie', 'Curie', 'Physique', 'Pionnière de la radioactivité'),"
                   "(3, 'Albert', 'Camus', 'Philosophie', 'Existentialisme et absurdité'),"
                   "(4, 'Jules', 'Verne', 'Science-fiction', 'Voyage extraordinaire'),"
                   "(5, 'Simone', 'de Beauvoir', 'Féminisme', 'Le Deuxième Sexe'),"
                   "(6, 'René', 'Descartes', 'Philosophie', 'Cogito ergo sum'),"
                   "(7, 'Gustave', 'Flaubert', 'Roman', 'Madame Bovary'),"
                   "(8, 'George', 'Orwell', 'Politique', '1984 et La Ferme des animaux'),"
                   "(9, 'Stephen', 'Hawking', 'Cosmologie', 'Brief History of Time'),"
                   "(10, 'Frida', 'Kahlo', 'Art', 'Artiste peintre mexicaine')");
    }
    query.exec("SELECT COUNT(*) FROM members");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO members (ID, firstName, lastName, phone, email, gender) VALUES "
                   "(1, 'Ali', 'Ben Ali', '0600000000', 'ali@example.com', 'Homme'),"
                   "(2, 'Noura', 'Bensalem', '0700000000', 'noura@example.com', 'Femme'),"
                   "(3, 'Rachid', 'Amrani', '0661000001', 'rachid@ex.com', 'Homme'),"
                   "(4, 'Lina', 'El Ayoubi', '0662000002', 'lina@ex.com', 'Femme'),"
                   "(5, 'Samir', 'Tazi', '0663000003', 'samir@ex.com', 'Homme'),"
                   "(6, 'Salma', 'Alaoui', '0664000004', 'salma@ex.com', 'Femme'),"
                   "(7, 'Mounir', 'El Idrissi', '0665000005', 'mounir@ex.com', 'Homme'),"
                   "(8, 'Hiba', 'Rami', '0666000006', 'hiba@ex.com', 'Femme'),"
                   "(9, 'Youssef', 'Bakkali', '0667000007', 'youssef@ex.com', 'Homme'),"
                   "(10, 'Najwa', 'Karim', '0668000008', 'najwa@ex.com', 'Femme')");
    }
    query.exec("SELECT COUNT(*) FROM books");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO books (ID, ISBN, name, author, genre, quantity, publisher, price, date, description, cover) VALUES "
                   "(1, '978-1234567890', 'Les Misérables', 'Victor Hugo', 'Roman', 5, 'Gallimard', 14.99, '1862-01-01', 'Classique français', 'cover1.jpg'),"
                   "(2, '978-0987654321', 'La Science pour tous', 'Marie Curie', 'Science', 3, 'CNRS Éditions', 19.99, '1903-01-01', 'Radioactivité', 'cover2.jpg'),"
                   "(3, '978-1111111111', 'L’Étranger', 'Albert Camus', 'Philosophie', 4, 'Folio', 9.99, '1942-01-01', 'Existentialisme', 'cover3.jpg'),"
                   "(4, '978-2222222222', '20 000 Lieues sous les mers', 'Jules Verne', 'Science-fiction', 6, 'Hachette', 12.50, '1870-01-01', 'Aventure sous-marine', 'cover4.jpg'),"
                   "(5, '978-3333333333', 'Le Deuxième Sexe', 'Simone de Beauvoir', 'Féminisme', 2, 'Gallimard', 15.00, '1949-01-01', 'Réflexion féministe', 'cover5.jpg'),"
                   "(6, '978-4444444444', 'Discours de la méthode', 'René Descartes', 'Philosophie', 3, 'PUF', 8.00, '1637-01-01', 'Rationalisme', 'cover6.jpg'),"
                   "(7, '978-5555555555', 'Madame Bovary', 'Gustave Flaubert', 'Roman', 5, 'GF Flammarion', 10.00, '1856-01-01', 'Réalisme', 'cover7.jpg'),"
                   "(8, '978-6666666666', '1984', 'George Orwell', 'Politique', 7, 'Secker & Warburg', 13.99, '1949-01-01', 'Dictature imaginaire', 'cover8.jpg'),"
                   "(9, '978-7777777777', 'Une brève histoire du temps', 'Stephen Hawking', 'Science', 6, 'Bantam Books', 17.00, '1988-01-01', 'Cosmologie', 'cover9.jpg'),"
                   "(10, '978-8888888888', 'Le Journal de Frida', 'Frida Kahlo', 'Art', 2, 'Éditions du Chêne', 22.50, '1954-01-01', 'Art et souffrance', 'cover10.jpg')");
    }

    //Create a table named bookStatus
    QString Table{"CREATE TABLE IF NOT EXISTS bookStatus"
                  "(Book INTEGER, Member INTEGER, Status VARCHAR(10),"
                  "IssueDate date, ReturnDate date, Note VARCHAR(50))"};
    if(!query.exec(Table))
        QMessageBox::critical(this,"Info","Cannot create bookStatus Table");
}

digitalLibrary::~digitalLibrary()
{
    delete ui;
}

void digitalLibrary::on_statsButton_clicked() {
    if (!statWindow) {
        statWindow = new Statistic(db, this); // 'this' pour parentage
        connect(statWindow, &QObject::destroyed, [this]() {
            statWindow = nullptr;
        });
    }
    statWindow->loadAndShowStats(); // Charge et affiche
    //statWindow->show();
}
void digitalLibrary::on_manageGenre_clicked()
{
    manageBooks manage;
    manage.exec();
}

void digitalLibrary::on_manageAuthorButton_clicked()
{
    ManageAuthors manage;
    manage.exec();
}

void digitalLibrary::on_addMemberBtn_clicked()
{
    addMember member;
    member.exec();
}

void digitalLibrary::on_editMemberBtn_clicked()
{
    editMember editMember;
    editMember.exec();
}

void digitalLibrary::on_deleteMemberBtn_clicked()
{
    deleteMember delMember;
    delMember.exec();
}

void digitalLibrary::on_membersListBtn_clicked()
{
    membersList memberlist;
    memberlist.exec();
}

void digitalLibrary::on_addBookBtn_clicked()
{
    addBook addBook;
    //  addBook.setDatabase(db);
    addBook.exec();
}

void digitalLibrary::on_editBookBtn_clicked()
{
    editBook editBook;
    editBook.exec();
}

void digitalLibrary::on_deleteBookBtn_clicked()
{
    deleteBook delBook;
    delBook.exec();
}

void digitalLibrary::on_booksListBtn_clicked()
{
    bookList book;
    book.exec();
}


void digitalLibrary::setUsername(const QString &username)
{
    m_username = username;

    if(!m_usernameLabel) {
        m_usernameLabel = findChild<QLabel*>("usernameLabel");
    }

    if(m_usernameLabel) {
        m_usernameLabel->setText(username);

        // Style optionnel
        m_usernameLabel->setStyleSheet(
            "QLabel {"
            "   color: #2c3e50;"
            "   font-weight: bold;"
            "   padding: 5px 15px;"
            "   background-color: #ecf0f1;"
            "   border-radius: 10px;"
            "}"
            );
    }
}
// void digitalLibrary::showBookNum()
// {
//     QSqlQuery query(db);
//     if(!query.exec("SELECT COUNT(*) FROM books")) {
//         qDebug() << "Error counting books:" << query.lastError();
//         return;
//     }

//     if(query.next()) {
//         // Trouver la carte livre via son objectName
//         QFrame bookCard = findChild<QFrame>("bookCard");
//         if(bookCard) {
//             QLabel valueLabel = bookCard->findChild<QLabel>();
//             if(valueLabel) {
//                 valueLabel->setText(query.value(0).toString());
//             }
//         }
//     }
// }

void digitalLibrary::showMemberNum(){

    //define the query on the db and the model
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM accounts"};

    //execute the query
    if(!query.exec(select))
        qDebug() << "Cannot select from members";

    int count = 0;
    while(query.next())
        count++;

    ui->memberNum->setText(QString::number(count));
}

void digitalLibrary::showAuthorNum(){

    //define the query
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM authors"};

    //execute the query
    if(!query.exec(select))
        qDebug() << "Cannot select from authors";

    int count = 0;
    while(query.next())
        count++;

    ui->authorNum->setText(QString::number(count));
}
void digitalLibrary::insertTestData()
{
    QSqlQuery query(db);

    // Désactiver les vérifications de clés étrangères temporairement
    query.exec("PRAGMA foreign_keys = OFF");

    // Vider les tables existantes
    query.exec("DELETE FROM bookStatus");
    query.exec("DELETE FROM books");
    query.exec("DELETE FROM members");
    query.exec("DELETE FROM authors");
    query.exec("DELETE FROM genres");

    // Insérer les genres
    query.prepare("INSERT INTO genres (ID, name) VALUES (?, ?)");
    QList<QPair<int, QString>> genres = {
        {1, "Roman"},
        {2, "Science-Fiction"},
        {3, "Histoire"},
        {4, "Informatique"},
        {5, "Biographie"}
    };

    for (const auto &genre : genres) {
        query.addBindValue(genre.first);
        query.addBindValue(genre.second);
        query.exec();
    }

    // Insérer les auteurs
    query.prepare("INSERT INTO authors (ID, firstName, lastName, expertise, about) VALUES (?, ?, ?, ?, ?)");
    QList<QList<QVariant>> authors = {
        {1, "Victor", "Hugo", "Littérature", "Écrivain français du 19ème siècle"},
        {2, "Isaac", "Asimov", "Science-Fiction", "Auteur de science-fiction américain"},
        {3, "Stephen", "Hawking", "Physique", "Physicien théoricien et cosmologiste"}
    };

    for (const auto &author : authors) {
        for (int i = 0; i < author.size(); ++i) {
            query.bindValue(i, author[i]);
        }
        query.exec();
    }

    // Insérer les membres
    query.prepare("INSERT INTO members (ID, firstName, lastName, phone, email, gender) VALUES (?, ?, ?, ?, ?, ?)");
    QList<QList<QVariant>> members = {
        {1, "Jean", "Dupont", "0612345678", "jean.dupont@email.com", "Male"},
        {2, "Marie", "Martin", "0698765432", "marie.martin@email.com", "Female"},
        {3, "Pierre", "Durand", "0601020304", "pierre.durand@email.com", "Male"}
    };

    for (const auto &member : members) {
        for (int i = 0; i < member.size(); ++i) {
            query.bindValue(i, member[i]);
        }
        query.exec();
    }

    // Insérer les livres
    query.prepare("INSERT INTO books (ID, ISBN, name, author, genre, quantity, publisher, price, date, description) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    QList<QList<QVariant>> books = {
        {1, "9782070408504", "Les Misérables", "Victor Hugo", "Roman", 10, "Gallimard", 12.50, "1862", "Un classique de la littérature française"},
        {2, "9782290032724", "Fondation", "Isaac Asimov", "Science-Fiction", 8, "Pocket", 8.90, "1951", "Un chef-d'œuvre de science-fiction"},
        {3, "9782020093609", "Une brève histoire du temps", "Stephen Hawking", "Science", 5, "Flammarion", 15.90, "1988", "Introduction aux concepts de cosmologie"},
        {4, "9782253080262", "Notre-Dame de Paris", "Victor Hugo", "Roman", 7, "LGF", 7.40, "1831", "Roman historique se déroulant à Paris"},
        {5, "9782290032731", "Fondation et Empire", "Isaac Asimov", "Science-Fiction", 6, "Pocket", 8.90, "1952", "Suite de Fondation"}
    };

    for (const auto &book : books) {
        for (int i = 0; i < book.size(); ++i) {
            query.bindValue(i, book[i]);
        }
        query.exec();
    }

    // Insérer les emprunts
    query.prepare("INSERT INTO bookStatus (Book, Member, Status, IssueDate, ReturnDate, Note) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    QList<QList<QVariant>> borrowings = {
        {1, 1, "Borrowed", "2023-01-15", "2023-02-15", ""},
        {1, 2, "Borrowed", "2023-03-10", "2023-04-10", ""},
        {1, 3, "Borrowed", "2023-05-05", "2023-06-05", ""},
        {2, 1, "Borrowed", "2023-02-01", "2023-03-01", ""},
        {2, 2, "Borrowed", "2023-04-01", "2023-05-01", ""},
        {3, 1, "Borrowed", "2023-01-10", "2023-02-10", ""},
        {4, 3, "Borrowed", "2023-03-15", "2023-04-15", ""},
        {5, 2, "Borrowed", "2023-05-20", QVariant(QMetaType::fromType<QString>()), ""} // NULL pour ReturnDate
    };

    for (const auto &borrowing : borrowings) {
        for (int i = 0; i < borrowing.size(); ++i) {
            query.bindValue(i, borrowing[i]);
        }
        query.exec();
    }

    // Réactiver les vérifications de clés étrangères
    query.exec("PRAGMA foreign_keys = ON");

    QMessageBox::information(this, "Succès", "Données de test insérées avec succès!");
}
void digitalLibrary::on_testDataButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Voulez-vous vraiment insérer des données de test?\n"
                                  "Toutes les données existantes seront effacées!",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        insertTestData();
    }
}


void digitalLibrary::on_issueBookBtn_clicked() {
    // Code
}

void digitalLibrary::on_returnBookBtn_clicked() {
    // Code
}
