#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QVBoxLayout>
#include <QDialog>
#include <QTableWidget>
#include <QLabel>
#include <QVector>
#include <QStringList>

class Historique : public QDialog
{
    Q_OBJECT

public:
    explicit Historique(QWidget *parent = nullptr);
    ~Historique();

private:
    QLabel *labelConnexions;
    QTableWidget *tableReservations;
    QTableWidget *tableActions;  // Table pour les actions (emprunts, retours, suppressions)
    void appliquerAnimation(QWidget *widget);
    void chargerConnexions();
    void chargerReservations();
    void chargerActions();  // Méthode pour charger les actions (emprunts, retours, suppressions)
public:
    QVBoxLayout *connexionsLayout;

};

#endif // HISTORIQUE_H
