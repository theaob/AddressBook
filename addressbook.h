#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
#include <QMap>

#include <QtGui>

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

    QMap<QString, QString> contacts;
    QString oldname;
    QString oldaddress;

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


    
};

#endif // ADDRESSBOOK_H
