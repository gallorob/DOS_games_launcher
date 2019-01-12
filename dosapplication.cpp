#include "dosapplication.h"
#include <QStringList>

DOSApplication::DOSApplication() {}

DOSApplication::DOSApplication(QString title,
                               int year,
                               QString developer,
                               QString publisher,
                               QStringList genres,
                               QString manual,
                               QString boxart,
                               QStringList themes,
                               QString conf,
                               QString extras) {
    this->title = title;
    this->year = year;
    this->developer = developer;
    this->publisher = publisher;
    this->genres = genres;
    this->manual = manual;
    this->boxart = boxart;
    this->themes = themes;
    this->conf = conf;
    this->playtime = 0;
    this->completed = false;
    this->extras = extras;
}

QString DOSApplication::getGenres() const {
    if(this->genres.size() == 0) return "";

    QString t = "";
    for (int i = 0; i < this->genres.length() - 1; i++) {
        t.append(this->genres[i]);
        t.append(", ");
    }
    t.append(this->genres[this->genres.length() - 1]);
    return t;
}

QString DOSApplication::getThemes() const {
    if(this->themes.size() == 0) return "";

    QString t = "";
    for (int i = 0; i < this->themes.length() - 1; i++) {
        t.append(this->themes[i]);
        t.append(", ");
    }
    t.append(this->themes[this->themes.length() - 1]);
    return t;
}

// return play time in format h:m:s
QString DOSApplication::gettime() const {
    return QString::number(playtime/3600) + ':' + QString::number(playtime/60 % 60) +  + ':' + QString::number(playtime % 60);
}

void DOSApplication::updateplaytime(int time) {
    this->playtime += time;
}

bool DOSApplication::hasTheme(QString theme) const {
    for (QString t : this->themes) {
        if (theme.compare(t) == 0) return true;
    }
    return false;
}

bool DOSApplication::hasGenre(QString genre) const {
    for (QString g : this->genres) {
        if (genre.compare(g) == 0) return true;
    }
    return false;
}

bool DOSApplication::operator == (const DOSApplication &other) {
   return (strcmp(this->title.toStdString().c_str(), other.title.toStdString().c_str()) == 0);
}
