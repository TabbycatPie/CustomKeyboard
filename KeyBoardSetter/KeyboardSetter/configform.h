#ifndef CONFIGFORM_H
#define CONFIGFORM_H

#include "customkeyboard.h"
#include "hidcodetable.h"
#include "uipainter.h"

#include <QWidget>
#include <qpushbutton.h>
#include <qtranslator.h>

namespace Ui {
class ConfigForm;
}

class ConfigForm : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigForm(QWidget *parent = nullptr);
    ~ConfigForm();

private:
    Ui::ConfigForm *ui;
    //Translator
    QTranslator *translator =NULL;
    void changeLanguage(QString language);
    void softKeyPressed(int i);
    void showWarningDialog(QString title, QString content);
    bool addKeyValue();
};

#endif // CONFIGFORM_H
