#include "addgamewindow.h"
#include "ui_addgamewindow.h"
#include <QFileDialog>
#include <globalvars.h>
#include <dosapplication.h>

DOSApplication newgame;

AddGameWindow::AddGameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGameWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(iconlocation));

}

AddGameWindow::~AddGameWindow()
{
    delete ui;
}

void AddGameWindow::on_conf_button_clicked() {
    //todo: change to editable file
    QString conf_file_path = QFileDialog::getOpenFileName(this, tr("Select config file"), QDir::currentPath(), tr("Text files (*.conf)"));
    ui->conf_path->setText(conf_file_path);
}

void AddGameWindow::on_boxart_button_clicked() {
    QString boxart_path = QFileDialog::getOpenFileName(this, tr("Select boxart"), QDir::currentPath(), tr("Image files (*.png *.jpg *jpeg *bmp)"));
    ui->boxart_path->setText(boxart_path);
}

void AddGameWindow::on_manual_button_clicked() {
    QString manual_path = QFileDialog::getOpenFileName(this, tr("Select manual"), QDir::currentPath(), tr("Text files (*.pdf *.txt *.doc)"));
    ui->manual_path->setText(manual_path);
}

void AddGameWindow::on_extras_button_clicked() {
    QString extras_path = QFileDialog::getExistingDirectory(this, tr("Select extras location directory"), QDir::currentPath(), QFileDialog::ShowDirsOnly);
    ui->extras_path->setText(extras_path);
}

void AddGameWindow::on_add_game_button_clicked() {
    if(ui->title->text() != "" and
            ui->year->text() != "" and
            ui->developer->text() != "" and
            ui->publisher->text() != "" and
            ui->genre->text() != "" and
            ui->boxart_path->text() != "" and
            ui->conf_path->text() != "") {
        newgame = DOSApplication(ui->title->text(),
                                  ui->year->text().toInt(),
                                  ui->developer->text(),
                                  ui->publisher->text(),
                                  ui->genre->text(),
                                  ui->manual_path->text(),
                                  ui->boxart_path->text(),
                                  ui->conf_path->text(),
                                  ui->extras_path->text());
        emit newGame(newgame);
        AddGameWindow::close();
    } else {
        //do nothing
    }
}

