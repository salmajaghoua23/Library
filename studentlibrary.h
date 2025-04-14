#ifndef STUDENTLIBRARY_H
#define STUDENTLIBRARY_H
//#include <cart.h>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
namespace Ui { class studentLibrary; }
QT_END_NAMESPACE

class studentLibrary : public QDialog
{
    Q_OBJECT

public:
    explicit studentLibrary(QWidget *parent = nullptr, QSqlDatabase database = QSqlDatabase());
    ~studentLibrary();


private slots:
    void on_searchButton_clicked();
    void on_bookListView_clicked(const QModelIndex &index);
    void on_addToCartButton_clicked();
    //void showCart();
    void on_backButton_clicked();
    void on_btnHistorique_clicked();
    void on_btnVoirPanier_clicked();
    void on_btnCart_clicked();
private:
    void showBookDetails(int bookId);
   // Cart userCart;
    Ui::studentLibrary *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    int currentBookId;
    int getUserId();
};

#endif // STUDENTLIBRARY_H
