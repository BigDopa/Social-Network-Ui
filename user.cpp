#include "user.h"
#include "directmessage.h"
#include <cassert>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <string>
//default contstructor, default values
user::user()
{
    id = 0;
    name = "N/A";
    year = 0000;
    zip = 00000;
    friends = std::vector<std::size_t>();
    predecessor = -1;
    depth = 0;
    messages_ = std::vector<post*>();
}
//primary constructor, will set object variables to given paramteters
user::user(std::string newname, int newyear, int newzip)
{
    name = newname;
    year = newyear;
    zip = newzip;
    friends = std::vector<std::size_t>();
    predecessor = -1;
    depth = 0;
    messages_ = std::vector<post*>();
}
//add user function to push new id into vector
void user::add_friend(int id)
{
    friends.push_back(id);
}
void user::set_depth(int d)
{
    depth = d;
}
void user::set_predecessor(std::size_t p)
{
    predecessor = p;
}
void user::set_id(std::size_t newid)
{
    id = newid;
}
void user::addPost(post *p)
{
    messages_.push_back(p);
}
std::string user::displayPosts(int howmany)
{
    std::string output;
    int c = 0;
    for (int i = 0; i < messages_.size(); i++)
    {
        int f = messages_[i]->displayPost().find('$');
        if ((f == -1) && (c != howmany))
        {
            output += messages_[i]->displayPost() + "\n\n";
            c++;
        }
    }
    return output;
}
std::string user::displayDMs(int who, std::string name, int howmany)
{
    std::string output, temp;
    int i = 0;
    int c = 0;
    for (int i = 0; i < messages_.size(); i++)
    {
        int f = messages_[i]->displayPost().find('$');
        if ((f != -1) && (c != howmany))
        {
            directmessage *d = (directmessage*)messages_[i];
            if (d->getRECIPIENT() == who)
            {
                output +=  "From: " + name + ": " + messages_[i]->displayPost();
                for (int k = 0; k < output.size(); k++)
                {
                    if (output[k] == '$')
                    {
                        output[k] = '\0';
                    }
                }
                output += "\n\n";
            }
            c++;
        }
    }
    return output;
}
//delete user function to remove id from vector
void user::delete_friend(int id)
{
    for (int i = 0; i < friends.size(); i++)
    {
        if (friends[i] == id)
        {
            friends.erase(friends.begin() + i);
        }
    }
}
//ID accessor
std::size_t user::getID() const
{
    return id;
}
//Name accessor
std::string user::getNAME() const
{
    return name;
}
//Year accessor
std::size_t user::getYEAR() const
{
    return year;
}
//zip accessor
std::size_t user::getZIP() const
{
    return zip;
}
std::vector<std::size_t> user::getFRIENDS() const
{
    return friends;
}
std::size_t user::get_predecessor() const
{
    return predecessor;
}
int user::get_depth() const
{
    return depth;
}
int user::get_messages() const
{
    return messages_.size();
}
