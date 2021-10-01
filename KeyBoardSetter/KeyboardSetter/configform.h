#ifndef CONFIGFORM_H
#define CONFIGFORM_H

#include <QWidget>
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
};

#endif // CONFIGFORM_H
