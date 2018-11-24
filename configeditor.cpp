#include "configeditor.h"
#include "ui_configeditor.h"
#include "configfile.h"

ConfigEditor::ConfigEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigEditor) {
    ui->setupUi(this);
}

ConfigEditor::~ConfigEditor() {
    delete ui;
}

void ConfigEditor::on_cancel_button_clicked() {
    ConfigEditor::close();
}

void ConfigEditor::on_cycles_currentIndexChanged(const QString &arg1) {
    if(arg1 == "fixed") {
        ui->cycles_number->setEnabled(true);
    } else {
        ui->cycles_number->setEnabled(false);
    }
}
