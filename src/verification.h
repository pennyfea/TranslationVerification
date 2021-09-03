#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QObject>
#include <QFont>
#include <QFontMetrics>
#include <QDebug>

enum class Status {
    PASSED,
    FAILED,
    EMPTY
};

class Verification : public QObject
{
    Q_OBJECT
public:
    explicit Verification(QObject *parent = nullptr);

public slots:
    void setFontSize(double fontSize);
    void setContainerWidth(double containerWidth);
    void setTranslation(const QString& translation);
    void setFont(const QFont& f);
    void verificationCheck();

signals:
    void verificationStatus(Status status);
    void currentTextWidth(int width);

private:
    double m_fontSize;
    double m_containerWidth;
    QString m_translation;
    QFont m_font;
};

#endif // VERIFICATION_H
