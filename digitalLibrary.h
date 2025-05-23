#ifndef DIGITALLIBRARY_H
#define DIGITALLIBRARY_H
#include "statistic.h"
#include"addBook.h"
#include"manageBooks.h"
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDir>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>

namespace Ui {
class digitalLibrary;
}

class digitalLibrary : public QDialog
{
    Q_OBJECT

public:
    explicit digitalLibrary(QWidget *parent = nullptr);
    ~digitalLibrary();
    QSqlDatabase db;
    void connectDB();
    void on_testDataButton_clicked();
    // void setUsername(QString username);
    void showBookNum();
    void showMemberNum();
    void showAuthorNum();
    void showCover();
public:
    void setUsername(const QString &username);  // Déclaration unique
private:
    QMap<QString, int> getBookPopularityData();
    QMap<QString, int> getQuantityByCategoryData();
    void insertTestData();
    addBook *m_addBookDialog;
    manageBooks *m_manageBooksDialog;
private slots:

    void on_manageGenre_clicked();

    void on_manageAuthorButton_clicked();

    void on_addMemberBtn_clicked();

    void on_editMemberBtn_clicked();

    void on_deleteMemberBtn_clicked();

    void on_membersListBtn_clicked();

    void on_addBookBtn_clicked();

    void on_editBookBtn_clicked();

    void on_deleteBookBtn_clicked();

    void on_booksListBtn_clicked();

    void on_issueBookBtn_clicked();

    void on_statsButton_clicked();
    void on_returnBookBtn_clicked();
private:
    QString m_username;  // Variable membre pour stocker le nom d'utilisateur
    QLabel* m_usernameLabel;  // Pointeur vers le QLabel qui affichera le nom
private slots:
    void updateStatsCards(); // Nouvelle méthode pour mettre à jour les stats
    void showAdminProfile(); // Afficher le profil admin
    void saveAdminProfile(); // Sauvegarder les modifications
private:
    QPushButton *booksBtn;
    QPushButton *membersBtn;
    QPushButton* createSubMenuButton(const QString &text);

private:
    // Pour les cartes statistiques
    QFrame *bookCard;
    QFrame *memberCard;
    QFrame *authorCard;
    QFrame *loanCard;

    // Pour le profil admin
    QDialog *m_adminProfileDialog;
    QLineEdit *m_adminUsernameEdit;
    QLineEdit *m_adminNameEdit;
    QLineEdit *m_adminPasswordEdit;

    // Labels pour les stats
    QLabel *m_bookCountLabel;
    QLabel *m_memberCountLabel;
    QLabel *m_authorCountLabel;
    QLabel *m_loanCountLabel;

private:
    Ui::digitalLibrary *ui;
    QString filename = QDir::homePath()+ "/library.db";
    QPushButton* createSidebarButton(const QString& text, const QString& style);
    QFrame* createStatCard(const QString& icon, const QString& title,
                           const QString& value, const QString& color);
    QPushButton* createQuickActionButton(const QString& text, const QString& color);
    // Widgets principaux
    QLabel *bookCountLabel;
    QLabel *memberCountLabel;
    QLabel *authorCountLabel;
    QString username;
private:
    Statistic* statWindow = nullptr;
};

#endif // DIGITALLIBRARY_H
