#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include "post.h"
class user
{
public:
    //defualt construcutor
    user();
    //primary construcutor
    user(std::string newname, int newyear, int newzip);
    //add friend function
    void add_friend(int id);
    //delete firend function
    void delete_friend(int id);
    //set id function for vector location
    void set_id(std::size_t newid);
    //set depth function for bfs and disjoint
    void set_depth(int d);
    //set predecessor function for bfs and disjoint
    void set_predecessor(std::size_t p);
    //adds post to user
    void addPost(post *p);
    //method that takes in a int and returns a string
    std::string displayPosts(int howmany);
    //method that takes in user ID, string and howmany int and returns dms between them
    std::string displayDMs(int who, std::string name, int howmany);
    //depth field
    int depth;
    //predecessor
    int predecessor;
    //collection of acessor methods
    std::size_t getID() const;
    std::string getNAME() const;
    std::size_t getYEAR() const;
    std::size_t getZIP() const;
    std::vector<std::size_t> getFRIENDS() const;
    std::size_t get_predecessor() const;
    int get_depth() const;
    int get_messages() const;
private:
    //id field
    std::size_t id;
    //name field
    std::string name;
    //year field
    int year;
    //zip field
    int zip;
    //firend list field
    std::vector<std::size_t> friends;
    std::vector<post*> messages_;
};
#endif
