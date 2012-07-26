#include <QtGui>

#include "addressbook.h"

AddressBook::AddressBook(QWidget *parent) :
    QWidget(parent)
{
    QLabel *nameLabel = new QLabel("Name:");
    nameLine = new QLineEdit;
    nameLine->setReadOnly(true);

    QLabel *addressLabel = new QLabel("Address:");
    addressText = new QTextEdit;
    addressText->setReadOnly(true);

    addButton = new QPushButton("Add");
    addButton->show();
    submitButton = new QPushButton("Submit");
    submitButton->hide();
    cancelButton = new QPushButton("Cancel");
    cancelButton->hide();

    connect(addButton, SIGNAL(clicked()), this, SLOT(addContact()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitContact()));
    connect(cancelButton, SIGNAL(clicked()),this,SLOT(cancel()));

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);

    buttonLayout1->addStretch();


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel,0,0);
    mainLayout->addWidget(nameLine,0,1);

    mainLayout->addWidget(addressLabel,1,0, Qt::AlignTop);
    mainLayout->addWidget(addressText,1,1);

    mainLayout->addLayout(buttonLayout1,1,2);

    setLayout(mainLayout);
    setWindowTitle("AddressBook");
}

void AddressBook::addContact()
{
    oldname = nameLine->text();
    oldaddress = addressText->toPlainText();

    nameLine->clear();
    addressText->clear();

    nameLine->setReadOnly(false);
    nameLine->setFocus(Qt::OtherFocusReason);
    addressText->setReadOnly(false);

    addButton->setEnabled(false);
    cancelButton->show();
    submitButton->show();
}

void AddressBook::cancel()
{

}

void AddressBook::submitContact()
{

}
