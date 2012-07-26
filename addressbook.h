#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>

#include <QtGui>

class AddressBook : public QWidget
{
    Q_OBJECT
public:
    explicit AddressBook(QWidget *parent = 0);

private:
    QLineEdit *nameLine;
    QTextEdit *addressText;
    
};

#endif // ADDRESSBOOK_H
