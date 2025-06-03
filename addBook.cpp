#include "addBook.h"
#include "ui_addBook.h"
#include "genreList.h"
#include "digitalLibrary.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include "authorsList.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QGraphicsDropShadowEffect>
#include<QPropertyAnimation>
#include "addBook.h"
#include "ui_addBook.h"
#include "genreList.h"
#include "digitalLibrary.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include "authorsList.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QLinearGradient>

addBook::addBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);

    // Configuration de base de la fenêtre
    this->setWindowTitle("Ajouter un Nouveau Livre • Bibliothèque Digitale");
    this->setMinimumSize(900, 700);
    this->setStyleSheet("background: #f5f7fa;");

    // Conteneur principal
    QFrame *mainContainer = new QFrame(this);
    mainContainer->setGeometry(0, 0, this->width(), this->height());
    mainContainer->setStyleSheet("background: transparent;");

    // Animation d'entrée
    QPropertyAnimation *slideAnim = new QPropertyAnimation(mainContainer, "geometry");
    slideAnim->setDuration(400);
    slideAnim->setStartValue(QRect(-this->width(), 0, this->width(), this->height()));
    slideAnim->setEndValue(QRect(0, 0, this->width(), this->height()));
    slideAnim->start();

    // Carte de formulaire
    QFrame *formCard = new QFrame(mainContainer);
    formCard->setGeometry(50, 30, this->width()-100, this->height()-60);
    formCard->setStyleSheet(
        "background: white;"
        "border-radius: 12px;"
        "border: none;"
        );

    // Ombre portée moderne
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(formCard);
    shadow->setBlurRadius(25);
    shadow->setOffset(0, 5);
    shadow->setColor(QColor(0, 0, 0, 30));
    formCard->setGraphicsEffect(shadow);

    // En-tête minimaliste
    QFrame *header = new QFrame(formCard);
    header->setGeometry(0, 0, formCard->width(), 70);
    header->setStyleSheet(
        "background: #4a6fa5;"
        "border-top-left-radius: 12px;"
        "border-top-right-radius: 12px;"
        );

    // Bouton de retour
    QPushButton *backBtn = new QPushButton(header);
    backBtn->setGeometry(20, 15, 40, 40);
    backBtn->setStyleSheet(
        "QPushButton {"
        "   background: rgba(255,255,255,0.2);"
        "   border-radius: 20px;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   background: rgba(255,255,255,0.3);"
        "}"
        );
   // backBtn->setIcon(QIcon(":/icons/arrow-left.svg"));
    backBtn->setIconSize(QSize(24, 24));

    // Titre
    QLabel *title = new QLabel("+ Nouveau Livre", header);
    title->setGeometry(70, 15, header->width()-90, 40);
    title->setStyleSheet(
        "color: white;"
        "font-family: 'Segoe UI';"
        "font-size: 22px;"
        "font-weight: 600;"
        );

    // Style commun pour les champs
    QString fieldStyle = R"(
        QFrame#fieldContainer {
            background: #f8fafc;
            border-radius: 8px;
            border: 1px solid #e2e8f0;
        }
        QLabel#fieldLabel {
            color: #4a5568;
            font-family: 'Segoe UI';
            font-size: 12px;
            font-weight: 600;
            padding-left: 5px;
        }
        QLineEdit, QTextEdit, QComboBox {
            border: none;
            background: transparent;
            font-family: 'Segoe UI';
            font-size: 14px;
            padding: 8px 12px;
            color: #2d3748;
        }
        QLineEdit:focus, QTextEdit:focus {
            background: white;
            border: 1px solid #a0aec0;
        }
    )";

    // Fonction pour créer des champs
    auto createField = [&](const QString &label, QWidget *widget, int yPos) {
        QFrame *container = new QFrame(formCard);
        container->setObjectName("fieldContainer");
        container->setGeometry(30, yPos, formCard->width()-60, 70);
        container->setStyleSheet(fieldStyle);

        QLabel *labelWidget = new QLabel(label, container);
        labelWidget->setObjectName("fieldLabel");
        labelWidget->setGeometry(10, 8, container->width()-20, 18);

        widget->setParent(container);
        widget->setGeometry(10, 30, container->width()-20, 30);
    };

    // Position verticale initiale
    int yPos = 90;

    // Création des champs
    createField("ISBN", ui->ISBN, yPos); yPos += 80;
    createField("Titre du Livre", ui->Name, yPos); yPos += 80;

    // Champ Auteur avec bouton
    QFrame *authorContainer = new QFrame(formCard);
    authorContainer->setObjectName("fieldContainer");
    authorContainer->setGeometry(30, yPos, formCard->width()-60, 70);
    authorContainer->setStyleSheet(fieldStyle);

    QLabel *authorLabel = new QLabel("Auteur", authorContainer);
    authorLabel->setObjectName("fieldLabel");
    authorLabel->setGeometry(10, 8, authorContainer->width()-20, 18);

    ui->author->setParent(authorContainer);
    ui->author->setGeometry(10, 30, authorContainer->width()-130, 30);

    ui->chooseAuthBtn->setParent(authorContainer);
    ui->chooseAuthBtn->setGeometry(authorContainer->width()-120, 30, 110, 30);
    ui->chooseAuthBtn->setStyleSheet(R"(
        QPushButton {
            background: #4a6fa5;
            border-radius: 6px;
            color: white;
            font-size: 12px;
            font-weight: 500;
            border: none;
        }
        QPushButton:hover {
            background: #3a5a80;
        }
    )");
   // ui->chooseAuthBtn->setIcon(QIcon(":/icons/user-plus.svg"));
    ui->chooseAuthBtn->setText(" Sélectionner");

    yPos += 80;

    // Champ Genre avec bouton
    QFrame *genreContainer = new QFrame(formCard);
    genreContainer->setObjectName("fieldContainer");
    genreContainer->setGeometry(30, yPos, formCard->width()-60, 70);
    genreContainer->setStyleSheet(fieldStyle);

    QLabel *genreLabel = new QLabel("Genre", genreContainer);
    genreLabel->setObjectName("fieldLabel");
    genreLabel->setGeometry(10, 8, genreContainer->width()-20, 18);

    ui->Genre->setParent(genreContainer);
    ui->Genre->setGeometry(10, 30, genreContainer->width()-130, 30);

    ui->chooseGenreBtn->setParent(genreContainer);
    ui->chooseGenreBtn->setGeometry(genreContainer->width()-120, 30, 110, 30);
    ui->chooseGenreBtn->setStyleSheet(R"(
        QPushButton {
            background: #4a6fa5;
            border-radius: 6px;
            color: white;
            font-size: 12px;
            font-weight: 500;
            border: none;
        }
        QPushButton:hover {
            background: #3a5a80;
        }
    )");
   // ui->chooseGenreBtn->setIcon(QIcon(":/icons/tag.svg"));
    ui->chooseGenreBtn->setText(" Choisir");

    yPos += 80;

    // Champ Description
    QFrame *descContainer = new QFrame(formCard);
    descContainer->setObjectName("fieldContainer");
    descContainer->setGeometry(30, yPos, formCard->width()-60, 150);
    descContainer->setStyleSheet(fieldStyle);

    QLabel *descLabel = new QLabel("Description", descContainer);
    descLabel->setObjectName("fieldLabel");
    descLabel->setGeometry(10, 8, descContainer->width()-20, 18);

    ui->description->setParent(descContainer);
    ui->description->setGeometry(10, 30, descContainer->width()-20, 110);
    ui->description->setStyleSheet("border: 1px solid #e2e8f0; border-radius: 6px;");

    yPos += 170;

    // Boutons d'action
    QFrame *buttonBar = new QFrame(formCard);
    buttonBar->setGeometry(30, formCard->height()-70, formCard->width()-60, 50);
    buttonBar->setStyleSheet("background: transparent;");

    // Bouton Annuler
    QPushButton *cancelBtn = new QPushButton("Annuler", buttonBar);
    cancelBtn->setGeometry(0, 0, 120, 40);
    cancelBtn->setStyleSheet(R"(
        QPushButton {
            background: transparent;
            border: 1px solid #cbd5e0;
            border-radius: 6px;
            color: #4a5568;
            font-weight: 500;
        }
        QPushButton:hover {
            background: rgba(203, 213, 224, 0.3);
        }
    )");

    // Bouton Ajouter
    QPushButton *addBtn = new QPushButton("Ajouter le Livre", buttonBar);
    addBtn->setGeometry(buttonBar->width()-200, 0, 200, 40);
    addBtn->setStyleSheet(R"(
        QPushButton {
            background: #4a6fa5;
            border-radius: 6px;
            color: white;
            font-weight: 600;
            border: none;
        }
        QPushButton:hover {
            background: #3a5a80;
        }
        QPushButton:pressed {
            background: #2a4a70;
        }
    )");

    // Animation de survol pour le bouton Ajouter
    QPropertyAnimation *hoverAnim = new QPropertyAnimation(addBtn, "geometry");
    hoverAnim->setDuration(150);

    connect(addBtn, &QPushButton::pressed, [=]() {
        hoverAnim->stop();
        hoverAnim->setEndValue(QRect(buttonBar->width()-200, 2, 200, 38));
        hoverAnim->start();
    });

    connect(addBtn, &QPushButton::released, [=]() {
        hoverAnim->stop();
        hoverAnim->setEndValue(QRect(buttonBar->width()-200, 0, 200, 40));
        hoverAnim->start();
    });

    // Connecter les signaux
    connect(backBtn, &QPushButton::clicked, this, &addBook::reject);
    connect(cancelBtn, &QPushButton::clicked, this, &addBook::reject);
    connect(addBtn, &QPushButton::clicked, this, &addBook::on_addBookBtn_clicked);

    // Initialisation des validateurs
    setValidator();
}

// Les autres méthodes de la classe restent inchangées
addBook::~addBook()
{
    delete ui;
}

void addBook::on_cancelBtn_clicked()
{
    this->hide();
}

void addBook::on_addBookBtn_clicked()
{
    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //get the content
    QString ISBN = ui->ISBN->text();
    QString name = ui->Name->text();
    QString author = ui->author->text();
    QString genre = ui->Genre->currentText();
    QString quantity = ui->quantity->text();
    QString publisher = ui->publisher->text();
    QString price = ui->price->text();
    QString date = ui->date->text();
    QString description = ui->description->toPlainText();
    QString coverPath = coverFilename;

    QStringList bookInfo {ISBN, name, author, genre, quantity, publisher, price, date};

    //test if the fields are not empty
    bool full = true;
    for(int i=0; i<bookInfo.length(); i++)
    {
        if(bookInfo[i].isEmpty())
        {
            full = false;
            break;
        }
    }

    //test if the book already exits
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM books WHERE ISBN = '%1'"};
    if(!query.exec(select.arg(ISBN)))
        qDebug() << "Cannot select from books table";

    int count = 0;
    while(query.next())
        count++;

    if(full)
    {
        if(count == 0)
        {
            //Define the query on the db
            auto query = QSqlQuery(db);
            QString insert{"INSERT INTO books (ISBN, name, author, genre, quantity, publisher, price, date, description, cover)"
                           "VALUES ('%1', '%2', '%3','%4','%5','%6','%7','%8','%9', '%10')"};

            //execute the query
            if(!query.exec(insert.arg(ISBN).arg(name).arg(author).arg(genre).arg(quantity.toInt()).arg(publisher).arg(price.toDouble()).arg(date).arg(description).arg(coverPath)))
            {
                QMessageBox::critical(this,"Failed","Cannot fill books Table");
            }
            else
            {
                QMessageBox::information(this,"Info","Book is added sucessfully");
            }
        }
        else
            QMessageBox::warning(this, "Info", "Book already exists");
    }
    else
        QMessageBox::critical(this,"Failed","Fields are empty");
}

void addBook::on_selectImgBtn_clicked()
{
    //Open a file dialog to choose the image
    coverFilename = QFileDialog::getOpenFileName();
    ui->coverLabel->setPixmap(coverFilename);
}

void addBook::on_chooseAuthBtn_clicked()
{
    authorsList authors;
    authors.exec();
    ui->author->setText(authors.author);
}

void addBook::setValidator(){
    //ISBN Validator
    QRegularExpression ISBN ("[0-9]*[-| ][0-9]*[-| ][0-9]*[-| ][0-9]*[-| ][0-9]*");
    QRegularExpressionValidator *ISBNVal = new QRegularExpressionValidator(ISBN, this);
    ui->ISBN->setValidator(ISBNVal);

    //regx for name
    QRegularExpression Name("[a-zA-Z0-9_+-\\\\s]{1000}");
    QRegularExpressionValidator *valName = new QRegularExpressionValidator(Name, this);
    ui->Name->setValidator(valName);
    ui->publisher->setValidator(valName);

    //setValidator for price
    QRegularExpression price("^\\d{0,8}(\\.\\d{1,4})?$");
    QRegularExpressionValidator *valPrice = new QRegularExpressionValidator(price, this);
    ui->price->setValidator(valPrice);
}

void addBook::on_chooseGenreBtn_clicked()
{
    genreList genre;
    genre.exec();
    ui->Genre->addItem(genre.genre);
}
