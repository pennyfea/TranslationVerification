#include <QDir>
#include <QDirIterator>
#include "widgetwindow.h"
#include "ui_widgetwindow.h"

widgetwindow::widgetwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetwindow),
    m_width(0),
    m_translator(new QOnlineTranslator(this)),
    m_language_source(QOnlineTranslator::NoLanguage),
    m_language_dest(QOnlineTranslator::NoLanguage),
    m_verification(new Verification(this))
{
    ui->setupUi(this);
    ui->menuBar->hide();

    QStringList fontFileList = QDir(":/fonts/").entryList(QStringList() << "*.", QDir::Files | QDir::NoDotDot | QDir::NoDot);
    QDirIterator it(":/fonts/",  QDir::Files | QDir::NoDotDot | QDir::NoDot, QDirIterator::Subdirectories);
    while (it.hasNext())
        fontFileList << it.next();

    m_fontComboBox = new FontComboBox(fontFileList, this);
    ui->horizontalLayout->addWidget(m_fontComboBox);

    m_signalMapper = new QSignalMapper(this);
    connect(m_signalMapper, &QSignalMapper::mappedInt, this, &widgetwindow::openLanguageDialog);

    ui->translationLineEdit->setFont(m_fontComboBox->getFont());
    ui->textWidthLabel->setText("0");
    ui->translatedLineEdit->setReadOnly(true);
    QPalette palette;
    palette.setColor(QPalette::Base,Qt::gray);
    ui->translatedLineEdit->setPalette(palette);
    QFontMetrics fm(m_fontComboBox->getFont());
    ui->fontSizeSpinBox->setValue(fm.height());

    ui->fontSizeSpinBox->setMaximum(MAXIMUM);
    ui->containerWidthSpinBox->setMaximum(MAXIMUM);

    QObject::connect(ui->fontSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), m_verification,
        &Verification::setFontSize);

    QObject::connect(ui->containerWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), m_verification,
        &Verification::setContainerWidth);

    QObject::connect(ui->translationLineEdit, &QLineEdit::textChanged, m_verification,
        &Verification::setTranslation);


    QObject::connect(m_fontComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), m_fontComboBox, &FontComboBox::setIndex);

    QObject::connect(m_fontComboBox, &FontComboBox::fontChanged, this, &widgetwindow::fontChanged);

    QObject::connect(m_fontComboBox, &FontComboBox::fontChanged, m_verification, &Verification::setFont);

    QObject::connect(m_verification, &Verification::verificationStatus, this, &widgetwindow::setVerification);

    QObject::connect(m_verification, &Verification::currentTextWidth, this, &widgetwindow::setTextWidthLabel);

    QObject::connect(ui->translationPushButton, &QPushButton::clicked, m_signalMapper,  QOverload<>::of(&QSignalMapper::map));
    m_signalMapper->setMapping(ui->translationPushButton, 0);

    QObject::connect(ui->translatedPushButton, &QPushButton::clicked, m_signalMapper, QOverload<>::of(&QSignalMapper::map));
    m_signalMapper->setMapping(ui->translatedPushButton, 1);

    QObject::connect(ui->translationLineEdit, &QLineEdit::textChanged, this, &widgetwindow::requestTranslation);
}

widgetwindow::~widgetwindow()
{
    delete ui;
}

void widgetwindow::setVerification(Status status)
{

    ui->verificationStatusLabel->setAutoFillBackground(true);
    ui->textWidthLabel->setText(QVariant(m_width).toString());
    switch (status)
    {
    case Status::PASSED:
        palette.setColor(QPalette::WindowText, Qt::green);
        ui->verificationStatusLabel->setPalette(palette);
        ui->verificationStatusLabel->setText(tr("The text fits in the container"));
        break;
    case Status::FAILED:
        palette.setColor(QPalette::WindowText, Qt::red);
        ui->verificationStatusLabel->setPalette(palette);
        ui->verificationStatusLabel->setText(tr("The text does not fit in the container"));
        break;
    case Status::EMPTY:
        ui->verificationStatusLabel->clear();
        break;
    default:
        break;
    }

}

void widgetwindow::fontChanged(const QFont& f)
{
    QFontMetrics fm(f);
    ui->translationLineEdit->setFont(f);
    ui->translatedLineEdit->setFont(f);
    ui->fontSizeSpinBox->setValue(fm.height());
}

void widgetwindow::setTextWidthLabel(int width)
{
    if (m_width != width)
        m_width = width;
}

void widgetwindow::openLanguageDialog(int id)
{
    if(QPushButton *button = qobject_cast<QPushButton *>(m_signalMapper->mapping(id)))
    {
        m_languageDialog = new AddLanguageDialog(this);

        m_languageDialog->show();
        if (m_languageDialog->exec() == QDialog::Accepted)
        {
            if(id == 0)
            {
                ui->translationPushButton->setText(QOnlineTranslator::languageName(m_languageDialog->languages()[0]));
                setLanguage(m_languageDialog->languages()[0], id);
            }
            if(id == 1)
            {
                ui->translatedPushButton->setText(QOnlineTranslator::languageName(m_languageDialog->languages()[0]));
                setLanguage(m_languageDialog->languages()[0], id);
                requestTranslation();
            }
        }

        m_languageDialog->deleteLater();
    }
}

void widgetwindow::requestTranslation()
{
    if (m_language_dest == QOnlineTranslator::NoLanguage && m_language_source == QOnlineTranslator::NoLanguage)
    {
        return;
    }
    m_translator->translate(ui->translationLineEdit->text(), currentEngine(), m_language_dest, m_language_source);
    QObject::connect(m_translator, &QOnlineTranslator::finished, [&] {
        if (m_translator->error() == QOnlineTranslator::NoError)
        {
             ui->translatedLineEdit->setText(m_translator->translation());
        }
        else if (m_translator->error() == QOnlineTranslator::NetworkError)
        {
            qCritical() << m_translator->errorString();
        }
        else if (m_translator->error() == QOnlineTranslator::ServiceError)
        {
            qCritical() << m_translator->errorString();
        }
        else
        {
            qCritical() << m_translator->errorString();
        }
    });
}

void widgetwindow::setLanguage(QOnlineTranslator::Language &language, int id)
{
    if (id == 0)
    {
        if (m_language_source == language)
            return;
        m_language_source = language;
    }
    if (id == 1)
    {
        if (m_language_dest == language)
            return;
        m_language_dest = language;
    }
}

QOnlineTranslator::Engine widgetwindow::currentEngine() const
{
    return QOnlineTranslator::Google;
}

