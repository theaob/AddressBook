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

    previousButton = new QPushButton("Previous");

    nextButton = new QPushButton("Next");

    connect(nextButton, SIGNAL(clicked()),this,SLOT(next()));
    connect(previousButton, SIGNAL(clicked()),this,SLOT(previous()));

    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel,0,0);
    mainLayout->addWidget(nameLine,0,1);

    mainLayout->addWidget(addressLabel,1,0, Qt::AlignTop);
    mainLayout->addWidget(addressText,1,1);

    mainLayout->addLayout(buttonLayout1,1,2);
    mainLayout->addLayout(buttonLayout2,2,0,1,3);

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

    nextButton->setEnabled(false);
    previousButton->setEnabled(false);
}

void AddressBook::cancel()
{
    nameLine->setText(oldname);
    nameLine->setReadOnly(true);

    addressText->setText(oldaddress);
    addressText->setReadOnly(true);

    addButton->setEnabled(true);
    cancelButton->hide();
    submitButton->hide();

    nextButton->setEnabled(true);
    previousButton->setEnabled(true);
}

void AddressBook::submitContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if(name.isEmpty() || address.isEmpty())
    {
        QMessageBox::information(this, "Error!", "You cannot save a contact without a name or an address!");
        return;
    }

    if(contacts.contains(name))
    {
        QMessageBox::information(this,"Error!","There is a address saved for\"" + name + "\"");
        return;
    }
    else
    {
        contacts.insert(name,address);
        QMessageBox::information(this, "Success", "Address saved for \"" + name + "\"" );
    }

    if(contacts.isEmpty())
    {
        nameLine->clear();
        addressText->clear();
    }

    nameLine->setReadOnly(true);
    addressText->setReadOnly(true);

    addButton->setEnabled(true);
    submitButton->hide();
    cancelButton->hide();

    nextButton->setEnabled(true);
    previousButton->setEnabled(true);
}

void AddressBook::previous()
{
    QString name = nameLine->text();
    QMap<QString,QString>::iterator i = contacts.find(name);

    if(i == contacts.end())
    {
        nameLine->clear();
        addressText->clear();
        return;
    }

    if(i == contacts.begin())
    {
        i = contacts.end();
    }

    i--;

    nameLine->setText(i.key());
    addressText->setText(i.value());
}

void AddressBook::next()
{
    QString name = nameLine->text();
    QMap<QString,QString>::iterator i = contacts.find(name);

    if(i != contacts.end())
    {
        i++;
    }

    if(i == contacts.end())
    {
        i = contacts.begin();
    }

    nameLine->setText(i.key());
    addressText->setText(i.value());
}
