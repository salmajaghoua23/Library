#include "deletebook.h"
#include "ui_deletebook.h"
#include "digitalLibrary.h"
#include "addBook.h"
#include <QtDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "deletebook.h"
#include "ui_deletebook.h"
#include "digitalLibrary.h"
#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>

deleteBook::deleteBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteBook)
{
    ui->setupUi(this);
    this->setWindowTitle("✨ Supprimer un livre");

    // Applique le style général pastel/violet à tous les composants du .ui
    this->setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #fbeffb, stop:1 #a18cd1);
        }
        QTableWidget {
            background: #fbeffb;
            border-radius: 16px;
            font-size: 16px;
            color: #7c3aed;
            border: 2px solid #a18cd1;
        }
        QHeaderView::section {
            background: #a18cd1;
            color: #fff;
            font-weight: bold;
            font-size: 16px;
            border: none;
        }
        QTableWidget::item:selected {
            background: #a18cd1;
            color: #fff;
        }
        QTableWidget::item:hover {
            background: #e1bee7;
            color: #4a148c;
        }
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #fbc2eb, stop:1 #a18cd1);
            color: #fff;
            border-radius: 15px;
            font-size: 16px;
            font-weight: bold;
            padding: 10px 24px;
            margin: 10px 0;
        }
        QPushButton:hover {
            background: #ede7f6;
            color: #a21caf;
        }
    )");

    // Ajoute un bouton de retour moderne en haut à gauche
    QPushButton *btnRetour = new QPushButton("← Retour", this);
    btnRetour->setStyleSheet(
        "QPushButton { background: transparent; color: #a18cd1; font-size: 18px; font-weight: bold; border: none; padding: 6px 18px; border-radius: 10px; min-width: 90px; }"
        "QPushButton:hover { background: #ede7f6; color: #7c3aed; }"
        );
    btnRetour->setCursor(Qt::PointingHandCursor);

    // Place le bouton dans le layout principal (au-dessus)
    if (QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(this->layout())) {
        mainLayout->insertWidget(0, btnRetour, 0, Qt::AlignLeft | Qt::AlignTop);
    } else {
        this->layout()->addWidget(btnRetour);
    }
    connect(btnRetour, &QPushButton::clicked, this, &deleteBook::close);
}

deleteBook::~deleteBook()
{
    delete ui;
}
void deleteBook::on_deleteBookBtn_clicked()
{

    //Get The ID
    QString ID = ui->ID->text();

    //call the mail Database
    digitalLibrary lib;
    auto db = lib.db;

    //check if the member exists
    auto searchQuery = QSqlQuery(db);
    QString search{"SELECT * FROM books WHERE ID = '%1'"};
    if(!searchQuery.exec(search.arg(ID)))
        qDebug() << "cannot search in members";
    int count = 0;
    while(searchQuery.next())
        count++;

    if(!ID.isEmpty())
    {
        if(count == 1)
        {
            //define the query on the db
            auto query = QSqlQuery(db);
            QString del{"DELETE FROM books WHERE ID= '%1'"};

            //execute the query
            if(!query.exec(del.arg(ID)))
                qDebug() << "Cannot delete book";
            else
            {
                QMessageBox::information(this, "SUCCESS", "Book deleted successfully");
            }
        }
        else
        {
            QMessageBox::warning(this, "Failed", "Book not found");
            ui->ID->clear();
        }
    }
    else
        QMessageBox::warning(this, "Failed", "Insert ID");


}

