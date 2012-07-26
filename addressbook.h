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

    QMap<QString, QString> contacts;
    QString oldname;
    QString oldaddress;

public slots:
    void addContact();
    void submitContact();
    void cancel();


    
};

#endif // ADDRESSBOOK_H
