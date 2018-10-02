#include "addgamewindow.h"
#include "ui_addgamewindow.h"
#include <QFileDialog>

AddGameWindow::AddGameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGameWindow)
{
    ui->setupUi(this);
}

AddGameWindow::~AddGameWindow()
{
    delete ui;
}

void AddGameWindow::on_gamepathbutton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, "Select game location directory", QString(), QFileDialog::ShowDirsOnly);
    ui->gameloc->setText(directory);
}
