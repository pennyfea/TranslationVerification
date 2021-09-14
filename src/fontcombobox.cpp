#include "fontcombobox.h"
#include <QDebug>
#include <QFileInfo>
FontComboBox::FontComboBox(const QStringList& fontFileList, QWidget *parent):
    m_fontFileList(fontFileList)
{
    foreach (const QString& filename,  m_fontFileList)
    {
        QFileInfo file(filename);
        QString path = file.fileName();
        QString fname = path.section(".",0,0);
        m_fontId = QFontDatabase::addApplicationFont(filename);

        if (m_fontId == -1)
        {
            const QString info = QString("Unable to install font %1").arg(filename);
            qWarning() << info;
        }
        else
        {
           m_applicationFontFamilyList.append(QFontDatabase::applicationFontFamilies(m_fontId));
           m_applicationFontName.append(fname);
        }
    }
       addItems(m_applicationFontName);
}

void FontComboBox::setIndex(int index)
{
    if (m_index != index)
        m_index = index;
    setFont();
}

QFont FontComboBox::getFont()
{
    return m_applicationFontFamilyList[currentIndex()];
}

void FontComboBox::setFont()
{

    QFont font(m_applicationFontName[m_index]);
    if (m_applicationFontName[m_index].contains("Italic", Qt::CaseInsensitive))
    {
        font.setItalic(true);
    }
    font.setFamily(m_applicationFontFamilyList[m_index]);
    m_font = font;
    emit fontChanged(m_font);
}
