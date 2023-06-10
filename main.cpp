#include <iostream>
#include <istream>
#include <fstream>
#include <stack>
#include "user.h"
#include "network.h"
#include "post.h"
#include "directmessage.h"
#include "interface.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface w;
    w.show();
    return a.exec();
}
