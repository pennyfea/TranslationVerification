#include "verification.h"

Verification::Verification(QObject *parent) :
    QObject(parent),
    m_fontSize(0),
    m_containerWidth(0),
    m_translation(""),
    m_font("")
{

}

void Verification::setFontSize(double fontSize)
{
    if (m_fontSize != fontSize)
        m_fontSize = fontSize;
    verificationCheck();
}

void Verification::setContainerWidth(double containerWidth)
{
    if (m_containerWidth != containerWidth)
        m_containerWidth = containerWidth;
    verificationCheck();
}

void Verification::setTranslation(const QString& translation)
{
    if (m_translation != translation)
        m_translation = translation;
    verificationCheck();
}

void Verification::setFont(const QFont& f)
{
    if (m_font != f)
        m_font = f;
    verificationCheck();
}



void Verification::verificationCheck()
{
    m_font.setPixelSize(m_fontSize);
    QFontMetrics fm(m_font);
    int pixelsWide = fm.horizontalAdvance(m_translation);

    if (m_translation.isEmpty())
    {
        emit currentTextWidth(0);
        emit verificationStatus(Status::EMPTY);
        return;
    }
    emit currentTextWidth(pixelsWide);
    if (pixelsWide > m_containerWidth)
    {
        emit verificationStatus(Status::FAILED);
    }
    else
    {
        emit verificationStatus(Status::PASSED);
    }
}
