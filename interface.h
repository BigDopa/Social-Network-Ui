
#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include "network.h"
#include "user.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Interface; }
QT_END_NAMESPACE

class Interface : public QMainWindow

{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
    void newfriends();
    void addnewfriend(int row, int column);
    void shortestpath();
    void DMwindow();
    void profile(user u);
private slots:
    void login();
    void userclick(int row, int column);
    void addfriend();
    void backtoprofile();

private:
    Ui::Interface *ui;
    network n;
    user l, i;
};

#endif // INTERFACE_H
