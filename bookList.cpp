#include "bookList.h"
#include "ui_bookList.h"
#include "digitalLibrary.h"
#include "addBook.h"
#include <QDebug>
#include <QSqlQuery>
#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include<QSqlError>
// ...existing includes...
bookList::bookList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookList)
{
    ui->setupUi(this);
    this->setWindowTitle("Bibliothèque • Liste des Livres");
    this->setMinimumSize(1200, 800);
    this->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #ede7f6, stop:1 #a18cd1);");

    // Titre principal
    QLabel *headerTitle = new QLabel("📚 Livres disponibles dans la bibliothèque", this);
    headerTitle->setAlignment(Qt::AlignCenter);
    headerTitle->setStyleSheet("font-size: 26px; font-weight: bold; color: #6c3eb6; margin-top: 20px;");

    // Bouton retour
    QPushButton *returnButton = new QPushButton("⬅️ Retour", this);
    returnButton->setFixedSize(120, 40);
    returnButton->setStyleSheet(
        "QPushButton {"
        " background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #a18cd1, stop:1 #6c3eb6);"
        " color: white;"
        " border-radius: 10px;"
        " font-size: 15px;"
        " font-weight: bold;"
        "}"
        "QPushButton:hover { background: #7c3aed; color: #fff; }"
    );
    connect(returnButton, &QPushButton::clicked, this, &bookList::close);

    // Conteneur principal
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->addWidget(returnButton, 0, Qt::AlignLeft);
    mainLayout->addWidget(headerTitle, 0, Qt::AlignCenter);

    // Scroll Area
    QScrollArea *scrollArea = new QScrollArea(mainWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("border: none; background: transparent;");
    mainLayout->addWidget(scrollArea);

    QWidget *cardsContainer = new QWidget(scrollArea);
    cardsContainer->setStyleSheet("background: transparent;");
    scrollArea->setWidget(cardsContainer);

    QGridLayout *gridLayout = new QGridLayout(cardsContainer);
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(30, 30, 30, 30);

    // Dégradés de violet pour les cartes
    QStringList colorThemes = {
        "qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #a18cd1, stop:1 #fbc2eb)", // violet-rose
        "qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #7c3aed, stop:1 #a18cd1)", // violet
        "qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #c084fc, stop:1 #a78bfa)"  // violet clair
    };

    int row = 0, col = 0, colorIndex = 0;
    digitalLibrary lib;
    auto db = lib.db;
    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM books"))
        qDebug() << "Erreur de requête : " << query.lastError();

    while (query.next()) {
        QString title = query.value(2).toString();
        QString author = query.value(3).toString();
        QString genre = query.value(4).toString();
        QString id = query.value(0).toString();

        QString emoji = "📖";

        // Carte
        QFrame *card = new QFrame(cardsContainer);
        card->setMinimumSize(250, 350);
        card->setMaximumSize(250, 350);
        card->setStyleSheet(QString(
            "QFrame {"
            " background: white;"
            " border-radius: 14px;"
            " border: 2px solid #a18cd1;"
            " box-shadow: 0px 0px 16px rgba(124,62,237,0.10);"
            "}"
            "QFrame:hover {"
            " border: 2px solid #7c3aed;"
            " box-shadow: 0px 0px 24px #a18cd1;"
            "}"
        ));

        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(card);
        shadow->setBlurRadius(18);
        shadow->setOffset(0, 6);
        shadow->setColor(QColor(161, 140, 209, 80));
        card->setGraphicsEffect(shadow);

        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setContentsMargins(0, 0, 0, 0);
        cardLayout->setSpacing(0);

        // En-tête coloré (dégradé violet)
        QLabel *emojiLabel = new QLabel(emoji, card);
        emojiLabel->setAlignment(Qt::AlignCenter);
        emojiLabel->setMinimumHeight(180);
        emojiLabel->setStyleSheet(QString(
            "background: %1;"
            "font-size: 64px;"
            "border-top-left-radius: 14px;"
            "border-top-right-radius: 14px;"
        ).arg(colorThemes[colorIndex % colorThemes.size()]));
        cardLayout->addWidget(emojiLabel);

        // Contenu
        QFrame *textFrame = new QFrame(card);
        textFrame->setStyleSheet(
            "background: white;"
            "padding: 18px;"
            "border-bottom-left-radius: 14px;"
            "border-bottom-right-radius: 14px;"
        );
        QVBoxLayout *textLayout = new QVBoxLayout(textFrame);

        QLabel *titleLabel = new QLabel(title, textFrame);
        titleLabel->setStyleSheet("font-size: 17px; font-weight: bold; color: #7c3aed;");
        titleLabel->setWordWrap(true);

        QLabel *authorLabel = new QLabel(author, textFrame);
        authorLabel->setStyleSheet("font-size: 14px; color: #a18cd1;");
        authorLabel->setWordWrap(true);

        QLabel *genreLabel = new QLabel("Genre : " + genre, textFrame);
        genreLabel->setStyleSheet("font-size: 13px; color: #c084fc;");

        QPushButton *detailsBtn = new QPushButton("📘 Voir détails", textFrame);
        detailsBtn->setStyleSheet(
            "QPushButton {"
            " background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #a18cd1, stop:1 #7c3aed);"
            " color: white;"
            " padding: 6px 14px;"
            " border-radius: 8px;"
            " font-size: 13px;"
            " font-weight: bold;"
            "}"
            "QPushButton:hover { background: #c084fc; color: #fff; }"
        );

        textLayout->addWidget(titleLabel);
        textLayout->addWidget(authorLabel);
        textLayout->addWidget(genreLabel);
        textLayout->addWidget(detailsBtn, 0, Qt::AlignRight);
        cardLayout->addWidget(textFrame);

        gridLayout->addWidget(card, row, col);

        connect(detailsBtn, &QPushButton::clicked, [this, id]() {
            showBookDetails(id);
        });

        col++;
        if (col > 3) {
            col = 0;
            row++;
        }
        colorIndex++;
    }

    // Ajouter le layout principal à la boîte de dialogue
    QVBoxLayout *finalLayout = new QVBoxLayout(this);
    finalLayout->addWidget(mainWidget);
}

// ...showBookDetails et autres fonctions inchangées...

void bookList::showBookDetails(const QString &bookId)
{
    digitalLibrary lib;
    auto db = lib.db;

    QSqlQuery query(db);
    query.prepare("SELECT * FROM books WHERE ID = :id");
    query.bindValue(":id", bookId);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError();
        return;
    }

    if (query.next()) {
        QString ISBN = query.value(1).toString();
        QString name = query.value(2).toString();
        QString author = query.value(3).toString();
        QString genre = query.value(4).toString();
        QString quantity = query.value(5).toString();
        QString publisher = query.value(6).toString();
        QString price = query.value(7).toString();
        QString date = query.value(8).toString();
        QString desc = query.value(9).toString();
        QString cover = query.value(10).toString();

        QDialog *detailsDialog = new QDialog(this);
        detailsDialog->setWindowTitle("Détails du Livre");
        detailsDialog->setMinimumSize(600, 500);
        detailsDialog->setStyleSheet("background: #f8fafc;");

        QVBoxLayout *layout = new QVBoxLayout(detailsDialog);

        // En-tête
        QFrame *header = new QFrame(detailsDialog);
        header->setStyleSheet("background: #4a6fa5; border-top-left-radius: 8px; border-top-right-radius: 8px; padding: 20px;");
        QHBoxLayout *headerLayout = new QHBoxLayout(header);

        QLabel *coverLabel = new QLabel(header);
        coverLabel->setMinimumSize(120, 180);
        coverLabel->setMaximumSize(120, 180);
        coverLabel->setAlignment(Qt::AlignCenter);
        coverLabel->setStyleSheet("background: white; border-radius: 4px; border: 1px solid #e2e8f0;");

        if (!cover.isEmpty()) {
            QPixmap pixmap(cover);
            if (!pixmap.isNull()) {
                coverLabel->setPixmap(pixmap.scaled(120, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
        } else {
            coverLabel->setPixmap(QIcon(":/icons/book.svg").pixmap(64, 64));
        }

        QVBoxLayout *titleLayout = new QVBoxLayout();
        QLabel *titleLabel = new QLabel(name, header);
        titleLabel->setStyleSheet("font-size: 22px; font-weight: 600; color: white;");
        QLabel *authorLabel = new QLabel("par " + author, header);
        authorLabel->setStyleSheet("font-size: 16px; color: rgba(255,255,255,0.9);");

        titleLayout->addWidget(titleLabel);
        titleLayout->addWidget(authorLabel);
        titleLayout->addStretch();

        headerLayout->addWidget(coverLabel);
        headerLayout->addLayout(titleLayout);

        // Détails du livre
        QFrame *detailsFrame = new QFrame(detailsDialog);
        QFormLayout *formLayout = new QFormLayout(detailsFrame);
        detailsFrame->setStyleSheet("font-size: 14px; padding: 20px;");

        formLayout->addRow("ISBN :", new QLabel(ISBN));
        formLayout->addRow("Genre :", new QLabel(genre));
        formLayout->addRow("Quantité :", new QLabel(quantity));
        formLayout->addRow("Éditeur :", new QLabel(publisher));
        formLayout->addRow("Prix :", new QLabel(price));
        formLayout->addRow("Date d’ajout :", new QLabel(date));

        // Description
        QLabel *descLabel = new QLabel(desc);
        descLabel->setWordWrap(true);
        descLabel->setStyleSheet("padding: 0 20px; font-size: 13px; color: #4a5568;");

        layout->addWidget(header);
        layout->addWidget(detailsFrame);
        layout->addWidget(new QLabel("Description :"));
        layout->addWidget(descLabel);

        detailsDialog->exec();
    } else {
        qDebug() << "Livre introuvable.";
    }
}


void bookList::addDetailRow(QFormLayout *layout, const QString &label, const QString &value)
{
    QLabel *labelWidget = new QLabel(label);
    labelWidget->setStyleSheet(
        "font-family: 'Segoe UI';"
        "font-size: 14px;"
        "font-weight: 600;"
        "color: #718096;"
        );

    QLabel *valueWidget = new QLabel(value);
    valueWidget->setStyleSheet(
        "font-family: 'Segoe UI';"
        "font-size: 14px;"
        "color: #2d3748;"
        );

    layout->addRow(labelWidget, valueWidget);
}

void bookList::on_value_textEdited(const QString &arg1)
{
    // Implémentation existante inchangée
    QString value = ui->value->text() + "%";
    Q_UNUSED(arg1);
    digitalLibrary lib;
    auto db = lib.db;

    if(!value.isEmpty()) {
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM books WHERE ID LIKE '"+value+"'"
                                                                       "OR ISBN LIKE '"+value+"' OR name LIKE '"+value+"' OR author LIKE '"+value+"'"
                                                                                             "OR genre LIKE '"+value+"' OR quantity LIKE '"+value+"'"
                                                                  "OR publisher LIKE '"+value+"' OR price LIKE '"+value+"' OR date LIKE '"+value+"'"};

        if(!query.exec(select))
            qDebug() << "Cannot select from books";
    } else {
        auto query = QSqlQuery(db);
        QString select{"SELECT * FROM books"};
        if(!query.exec(select))
            qDebug() << "Cannot select from books";
    }
}

bookList::~bookList()
{
    delete ui;
}
