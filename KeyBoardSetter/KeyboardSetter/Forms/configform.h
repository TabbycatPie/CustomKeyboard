#ifndef CONFIGFORM_H
#define CONFIGFORM_H

#include "Utils/customkeyboard.h"
#include "HidAPI/hidcodetable.h"
#include "UIpainter/uipainter.h"

#include <QPointer>
#include <QWidget>
#include <qpushbutton.h>
#include <qtranslator.h>

class SettingForm;

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
    QPointer<SettingForm> setting_form;
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
    bool changeLanguage(QString language);
    void loadConfigFromMenu();
    void saveConfigFromMenu();
    int getModifierDelayLevel() const;
    void setModifierDelayLevel(int level);

};

#endif // CONFIGFORM_H
