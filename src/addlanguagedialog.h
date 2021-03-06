#ifndef ADDLANGUAGEDIALOG_H
#define ADDLANGUAGEDIALOG_H

#include <QObject>
#include <QDialog>
#include <QKeyEvent>
#include <QPushButton>
#include <QDebug>
#include "qonlinetranslator.h"

class QListWidget;
class QAbstractButton;
class QShortcut;


namespace Ui {
class AddLanguageDialog;
}

class AddLanguageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLanguageDialog(QWidget *parent = nullptr);
    ~AddLanguageDialog();
    QVector<QOnlineTranslator::Language> languages() const;

public slots:
     void accept() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void isSelected();

private slots:
     void filterLanguages(const QString &text);
     void selectLanguage();
     void deselectLanguage();



 private:
     static void addLanguage(QListWidget *widget, QOnlineTranslator::Language lang);
     static void moveLanguageHorizontally(QListWidget *from, QListWidget *to, QAbstractButton *addButton, QAbstractButton *removeButton);
     Ui::AddLanguageDialog *ui;
     QVector<QOnlineTranslator::Language> m_languages;
};

#endif // ADDLANGUAGEDIALOG_H
