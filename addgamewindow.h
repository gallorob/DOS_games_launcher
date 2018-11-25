#ifndef ADDGAMEWINDOW_H
#define ADDGAMEWINDOW_H

#include <QDialog>
#include <dosapplication.h>

namespace Ui {
class AddGameWindow;
}

class AddGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddGameWindow(QWidget *parent = 0);
    ~AddGameWindow();

signals:
    void newGame(DOSApplication newgame);

private slots:

    void on_conf_button_clicked();

    void setConfFilePath(QString filename);

    void on_boxart_button_clicked();

    void on_manual_button_clicked();

    void on_extras_button_clicked();

    void on_add_game_button_clicked();

    void on_cancel_button_clicked();

    void on_create_config_button_clicked();

private:
    Ui::AddGameWindow *ui;
};

#endif // ADDGAMEWINDOW_H
