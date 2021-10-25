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
    void softKeyPressed(int i);
    void showWarningDialog(QString title, QString content);
    bool addKeyValue();
    bool saveConfigToFile();
    bool loadConfigFromFile();
    bool downloadToDevice();
    void delayindecrease(bool is_add);
    void setDelay();
    bool deleteKeyValue();
 public slots:
    void changeLanguage(QString language);

};

#endif // CONFIGFORM_H
