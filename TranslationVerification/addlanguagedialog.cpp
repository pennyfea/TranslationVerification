#include "addlanguagedialog.h"
#include "ui_addlanguagedialog.h"
#include <QPushButton>
#include <QDebug>

AddLanguageDialog::AddLanguageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLanguageDialog)
{
    ui->setupUi(this);
    setMinimumSize(395,200);
   // Load languages
   for (int i = 1; i <= QOnlineTranslator::Zulu; ++i)
   {
       const auto lang = static_cast<QOnlineTranslator::Language>(i);
       if (QOnlineTranslator::isSupportTranslation(QOnlineTranslator::Google, lang))
           addLanguage(ui->availableLanguagesListWidget, lang);
   }
   ui->availableLanguagesListWidget->setCurrentRow(0);

   if (ui->currentLanguagesListWidget->count() == 0)
   {
       ui->dialogButtonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
   }

   if (ui->currentLanguagesListWidget->count() != 0)
   {
       ui->currentLanguagesListWidget->setCurrentRow(0);
       ui->deselectButton->setEnabled(true);
   }


}

AddLanguageDialog::~AddLanguageDialog()
{
    delete ui;
}

QVector<QOnlineTranslator::Language> AddLanguageDialog::languages() const
{
    return m_languages;
}

void AddLanguageDialog::accept()
{
    QDialog::accept();

    m_languages.reserve(ui->currentLanguagesListWidget->count());
    QListWidgetItem *item = ui->currentLanguagesListWidget->item(0);
    m_languages.append(item->data(Qt::UserRole).value<QOnlineTranslator::Language>());
}

void AddLanguageDialog::filterLanguages(const QString &text)
{
    bool isItemSelected = false;
    for (int i = 0; i < ui->availableLanguagesListWidget->count(); ++i)
    {
        QListWidgetItem *item = ui->availableLanguagesListWidget->item(i);
        if (item->text().contains(text, Qt::CaseInsensitive))
        {
            item->setHidden(false);
            if (!isItemSelected)
            {
                ui->availableLanguagesListWidget->setCurrentItem(item); // Select first unhidden item
                isItemSelected = true;
            }
        }
        else
        {
            item->setHidden(true);
        }
    }
    // Disable Ok button if no item selected
    ui->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(isItemSelected);
}

void AddLanguageDialog::selectLanguage()
{
    moveLanguageHorizontally(ui->availableLanguagesListWidget, ui->currentLanguagesListWidget, ui->selectButton, ui->deselectButton);
    if (ui->currentLanguagesListWidget->count() == 1)
    {
        ui->selectButton->setDisabled(true);
        ui->dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        return;
    }
}

void AddLanguageDialog::deselectLanguage()
{
    // Block signals to emit index change after item deletion
    ui->currentLanguagesListWidget->blockSignals(true);
    moveLanguageHorizontally(ui->currentLanguagesListWidget, ui->availableLanguagesListWidget, ui->deselectButton, ui->selectButton);
    ui->currentLanguagesListWidget->blockSignals(false);
    emit ui->currentLanguagesListWidget->currentRowChanged(ui->currentLanguagesListWidget->currentRow());
}

void AddLanguageDialog::addLanguage(QListWidget *widget, QOnlineTranslator::Language lang)
{
    auto *item = new QListWidgetItem;
    item->setText(QOnlineTranslator::languageName(lang));
    item->setData(Qt::UserRole, lang);
    widget->addItem(item);
}

void AddLanguageDialog::moveLanguageHorizontally(QListWidget *from, QListWidget *to, QAbstractButton *addButton, QAbstractButton *removeButton)
{
    QListWidgetItem *item = from->takeItem(from->currentRow());
    to->addItem(item);
    to->setCurrentItem(item);
    removeButton->setEnabled(true);
    if (from->count() == 0)
        addButton->setEnabled(false);
}

