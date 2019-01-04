#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QVector>
#include <QSqlDatabase>

#include "dosapplication.h"

class DBManager {
public:
    DBManager(const QString &dbpath);
    ~DBManager();

    QVector<DOSApplication> getDOSApplications();
    QStringList getGenres();
    QStringList getThemes();

    bool addDOSApplication(DOSApplication &game);
    void updateGamePlayTime(QString &title, int &playtime);

    bool remDosApplication(DOSApplication &game);

private:
    QStringList getGameGenres(QString &gametitle);
    QStringList getGameThemes(QString &gametitle);

    bool addGameGenres(QString &gametitle, QStringList &gamegenres);
    bool addGameThemes(QString &gametitle, QStringList &gamethemes);

    bool remGameGenres(QString &gametitle, QStringList &gamegenres);
    bool remGameThemes(QString &gametitle, QStringList &gamethemes);

    QSqlDatabase db;
};

#endif // DBMANAGER_H
