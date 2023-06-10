#ifndef DMWINDOW_H
#define DMWINDOW_H

#include <QWidget>
//#include "network.h"
#include "user.h"
#include "network.h"
#include "interface.h"

namespace Ui {
class DmWindow;
}

class DmWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DmWindow(user *userF,user *userL, network *net, Interface *face,QWidget *parent = nullptr);
    ~DmWindow();
    void DMMainWindow(int x);
    void NewInput();
    void sendDM();
    void AddNewDM();
    void Leave();
private:
    Ui::DmWindow *ui;
    user *l, *f;
    network *n;
    Interface *i;
};

#endif // DMWINDOW_H
