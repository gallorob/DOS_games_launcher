#include "mainwindow.h"
#include <addgamewindow.h>
#include <dosapplication.h>
#include "ui_mainwindow.h"
#include <globalvars.h>
#include <QPixmap>
#include <QStringList>
#include <QTextStream>
#include <QFile>
#include <QModelIndex>
#include <QMessageBox>
#include <QStyle>
#include <QDesktopWidget>

QVector<DOSApplication> games;

MainWindow::MainWindow(QVector<DOSApplication>& gamesdata, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setFixedSize(QSize(800,400));
    this->setWindowIcon(QIcon(iconlocation));
    // start it centered
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), QApplication::desktop()->availableGeometry()));

    games = gamesdata;

    // add games' title to list
    for(const DOSApplication& app : games) {
        ui->games_list->addItem(app.title);
    }

    // set boxart
    ui->box_art->setScaledContents(true);

    // select first item by default
    ui->games_list->setCurrentRow(0);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_play_button_clicked() {
    // minimize window, start process and reshow window when process terminates
    MainWindow::hide();
    //todo: start a timer to track play time, then add it to game time counter
    system("dosbox"); //todo: change the way process is launched (add '-conf filepath')

    MainWindow::show();
}

void MainWindow::on_add_game_button_clicked() {
    MainWindow::hide();
    AddGameWindow addgamewindow;
    addgamewindow.exec();
    //todo: created game should be added both to data file and games' qvector
    MainWindow::show();
}

void MainWindow::on_games_list_itemSelectionChanged() {
    //updates all the labels to display selected game infos
    ui->year_label->setText("Year: " + QString::number(games.at(ui->games_list->currentIndex().row()).year));
    ui->developer_label->setText("Developer: " + games.at(ui->games_list->currentIndex().row()).developer);
    ui->publisher_label->setText("Publisher: " + games.at(ui->games_list->currentIndex().row()).publisher);
    ui->genre_label->setText("Genre: " + games.at(ui->games_list->currentIndex().row()).genre); //todo: will be changed to qstringlist
    QPixmap pm(games.at(ui->games_list->currentIndex().row()).boxart);
    ui->box_art->setPixmap(pm);
    ui->playtime_label->setText("Play time: " + QString::number(games.at(ui->games_list->currentIndex().row()).playtime));//todo: will be changed to function call
    ui->completed_label->setText("Completed: " + games.at(ui->games_list->currentIndex().row()).completed);

    //todo: disable/enable extras and manual buttons if game allows it
}

void MainWindow::on_extras_button_clicked() {
    std::string command = "pcmanfm "; //todo: common way?
    command = command + games.at(ui->games_list->currentIndex().row()).extras.toStdString();
    system(command.c_str());
}

void MainWindow::on_defaultdos_button_clicked() {
    // minimize window, start process and reshow window when process terminates
    MainWindow::hide();
    system("dosbox");

    MainWindow::show();
}
