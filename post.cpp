#include "post.h"
#include <iostream>
#include <sstream>
post::post()
{
    id_ = -1;
    message_ = "";
    author_ = -1;
    likes_ = -1;
}
post::post(int i, std::string message, int a, int l)
{
    id_ = i;
    message_ = message;
    author_ = a;
    likes_ = l;
}
std::string post::displayPost()
{
    std::ostringstream s;
    s << getLIKES();
    return getMESSAGE() + "\nLiked by " + s.str() + " people.";
}
int post::getID() const
{
    return id_;
}
std::string post::getMESSAGE() const
{
    return message_;
}
int post::getAUTHOR() const
{
    return author_;
}
int post::getLIKES() const
{
    return likes_;
}
