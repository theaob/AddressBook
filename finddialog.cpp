#include "finddialog.h"

#include <QtGui>

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent)
{
    QLabel *findLabel = new QLabel("Contact Name:");
    lineEdit = new QLineEdit;

    findButton = new QPushButton("Find");
    findText = "";

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(findLabel);
    layout->addWidget(lineEdit);
    layout->addWidget(findButton);

    setLayout(layout);
    setWindowTitle("Find Contact");


    connect(findButton, SIGNAL(clicked()),this, SLOT(findClicked()));
    connect(findButton, SIGNAL(clicked()),this, SLOT(accept()));

}

QString FindDialog::getFindText()
{
    return findText;
}

void FindDialog::findClicked()
{
    QString text = lineEdit->text();

    if(text.isEmpty())
    {
        hide();
        return;
    }
    else
    {
        findText = text;
        lineEdit->clear();
        hide();
        return;
    }


}
