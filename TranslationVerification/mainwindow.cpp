#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_width(0)
{
    ui->setupUi(this);

    ui->translationLineEdit->setFont(ui->fontComboBox->currentFont());
    ui->textWidthLabel->setText("0");
    verification = std::make_unique<Verification>(this);

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
}

void MainWindow::setTextWidthLabel(int width)
{
    if (m_width != width)
    {
        m_width = width;
    }
}
