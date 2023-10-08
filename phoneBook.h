#include "lib.h"
using namespace std;

class phoneBook{
  public:
    vector<Friend> phonebook;
    string filename = "phonebook.txt";
    void addFriend();
    void displayFriends();
    string getFriendIp(const string& friendName);
    void deleteFriend( const string &friendName);
  private:
  void reloadfriendlist();
  void savephonebook();
};

