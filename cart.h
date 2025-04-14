#ifndef CART_H
#define CART_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Cart;
}

class Cart : public QDialog
{
    Q_OBJECT

public:
    explicit Cart(QWidget *parent = nullptr, QSqlDatabase db = QSqlDatabase(), int userId = -1);

    ~Cart();
   void setUserId(int id);
    void chargerPanier(); // Déclare la fonction pour charger les données du panier
   void setDatabase(const QSqlDatabase &database);
    int getUserId();
private slots:
    void on_btnRemoveSelected_clicked();
    void on_btnClearCart_clicked();
    void on_btnBorrowAll_clicked();
     void on_borrowButton_clicked();
    void on_voirMonPanierButton_clicked();
     void showCart();
     void removeBookFromCart(int rowIndex);
private:
    Ui::Cart *ui;
    QSqlDatabase db;    // Déclare un membre pour la base de données
    int userId;  // 🔹 Ajoute ceci
};

#endif // CART_H
