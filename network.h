#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <vector>
#include <iostream>

class network
{
public:
    //default constructor
    network();
    //add user method, takes in a user object
    void add_user(const user &newUser);
    //add connection method, takes in two names and adds a connection between then
    int add_connection(std::string s1, std::string s2);
    //does the same as the previous method execpt removes it
    int remove_connection(std::string s1, std::string s2);
    //print data
    void print_data();
    //print friends
    void print_friends(int id);
    //Vector of shortest path (from -> to)
    std::vector<int> shortest_path(int from, int to);
    //Vector of vectors, for groups of seperate friends in graph
    std::vector<std::vector<int>> groups();
    //sugget friend function, takes in a ID of a user and a refrence to a score and returns a vecotr of users with the highest score
    std::vector<int> suggest_friends(int who, int& score);
    //distance from user function, takes in starting user, reference to a destination user, and a distance variable
    std::vector<int> distance_user(int from, int &to, int distance);
    //displays posts
    void displayPosts(std::string name, int howmany);
    //displays DMs
    void displayDM(std::string from, std::string to, int howmany);
    //adds posts
    void addPost(std::string who, std::string message, int likes, int id);
    //adds DMS
    void addDM(std::string who, std::string message, int likes, int id, std::string recipient);
    //returns id, given name
    int get_id(std::string name);
    //returns name, given id
    std::string get_name(int id);
    //reads in data from file
    int read_friends(char *fname);
    //reads posts from file
    int read_posts(char *fname);
    //writes data from the file
    int write_friends(char *fname);
    //returns number of users
    std::size_t num_users();
    //returns user object when given id #
    user get_user(std::size_t id);

private:
    //vector of user objects, holds data for network
    std::vector<user> users;
};

#endif
