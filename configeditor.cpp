#include "configeditor.h"
#include "ui_configeditor.h"
#include "configfile.h"
#include "globalvars.h"
#include <QLineEdit>
#include <QFileDialog>
#include <QDir>

ConfigEditor::ConfigEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigEditor) {
    ui->setupUi(this);
    this->setWindowIcon(QIcon(iconlocation));
}

ConfigEditor::~ConfigEditor() {
    delete ui;
}

void ConfigEditor::on_cancel_button_clicked() {
    ConfigEditor::close();
}

void ConfigEditor::on_cycles_currentIndexChanged(const QString &arg1) {
    ui->cycles_number->setEnabled(arg1.compare(QString("fixed")) == 0);
}

void ConfigEditor::updateSerialParameters(QString arg1, QLineEdit* parameter) {
    if (arg1 == "directserial") {
        parameter->setEnabled(true);
        parameter->setToolTip("irq:, realport(required):, rxdelay:");
    } else if (arg1 == "modem") {
        parameter->setEnabled(true);
        parameter->setToolTip("irq:, listenport:");
    } else if (arg1 == "nullmodem") {
        parameter->setEnabled(true);
        parameter->setToolTip("irq:, rxdelay:, txdelay:, telnet:, usedtr:, transparent:, port:, inhsocket:");
    } else {
        parameter->setEnabled(false);
        parameter->setText("");
        parameter->setToolTip("No possible extra parameters for this option");
    }
}

void ConfigEditor::on_serial1_currentIndexChanged(const QString &arg1) {
    updateSerialParameters(arg1, ui->parameter1);
}

void ConfigEditor::on_serial2_currentIndexChanged(const QString &arg1) {
    updateSerialParameters(arg1, ui->parameter2);
}

void ConfigEditor::on_serial3_currentIndexChanged(const QString &arg1) {
    updateSerialParameters(arg1, ui->parameter3);
}

void ConfigEditor::on_serial4_currentIndexChanged(const QString &arg1) {
    updateSerialParameters(arg1, ui->parameter4);
}

void ConfigEditor::on_keyboardlayout_currentIndexChanged(const QString &arg1) {
    if (arg1 == "(specify...)") {
        ui->kb_val->setEnabled(true);
    } else {
        ui->kb_val->setEnabled(true);
        ui->kb_val->setText("");
    }
}

void ConfigEditor::setVariablesToConfigFile(ConfigFile *cf) {
    // sdl
    cf->fullscreen = ui->fullscreen->isChecked();
    cf->fulldouble = ui->fulldouble->isChecked();
    if (ui->fullresolution->text() != "") {
        cf->fullresolution = ui->fullresolution->text();
    }
    if (ui->windowresolution->text() != "") {
        cf->windowresolution = ui->windowresolution->text();
    }
    cf->output = ui->output->currentText();
    cf->autolock = ui->autolock->isChecked();
    cf->sensitivity = ui->sensitivity->text().toUInt();
    cf->waitonerror = ui->waitonerror->isChecked();
    cf->priority.push_back(ui->priority_1->currentText());
    cf->priority.push_back(ui->priority_2->currentText());
    cf->usescancodes = ui->usescancodes->isChecked();
    // dosbox
    cf->machine = ui->machine->currentText();
    cf->memsize = ui->memsize->text().toUInt();
    // render
    cf->frameskip = ui->frameskip->text().toUInt();
    cf->aspect = ui->aspect->isChecked();
    cf->scaler = ui->scaler->currentText();
    // cpu
    cf->core = ui->core->currentText();
    cf->cputype = ui->type->currentText();
    cf->cycles = ui->cycles->currentText();
    if (ui->cycles->currentText().compare(QString("fixed")) == 0) cf->fixed_cycles = ui->cycles_number->text().toUInt();
    cf->cycleup = ui->cycleup->text().toUInt();
    cf->cycledown = ui->cycledown->text().toUInt();
    // mixer
    cf->nosound = ui->nosound->isChecked();
    cf->rate = ui->rate->currentText().toUInt();
    cf->blocksize = ui->blocksize->currentText().toUInt();
    cf->prebuffer = ui->prebuffer->text().toUInt();
    // midi
    cf->mpu401 = ui->mpu401->currentText();
    cf->mididevice = ui->mididevice->currentText();
    // sblaster
    cf->sbtype = ui->sbtype->currentText();
    cf->sbbase = ui->sbbase->currentText().toUInt();
    cf->irq = ui->irq->currentText().toUInt();
    cf->dma = ui->dma->currentText().toUInt();
    cf->hdma = ui->hdma->currentText().toUInt();
    cf->sbmixer = ui->sbmixer->isChecked();
    cf->oplmode = ui->oplmode->currentText();
    cf->oplemu = ui->oplemu->currentText();
    cf->oplrate = ui->oplrate->currentText().toUInt();
    // gus
    cf->gus = ui->gus->isChecked();
    cf->gusrate = ui->gusrate->currentText().toUInt();
    cf->gusbase = ui->gusbase->currentText().toUInt();
    cf->gusirq = ui->gusirq->currentText().toUInt();
    cf->gusdma = ui->gusdma->currentText().toUInt();
    if (ui->ultradir->text() != "") {
        cf->ultradir = ui->ultradir->text();
    }
    // speaker
    cf->pcspeaker = ui->pcspeaker->isChecked();
    cf->pcrate = ui->pcrate->currentText().toUInt();
    cf->tandy = ui->tandy->currentText();
    cf->tandyrate = ui->tandyrate->currentText().toUInt();
    cf->disney = ui->disney->isChecked();
    // joystick
    cf->joysticktype = ui->joysticktype->currentText();
    cf->timed = ui->timed->isChecked();
    cf->autofire = ui->autofire->isChecked();
    cf->swap34 = ui->swap34->isChecked();
    cf->buttonwrap = ui->buttonwrap->isChecked();
    // serial
    if ((ui->serial1->currentText() == "dummy") | (ui->serial1->currentText() == "disabled")) {
        cf->serial1 = ui->serial1->currentText();
    } else {
        cf->serial1 = ui->serial1->currentText() + " " + ui->parameter1->text();
    }
    if ((ui->serial2->currentText() == "dummy") | (ui->serial2->currentText() == "disabled")) {
        cf->serial2 = ui->serial2->currentText();
    } else {
        cf->serial2 = ui->serial2->currentText() + " " + ui->parameter2->text();
    }
    if ((ui->serial3->currentText() == "dummy") | (ui->serial3->currentText() == "disabled")) {
        cf->serial3 = ui->serial3->currentText();
    } else {
        cf->serial3 = ui->serial3->currentText() + " " + ui->parameter3->text();
    }
    if ((ui->serial4->currentText() == "dummy") | (ui->serial4->currentText() == "disabled")) {
        cf->serial4 = ui->serial4->currentText();
    } else {
        cf->serial4 = ui->serial4->currentText() + " " + ui->parameter4->text();
    }
    // dos
    cf->xms = ui->xms->isChecked();
    cf->ems = ui->ems->isChecked();
    cf->umb = ui->umb->isChecked();
    cf->keyboardlayout = ui->keyboardlayout->currentText();
    // ipx
    cf->ipx = ui->ipx->isChecked();
    // autoexec
    cf->autoexec = ui->autoexec->toPlainText();
}

void ConfigEditor::on_save_button_clicked() {
    ConfigFile cf = ConfigFile();
    setVariablesToConfigFile(&cf);
    QString filename = QFileDialog::getSaveFileName(this, tr("Save current configuration file..."), QDir::currentPath(), tr("Text files (*.conf)"));
    cf.dumpToFile(filename);
    emit newConfigFile(filename);
    ConfigEditor::close();
}
