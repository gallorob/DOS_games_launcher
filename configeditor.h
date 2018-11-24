#ifndef CONFIGEDITOR_H
#define CONFIGEDITOR_H

#include <QDialog>
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

private slots:
    void on_cancel_button_clicked();

    void on_cycles_currentIndexChanged(const QString &arg1);

private:
    Ui::ConfigEditor *ui;
};

#endif // CONFIGEDITOR_H
