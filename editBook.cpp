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
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>

editBook::editBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editBook)
{
    ui->setupUi(this);

    // Style général pastel/violet moderne appliqué à tous les widgets
    this->setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #fbeffb, stop:1 #a18cd1);
        }
        QLabel {
            color: #7c3aed;
            font-size: 18px;
            font-weight: bold;
            background: transparent;
            border: none;
        }
        QLineEdit, QTextEdit, QComboBox, QDateEdit, QSpinBox {
            background: #fff;
            border: 2px solid #d291bc;
            border-radius: 10px;
            padding: 10px 16px;
            font-size: 16px;
            color: #7c3aed;
            font-weight: 600;
        }
        QLineEdit:focus, QTextEdit:focus, QComboBox:focus, QDateEdit:focus, QSpinBox:focus {
            border: 2px solid #a18cd1;
            background: #fff0f6;
            color: #a21caf;
        }
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #fbc2eb, stop:1 #a18cd1);
            color: #fff;
            border: none;
            border-radius: 15px;
            padding: 10px 24px;
            font-size: 16px;
            font-weight: bold;
            margin: 0 8px;
            min-width: 100px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #ede7f6, stop:1 #a18cd1);
            color: #7c3aed;
        }
        #coverLabel {
            border: 2px dashed #b39ddb;
            border-radius: 10px;
            background: #f5f0ff;
        }
    )");

    // Ajoute un bouton de retour en haut à gauche (emoji ←)
    QPushButton *btnRetour = new QPushButton("← Retour", this);
    btnRetour->setStyleSheet(
        "QPushButton {"
        " background: transparent;"
        " color: #a18cd1;"
        " font-size: 18px;"
        " font-weight: bold;"
        " border: none;"
        " padding: 6px 18px;"
        " border-radius: 10px;"
        " min-width: 90px;"
        "}"
        "QPushButton:hover {"
        " background: #ede7f6;"
        " color: #7c3aed;"
        "}"
        );
    btnRetour->setCursor(Qt::PointingHandCursor);

    // Place le bouton de retour dans le layout principal (vertical ou horizontal)
    if (QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(this->layout())) {
        mainLayout->insertWidget(0, btnRetour, 0, Qt::AlignLeft | Qt::AlignTop);
    } else if (QHBoxLayout *mainLayout = qobject_cast<QHBoxLayout*>(this->layout())) {
        mainLayout->insertWidget(0, btnRetour, 0, Qt::AlignLeft | Qt::AlignTop);
    } else {
        this->layout()->addWidget(btnRetour);
    }
    connect(btnRetour, &QPushButton::clicked, this, &editBook::close);

    // Initialisation
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
        int count = 0;
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
