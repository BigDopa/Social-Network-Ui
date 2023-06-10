#include "dmwindow.h"
#include "ui_dmwindow.h"
#include <sstream>
#include <iostream>
#include "dmwindow.h"
#include "directmessage.h"
#include "post.h"
#include "interface.h"

DmWindow::DmWindow(user *userF, user *userL, network *net, Interface *face,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DmWindow), l(userL), f(userF), n(net), i(face)
{
    ui->setupUi(this);
    ui->SendDM->setVisible(false);
    ui->DMView->setVisible(false);
    ui->ViewMore->setVisible(false);
    ui->AddDMWindow->setVisible(false);
    ui->AddDM->setVisible(false);
    ui->Input->setVisible(true);
    ui->DMInput->setVisible(true);
    connect(ui->Input, &QPushButton::clicked, this, [=](){
    int value = ui->DMInput->value();
        DMMainWindow(value);
    });
    connect(ui->ViewMore, &QPushButton::clicked,this, &DmWindow::NewInput);
    connect(ui->SendDM, &QPushButton::clicked, this, &DmWindow::sendDM);
    connect(ui->AddDM, &QPushButton::clicked, this, &DmWindow::AddNewDM);
    connect(ui->GoBack, &QPushButton::clicked, this, &DmWindow::Leave);

}
void DmWindow::AddNewDM()
{
    QString qs = ui->AddDMWindow->toPlainText();
    std::string dm = qs.toStdString();
    directmessage *d = new directmessage{n->get_id(l->getNAME()), dm, 0, 0, n->get_id(f->getNAME())};
    l->addPost(d);
    DMMainWindow(1);
}
void DmWindow::Leave()
{
    i->profile(*l);
    this->hide();
    i->show();
}
void DmWindow::sendDM()
{
    ui->SendDM->setVisible(false);
    ui->DMView->setVisible(false);
    ui->ViewMore->setVisible(false);
    ui->AddDMWindow->setVisible(true);
    ui->AddDM->setVisible(true);
    ui->Input->setVisible(false);
    ui->DMInput->setVisible(false);
}
void DmWindow::NewInput()
{
    ui->SendDM->setVisible(false);
    ui->DMView->setVisible(false);
    ui->ViewMore->setVisible(false);
    ui->AddDMWindow->setVisible(false);
    ui->AddDM->setVisible(false);
    ui->Input->setVisible(true);
    ui->DMInput->setVisible(true);
}
void DmWindow::DMMainWindow(int x)
{
    ui->SendDM->setVisible(true);
    ui->DMView->setVisible(true);
    ui->DMInput->setVisible(true);
    ui->AddDMWindow->setVisible(false);
    ui->AddDM->setVisible(false);
    ui->Input->setVisible(false);
    ui->DMInput->setVisible(false);
    ui->ViewMore->setVisible(true);
    ui->DMView->setColumnCount(2);
    ui->DMView->setRowCount(x);
    std::vector<std::string> message;
    std::string dms = l->displayDMs(n->get_id(f->getNAME()), l->getNAME(), x);
    std::istringstream ss(dms);
    std::string temp;
    int line = 0;
    //std::cout << dms << std::endl;
    while (std::getline(ss, temp))
    {
        if ((line%3 == 0) || (line == 0))
        {
            int first = temp.find(": ");
            int second = temp.find(": ", first + 2);
            std::string mtemp = temp.substr(second + 2);
            message.push_back(mtemp);
        }
        line++;
    }
    for (std::size_t k = 0; k < message.size(); k++)
    {
        QString qs = QString::fromStdString(message[k]);
        ui->DMView->setItem(k, 0, new QTableWidgetItem(qs));
        QString qn = QString::fromStdString(f->getNAME());
        ui->DMView->setItem(k, 1, new QTableWidgetItem(qn));
    }
}
DmWindow::~DmWindow()
{
    delete ui;
}
