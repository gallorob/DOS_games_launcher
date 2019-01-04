#include <globalvars.h>
#include <QString>
#include <QDir>

QDir dir = QDir::current();

QString dblocation = dir.relativeFilePath("./dosgames.db");
QString gamedatalocation = dir.relativeFilePath("./list.dat");
QString iconlocation = dir.relativeFilePath("./dosgamesicon.ico");

QStringList genres = QStringList();
QStringList themes = QStringList();
