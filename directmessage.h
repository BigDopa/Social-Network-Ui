#ifndef DIRECTMESSAGE_H
#define DIRECTMESSAGE_H
#include <iostream>
#include <vector>
#include "post.h"
class directmessage: public post
{
public:
    //default constructor
    directmessage();
    //primary constructor
    directmessage(int i, std::string m, int a, int l, int r);
    //a method that returns the direct message
    std::string displayPost();
    //accessors
    int getRECIPIENT() const;
private:
    //ID of reciever of message
    int recipient_;
};
#endif
