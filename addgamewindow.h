#ifndef ADDGAMEWINDOW_H
#define ADDGAMEWINDOW_H

#include <QDialog>

namespace Ui {
class AddGameWindow;
}

class AddGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddGameWindow(QWidget *parent = 0);
    ~AddGameWindow();

private slots:
    void on_gamepathbutton_clicked();

private:
    Ui::AddGameWindow *ui;
};

#endif // ADDGAMEWINDOW_H
