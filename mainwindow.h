#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <dosapplication.h>
#include <addgamewindow.h>
#include <dbmanager.h>
#include <globalvars.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QVector<DOSApplication>&, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_play_button_clicked();

    void getNewGame(DOSApplication newgame);

    void addGenres();

    void addThemes();

    void refreshGenresAndThemes();

    void on_games_list_itemSelectionChanged();

    void refreshGamesList();

    void filterByGenre();

    void filterByTheme();

    void filterBySearchTerm();

    void on_set_completed_clicked();

    void on_actionExit_triggered();

    void on_actionAdd_Game_triggered();

    void on_actionLaunch_normale_DOSBox_triggered();

    void on_actionOpen_game_s_manual_triggered();

    void on_actionBrowse_game_s_extras_triggered();

    void on_actionTitle_triggered();

    void on_actionYear_triggered();

    void on_actionPublisher_triggered();

    void on_actionDeveloper_triggered();

    void on_actionPlay_time_triggered();

    void on_actionHide_completed_games_triggered();

    void on_actionDelete_Game_triggered();

    void on_titleSearch_textEdited(const QString &arg1);

private:
    QVector<DOSApplication> games;
    QVector<DOSApplication*> displayed;

    DBManager dbm = DBManager(dblocation);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
