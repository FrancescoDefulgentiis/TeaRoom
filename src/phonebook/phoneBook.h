#include "../main.h"
#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>

#define DB_PATH  "src/phonebook/phonebook.db"

using namespace std;

// Structure to represent a friend's information
struct Friend
{
  std::string name;
  std::string ipAddress;
};

class phoneBook{
  public:
  
    vector<Friend> phonebook;
    sqlite3* db;
    string filename = DB_PATH;
    phoneBook();
    void addFriend(const Friend &friendInfo);
    void displayFriends();
    string getFriendIp(const string& friendName);
    void deleteFriend( const string &friendName);
  private:
  void reloadfriendlist();
};

