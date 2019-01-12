#include "fontdialog.h"

#include <QDebug>
#include <QBoxLayout>
#include <QPushButton>

FontDialog::FontDialog(QWidget *parent, QFont *font) : QDialog(parent)
{
    this->currentFont = font;
    this->createLayout();
    this->loadCurrentFont();

    setWindowTitle(tr("Formato del texto"));
    resize(280, 180);
    setMaximumSize(290, 190);
}

FontDialog::~FontDialog()
{

}

void FontDialog::createLayout()
{
    // text family
    QHBoxLayout *textFamilyLayout = new QHBoxLayout();
    textFamilyLayout->addWidget(textFamilyLabel = new QLabel(tr("Fuente:"))); // QLabel
    textFamilyLayout->addWidget(textFamilyBox = new QComboBox()); // QComboBox

    textFamilyBox->addItems(QStringList({"Arial"}));

    // text size
    QHBoxLayout *textSizeLayout = new QHBoxLayout();
    textSizeLayout->addWidget(textSizeLabel = new QLabel(tr("Tamaño:"))); // QLabel
    textSizeLayout->addWidget(textSizeBox = new QComboBox()); // QComboBox

    QStringList sizeList = {};
    for (int i = 8; i < 41; i++){
        sizeList << QString::number(i);
    }

    textSizeBox->addItems(sizeList);

    // text format
    QHBoxLayout *textFormatLayout = new QHBoxLayout();
    textFormatLayout->addWidget(textFormatLabel = new QLabel(tr("Formato:"))); // QLabel

    QHBoxLayout *checkBoxLayout = new QHBoxLayout();
    checkBoxLayout->addWidget(boldCheckBox = new QCheckBox(tr("Negrita"))); // QCheckBox
    checkBoxLayout->addWidget(italicCheckBox = new QCheckBox(tr("Oblicua"))); // QCheckBox
    textFormatLayout->addLayout(checkBoxLayout);


    // buttons
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    buttonsLayout->addWidget(acceptButton = new QPushButton(tr("Aceptar")));
    connect(acceptButton, &QPushButton::clicked, this, &FontDialog::acceptChanges);

    buttonsLayout->addWidget(cancelButton = new QPushButton(tr("Cancelar")));
    connect(cancelButton, &QPushButton::clicked, this, &FontDialog::cancelChanges);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(textFamilyLayout);
    mainLayout->addLayout(textSizeLayout);
    mainLayout->addLayout(textFormatLayout);
    mainLayout->addLayout(buttonsLayout);

    this->setLayout(mainLayout);
}

void FontDialog::loadCurrentFont()
{
    textSizeBox->setCurrentIndex(currentFont->pointSize() - 8);

    if(currentFont->bold()){
        boldCheckBox->setChecked(true);
    }

    if(currentFont->italic()){
        italicCheckBox->setChecked(true);
    }
}

void FontDialog::saveCurrentFont()
{
    // set size
    currentFont->setPointSize(textSizeBox->currentIndex() + 8);

    // set bold
    currentFont->setBold( boldCheckBox->isChecked()? true : false );

    // set italic
    currentFont->setItalic( italicCheckBox->isChecked()? true : false );
}

void FontDialog::acceptChanges()
{
    saveCurrentFont();
    this->~FontDialog();
}

void FontDialog::cancelChanges()
{
    this->~FontDialog();
}
