#ifndef EDITBOOK_H
#define EDITBOOK_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class editBook; }
QT_END_NAMESPACE

class editBook : public QDialog
{
    Q_OBJECT

public:
    editBook(QWidget *parent = nullptr);
    ~editBook();

    // Méthodes pour créer des champs composés
    QWidget* createAuthorField(QWidget* parent);
    QWidget* createGenreField(QWidget* parent);

    QString coverFilename;
    bool clicked = false;

private slots:
    void on_cancelBtn_clicked();
    void on_selectImgBtn_clicked();
    void on_editBookBtn_clicked();
    void on_searchBtn_clicked();
    void on_changeAuthorBtn_clicked();
    void on_changeGenreBtn_clicked();

private:
    Ui::editBook *ui;

    // Méthodes pour le design amélioré
    void resetStyles();
    void applyModernDesign();
    void addVisualEffects();
    void addButtonShadow(QPushButton *button);
    void createReturnButton();
    void showSuccessMessage(const QString &message);
    void showErrorMessage(const QString &message);

    // Méthode de validation
    void setValidator();
};

#endif // EDITBOOK_H
