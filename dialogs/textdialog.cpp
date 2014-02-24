
#include "textdialog.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QFontDialog>
#include <QDialogButtonBox>
#include <QMessageBox>

TextDialog::TextDialog(QString text, ImageArea *parent) :
    QDialog(parent)
{
    initializeGui();
    if (!text.isEmpty())
    {
        mTextEdit->setText(text);
        QTextCursor cursor(mTextEdit->textCursor());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        mTextEdit->setTextCursor(cursor);
    }
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setWindowTitle(tr("Text"));
}

void TextDialog::initializeGui()
{
    QPushButton *mFontButton = new QPushButton(tr("Select Font..."));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                       QDialogButtonBox::Cancel);
    connect(mFontButton, SIGNAL(clicked()), this, SLOT(selectFont()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(cancel()));
    QHBoxLayout *hBox = new QHBoxLayout();
    hBox->addWidget(mFontButton);
    hBox->addWidget(buttonBox);
    mTextEdit = new QTextEdit();
    mTextEdit->setLineWrapMode(QTextEdit::NoWrap);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mTextEdit);
    mainLayout->addLayout(hBox);
    setLayout(mainLayout);
    connect(mTextEdit, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

void TextDialog::textChanged()
{
    emit textChanged(qobject_cast<ImageArea*>(this->parent()), mTextEdit->toPlainText());
}

void TextDialog::selectFont()
{
    bool ok;
    QFont font = DataSingleton::Instance()->getTextFont();
    font = QFontDialog::getFont(&ok, font, this);
    if (ok)
    {
        DataSingleton::Instance()->setTextFont(font);
        textChanged();
        mTextEdit->setFocus();
    }
}

void TextDialog::cancel()
{
    emit canceled(qobject_cast<ImageArea*>(this->parent()));
    QDialog::reject();
}

void TextDialog::reject() 
{
    if (mTextEdit->toPlainText().isEmpty() ||
        QMessageBox::question(this, tr("Question"), tr("Clear text?"),
                              QMessageBox::Yes | QMessageBox::No,
                              QMessageBox::No) == QMessageBox::Yes)
    {
        emit canceled(qobject_cast<ImageArea*>(this->parent()));
    }
    QDialog::reject();
}
