#include "editBook.h"
#include "ui_editBook.h"
#include "genreList.h"
#include "addBook.h"
#include "authorsList.h"
#include "digitalLibrary.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include <QFileInfo>
#include "editBook.h"
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>

editBook::editBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editBook)
{
    ui->setupUi(this);

    // 1. Liste des widgets à conserver
    QWidget* widgetsToKeep[] = {
        ui->ISBN, ui->name, ui->author, /* liste complète */
    };

    // 2. Désactiver le style pour tous les widgets
    for (QObject *child : this->children()) {
        if (QWidget *widget = qobject_cast<QWidget*>(child)) {
            bool keep = false;
            for (QWidget* toKeep : widgetsToKeep) {
                if (widget == toKeep) {
                    keep = true;
                    break;
                }
            }
            if (!keep) {
                widget->deleteLater(); // Supprime les widgets non désirés
            } else {
                widget->setStyleSheet(""); // Réinitialise le style
                widget->setAttribute(Qt::WA_StyledBackground, false);
            }
        }
    }
    // 1. Suppression complète du style existant
    this->setStyleSheet(" ");
    for (QObject *child : this->children()) {
        if (QWidget *widget = qobject_cast<QWidget*>(child)) {
            widget->setStyleSheet("");
            widget->setAttribute(Qt::WA_StyledBackground, false);
        }
    }

    // 2. Configuration de base
    this->setWindowTitle("Éditer Livre • Bibliothèque Digitale");
    this->setFixedSize(1000, 900);
    this->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f5f0ff, stop:1 #eef2ff);");

    // 3. Conteneur principal avec ombre
    QFrame *mainContainer = new QFrame(this);
    mainContainer->setGeometry(25, 25, 950, 750);
    mainContainer->setStyleSheet(
        "background: white;"
        "border-radius: 20px;"
        );

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(mainContainer);
    shadow->setBlurRadius(30);
    shadow->setOffset(0, 5);
    shadow->setColor(QColor(106, 90, 205, 80));
    mainContainer->setGraphicsEffect(shadow);

    // 4. Header avec dégradé
    QFrame *header = new QFrame(mainContainer);
    header->setGeometry(0, 0, 950, 100);
    header->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #6a5acd, stop:1 #9575cd);"
        "border-top-left-radius: 20px;"
        "border-top-right-radius: 20px;"
        );

    // 5. Titre et boutons d'action
    QLabel *title = new QLabel("Éditer un Livre", header);
    title->setGeometry(80, 20, 790, 60);
    title->setStyleSheet(
        "color: white;"
        "font-family: 'Segoe UI';"
        "font-size: 28px;"
        "font-weight: bold;"
        );

    QPushButton *backBtn = new QPushButton(header);
    backBtn->setGeometry(20, 20, 50, 50);
    backBtn->setStyleSheet(
        "QPushButton {"
        "   background: rgba(255,255,255,0.2);"
        "   border-radius: 25px;"
        "   border: none;"
        "}"
        "QPushButton:hover { background: rgba(255,255,255,0.3); }"
        );
    backBtn->setIcon(QIcon(":/edit_book.png"));
    backBtn->setIconSize(QSize(24, 24));
    connect(backBtn, &QPushButton::clicked, this, &editBook::on_cancelBtn_clicked);

    // 6. Zone de formulaire (2 colonnes)
    QFrame *formContainer = new QFrame(mainContainer);
    formContainer->setGeometry(30, 120, 890, 560);
    formContainer->setStyleSheet("background: transparent;");

    // Colonne gauche (champs éditables)
    QFrame *leftCol = new QFrame(formContainer);
    leftCol->setGeometry(0, 0, 430, 560);
    leftCol->setStyleSheet("background: transparent;");

    // Colonne droite (image + boutons)
    QFrame *rightCol = new QFrame(formContainer);
    rightCol->setGeometry(460, 0, 430, 560);
    rightCol->setStyleSheet("background: transparent;");

    // 7. Style des champs de formulaire
    QString fieldStyle = R"(
        QFrame#fieldGroup {
            background: transparent;
            border-radius: 10px;
        }
        QLabel#fieldLabel {
            color: #5e4d9b;
            font-family: 'Segoe UI';
            font-size: 14px;
            font-weight: bold;
            margin-bottom: 5px;
        }
        QLineEdit, QComboBox, QTextEdit, QDateEdit, QSpinBox {
            border: 2px solid #d1c4e9;
            border-radius: 8px;
            padding: 10px 15px;
            font-size: 14px;
            background: #fafaff;
            min-width: 300px;
        }
        QLineEdit:focus, QTextEdit:focus {
            border: 2px solid #7e57c2;
            background: white;
        }
    )";

    // 8. Réorganisation des champs existants
    struct FieldConfig {
        QWidget* widget;
        QString label;
        int yPos;
    };

    QVector<FieldConfig> leftFields = {
        {ui->ISBN, "ISBN", 0},
        {ui->name, "Titre du Livre", 80},
        {createAuthorField(leftCol), "Auteur", 160},
        {createGenreField(leftCol), "Genre", 240},
        {ui->quantity, "Quantité", 320},
        {ui->publisher, "Éditeur", 400},
        {ui->price, "Prix", 480}
    };

    for (const FieldConfig &field : leftFields) {
        QFrame *group = new QFrame(leftCol);
        group->setObjectName("fieldGroup");
        group->setGeometry(0, field.yPos, 430, 70);
        group->setStyleSheet(fieldStyle);

        QLabel *label = new QLabel(field.label, group);
        label->setObjectName("fieldLabel");
        label->setGeometry(0, 0, 400, 20);

        field.widget->setParent(group);
        field.widget->setGeometry(0, 30, 400, 40);
    }

    // 9. Zone d'image et boutons
    ui->coverLabel->setParent(rightCol);
    ui->coverLabel->setGeometry(0, 0, 430, 300);
    ui->coverLabel->setStyleSheet(
        "border: 2px dashed #b39ddb;"
        "border-radius: 10px;"
        "background: #f5f0ff;"
        );

    ui->selectImgBtn->setParent(rightCol);
    ui->selectImgBtn->setGeometry(0, 310, 200, 40);
    ui->selectImgBtn->setStyleSheet(
        "QPushButton {"
        "   background: #7e57c2;"
        "   color: white;"
        "   border-radius: 8px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover { background: #9575cd; }"
        );

    ui->searchBtn->setParent(rightCol);
    ui->searchBtn->setGeometry(230, 310, 200, 40);
    ui->searchBtn->setStyleSheet(
        "QPushButton {"
        "   background: #6a5acd;"
        "   color: white;"
        "   border-radius: 8px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover { background: #7e57c2; }"
        );

    // 10. Boutons d'action en bas
    QFrame *buttonBar = new QFrame(mainContainer);
    buttonBar->setGeometry(30, 700, 890, 60);
    buttonBar->setStyleSheet("background: transparent;");

    ui->editBookBtn->setParent(buttonBar);
    ui->editBookBtn->setGeometry(590, 10, 300, 40);
    ui->editBookBtn->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #6a5acd, stop:1 #9575cd);"
        "   color: white;"
        "   border-radius: 8px;"
        "   font-weight: bold;"
        "   font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #7e57c2, stop:1 #a188d6);"
        "}"
        );

    ui->cancelBtn->setParent(buttonBar);
    ui->cancelBtn->setGeometry(280, 10, 300, 40);
    ui->cancelBtn->setStyleSheet(
        "QPushButton {"
        "   background: transparent;"
        "   color: #6a5acd;"
        "   border-radius: 8px;"
        "   border: 2px solid #6a5acd;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background: rgba(106, 90, 205, 0.1);"
        "}"
        );

    // 11. Initialisation
    ui->date->setDate(QDate::currentDate());
    setValidator();
}

// Fonctions helpers pour créer des champs complexes
QWidget* editBook::createAuthorField(QWidget *parent) {
    QWidget *container = new QWidget(parent);
    container->setGeometry(0, 0, 400, 40);

    ui->author->setParent(container);
    ui->author->setGeometry(0, 0, 300, 40);

    ui->changeAuthorBtn->setParent(container);
    ui->changeAuthorBtn->setGeometry(310, 0, 80, 40);
    ui->changeAuthorBtn->setStyleSheet(
        "QPushButton {"
        "   background: #b39ddb;"
        "   color: white;"
        "   border-radius: 8px;"
        "}"
        "QPushButton:hover { background: #c5aae2; }"
        );

    return container;
}

QWidget* editBook::createGenreField(QWidget *parent) {
    QWidget *container = new QWidget(parent);
    container->setGeometry(0, 0, 400, 40);

    ui->genre->setParent(container);
    ui->genre->setGeometry(0, 0, 300, 40);

    ui->changeGenreBtn->setParent(container);
    ui->changeGenreBtn->setGeometry(310, 0, 80, 40);
    ui->changeGenreBtn->setStyleSheet(
        "QPushButton {"
        "   background: #b39ddb;"
        "   color: white;"
        "   border-radius: 8px;"
        "}"
        "QPushButton:hover { background: #c5aae2; }"
        );

    return container;
}
editBook::~editBook()
{
    delete ui;
}

void editBook::on_cancelBtn_clicked()
{
    this->hide();
}

void editBook::on_selectImgBtn_clicked()
{
    coverFilename = QFileDialog::getOpenFileName();
    ui->coverLabel->setPixmap(coverFilename);
    clicked = true;
}

void editBook::on_editBookBtn_clicked()
{
    //get the content of the Line edit
    QString ISBN = ui->ISBN->text();
    QString name = ui->name->text();
    QString author = ui->author->text() ;
    QString genre = ui->genre->currentText();
    QString quantity = ui->quantity->text();
    QString publisher = ui->publisher->text();
    QString price = ui->price->text();
    QString date = ui->date->text();
    QString description = ui->description->toPlainText();

    //test if the fields are not empty
    QStringList bookInfo {ISBN, name, author, genre, quantity, publisher, price, date};
    bool full = true;
    for(int i=0; i<bookInfo.length(); i++)
    {
        if(bookInfo[i].isEmpty())
        {
            full = false;
            break;
        }
    }

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(full)
    {
        if(clicked)
        {
            QString coverPath = coverFilename;
            //Define the query
            auto query = QSqlQuery(db);
            QString searchISBN = {"UPDATE books SET name = '"+name+"',"
                                "author = '"+author+"', genre = '"+genre+"',"
                                "quantity = '"+quantity+"', publisher = '"+publisher+"',"
                                "price = '"+price+"', date = '"+date+"', description = '"+description+"',"
                                "cover = '"+coverPath+"' WHERE ISBN = '"+ISBN+"'"};
            if(!query.exec(searchISBN))
                qDebug() << "Cannot search ISBN";
            else
                QMessageBox::information(this,"SUCCESS", "Book updated successfully");
        }
        else
        {
            //Define the query
            auto query = QSqlQuery(db);
            QString searchISBN = {"UPDATE books SET name = '"+name+"',"
                                "author = '"+author+"', genre = '"+genre+"',"
                                "quantity = '"+quantity+"', publisher = '"+publisher+"',"
                                "price = '"+price+"', date = '"+date+"', description = '"+description+"'"
                                "WHERE ISBN = '"+ISBN+"'"};
            if(!query.exec(searchISBN))
                qDebug() << "Cannot search ISBN";
            else
                QMessageBox::information(this,"SUCCESS", "Book updated successfully");
        }
    }
    else
        QMessageBox::warning(this,"Failed", "Fields are empty");
}

void editBook::on_searchBtn_clicked()
{
    //get the content of the Line edit
    QString ISBN = ui->ISBN->text();
    QString name;
    QString author;
    QString genre;
    QString quantity;
    QString publisher;
    QString price;
    QString date;
    QString description;
    QString coverPath;

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    if(!ISBN.isEmpty())
    {
        //Define the query
        auto query = QSqlQuery(db);
        QString searchISBN = {"SELECT * FROM books WHERE ISBN = '%1'"};

        //execute the query
        if(!query.exec(searchISBN.arg(ISBN)))
            qDebug() << "Cannot select from books";

        //check if the book is found
        while(query.next())
            count++;

        if(count != 1)
        {
            QMessageBox::warning(this, "Not Found", "Book not Found");
            ui->ISBN->clear();
        }
        else
        {
            //Retrieve the fields identified by ID
            if(query.first())
            {
                name = query.value(2).toString();
                author = query.value(3).toString();
                genre = query.value(4).toString();
                quantity = query.value(5).toString();
                publisher = query.value(6).toString();
                price = query.value(7).toString();
                date = query.value(8).toString();
                description = query.value(9).toString();
                coverPath = query.value(10).toString();
            }
        }

        //Convert to QDate
        QStringList dateList = date.split("/");
        QDate Date;
        if(dateList.length() == 3)
            Date = QDate(dateList[2].toInt(), dateList[1].toInt(), dateList[0].toInt());

        //Show the fields in the corresponding line Edit
        ui->name->setText(name);
        ui->author->setText(author);
        ui->genre->setCurrentText(genre);
        ui->quantity->setValue(quantity.toInt());
        ui->publisher->setText(publisher);
        ui->price->setText(price);
        ui->date->setDate(Date);
        ui->description->setText(description);
        if(QFileInfo::exists(coverPath))
            ui->coverLabel->setPixmap(coverPath);
        else
            ui->coverLabel->setText("Book cover not found");
    }
    else
        QMessageBox::warning(this, "ISBN", "Insert ISBN");

}

void editBook::on_changeAuthorBtn_clicked()
{
    authorsList authors;
    authors.exec();
    ui->author->setText(authors.author);
}

void editBook::setValidator(){


    //ISBN Validator
    QRegularExpression ISBN ("[0-9]*[-| ][0-9]*[-| ][0-9]*[-| ][0-9]*[-| ][0-9]*");
   QRegularExpressionValidator *ISBNVal = new QRegularExpressionValidator(ISBN, this);
    ui->ISBN->setValidator(ISBNVal);

    //regx for name
    QRegularExpression Name("^[A-Za-z]{7,29}$");
    QRegularExpressionValidator *valName = new QRegularExpressionValidator(Name, this);
    ui->name->setValidator(valName);
    ui->publisher->setValidator(valName);

    //setValidator for price
    //regx for name
    QRegularExpression price("^\\d{0,8}(\\.\\d{1,4})?$");
    QRegularExpressionValidator *valPrice = new QRegularExpressionValidator(price, this);
    ui->price->setValidator(valPrice);
}

void editBook::on_changeGenreBtn_clicked()
{
    genreList genre;
    genre.exec();
    ui->genre->addItem(genre.genre);
}

