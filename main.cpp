#include "mainwindow.h"
#include <QApplication>
#include <dosapplication.h>
#include <QFile>
#include <QTextStream>
#include <globalvars.h>

/**
 * main program
 * @author Roberto Gallotta
 */

// reads data from csv file and returns qvector of DOSApplications
void getgamesdata(QVector<DOSApplication>& data);

int main(int argc, char *argv[]) {
    QVector<DOSApplication> gamesdata;
    getgamesdata(gamesdata);
    QApplication a(argc, argv);
    MainWindow w(gamesdata);
    w.show();

    return a.exec();
}

void getgamesdata(QVector<DOSApplication>& data) {
    QFile inputFile(gamedatalocation);
    if(inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while(!in.atEnd()) {
            DOSApplication temp(in.readLine());
            data.push_back(temp);
        }
        inputFile.close();
    }
}
