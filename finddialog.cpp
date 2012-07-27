#include <QtGui>

#include "finddialog.h"



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


    connect(findButton(),SIGNAL());

}

QString FindDialog::getFindText()
{

}
