#include "dbmanager.h"

#include <QDebug>
#include <QSqlQuery>

DBManager::DBManager(const QString &dbpath) {
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(dbpath);

    if(!this->db.open()) {
        qDebug() << "Error in opening database file!";
    } else {
        qDebug() << "Database file opened ok.";
    }
}

DBManager::~DBManager() {
    this->db.close();
}

QVector<DOSApplication> DBManager::getDOSApplications() {
    QVector<DOSApplication> toReturn;

    QSqlQuery query;
    query.prepare("SELECT * FROM `games`;");

    if (query.exec()) {
       while (query.next()) {
          QString title = query.value("title").toString();
          int year = query.value("year").toInt();
          QString developer = query.value("developer").toString();
          QString publisher = query.value("publisher").toString();
          QString manual = query.value("manual").toString();
          QString boxart = query.value("boxart").toString();
          QString configfile = query.value("configfile").toString();
          int playtime = query.value("playtime").toInt();
          bool completed = query.value("completed").toBool();
          QString extras = query.value("extras").toString();

          QStringList themes = this->getGameThemes(title);
          QStringList genres = this->getGameGenres(title);

          DOSApplication game = DOSApplication(title,
                                               year,
                                               developer,
                                               publisher,
                                               genres,
                                               manual,
                                               boxart,
                                               themes,
                                               configfile,
                                               extras);
          game.updateplaytime(playtime);
          game.completed = completed;

          toReturn.push_back(game);
       }
    }

    return toReturn;
}

QStringList DBManager::getGameGenres(QString &gametitle) {
    QStringList genres = QStringList();

    QSqlQuery query;
    query.prepare("SELECT `genre` FROM `game_genres` WHERE `game` = (:game);");
    query.bindValue(":game", gametitle);

    if (query.exec()) {
       while (query.next()) {
           genres.append(query.value("genre").toString());
       }
    }

    return genres;
}

QStringList DBManager::getGameThemes(QString &gametitle) {
    QStringList themes = QStringList();

    QSqlQuery query;
    query.prepare("SELECT `theme` FROM `game_themes` WHERE `game` = (:game);");
    query.bindValue(":game", gametitle);

    if (query.exec()) {
       while (query.next()) {
           themes.append(query.value("theme").toString());
       }
    }

    return themes;
}

QStringList DBManager::getGenres() {
    QStringList genres = QStringList();

    QSqlQuery query;
    query.prepare("SELECT `name` FROM `genres`;");

    if (query.exec()) {
       while (query.next()) {
           genres.append(query.value("name").toString());
       }
    }

    return genres;
}

QStringList DBManager::getThemes() {
    QStringList themes = QStringList();

    QSqlQuery query;
    query.prepare("SELECT `name` FROM `themes`;");

    if (query.exec()) {
       while (query.next()) {
           themes.append(query.value("name").toString());
       }
    }

    return themes;
}

bool DBManager::addDOSApplication(DOSApplication &game) {
    // add to games table
    QSqlQuery query;
    query.prepare("REPLACE INTO `games` VALUES (:title, :year, :developer, :publisher, :manual, :boxart, :configfile, :playtime, :completed, :extras);");
    query.bindValue(":title", game.title);
    query.bindValue(":year", game.year);
    query.bindValue(":developer", game.developer);
    query.bindValue(":publisher", game.publisher);
    query.bindValue(":manual", game.manual);
    query.bindValue(":boxart", game.boxart);
    query.bindValue(":configfile", game.conf);
    query.bindValue(":playtime", game.playtime);
    query.bindValue(":completed", game.completed);
    query.bindValue(":extras", game.extras);

    if(!query.exec()) return false;

    // add game's genres
    if(!addGameGenres(game.title, game.genres)) return false;
    // add game's themes
    if(!addGameThemes(game.title, game.themes)) return false;

    return true;
}

bool DBManager::addGameGenres(QString &gametitle, QStringList &gamegenres) {
    // add game genres if they don't exist already
    for(QString genre : gamegenres) {
        QSqlQuery query;
        query.prepare("REPLACE INTO `genres` VALUES (:genre);");
        query.bindValue(":genre", genre);
        if(!query.exec()) return false;
    }
    // add tuple (game, genre) in game_genres
    for(QString genre : gamegenres) {
        QSqlQuery query;
        query.prepare("REPLACE INTO `game_genres` VALUES (:game, :genre);");
        query.bindValue(":game", gametitle);
        query.bindValue(":genre", genre);
        if(!query.exec()) return false;
    }
    return true;
}

bool DBManager::addGameThemes(QString &gametitle, QStringList &gamethemes) {
    // add game themes if they don't exist already
    for(QString theme : gamethemes) {
        QSqlQuery query;
        query.prepare("REPLACE INTO `themes` VALUES (:theme);");
        query.bindValue(":theme", theme);
        if(!query.exec()) return false;
    }
    // add tuple (game, theme) in game_themess
    for(QString theme : gamethemes) {
        QSqlQuery query;
        query.prepare("REPLACE INTO `game_themes` VALUES (:game, :theme);");
        query.bindValue(":game", gametitle);
        query.bindValue(":theme", theme);
        if(!query.exec()) return false;
    }
    return true;
}

void DBManager::updateGamePlayTime(QString &title, int &playtime) {
    QSqlQuery query;
    query.prepare("UPDATE `games` SET `playtime` = :playtime WHERE `title` = :title;");
    query.bindValue(":playtime", playtime);
    query.bindValue(":title", title);
    query.exec();
}

bool DBManager::remDosApplication(DOSApplication &game) {
    QSqlQuery query;
    query.prepare("DELETE FROM `games` WHERE `title` = :title;");
    query.bindValue(":title", game.title);
    if(!query.exec()) return false;

    if(!remGameGenres(game.title, game.genres)) return false;
    if(!remGameThemes(game.title, game.themes)) return false;

    return true;
}

bool DBManager::remGameGenres(QString &gametitle, QStringList &gamegenres) {
    // remove tuples from game_genres
    QSqlQuery query;
    query.prepare("DELETE FROM `game_genres` WHERE `game` = :title;");
    query.bindValue(":title", gametitle);
    if(!query.exec()) return false;
    // search if there are still games with same genre
    for (QString genre : gamegenres) {
        query.prepare("SELECT COUNT(`game`) FROM `game_genres` WHERE `genre` = :genre;");
        query.bindValue(":genre", genre);
        if (query.exec()) {
            if (query.next()) {
                if (query.value(0).toInt() == 0) {
                    // remove genre from genres
                    query.prepare("DELETE FROM `genres` WHERE `name` = :genre;");
                    query.bindValue(":genre", genre);
                    if(!query.exec()) return false;

                }
            }
        }
    }

    return true;
}

bool DBManager::remGameThemes(QString &gametitle, QStringList &gamethemes) {
    // remove tuples from game_themes
    QSqlQuery query;
    query.prepare("DELETE FROM `game_themes` WHERE `game` = :title;");
    query.bindValue(":title", gametitle);
    if(!query.exec()) return false;
    // search if there are still games with same genre
    for (QString theme : gamethemes) {
        query.prepare("SELECT COUNT(`game`) FROM `game_themes` WHERE `theme` = :theme;");
        query.bindValue(":theme", theme);
        if (query.exec()) {
            if (query.next()) {
                if (query.value(0).toInt() == 0) {
                    // remove theme from themes
                    query.prepare("DELETE FROM `themes` WHERE `name` = :theme;");
                    query.bindValue(":theme", theme);
                    if(!query.exec()) return false;
                }
            }
        }
    }

    return true;
}
