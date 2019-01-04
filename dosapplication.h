#ifndef DOSAPPLICATION_H
#define DOSAPPLICATION_H
#include <QString>
#include <QStringList>


class DOSApplication {
public:
    DOSApplication();
    DOSApplication(QString title, int year, QString developer, QString publisher, QStringList genres, QString manual, QString boxart, QStringList themes, QString conf, QString extras);
    QString title = "Application title";
    int year = 0;
    QString developer = "Application developer";
    QString publisher = "Application publisher";
    QStringList genres = {"Application", "genres"};
    QString manual = "";
    QString boxart = "";
    QString captures = "";
    QStringList themes = {"Application", "themes"};
    QString conf = "/home/pi/DOS Games/default.conf";
    int playtime= 0;
    bool completed = false;
    QString extras = "";

    QString gettime() const;
    QString getGenres() const;
    QString getThemes() const;
    void updateplaytime(int time);
    bool hasTheme(QString theme) const;
    bool hasGenre(QString genre) const;
};

#endif // DOSAPPLICATION_H
