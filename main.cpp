#include <addressbook.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AddressBook ab;

    ab.show();

    return app.exec();

}

