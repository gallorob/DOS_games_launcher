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
#include <QDesktopServices>
#include <QUrl>
#include <chrono>
#include <QMenu>

#define COMPARATOR(code) [](auto && left, auto && right) -> bool {return code;}

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

    // add games' title to list and select first item by default
    refreshGamesList();

    // set boxart
    ui->box_art->setScaledContents(true);

    // add drop down menu to order_button
    QAction *sorttitle = new QAction(tr("Title"), this);
    connect(sorttitle, SIGNAL(triggered()), this, SLOT(sort_title()));

    QAction *sortyear = new QAction(tr("Year"), this);
    connect(sortyear, SIGNAL(triggered()), this, SLOT(sort_year()));

    QAction *sortdev = new QAction(tr("Developer"), this);
    connect(sortdev, SIGNAL(triggered()), this, SLOT(sort_dev()));

    QAction *sortpub = new QAction(tr("Publisher"), this);
    connect(sortpub, SIGNAL(triggered()), this, SLOT(sort_pub()));

    QMenu* menu = new QMenu(this);
    menu->addAction(sorttitle);
    menu->addAction(sortyear);
    menu->addAction(sortdev);
    menu->addAction(sortpub);
    ui->order_button->setMenu(menu);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_play_button_clicked() {
    int playtime = (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())).count();
    // minimize window, start process and reshow window when process terminates
    MainWindow::hide();
    system("dosbox"); //todo: change the way process is launched (add '-conf filepath')

    playtime -= (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())).count();
    games[ui->games_list->currentIndex().row()].updateplaytime(-playtime);
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
    ui->genre_label->setText("Genre: " + games[ui->games_list->currentIndex().row()].genre); //todo: will be changed to qstringlist
    QPixmap pm(games.at(ui->games_list->currentIndex().row()).boxart);
    ui->box_art->setPixmap(pm);
    ui->playtime_label->setText("Play time: " + games.at(ui->games_list->currentIndex().row()).gettime());
    QString booltext = games.at(ui->games_list->currentIndex().row()).completed == "1" ? "Yes" : "No";
    ui->completed_label->setText("Completed: " + booltext);

    //todo: disable/enable extras and manual buttons if game allows it
}

void MainWindow::on_extras_button_clicked() {
    MainWindow::hide();
    QString filepath = "file:///"  + games.at(ui->games_list->currentIndex().row()).extras;
    QDesktopServices::openUrl(QUrl(filepath, QUrl::TolerantMode));
    MainWindow::show();
}

void MainWindow::on_defaultdos_button_clicked() {
    // minimize window, start process and reshow window when process terminates
    MainWindow::hide();
    system("dosbox");
    MainWindow::show();
}

void MainWindow::on_manual_button_clicked() {
    MainWindow::hide();
    QString filepath = "file:///"  + games.at(ui->games_list->currentIndex().row()).manual;
    QDesktopServices::openUrl(QUrl(filepath, QUrl::TolerantMode));
    MainWindow::show();
}

// comparators using pre-defined lambda; will be made better
void MainWindow::sort_title() {
    std::stable_sort(games.begin(), games.end(), COMPARATOR(left.title < right.title));
    refreshGamesList();
}
void MainWindow::sort_year() {
    std::stable_sort(games.begin(), games.end(), COMPARATOR(left.year < right.year));
    refreshGamesList();
}
void MainWindow::sort_dev() {
    std::stable_sort(games.begin(), games.end(), COMPARATOR(left.developer < right.developer));
    refreshGamesList();
}
void MainWindow::sort_pub() {
    std::stable_sort(games.begin(), games.end(), COMPARATOR(left.publisher < right.publisher));
    refreshGamesList();
}

void MainWindow::refreshGamesList() {
    ui->games_list->clear();
    for(const DOSApplication& app : games) {
        ui->games_list->addItem(app.title);
    }
    ui->games_list->setCurrentRow(0);
}

void MainWindow::on_onlycompleted_box_clicked() {
    if (ui->onlycompleted_box->isChecked()) {
        ui->games_list->clear();
        for(const DOSApplication& app : games) {
            if (app.completed == "0") {
                ui->games_list->addItem(app.title);
            }
        }
    } else {
        refreshGamesList();
    }
}
