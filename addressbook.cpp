#include <QtGui>

#include "addressbook.h"
#include "finddialog.h"

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

    deleteButton = new QPushButton("Remove");
    deleteButton->setEnabled(false);
    editButton = new QPushButton("Edit");
    editButton->setEnabled(false);

    findButton = new QPushButton("Find");
    findButton->setEnabled(false);

    loadButton = new QPushButton("Load");
    loadButton->setEnabled(true);
    loadButton->setToolTip("Load previously saved contact book");

    saveButton = new QPushButton("Save");
    saveButton->setEnabled(true);
    saveButton->setToolTip("Save this contact book");

    exitButton = new QPushButton("Exit");
    exitButton->setEnabled(true);
    exitButton->setToolTip("Exit application");

    connect(addButton, SIGNAL(clicked()), this, SLOT(addContact()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitContact()));
    connect(cancelButton, SIGNAL(clicked()),this,SLOT(cancel()));
    connect(deleteButton, SIGNAL(clicked()),this, SLOT(removeContact()));
    connect(editButton, SIGNAL(clicked()),this,SLOT(editContact()));
    connect(findButton, SIGNAL(clicked()),this,SLOT(findContact()));

    connect(exitButton, SIGNAL(clicked()),this,SLOT(exitApplication()));
    connect(saveButton,SIGNAL(clicked()),this,SLOT(saveContacts()));
    connect(loadButton,SIGNAL(clicked()),this,SLOT(loadContacts()));

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addWidget(deleteButton);
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(findButton);
    buttonLayout1->addWidget(saveButton);
    buttonLayout1->addWidget(loadButton);
    buttonLayout1->addWidget(exitButton);

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

    dialog = new FindDialog;
}

void AddressBook::addContact()
{
    oldname = nameLine->text();
    oldaddress = addressText->toPlainText();

    nameLine->clear();
    addressText->clear();

    updateInterface(AddingMode);

}

void AddressBook::cancel()
{
    nameLine->setText(oldname);
    addressText->setText(oldaddress);

    updateInterface(NavigationMode);
}

void AddressBook::submitContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if(currentMode == AddingMode){
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
    }
    else if(currentMode == EditingMode)
    {
        if(name !=  oldname)
        {
            if(!contacts.contains(name))
            {
                QMessageBox::information(this, "Success", "Contact information for " + name + " added!");
                contacts.remove(oldname);
                contacts.insert(name,address);
            }
            else
            {
                QMessageBox::information(this, "Error!", "There is already a contact for " + name);
                return;
            }
        }
        else if(oldaddress != address)
        {
            QMessageBox::information(this, "Success", "Address information of " + name + " is updated!");
            contacts[name] = address;
        }
    }

    updateInterface(NavigationMode);
}

void AddressBook::previous()
{
    if(contacts.empty())
    {
        nameLine->setText("");
        addressText->setText("");
        return;
    }

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
    if(contacts.empty())
    {
        return;
    }

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

void AddressBook::removeContact()
{
    QString name = nameLine->text();
    if(contacts.contains(name))
    {
        int button = QMessageBox::question(this, "Are you sure?", "Are you sure that you want to delete information of "+name,QMessageBox::Yes|QMessageBox::No);
        if(button == QMessageBox::Yes)
        {
            contacts.remove(name);
            previous();
        }
    }
    else
    {
        QMessageBox::information(this,"Error","Couldn't find "+name+" on saved addresses!");
        return;
    }
}

void AddressBook::editContact()
{
    oldname = nameLine->text();
    oldaddress = addressText->toPlainText();

    updateInterface(EditingMode);
}

void AddressBook::updateInterface(Mode mode)
{
    currentMode = mode;

    switch(currentMode)
    {
        case AddingMode:
        case EditingMode:
            nameLine->setReadOnly(false);
            nameLine->setFocus(Qt::OtherFocusReason);
            addressText->setReadOnly(false);

            addButton->setEnabled(false);
            cancelButton->show();
            submitButton->show();

            findButton->setEnabled(false);

            saveButton->hide();
            loadButton->hide();

            nextButton->hide();
            previousButton->hide();
            break;

        case NavigationMode:
            nameLine->setReadOnly(true);
            addressText->setReadOnly(true);

            addButton->setEnabled(true);
            cancelButton->hide();
            submitButton->hide();

            deleteButton->setEnabled(true);
            editButton->setEnabled(true);

            findButton->setEnabled(true);

            saveButton->show();
            loadButton->show();

            nextButton->show();
            previousButton->show();
            break;
    }

}

void AddressBook::findContact()
{
    dialog->show();

    if(dialog->exec() == QDialog::Accepted)
    {
        QString contactName = dialog->getFindText();
        if(contacts.contains(contactName))
        {
            nameLine->setText(contactName);
            addressText->setText(contacts.value(contactName));
        }
        else
        {
            QMessageBox::information(this,"Error!","Couldn't find " + contactName + " in contacts!");
            return;
        }
    }

    updateInterface(NavigationMode);

}

void AddressBook::exitApplication()
{
    exit(1);
}

void AddressBook::saveContacts()
{
    if(contacts.isEmpty())
    {
        QMessageBox::information(this,"Error!","You have no contacts in this book!");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this,"Save Contacts", "", "Address Book (*.acb);;All Files (*)");

    if(fileName.isEmpty())
    {
        return;
    }


    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, "Error", "Couldn't open file. " + file.errorString());
        return;
    }
    else
    {
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_8);
        out << contacts;

        QMessageBox::information(this, "Success", "Saved contacts!");
        //file.close();
    }

}

void AddressBook::loadContacts()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Contacts", "", "Address Book (*.acb);;All Files (*)");

    if(fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Error", "Couldn't open file " + file.errorString() );
        return;
    }
    else
    {
        if(!contacts.isEmpty())
        {
            if(QMessageBox::question(this,"Are you sure?", "Do you want to load over the contacts?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
            {
                QDataStream in(&file);
                in.setVersion(QDataStream::Qt_4_8);
                contacts.empty();
                in >> contacts;
                //file.close();
                if(!contacts.isEmpty())
                {
                    QMap<QString,QString>::iterator i = contacts.begin();
                    nameLine->setText(i.key());
                    addressText->setText(i.value());
                }
            }
            else
            {
                return;
            }
        }
        else
        {
            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_4_8);
            contacts.empty();
            in >> contacts;
            //file.close();
            if(!contacts.isEmpty())
            {
                QMap<QString,QString>::iterator i = contacts.begin();
                nameLine->setText(i.key());
                addressText->setText(i.value());
            }
        }

    }
}
