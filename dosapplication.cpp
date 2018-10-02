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
    completed = parsed.at(9);
    extras = parsed.at(10);
}
