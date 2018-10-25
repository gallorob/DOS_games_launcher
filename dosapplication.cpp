#include "dosapplication.h"
#include <QStringList>

DOSApplication::DOSApplication() {}

DOSApplication::DOSApplication(QString line) {
    QStringList parsed = line.remove("\"").split(";");
    title = parsed.at(0);
    year = parsed.at(1).toInt();
    developer = parsed.at(2);
    publisher = parsed.at(3);
    genre = parsed.at(4);
    manual = parsed.at(5);
    boxart = parsed.at(6);
    conf = parsed.at(7);
    playtime = parsed.at(8).toInt();
    completed = parsed.at(9) != "0";
    extras = parsed.at(10);
}

DOSApplication::DOSApplication(QString title, int year, QString developer, QString publisher, QString genre, QString manual, QString boxart, QString conf, QString extras) {
    this->title = title;
    this->year = year;
    this->developer = developer;
    this->publisher = publisher;
    this->genre = genre;
    this->manual = manual;
    this->boxart = boxart;
    this->conf = conf;
    this->playtime = 0;
    this->completed = false;
    this->extras = extras;
}

// return play time in format h:m:s
QString DOSApplication::gettime() const {
    return QString::number(playtime/3600) + ':' + QString::number(playtime/60 % 60) +  + ':' + QString::number(playtime % 60);
}

void DOSApplication::updateplaytime(int time) {
    this->playtime += time;
}

QString DOSApplication::printable() {
    QString line = "\"" + this->title + "\";\"" +
            QString::number(this->year) + "\";\"" +
            this->developer + "\";\"" +
            this->publisher + "\";\"" +
            this->genre + "\";\"" +
            this->manual + "\";\"" +
            this->boxart + "\";\"" +
            this->conf + "\";\"" +
            QString::number(this->playtime) + "\";\"" +
            (this->completed ? "1" : "0") + "\";\"" +
            this->extras + "\"\n";
    return line;
}
