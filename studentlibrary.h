#ifndef STUDENTLIBRARY_H
#define STUDENTLIBRARY_H
//#include <cart.h>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QWidget>
#include<QTableView>
#include <qlabel.h>
QT_BEGIN_NAMESPACE
namespace Ui { class studentLibrary; }
QT_END_NAMESPACE

class studentLibrary : public QDialog
{
    Q_OBJECT

public:
    explicit studentLibrary(QWidget *parent = nullptr, QSqlDatabase db = QSqlDatabase(), int userId = -1);

    ~studentLibrary();
  void setStats(int borrowed, int reserved, QString nextReturnDate);
    void checkAndCreateLocalisationColumn();
  void updateBookLocalisation(int bookId, const QString& localisation);
    QPoint getCoordonnées(const QString& localisation);
  private:
  // Fonctions de style
  QString getGroupBoxStyle();
  QString getLineEditStyle();
  QString getMainButtonStyle();
  QString getTableViewStyle();
  QString getDetailTextStyle();
  QString getActionButtonStyle();
  QString getNavButtonStyle();
private slots:
    void on_searchButton_clicked();
    void on_bookListView_clicked(const QModelIndex &index);
    void on_addToCartButton_clicked();
    void showCart();
    void on_backButton_clicked();
    void on_btnHistorique_clicked();
    void on_voirMonPanierButton_clicked();
    void on_btnCart_clicked();
    void afficherCarteLivre();
    void removeBookFromCart(int rowIndex);
    void on_btnLocalisation_clicked();
    void on_borrowButton_clicked();
private:
    void showBookDetails(int bookId);
    QTableView *cartTableView;
    Ui::studentLibrary *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    int currentBookId;
    int getUserId();
    QLabel *welcomeLabel;

public:
    void setCurrentUserId(int id);

private:
    int userId;

};

#endif // STUDENTLIBRARY_H
