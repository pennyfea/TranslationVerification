#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_width(0),
     m_translator(new QOnlineTranslator(this)),
     m_language_source(QOnlineTranslator::NoLanguage),
     m_language_dest(QOnlineTranslator::NoLanguage)
{
    ui->setupUi(this);

    verification = std::make_unique<Verification>(this);
    signalMapper = new QSignalMapper(this);
    QObject::connect(signalMapper, &QSignalMapper::mappedInt, this, &MainWindow::openLanguageDialog);

    ui->translationLineEdit->setFont(ui->fontComboBox->currentFont());
    ui->textWidthLabel->setText("0");
    ui->translatedLineEdit->setDisabled(true);

    QObject::connect(ui->fontSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), verification.get(),
        &Verification::setFontSize);

    QObject::connect(ui->containerWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), verification.get(),
        &Verification::setContainerWidth);

    QObject::connect(ui->translationLineEdit, &QLineEdit::textChanged, verification.get(),
        &Verification::setTranslation);

    QObject::connect(ui->fontComboBox, &QFontComboBox::currentFontChanged, this, &MainWindow::fontChanged);

    QObject::connect(ui->fontComboBox, &QFontComboBox::currentFontChanged, verification.get(), &Verification::setFont);

    QObject::connect(verification.get(), &Verification::verificationStatus, this, &MainWindow::setVerification);

    QObject::connect(verification.get(), &Verification::currentTextWidth, this, &MainWindow::setTextWidthLabel);

    QObject::connect(ui->translationPushButton, &QPushButton::clicked, signalMapper,  QOverload<>::of(&QSignalMapper::map));
    signalMapper->setMapping(ui->translationPushButton, 0);

    QObject::connect(ui->translatedPushButton, &QPushButton::clicked, signalMapper, QOverload<>::of(&QSignalMapper::map));
    signalMapper->setMapping(ui->translatedPushButton, 1);

    QObject::connect(ui->translationLineEdit, &QLineEdit::textChanged, this, &MainWindow::requestTranslation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setVerification(Status status)
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

void MainWindow::fontChanged(const QFont& f)
{
    ui->translationLineEdit->setFont(f);
    ui->translatedLineEdit->setFont(f);
}

void MainWindow::setTextWidthLabel(int width)
{
    if (m_width != width)
        m_width = width;
}

void MainWindow::openLanguageDialog(int id)
{
    if(QPushButton *button = qobject_cast<QPushButton *>(signalMapper->mapping(id)))
    {
        languageDialog = std::make_unique<AddLanguageDialog>(this);
        languageDialog->show();
        if (languageDialog->exec() == QDialog::Accepted)
        {
            if(id == 0)
            {
                ui->translationPushButton->setText(QOnlineTranslator::languageName(languageDialog->languages()[0]));
                setLanguage(languageDialog->languages()[0], id);
            }
            if(id == 1)
            {
                ui->translatedPushButton->setText(QOnlineTranslator::languageName(languageDialog->languages()[0]));
                setLanguage(languageDialog->languages()[0], id);
            }
        }
    }
}

void MainWindow::requestTranslation()
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
        if (m_translator->error() == QOnlineTranslator::ServiceError)
        {
            qCritical() << m_translator->errorString();
        }
        if (m_translator->error() == QOnlineTranslator::NetworkError)
        {
            qCritical() << m_translator->errorString();
        }
        else
        {
            qCritical() << m_translator->errorString();
        }
    });
}

void MainWindow::setLanguage(QOnlineTranslator::Language &language, int id)
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

QOnlineTranslator::Engine MainWindow::currentEngine() const
{
    return QOnlineTranslator::Google;
}
