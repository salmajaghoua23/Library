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
    QDialog(parent)
{
    setWindowTitle("Ajouter un Nouveau Livre • Bibliothèque Digitale");
    setMinimumSize(900, 700);
    setStyleSheet("background: #f5f7fa;");

    // Layout principal pour centrer la carte
    QHBoxLayout *dialogLayout = new QHBoxLayout(this);

    // Carte de formulaire
    QFrame *formCard = new QFrame;
    formCard->setObjectName("formCard");
    formCard->setStyleSheet(
        "background: white;"
        "border-radius: 16px;"
        "border: none;"
        );

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(formCard);
    shadow->setBlurRadius(25);
    shadow->setOffset(0, 5);
    shadow->setColor(QColor(0, 0, 0, 30));
    formCard->setGraphicsEffect(shadow);

    dialogLayout->addStretch();
    dialogLayout->addWidget(formCard, 0, Qt::AlignCenter);
    dialogLayout->addStretch();

    QVBoxLayout *formLayout = new QVBoxLayout(formCard);
    formLayout->setContentsMargins(40, 30, 40, 30);
    formLayout->setSpacing(24);

    // Header avec bouton retour et titre
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QPushButton *backBtn = new QPushButton("⬅️ Retour");
    backBtn->setFixedHeight(44);
    backBtn->setStyleSheet(
        "background: #fbc2eb;"
        "color: #232946;"
        "font-size: 20px;"
        "font-weight: bold;"
        "border: 2px solid #a18cd1;"
        "border-radius: 12px;"
        "padding: 0 28px;"
        );
    headerLayout->addWidget(backBtn, 0, Qt::AlignLeft);

    QLabel *title = new QLabel("+ Nouveau Livre");
    title->setStyleSheet(
        "color: #4a6fa5;"
        "font-family: 'Segoe UI';"
        "font-size: 28px;"
        "font-weight: 700;"
        );
    headerLayout->addWidget(title, 1, Qt::AlignCenter);
    headerLayout->addStretch();
    formLayout->addLayout(headerLayout);

    // Style commun pour les champs
    QString fieldStyle = R"(
        QFrame#fieldContainer {
            background: #f8fafc;
            border-radius: 10px;
            border: 1px solid #e2e8f0;
        }
        QLabel#fieldLabel {
            color: #232946;
            font-family: 'Segoe UI';
            font-size: 18px;
            font-weight: 700;
            padding-left: 5px;
        }
        QLineEdit, QTextEdit, QComboBox, QSpinBox, QDoubleSpinBox, QDateEdit {
            border: none;
            background: transparent;
            font-family: 'Segoe UI';
            font-size: 18px;
            font-weight: 600;
            padding: 12px 16px;
            color: #2d3748;
            min-height: 38px;
        }
        QLineEdit:focus, QTextEdit:focus {
            background: white;
            border: 1px solid #a0aec0;
        }
    )";

    // Fonction pour créer des champs
    auto createField = [&](const QString &label, QWidget *widget) {
        widget->setMinimumHeight(38);
        widget->setFont(QFont("Segoe UI", 16, QFont::Bold));
        QFrame *container = new QFrame;
        container->setObjectName("fieldContainer");
        container->setStyleSheet(fieldStyle);

        QVBoxLayout *fieldLayout = new QVBoxLayout(container);
        fieldLayout->setContentsMargins(10, 8, 10, 8);
        fieldLayout->setSpacing(2);

        QLabel *labelWidget = new QLabel(label, container);
        labelWidget->setObjectName("fieldLabel");
        fieldLayout->addWidget(labelWidget);
        fieldLayout->addWidget(widget);

        formLayout->addWidget(container);
    };

    // Champs
    QLineEdit *isbnEdit = new QLineEdit();
    QLineEdit *nameEdit = new QLineEdit();
    QLineEdit *authorEdit = new QLineEdit();
    authorEdit->setReadOnly(true);
    QComboBox *genreCombo = new QComboBox();
    genreCombo->addItems({"Science", "Roman", "Philosophie", "Politique", "Sociale"});
    QTextEdit *descEdit = new QTextEdit();
    descEdit->setMinimumHeight(60);
    descEdit->setFont(QFont("Segoe UI", 15));
    QSpinBox *quantitySpin = new QSpinBox();
    quantitySpin->setMinimum(1);
    quantitySpin->setMaximum(1000);
    QLineEdit *publisherEdit = new QLineEdit();
    QDoubleSpinBox *priceSpin = new QDoubleSpinBox();
    priceSpin->setPrefix("€ ");
    priceSpin->setMaximum(9999.99);
    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);

    // Auteur avec bouton
    QHBoxLayout *authorLayout = new QHBoxLayout();
    authorLayout->addWidget(authorEdit, 1);
    QPushButton *chooseAuthorBtn = new QPushButton("Sélectionner");
    chooseAuthorBtn->setStyleSheet("background: #4a6fa5; border-radius: 8px; color: white; font-size: 15px; font-weight: 600; border: none; padding: 8px 20px;");
    authorLayout->addWidget(chooseAuthorBtn);

    // Genre avec bouton
    QHBoxLayout *genreLayout = new QHBoxLayout();
    genreLayout->addWidget(genreCombo, 1);
    QPushButton *chooseGenreBtn = new QPushButton("Choisir");
    chooseGenreBtn->setStyleSheet("background: #4a6fa5; border-radius: 8px; color: white; font-size: 15px; font-weight: 600; border: none; padding: 8px 20px;");
    genreLayout->addWidget(chooseGenreBtn);

    // Ajout des champs
    createField("ISBN", isbnEdit);
    createField("Titre du Livre", nameEdit);

    // Auteur (label + champ + bouton)
    {
        QFrame *container = new QFrame;
        container->setObjectName("fieldContainer");
        container->setStyleSheet(fieldStyle);
        QVBoxLayout *fieldLayout = new QVBoxLayout(container);
        fieldLayout->setContentsMargins(10, 8, 10, 8);
        fieldLayout->setSpacing(2);
        QLabel *labelWidget = new QLabel("Auteur", container);
        labelWidget->setObjectName("fieldLabel");
        fieldLayout->addWidget(labelWidget);
        fieldLayout->addLayout(authorLayout);
        formLayout->addWidget(container);
    }
    // Genre (label + champ + bouton)
    {
        QFrame *container = new QFrame;
        container->setObjectName("fieldContainer");
        container->setStyleSheet(fieldStyle);
        QVBoxLayout *fieldLayout = new QVBoxLayout(container);
        fieldLayout->setContentsMargins(10, 8, 10, 8);
        fieldLayout->setSpacing(2);
        QLabel *labelWidget = new QLabel("Genre", container);
        labelWidget->setObjectName("fieldLabel");
        fieldLayout->addWidget(labelWidget);
        fieldLayout->addLayout(genreLayout);
        formLayout->addWidget(container);
    }
    createField("Description", descEdit);
    createField("Quantité disponible", quantitySpin);
    createField("Éditeur", publisherEdit);
    createField("Prix (€)", priceSpin);
    createField("Date de publication", dateEdit);

    // Boutons d'action
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    QPushButton *cancelBtn = new QPushButton("Annuler");
    cancelBtn->setStyleSheet("background: transparent; border: 1.5px solid #cbd5e0; border-radius: 8px; color: #4a5568; font-weight: 600; font-size: 16px; padding: 10px 28px;");
    QPushButton *addBtn = new QPushButton("Ajouter le Livre");
    addBtn->setStyleSheet("background: #4a6fa5; border-radius: 8px; color: white; font-weight: 700; font-size: 16px; border: none; padding: 10px 36px;");
    btnLayout->addWidget(cancelBtn);
    btnLayout->addWidget(addBtn);
    formLayout->addLayout(btnLayout);

    // Connexions
    connect(backBtn, &QPushButton::clicked, this, &addBook::reject);
    connect(cancelBtn, &QPushButton::clicked, this, &addBook::reject);
    connect(addBtn, &QPushButton::clicked, [=](){
        // Ici, tu fais la validation et l'insertion SQL
        QString ISBN = isbnEdit->text();
        QString name = nameEdit->text();
        QString author = authorEdit->text();
        QString genre = genreCombo->currentText();
        QString description = descEdit->toPlainText();
        int quantity = quantitySpin->value();
        QString publisher = publisherEdit->text();
        double price = priceSpin->value();
        QDate date = dateEdit->date();

        if (ISBN.isEmpty() || name.isEmpty() || author.isEmpty() || genre.isEmpty() || publisher.isEmpty()) {
            QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs obligatoires.");
            return;
        }
        // ... Ajoute ici l'insertion SQL ...
        QMessageBox::information(this, "Succès", "Livre ajouté !");
        this->accept();
    });
    connect(chooseAuthorBtn, &QPushButton::clicked, [=](){
        authorsList authors;
        authors.exec();
        authorEdit->setText(authors.author);
    });
    connect(chooseGenreBtn, &QPushButton::clicked, [=](){
        genreList genre;
        genre.exec();
        genreCombo->addItem(genre.genre);
        genreCombo->setCurrentText(genre.genre);
    });
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
