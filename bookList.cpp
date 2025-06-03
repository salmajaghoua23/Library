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
bookList::bookList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookList)
{
    ui->setupUi(this);
    this->setWindowTitle("Bibliothèque • Liste des Livres");
    this->setMinimumSize(1200, 800);
    this->setStyleSheet("background: #f5f7fa;");

    // Créer le titre principal
    QLabel *headerTitle = new QLabel("📚 Livres disponibles dans la bibliothèque", this);
    headerTitle->setAlignment(Qt::AlignCenter);
    headerTitle->setStyleSheet("font-size: 24px; font-weight: bold; color: #2d3748; margin-top: 20px;");

    // Bouton retour
    QPushButton *returnButton = new QPushButton("⬅️ Retour", this);
    returnButton->setFixedSize(120, 40);
    returnButton->setStyleSheet(
        "QPushButton {"
        " background-color: #ff944d;"
        " color: white;"
        " border-radius: 8px;"
        " font-size: 14px;"
        " font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #e68a00; }"
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

    // Requête BDD
    digitalLibrary lib;
    auto db = lib.db;
    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM books"))
        qDebug() << "Erreur de requête : " << query.lastError();

    // Couleurs cycliques
    QStringList colorThemes = {
        "#ff9966", // orange
        "#6a5acd", // violet
        "#4a6fa5"  // bleu
    };

    int row = 0, col = 0, colorIndex = 0;
    while (query.next()) {
        QString title = query.value(2).toString();
        QString author = query.value(3).toString();
        QString genre = query.value(4).toString();
        QString id = query.value(0).toString();

        QString emoji = "📖";  // Emoji livre

        // Carte
        QFrame *card = new QFrame(cardsContainer);
        card->setMinimumSize(250, 350);
        card->setMaximumSize(250, 350);
        card->setStyleSheet(QString(
            "QFrame {"
            " background: white;"
            " border-radius: 12px;"
            " border: none;"
            " box-shadow: 0px 0px 10px rgba(0,0,0,0.1);"
            "}"
            ));

        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(card);
        shadow->setBlurRadius(15);
        shadow->setOffset(0, 5);
        shadow->setColor(QColor(0, 0, 0, 60));
        card->setGraphicsEffect(shadow);

        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setContentsMargins(0, 0, 0, 0);
        cardLayout->setSpacing(0);

        // En-tête coloré
        QLabel *emojiLabel = new QLabel(emoji, card);
        emojiLabel->setAlignment(Qt::AlignCenter);
        emojiLabel->setMinimumHeight(180);
        emojiLabel->setStyleSheet(QString(
                                      "background-color: %1;"
                                      "font-size: 64px;"
                                      "border-top-left-radius: 12px;"
                                      "border-top-right-radius: 12px;"
                                      ).arg(colorThemes[colorIndex % colorThemes.size()]));
        cardLayout->addWidget(emojiLabel);

        // Contenu
        QFrame *textFrame = new QFrame(card);
        textFrame->setStyleSheet(
            "background: white;"
            "padding: 15px;"
            "border-bottom-left-radius: 12px;"
            "border-bottom-right-radius: 12px;"
            );
        QVBoxLayout *textLayout = new QVBoxLayout(textFrame);

        QLabel *titleLabel = new QLabel(title, textFrame);
        titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2d3748;");
        titleLabel->setWordWrap(true);

        QLabel *authorLabel = new QLabel(author, textFrame);
        authorLabel->setStyleSheet("font-size: 13px; color: #555;");
        authorLabel->setWordWrap(true);

        QLabel *genreLabel = new QLabel("Genre : " + genre, textFrame);
        genreLabel->setStyleSheet("font-size: 12px; color: #888;");

        QPushButton *detailsBtn = new QPushButton("📘 Voir détails", textFrame);
        detailsBtn->setStyleSheet(
            "QPushButton {"
            " background-color: #4a6fa5;"
            " color: white;"
            " padding: 5px 10px;"
            " border-radius: 6px;"
            " font-size: 12px;"
            "}"
            "QPushButton:hover { background-color: #5a7fb5; }"
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

        colorIndex++; // Changer de couleur
    }

    // Ajouter le layout principal à la boîte de dialogue
    QVBoxLayout *finalLayout = new QVBoxLayout(this);
    finalLayout->addWidget(mainWidget);
}

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
