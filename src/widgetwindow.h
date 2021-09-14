#ifndef WIDGETWINDOW_H
#define WIDGETWINDOW_H

#include <QWidget>
#include <QSignalMapper>
#include "verification.h"
#include "addlanguagedialog.h"
#include "fontcombobox.h"

namespace Ui {
class widgetwindow;
}

class widgetwindow : public QWidget
{
    Q_OBJECT

public:
    explicit widgetwindow(QWidget *parent = nullptr);
    ~widgetwindow();
    void fontChanged(const QFont& f);
    void setVerification(Status status);
    void setTextWidthLabel(int width);
    void setLanguage(QOnlineTranslator::Language &language, int id);

public slots:
    void requestTranslation();
    void openLanguageDialog(int id);

private:
    Ui::widgetwindow *ui;
    int m_width;
    const int MAXIMUM = 1000;
    QPalette palette;

    QOnlineTranslator *m_translator;
    QOnlineTranslator::Engine currentEngine() const;
    QOnlineTranslator::Language m_language_source;
    QOnlineTranslator::Language m_language_dest;
    Verification* m_verification;
    QSignalMapper *m_signalMapper;
    AddLanguageDialog* m_languageDialog;
    FontComboBox* m_fontComboBox;

};

#endif // WIDGETWINDOW_H

