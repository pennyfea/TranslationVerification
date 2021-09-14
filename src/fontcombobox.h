#ifndef FONTCOMBOBOX_H
#define FONTCOMBOBOX_H

#include <QComboBox>
#include <QObject>
#include <QWidget>
#include <QList>
#include <QFontDatabase>


class FontComboBox : public QComboBox
{
    Q_OBJECT
public:
    FontComboBox(const QStringList& fontFileList, QWidget *parent = nullptr);
    void setFont();
    QFont getFont();
public slots:
    void setIndex(int index);
signals:
    QFont fontChanged(const QFont font);
private:
    int m_index;
    int m_fontId;
    QFont m_font;
    QStringList m_applicationFontFamilyList;
    QStringList m_applicationFontName;
    QStringList m_fontFileList;
};

#endif // FONTCOMBOBOX_H
