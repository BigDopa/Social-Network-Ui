#include "directmessage.h"
#include "post.h"
#include <iostream>
#include <sstream>
directmessage::directmessage(): post()
{
    recipient_ = -1;
}
directmessage::directmessage(int i, std::string m, int a, int l, int r) : post (i, m, a, l)
{
    recipient_ = r;
}
std::string directmessage::displayPost()
{
    std::ostringstream s;
    s << getRECIPIENT();
    return post::displayPost() + " $" + s.str() + "$";
}
int directmessage::getRECIPIENT() const
{
    return recipient_;
}
