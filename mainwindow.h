#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <dosapplication.h>

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

    void on_add_game_button_clicked();

    void on_games_list_itemSelectionChanged();

    void on_extras_button_clicked();

    void on_defaultdos_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
