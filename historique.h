#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QSqlDatabase>
#include <QDialog>
#include <QTableWidget>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QGroupBox>
#include <QScrollArea>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
//QT_CHARTS_USE_NAMESPACE

class Historique : public QDialog
{
    Q_OBJECT

public:
    // Ajoutez un paramètre pour l'ID utilisateur
    explicit Historique(int userId,QSqlDatabase db, QWidget *parent = nullptr);
    // Méthode statique pour enregistrer les connexions
    static void enregistrerConnexion(int userId, QSqlDatabase db);
    // Ajoutez un membre pour stocker l'ID utilisateur
    ~Historique() override ;

    void enregistrerReservation(const QString& livre, const QString& utilisateur);
private slots:
    void retourArriere();
private:
    int currentUserId;
private:
    QPushButton *btnRetour;
private:
    QSqlDatabase db;
private:
    void setupReservationsTable();
    void chargerDonnees();
    void chargerConnexions();
    void chargerReservations();
    void chargerStatsConnexions();
    void chargerStatsReservations();
    void appliquerAnimation(QWidget *widget);
    QChartView*createEmpruntsChart();
    QChartView* createConnexionsChart();
    QChartView* createReservationsChart();
    QMap<QString, int> getConnexionsDataLast7Days();
    QMap<QString, int> getReservationsDataLast7Days();
    void initReservationFile();

    // Widgets
    QLabel *labelConnexions;
    QTableWidget *tableReservations;
    QMap<QString, int> getEmpruntsDataLast7Days();
    QMap<QString, int> getRetoursDataLast7Days();
    void chargerEmpruntsFromDB();
    void  chargerStatsEmprunts();
};

#endif // HISTORIQUE_H
