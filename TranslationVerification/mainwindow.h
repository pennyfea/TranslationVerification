#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "verification.h"

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

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Verification> verification;
    QPalette palette;
    int m_width;
};
#endif // MAINWINDOW_H
