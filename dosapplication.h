#ifndef DOSAPPLICATION_H
#define DOSAPPLICATION_H
#include <QString>


class DOSApplication {
public:
    DOSApplication();
    DOSApplication(QString title, int year, QString developer, QString publisher, QString genre, QString manual, QString boxart, QString conf, QString extras);
    DOSApplication(QString line);
    QString title = "Application title";
    int year = 0;
    QString developer = "Application developer";
    QString publisher = "Application publisher";
    QString genre = "Application genre"; //todo: change to qstringlist
    QString manual;
    QString boxart;
    QString conf = "/home/pi/DOS Games/default.conf";
    int playtime= 0;
    bool completed;
    QString extras = "";

    QString gettime() const;
    void updateplaytime(int time);
    QString printable();
};

#endif // DOSAPPLICATION_H
