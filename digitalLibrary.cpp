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
digitalLibrary::digitalLibrary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::digitalLibrary)
{
    ui->setupUi(this);
    connectDB();
    connect(ui->statsButton, &QPushButton::clicked, this, &digitalLibrary::on_statsButton_clicked);
    setUsername(username);
    connect(ui->statsButton, &QPushButton::clicked, this, &digitalLibrary::on_statsButton_clicked);

    showBookNum();
    showMemberNum();
    showAuthorNum();
}

void digitalLibrary::connectDB()
{
    //Add the database with the SQLITE driver
    db = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");

    //Set the database path
    db.setDatabaseName(this->filename);

    //check if the database is opened
    if(!db.open())
        QMessageBox::critical(this, "FAILED", "DB is not opened");

    //définir la requete sur la base de données
    auto query = QSqlQuery(db);

    //Create a table named accounts
    QString accountTable{"CREATE TABLE IF NOT EXISTS accounts"
                         "(username VARCHAR(20), name VARCHAR(20),"
                         "password VARCHAR(20))"};

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

    //Create a table named books
    QString bookTable{"CREATE TABLE IF NOT EXISTS books"
                      "(ID INTEGER PRIMARY KEY, ISBN VARCHAR(20), name VARCHAR(20),"
                      "author VARCHAR(20), genre VARCHAR(20), quantity INT,"
                      "publisher VARCHAR(20), price REAL, date VARCHAR(10),"
                      "description VARCHAR(80), cover VARCHAR(50))"};
    if(!query.exec(bookTable))
        QMessageBox::critical(this,"Failed","Cannot create books Table");

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



void digitalLibrary::setUsername(QString username)
{
    ui->username->setText(username);
}

void digitalLibrary::showBookNum(){

    //define the query on the db and the model
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM books"};

    //execute the query
    if(!query.exec(select))
        qDebug() << "Cannot select from books";

    int count = 0;
    while(query.next())
        count++;

    ui->bookNum->setText(QString::number(count));
}

void digitalLibrary::showMemberNum(){

    //define the query on the db and the model
    auto query = QSqlQuery(db);
    QString select{"SELECT * FROM members"};

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




