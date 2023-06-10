
#include "interface.h"
#include "ui_interface.h"
#include "network.h"
#include "user.h"
#include "dmwindow.h"
#include <fstream>
#include <QDir>
#include <sstream>
#include <iostream>

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Interface)
{
    ui->setupUi(this);
    n = network();
    std::string ufilepath, pfilepath;
    ufilepath = "C:/Users/Yusuf/Documents/HW5/userdata.txt";
    pfilepath = "C:/Users/Yusuf/Documents/HW5/posts.txt";
    n.read_friends(ufilepath.data());
    n.read_posts(pfilepath.data());
    ui->FriendList->setVisible(false);
    ui->PostList->setVisible(false);
    ui->ProfileName->setVisible(false);
    ui->ProfileButton->setVisible(false);
    ui->AddFriend->setVisible(false);
    ui->SuggestButton->setVisible(false);
    ui->SuggestTable->setVisible(false);
    ui->ShortestButton->setVisible(false);
    ui->ShortestBox->setVisible(false);
    ui->ShortestTextEdit->setVisible(false);
    ui->ErrorLabel->setVisible(false);
    ui->AddSuggestFriendButton->setVisible(false);
    ui->ViewDm->setVisible(false);
    connect(ui->LoginButton, &QPushButton::clicked, this, &Interface::login);
    connect(ui->ProfileButton, &QPushButton::clicked, this, &Interface::backtoprofile);
    connect(ui->FriendList, &QTableWidget::cellClicked, this, &Interface::userclick);
    connect(ui->AddFriend, &QPushButton::clicked, this, &Interface::addfriend);
    connect(ui->SuggestButton, &QPushButton::clicked, this, &Interface::newfriends);
    connect(ui->AddSuggestFriendButton, &QPushButton::clicked, this, &Interface::addfriend);
    connect(ui->SuggestTable, &QTableWidget::cellClicked, this, &Interface::addnewfriend);
    connect(ui->ShortestButton, &QPushButton::clicked, this, &Interface::shortestpath);
    connect(ui->ViewDm, &QPushButton::clicked, this, &Interface::DMwindow);
    connect(ui->LoginText, &QLineEdit::returnPressed, this, &Interface::login);
}

Interface::~Interface()
{
    delete ui;
}
void Interface::DMwindow()
{
    DmWindow *dm = new DmWindow(&i, &l, &n, this);
    this->hide();
    dm->show();

}
void Interface::login()
{
    QString qs = ui->LoginText->text();
    std::string name = qs.toStdString();
    int i = n.get_id(name);
    if (i == -1)
    {
        ui->label->setText("Incorrect Login");
        ui->LoginText->clear();
    }
    else
    {
        l = n.get_user(i);
        ui->ShortestButton->setVisible(true);
        ui->ShortestBox->setVisible(true);
        ui->FriendList->setVisible(true);
        ui->PostList->setVisible(true);
        ui->label->setVisible(false);
        ui->LoginText->setVisible(false);
        ui->LoginButton->setVisible(false);
        ui->ProfileName->setVisible(true);
        ui->ViewDm->setVisible(false);
        profile(l);
    }
}
void Interface::profile(user u)
{
    i = u;
    ui->PostList->setColumnCount(1);
    ui->PostList->setRowCount(5);
    ui->FriendList->setColumnCount(1);
    ui->FriendList->setRowCount(i.getFRIENDS().size());
    ui->ErrorLabel->setVisible(false);
    std::vector<std::size_t> temp1 = i.getFRIENDS();
    for (std::size_t k = 0; k < temp1.size(); k++)
    {
        QString qs = QString::fromStdString(n.get_name(temp1[k]));
        ui->FriendList->setItem(k, 0, new QTableWidgetItem(qs));
    }
    std::vector<std::string> temp2;
    std::string posts = i.displayPosts(5);
    std::istringstream ss(posts);
    std::string temp;
    int line = 0;
    while (std::getline(ss, temp))
    {
        if ((line%3 == 0) || (line == 0))
        {
            temp2.push_back(temp);
        }
        std::cout << temp << std::endl;
        line++;
    }
    for (std::size_t k = 0; k < temp2.size(); k++)
    {
        QString qs = QString::fromStdString(temp2[k]);
        ui->PostList->setItem(k, 0, new QTableWidgetItem(qs));
    }
    if (l.getNAME() == i.getNAME())
    {
        ui->ShortestTextEdit->setVisible(false);
        ui->ShortestButton->setVisible(true);
        ui->ShortestBox->setVisible(true);
        ui->AddFriend->setVisible(false);
        ui->ProfileButton->setVisible(false);
        ui->SuggestButton->setVisible(true);
        ui->ViewDm->setVisible(false);
        ui->ProfileName->setText("My Profile");
    }
    else
    {
        ui->SuggestTable->setRowCount(0);
        ui->ShortestButton->setVisible(false);
        ui->ShortestBox->setVisible(false);
        ui->SuggestButton->setVisible(false);
        ui->SuggestTable->setVisible(false);
        ui->ProfileButton->setVisible(true);
        ui->AddFriend->setVisible(true);
        ui->ViewDm->setVisible(true);
        std::string p = i.getNAME() + "'s Profile";
        QString Qp = QString::fromStdString(p);
        ui->ProfileName->setText(Qp);
    }
}
void Interface::userclick(int row, int column)
{
    ui->PostList->setRowCount(0);
    ui->ShortestTextEdit->clear();
    ui->ShortestTextEdit->setVisible(false);
    ui->ShortestBox->clear();
    QString cell = ui->FriendList->takeItem(row, column)->text();
    ui->ErrorLabel->setVisible(false);
    std::string name = cell.toStdString();
    if (l.getNAME()== name)
    {
        profile(l);
    }
    else
    {
        profile(n.get_user(n.get_id(name)));
    }
}
void Interface::addfriend()
{
    ui->ErrorLabel->setVisible(false);
    std::vector<std::size_t> check = l.getFRIENDS();
    bool found = false;
    for (int k = 0; k < check.size(); k++)
    {
        if (check[k] == i.getID())
        {
            found = true;
        }
    }
    if (!found)
    {
       l.add_friend(n.get_id(i.getNAME()));
    }
    else
    {
       ui->ErrorLabel->setVisible(true);
    }
}
void Interface::backtoprofile()
{
    profile(l);
}
void Interface::newfriends()
{
    int score = 0;
    ui->SuggestTable->setVisible(true);
    ui->SuggestTable->setColumnCount(1);
    std::vector<int> friends = n.suggest_friends(l.getID(), score);
    ui->SuggestTable->setRowCount(friends.size());
    ui->ErrorLabel->setVisible(false);
    for (int k = 0; k < friends.size(); k++)
    {
       std::string temp = n.get_name(friends[k]);
       QString qs = QString::fromStdString(temp);
       ui->SuggestTable->setItem(k, 0, new QTableWidgetItem(qs));
    }
}
void Interface::addnewfriend(int row, int column)
{
    ui->ShortestTextEdit->clear();
    ui->PostList->setRowCount(0);
    ui->ShortestTextEdit->setVisible(false);
    ui->ErrorLabel->setVisible(false);
    QString cell = ui->SuggestTable->takeItem(row, column)->text();
    std::string name = cell.toStdString();
    {
       profile(n.get_user(n.get_id(name)));
    }
}
void Interface::shortestpath()
{
    QString qs = ui->ShortestBox->text();
    std::string name = qs.toStdString();
    std::vector<int> path = n.shortest_path(l.getID(), n.get_id(name));
    ui->ErrorLabel->setVisible(false);
    ui->ShortestTextEdit->setVisible(true);
    for (int k = 0; k < path.size(); k++)
    {
       name = n.get_name(path[k]);
       qs = QString::fromStdString(name);
       ui->ShortestTextEdit->appendPlainText(qs);
    }
}


