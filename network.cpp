#include "network.h"
#include "user.h"
#include "directmessage.h"
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <queue>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stack>
#include <set>
//default constructor, sets users to be a empty vector of user objects
network::network()
{
    users = std::vector<user>();
}
//add user function, takes in a reference to a object of type user and pushes it and a id number into the vector
void network::add_user(const user &newUser)
{
    users.push_back(newUser);
    users[users.size() - 1].set_id(users.size() - 1);
}
//add connection function, takes in two strings for two names and checks to make sure they are in the network, if so add connection between the two of them
int network::add_connection(std::string s1, std::string s2)
{
    std::size_t s1ID, s2ID;
    s1ID = get_id(s1);
    s2ID = get_id(s2);
    if (s1ID == -1)
    {
        std::cout << s1 << " Does not exist, please try again" << std::endl;
        return -1;
    }
    else if (s2ID == -1)
    {
        std::cout << s2 << " Does not exist, please try again" << std::endl;
        return -1;
    }
    else
    {
        users[s1ID].add_friend(s2ID);
        users[s2ID].add_friend(s1ID);
        std::cout << std::endl;
        return 0;
    }
}
//print data function, when called prints out all of the relevant data from network vector, uysing setw to print out in allignment
void network::print_data()
{
    std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << " NAME" << std::setw(6) << "YEAR" << std::setw(6) << "ZIP" << std::endl;
    std::cout << "=========================================" << std::endl;
    for (int i = 0; i < users.size(); i++)
    {
        std::stringstream s;
        s << std::setw(5) << std::setfill('0') << users[i].getZIP();
        std::string temp = s.str();
        std::cout << std::setw(5) << users[i].getID() << std::setw(25) << users[i].getNAME() << std::setw(6) << users[i].getYEAR();
        std::cout << temp << std::endl;
        //std::cout << temp << std::endl;
    }
    std::cout << std::endl;
}
//print friends function, takes in ID, and iterates through the network vector to find relevant person, if found prints out data of the friend
void network::print_friends(int id)
{
    bool found = false;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getID() == id)
        {
            found = true;
            std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << " NAME" << std::setw(6) << "YEAR" << std::setw(6) << "ZIP" << std::endl;
            std::cout << "=========================================" << std::endl;
            auto friendlist = users[i].getFRIENDS();
            for (int j = 0; j < friendlist.size(); j++)
            {
                std::stringstream s;
                s << std::setw(5) << std::setfill('0') << users[friendlist[j]].getZIP();
                std::string temp = s.str();
                std::cout << std::setw(5) << users[friendlist[j]].getID() << std::setw(25) << users[friendlist[j]].getNAME() << std::setw(6) << users[friendlist[j]].getYEAR();
                std::cout << temp << std::endl;
            }
        }
    }
    if (found == false)
    {
        std::cout << "User not found" << std::endl;
    }

}
std::vector<int> network::shortest_path(int from, int to)
{
    std::set<std::size_t> visited;
    std::queue<std::size_t> q;
    std::vector<int> path;
    q.push(from);
    visited.insert(from);
    while (!q.empty())
    {
        std::size_t node = q.front();
        q.pop();
        for (auto i: users[node].getFRIENDS())
        {
            if (visited.count(i) == 0)
            {
                q.push(i);
                visited.insert(i);
                users[i].set_predecessor(node);

            }
            if (users[node].getID() == to)
            {
                path.push_back(to);
                while(users[node].get_predecessor() != -1)
                {
                    path.push_back(users[node].get_predecessor());
                    node = users[node].get_predecessor();
                }
            }
        }
    }
    return path;
}
std::vector<std::vector<int>> network::groups()
{
    std::set<std::size_t> check;
    std::vector<std::vector<int>> groups;
    for (int i = 0; i < users.size(); i++)
    {
        std::vector<int> group;
        if (check.count(users[i].getID()) == 0)
        {
            std::set<std::size_t> visited;
            std::queue<std::size_t> q;
            q.push(i);
            visited.insert(i);
            while (!q.empty())
            {
                std::size_t node = q.front();
                check.insert(node);
                group.push_back(node);
                q.pop();
                for (auto k: users[node].getFRIENDS())
                {
                    if (visited.count(k) == 0)
                    {
                        q.push(k);
                        visited.insert(k);
                        check.insert(k);
                    }
                }
            }
            groups.push_back(group);
        }
    }
    return groups;
}
//remove connection function, same as add connection, but instead removes it
int network::remove_connection(std::string s1, std::string s2)
{
    std::size_t s1ID, s2ID;
    s1ID = get_id(s1);
    s2ID = get_id(s2);
    if (s1ID == -1)
    {
        std::cout << s1 << " Does not exist, please try again" << std::endl;
        return -1;
    }
    else if (s2ID == -1)
    {
        std::cout << s2 << " Does not exist, please try again" << std::endl;
        return -1;
    }
    else
    {
        users[s1ID].delete_friend(s2ID);
        users[s2ID].delete_friend(s1ID);
        std::cout << std::endl;
        return 0;
    }
}
//Read friends function, currrently works, but not sure how to fix formatting
int network::read_friends(char *fname)
{
    std::string myline, newname;
    std::size_t n, i, newid, friendid;
    int newyear, newzip;
    std::ifstream myfile(fname);
    n = 0;
    i = 0;
    std::getline(myfile, myline);
    if (myfile.fail() == false)
    {
        while (std::getline(myfile, myline))
        {
            if(n == 1)
            {
                myline.erase(0, myline.find_first_not_of(" \n\r\t"));
                myline.erase(myline.find_last_not_of(" \n\r\t") + 1);
                //std::cout << "name: " << myline << std::endl;
                newname = myline;
            }
            if (n == 2)
            {
                myline.erase(0, myline.find_first_not_of(" \n\r\t"));
                myline.erase(myline.find_last_not_of(" \n\r\t") + 1);
                //std::cout << "year: " << myline << std::endl;
                newyear = std::stoi(myline);
            }
            if (n == 3)
            {
                myline.erase(0, myline.find_first_not_of(" \n\r\t"));
                myline.erase(myline.find_last_not_of(" \n\r\t") + 1);
                std::stringstream ss(myline);
                ss >> newzip;
                //std::cout << "zip: " << newzip << std::endl;
            }
            if (n == 4)
            {
                add_user(user(newname, newyear, newzip));
                std::stringstream ss(myline);
                myline.erase(0, myline.find_first_not_of(" \n\r\t"));
                myline.erase(myline.find_last_not_of(" \n\r\t") + 1);
                //std::cout << "friends: " << myline << std::endl;
                while (ss >> friendid)
                {
                    users[i].add_friend(friendid);
                }
                i++;
            }
            if (n == 5)
            {
                n = 0;
            }
            n++;
        }
    }
    else
    {
        std::cout << "Error File not read" << std::endl;
        return -1;
    }
    myfile.close();
    return 0;
}
int network::read_posts(char *fname)
{
    int id, likes, n;
    std::string myline, author, message, recipient;
    std::ifstream myfile(fname);
    n = 0;
    std::getline(myfile, myline);
    if (myfile.fail() == false)
    {
        while (std::getline(myfile, myline))
        {
            if (n == 0)
            {
                myline.erase(0, myline.find_first_not_of(" \n\r\t"));
                myline.erase(myline.find_last_not_of(" \n\r\t") + 1);
                //std::cout << "id: " << myline << std::endl;
                id = std::stoi(myline);
            }
            if (n == 1)
            {
                myline.erase(0, myline.find_first_not_of(" \n\r\t"));
                myline.erase(myline.find_last_not_of(" \n\r\t") + 1);
                //std::cout << "message: " << myline << std::endl;
                message = myline;
            }
            if (n == 2)
            {
                myline.erase(0, myline.find_first_not_of(" \n\r\t"));
                myline.erase(myline.find_last_not_of(" \n\r\t") + 1);
                //std::cout << "author: " << myline << std::endl;
                author = get_name(std::stoi(myline));
            }
            if (n == 3)
            {
                myline.erase(0, myline.find_first_not_of(" \n\r\t"));
                myline.erase(myline.find_last_not_of(" \n\r\t") + 1);
                //std::cout << "likes: " << myline << std::endl;
                likes = std::stoi(myline);
            }
            if (n == 4)
            {
                myline.erase(0, myline.find_first_not_of(" \n\r\t"));
                myline.erase(myline.find_last_not_of(" \n\r\t") + 1);
                if (myline == "DM")
                {
                    getline(myfile, myline);
                    myline.erase(0, myline.find_first_not_of(" \n\r\t"));
                    myline.erase(myline.find_last_not_of(" \n\r\t") + 1);
                    recipient = get_name(std::stoi(myline));
                    //std::cout << "recipient: " << myline << std::endl;
                    addDM(author, message, likes, id, recipient);
                    //std::cout << "added DM" << std::endl;
                }
                else
                {
                    addPost(author, message, likes, id);
                    //std::cout << "Added Post" << std::endl;
                }
                n = 0;
                continue;
            }
            n++;
        }
    }
    myfile.close();
    //std::cout << "finished!" << std::endl;
    return 0;
}
//write friends function, takes in a pointer to a char which is the name of the file to write the data too, then writes out all of the data of every user in the network
int network::write_friends(char *fname)
{
    std::ofstream myfile(fname);
    if (myfile.fail() == false)
    {
        myfile << users.size() << std::endl;
        {
            if (num_users() == 0)
            {
                std::cout << "Error: no users to print" << std::endl;
            }
            for (int i = 0; i < users.size(); i++)
            {
                myfile << "         " << users[i].getID() << std::endl;
                myfile << "         " << users[i].getNAME() << std::endl;
                myfile << "         " << users[i].getYEAR() << std::endl;
                myfile << "         " << users[i].getZIP() << std::endl;
                myfile << "Friends: ";
                if (users[i].getFRIENDS().size() == 0)
                {
                    myfile << std::endl;
                }
                else
                {
                    for (int j = 0; j < users[i].getFRIENDS().size(); j++)
                    {
                        myfile << users[i].getFRIENDS()[j] << " ";
                    }
                    myfile << std::endl;

                }
            }
        }
        myfile.close();
    }
    else
    {
        std::cout << "ERORR: FILE NOT OPENED" << std::endl;
        return -1;
    }
    return 0;
}
//get ID function, simply returns id of user given their name, will return -1 if name is not present
int network::get_id(std::string name)
{
    for (int i = 0; i < num_users(); i++)
    {
        if (name.compare(users[i].getNAME()) == 0)
        {
            return i;
        }
    }
    return -1;
}
std::string network::get_name(int id)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getID() == id)
        {
            return users[i].getNAME();
        }
    }
    return "No name found";
}
//num_users function, simply returns size of users vector, or the number of users
std::size_t network::num_users()
{
    return users.size();
}
std::vector<int> network::suggest_friends(int who, int &score)
{
    std::stack<int> s;
    std::unordered_map<int, std::size_t> pre, post, parent;
    std::size_t time = 0;
    int start = users[who].getID();
    std::unordered_map<int, int> list;
    s.push(start);
    std::vector<int> common_friends;
    score = 0;
    while(!s.empty())
    {
        int common = 0;
        int t = s.top();
        if ((s.top() != who) && (list.count(s.top()) == 0))
        {
            for (int i = 0; i < users[who].getFRIENDS().size(); i++)
            {
                for (int j = 0; j < users[s.top()].getFRIENDS().size(); j++)
                {
                    if (users[who].getFRIENDS()[i] == users[s.top()].getFRIENDS()[j])
                    {
                        common++;
                    }
                }
            }
            list.insert(std::make_pair(s.top(), common));
            if (score < common)
            {
                score = common;
            }
        }
        if (pre.count(t) == 0)
        {
            pre[t] = time;
            ++time;
            //std::cout << "at: " << s.top() << std::endl;
            if (users[t].get_depth() < 2)
            {
                for (auto neighbor: users[t].getFRIENDS())
                {
                    if (pre.count(neighbor) == 0)
                    {
                        s.push(neighbor);
                        //std::cout << "t: " << t << std::endl;
                        //std::cout << "neighbor: " <<neighbor << std::endl;
                        //std::cout << "Being pushed: " <<s.top() << std::endl;
                        users[neighbor].set_predecessor(t);
                        users[neighbor].set_depth(users[t].get_depth() + 1);
                        parent[neighbor] = t;
                    }
                }
            }
        }
        else
        {
            if(post.count(t) == 0)
            {
                post[t] = t;
                time++;
            }
            s.pop();
        }
    }
    std::unordered_map<int, int>::iterator it;
    for (it = list.begin(); it != list.end(); it++)
    {
        if (it->second == score)
        {
            common_friends.push_back(it->first);
        }
    }
    return common_friends;
}
std::vector<int> network::distance_user(int from, int &to, int distance)
{
    to = 0;
    std::stack<int> s;
    std::unordered_map<int, std::size_t> pre, post, parent;
    std::size_t time = 0;
    int start = users[from].getID();
    std::vector<int> path;
    s.push(start);
    while(!s.empty())
    {
        int t = s.top();
        //std::cout << s.top() << std::endl;
        if (pre.count(t) == 0)
        {
            pre[t] = time;
            ++time;
            if(users[t].get_depth() != distance)
            {
                for (auto neighbor: users[t].getFRIENDS())
                {
                    if (pre.count(neighbor) == 0)
                    {
                        s.push(neighbor);
                        users[neighbor].set_predecessor(t);
                        users[neighbor].set_depth(users[t].get_depth() + 1);
                        parent[neighbor] = t;
                    }
                }
            }
            else
            {
                to = t;
                path.push_back(to);
                while(users[t].get_predecessor() != -1)
                {
                    path.push_back(users[t].get_predecessor());
                    t = users[t].get_predecessor();
                }
                return path;
            }
        }
        else
        {
            if (post.count(t) == 0)
            {
                post[t] = t;
                time++;
            }
            s.pop();
        }
    }
    return path;
}
void network::addPost(std::string who, std::string message, int likes, int id)
{
    post *p = new post(id, message, get_id(who), likes);
    users[get_id(who)].addPost(p);
}
void network::addDM(std::string who, std::string message, int likes, int id, std::string recipient)
{
    directmessage *d = new directmessage{id, message, get_id(who), likes, get_id(recipient)};
    users[get_id(who)].addPost(d);
}
void network::displayPosts(std::string name, int howmany)
{
    for (int i = 0; i < num_users(); i++)
    {
        if (users[i].getNAME() == name)
        {
            std::cout << users[i].displayPosts(howmany) << std::endl;
        }
    }
}
void network::displayDM(std::string from, std::string to, int howmany)
{
    for (int i = 0; i < num_users(); i++)
    {
        if (users[i].getNAME() == from)
        {
            std::cout << users[i].displayDMs(get_id(to), from, howmany) << std::endl;
        }
    }
}
user network::get_user(std::size_t id)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getID() == id)
        {
            return users[i];
        }
    }
}
