#ifndef FONTDIALOG_H
#define FONTDIALOG_H

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QLabel>

namespace Ui {
class FontDialog;
}

class FontDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FontDialog(QWidget *parent = nullptr, QFont *font = nullptr);
    ~FontDialog();

private:
    // build the window
    void createLayout();
    void loadCurrentFont();
    void saveCurrentFont();

    QFont *currentFont;

    QLabel *textFamilyLabel;
    QLabel *textSizeLabel;
    QLabel *textFormatLabel;

    QComboBox *textFamilyBox;
    QComboBox *textSizeBox;
    QCheckBox *boldCheckBox;
    QCheckBox *italicCheckBox;

    QPushButton *acceptButton;
    QPushButton *cancelButton;

private slots:
    void acceptChanges();
    void cancelChanges();

};

#endif // FONTDIALOG_H
