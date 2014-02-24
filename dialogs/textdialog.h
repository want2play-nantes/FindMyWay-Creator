
#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include "../imagearea.h"

#include <QDialog>
#include <QTextEdit>


class TextDialog : public QDialog
{
    Q_OBJECT

public:

    explicit TextDialog(QString text, ImageArea *parent);
   
private:
    void initializeGui();
    QTextEdit *mTextEdit;
  
signals:
    void textChanged(ImageArea *, const QString);
    void canceled(ImageArea *);

private slots:
    void textChanged();
    void selectFont();    
    void cancel();
    void reject();
};

#endif // TEXTDIALOG_H
