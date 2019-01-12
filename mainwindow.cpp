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
#include <QDebug>

#define COMPARATOR(code) [](auto && left, auto && right) -> bool {return code;}

MainWindow::MainWindow(QVector<DOSApplication>& gamesdata, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setFixedSize(QSize(800,600));
    this->setWindowIcon(QIcon(iconlocation));
    // start it centered
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), QApplication::desktop()->availableGeometry()));

    games = gamesdata;

    // add games' title to list and select first item by default
    refreshGamesList();
    // have games sorted by title by default
    on_actionTitle_triggered();

    // set boxart
    ui->box_art->setScaledContents(true);

    this->addGenres();
    this->addThemes();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_play_button_clicked() {
    int playtime = int((std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())).count());
    // minimize window, start process and reshow window when process terminates
    MainWindow::hide();
    // full execution command is 'dosbox -conf "conf file path"'
    QString command = "dosbox -conf \"" + dir.absoluteFilePath(displayed.at(ui->games_list->currentIndex().row())->conf) + "\"";
    system(qPrintable(command));
    //get playtime and update game info
    playtime -= (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())).count();
    displayed[ui->games_list->currentIndex().row()]->updateplaytime(-playtime);
    this->dbm.updateGamePlayTime(displayed[ui->games_list->currentIndex().row()]->title, displayed[ui->games_list->currentIndex().row()]->playtime);
    // refresh automatically games_list
    int idx = ui->games_list->currentIndex().row();
    refreshGamesList();
    ui->games_list->setCurrentRow(idx);
    MainWindow::show();
}

void MainWindow::getNewGame(DOSApplication newgame) {
    games.push_back(newgame);
    on_actionTitle_triggered();
    dbm.addDOSApplication(newgame);
    // add new genres
    for(QString genre : newgame.genres) {
        if(!genres.contains(genre)) genres.append(genre);
    }
    std::stable_sort(genres.begin(), genres.end());
    addGenres();
    // add new themes
    for(QString theme : newgame.themes) {
        if(!themes.contains(theme)) themes.append(theme);
    }
    std::stable_sort(themes.begin(), themes.end());
    addThemes();

    refreshGamesList();
}

void MainWindow::addGenres() {
    ui->menuFilter_by_genre->clear();
    // add genre filters actions
    for(QString genre : genres) {
        QAction* newAct = new QAction(tr(genre.toLatin1()), this);
        newAct->setCheckable(true);
        connect(newAct, &QAction::triggered, this, &MainWindow::refreshGamesList);

        ui->menuFilter_by_genre->addAction(newAct);
    }
}

void MainWindow::addThemes() {
    ui->menuFilter_by_theme->clear();
    // add theme filters actions
    for(QString theme : themes) {
        QAction* newAct = new QAction(tr(theme.toLatin1()), this);
        newAct->setCheckable(true);
        connect(newAct, &QAction::triggered, this, &MainWindow::refreshGamesList);

        ui->menuFilter_by_theme->addAction(newAct);
    }
}

void MainWindow::refreshGenresAndThemes() {
    genres = this->dbm.getGenres();
    themes = this->dbm.getThemes();
}

void MainWindow::on_games_list_itemSelectionChanged() {
    //updates all the labels to display selected game infos
    ui->year_label->setText("Year: " + QString::number(displayed.at(ui->games_list->currentIndex().row())->year));
    ui->developer_label->setText("Developer: " + displayed.at(ui->games_list->currentIndex().row())->developer);
    ui->publisher_label->setText("Publisher: " + displayed.at(ui->games_list->currentIndex().row())->publisher);
    ui->genre_label->setText("Genre: " + displayed[ui->games_list->currentIndex().row()]->getGenres());
    ui->themes_label->setText("Themes: " + displayed[ui->games_list->currentIndex().row()]->getThemes());
    QPixmap pm(displayed.at(ui->games_list->currentIndex().row())->boxart);
    ui->box_art->setPixmap(pm);
    ui->playtime_label->setText("Play time: " + displayed.at(ui->games_list->currentIndex().row())->gettime());
    QString booltext = displayed.at(ui->games_list->currentIndex().row())->completed ? "Yes" : "No";
    ui->completed_label->setText("Completed: " + booltext);

    //disable/enable extras and manual buttons if game allows it
    ui->actionBrowse_game_s_extras->setEnabled(displayed.at(ui->games_list->currentIndex().row())->extras != "");
    ui->actionOpen_game_s_manual->setEnabled(displayed.at(ui->games_list->currentIndex().row())->manual != "");

    //disable/enable set_completed button
    ui->set_completed->setDisabled(displayed.at(ui->games_list->currentIndex().row())->completed);
}

void MainWindow::refreshGamesList() {
    //ui->games_list->clearSelection();
    ui->games_list->clear();
    displayed.clear();

    // if hide_completed_games is set, only display non completed games
    for(DOSApplication& game : games) {
        if (! ui->actionHide_completed_games->isChecked() || !game.completed) {
            displayed.push_back(&game);
        }
    }
    // apply filters
    filterByGenre();
    filterByTheme();
    // add to games_list
    for(DOSApplication* game : displayed) {
        ui->games_list->addItem(game->title);
    }
    // set first element as default
    if (displayed.size() > 0) ui->games_list->setCurrentRow(0);
}

void MainWindow::filterByGenre() {
    for (QAction* act : ui->menuFilter_by_genre->actions()) {
        if (act->isChecked()) {
            for(int i = displayed.size() - 1; i > -1; i--) {
                if (!displayed.at(i)->hasGenre(act->text())) displayed.remove(i);
            }
        }
    }
}

void MainWindow::filterByTheme() {
    for (QAction* act : ui->menuFilter_by_theme->actions()) {
        if (act->isChecked()) {
            for(int i = displayed.size() - 1; i > -1; i--) {
                if (!displayed.at(i)->hasTheme(act->text())) displayed.remove(i);
            }
        }
    }
}

void MainWindow::on_set_completed_clicked() {
    displayed.at(ui->games_list->currentIndex().row())->completed = true;
    dbm.addDOSApplication(*displayed.at(ui->games_list->currentIndex().row()));
    refreshGamesList();
}

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionAdd_Game_triggered() {
    MainWindow::hide();

    AddGameWindow addgamewindow;
    connect(&addgamewindow, SIGNAL(newGame(DOSApplication)), this, SLOT(getNewGame(DOSApplication)));
    addgamewindow.exec();

    MainWindow::show();
}

void MainWindow::on_actionLaunch_normale_DOSBox_triggered() {
    // minimize window, start process and reshow window when process terminates
    MainWindow::hide();
    system("dosbox");
    MainWindow::show();
}

void MainWindow::on_actionOpen_game_s_manual_triggered() {
    QString filepath = "file:///"  + dir.absoluteFilePath(displayed.at(ui->games_list->currentIndex().row())->manual);
    QDesktopServices::openUrl(QUrl(filepath, QUrl::TolerantMode));

}

void MainWindow::on_actionBrowse_game_s_extras_triggered() {
    QString filepath = "file:///"  + dir.absoluteFilePath(displayed.at(ui->games_list->currentIndex().row())->extras);
    QDesktopServices::openUrl(QUrl(filepath, QUrl::TolerantMode));
}

void MainWindow::on_actionTitle_triggered() {
    std::stable_sort(games.begin(), games.end(), COMPARATOR(left.title < right.title));
    refreshGamesList();
}

void MainWindow::on_actionYear_triggered() {
    std::stable_sort(games.begin(), games.end(), COMPARATOR(left.year < right.year));
    refreshGamesList();
}

void MainWindow::on_actionPublisher_triggered() {
    std::stable_sort(games.begin(), games.end(), COMPARATOR(left.publisher < right.publisher));
    refreshGamesList();
}

void MainWindow::on_actionDeveloper_triggered() {
    std::stable_sort(games.begin(), games.end(), COMPARATOR(left.developer < right.developer));
    refreshGamesList();
}

void MainWindow::on_actionPlay_time_triggered() {
    std::stable_sort(games.begin(), games.end(), COMPARATOR(left.playtime < right.playtime));
    refreshGamesList();
}

void MainWindow::on_actionHide_completed_games_triggered() {
    refreshGamesList();
}

void MainWindow::on_actionDelete_Game_triggered() {
    // have to save it before removing game, otherwise games_list refresh throws "list index out of range"
    int selectedRow = ui->games_list->currentIndex().row();
    ui->games_list->clearSelection();
    ui->games_list->clear();
    // remove db entry first and then local instance
    this->dbm.remDosApplication(*(displayed.at(selectedRow)));
    games.remove(games.indexOf(*(displayed.at(selectedRow))));
    // deleting a game causes current filters to be reset
    refreshGenresAndThemes();
    addGenres();
    addThemes();
    refreshGamesList();
}
