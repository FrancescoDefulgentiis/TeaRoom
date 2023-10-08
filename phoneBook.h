#include "lib.h"
using namespace std;

class phoneBook{
  public:
  
    vector<Friend> phonebook;
    sqlite3* db;
    string filename = "phonebook.db";
    phoneBook();
    void addFriend(const Friend &friendInfo);
    void displayFriends();
    string getFriendIp(const string& friendName);
    void deleteFriend( const string &friendName);
  private:
  void reloadfriendlist();
};

