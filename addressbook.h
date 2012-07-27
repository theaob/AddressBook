#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
#include <QMap>

#include <QtGui>

#include "finddialog.h"

class AddressBook : public QWidget
{
    Q_OBJECT
public:
    explicit AddressBook(QWidget *parent = 0);

private:
    QLineEdit *nameLine;
    QTextEdit *addressText;

    QPushButton *cancelButton;
    QPushButton *addButton;
    QPushButton *submitButton;

    QPushButton *nextButton;
    QPushButton *previousButton;

    QPushButton *editButton;
    QPushButton *deleteButton;

    QPushButton *findButton;

    QPushButton *saveButton;
    QPushButton *loadButton;

    QPushButton *exportButton;

    QPushButton *exitButton;

    QMap<QString, QString> contacts;
    QString oldname;
    QString oldaddress;

    FindDialog *dialog;

    enum Mode{ NavigationMode, AddingMode, EditingMode };

    Mode currentMode;

    void updateInterface(Mode);

public slots:
    void addContact();
    void submitContact();
    void cancel();

    void next();
    void previous();

    void editContact();
    void removeContact();

    void findContact();
    
    void saveContacts();
    void loadContacts();

    void exportAsVCard();

    void exitApplication();
};

#endif // ADDRESSBOOK_H
