#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include "verification.h"
#include "addlanguagedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void fontChanged(const QFont& f);
    void setVerification(Status status);
    void setTextWidthLabel(int width);
    void setLanguage(QOnlineTranslator::Language &language, int id);

public slots:
    void requestTranslation();
    void openLanguageDialog(int id);

private:
    Ui::MainWindow *ui;
    int m_width;
    const int MAXIMUM = 1000;
    QPalette palette;
    QSignalMapper *signalMapper;
    QOnlineTranslator *m_translator;
    QOnlineTranslator::Engine currentEngine() const;
    QOnlineTranslator::Language m_language_source;
    QOnlineTranslator::Language m_language_dest;
    Verification* m_verification;
    AddLanguageDialog* m_languageDialog;
};
#endif // MAINWINDOW_H
