#ifndef CONFIGEDITOR_H
#define CONFIGEDITOR_H

#include <QDialog>
#include <QLineEdit>
#include "configfile.h"

namespace Ui {
class ConfigEditor;
}

class ConfigEditor : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigEditor(QWidget *parent = 0);
    ~ConfigEditor();

signals:
    void newConfigFile(QString filename);

private slots:
    void on_cancel_button_clicked();

    void on_cycles_currentIndexChanged(const QString &arg1);

    void updateSerialParameters(QString arg1, QLineEdit* parameter);

    void on_serial1_currentIndexChanged(const QString &arg1);

    void on_serial2_currentIndexChanged(const QString &arg1);

    void on_serial3_currentIndexChanged(const QString &arg1);

    void on_serial4_currentIndexChanged(const QString &arg1);

    void on_keyboardlayout_currentIndexChanged(const QString &arg1);

    void setVariablesToConfigFile(ConfigFile *cf);

    void on_save_button_clicked();

private:
    Ui::ConfigEditor *ui;
};

#endif // CONFIGEDITOR_H
