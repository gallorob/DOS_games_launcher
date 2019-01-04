#include "mainwindow.h"

#include <QApplication>
#include <dosapplication.h>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <globalvars.h>
#include <dbmanager.h>

/**
 * main program
 * @author Roberto Gallotta
 */

// reads data from csv file and returns qvector of DOSApplications
void getgamesdata(QVector<DOSApplication>& data);

int main(int argc, char *argv[]) {
    DBManager dbm(dblocation);
    QVector<DOSApplication> gamesdata = dbm.getDOSApplications();

    genres = dbm.getGenres();
    std::stable_sort(genres.begin(), genres.end());

    themes = dbm.getThemes();
    std::stable_sort(themes.begin(), themes.end());

    //getgamesdata(gamesdata);
    QApplication a(argc, argv);
    MainWindow mainwindow(gamesdata);
    mainwindow.show();

    return a.exec();
}
