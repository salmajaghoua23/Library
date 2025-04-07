#include "pagestudent.h"
#include "ui_pagestudent.h"
#include "cart.h"
Cart userCart;
Pagestudent::Pagestudent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Pagestudent)
{
    ui->setupUi(this);
}

Pagestudent::~Pagestudent()
{
    delete ui;
}

void Pagestudent::on_bookListView_clicked(const QModelIndex &index)
{
    int bookId = model->data(model->index(index.row(), 0)).toInt();
    currentBookId = bookId; // Ajoute un attribut dans ton .h

    showBookDetails(bookId);

    // Afficher les boutons
    ui->addToCartButton->setVisible(true);
    ui->borrowButton->setVisible(true);
}
