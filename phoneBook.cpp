#include "lib.h"


using namespace std;

// Function to add a friend to the phonebook vector of structs and save the phonebook into a file
void addFriend(vector<Friend> &phonebook, const string &filename){
  Friend friendInfo;
  bool flag = true;

  while(flag){
    cout << "Enter friend's name: ";
    cin.ignore();
    getline(cin, friendInfo.name);
    flag = false;

    for (const Friend &allfriend : phonebook){
      if(friendInfo.name == allfriend.name){
        cout << "Name alredy in use, choose another one." << endl;
        flag = true;
      }
    }
  }
  cout << "Enter friend's IPv6 address: ";
  cin >> friendInfo.ipv6Address;

  phonebook.push_back(friendInfo);//add friend struct to phonebook vector of structs

  ofstream outputFile(filename);
  if (!outputFile){
    cerr << "Error opening file for writing." << endl;
    return;
  }

  for (const Friend &friendInfo : phonebook){
    outputFile << friendInfo.name << " " << friendInfo.ipv6Address << endl;
  }

  outputFile.close();
  cout << "Friend added and phonebook saved to " << filename << endl;
}

// Function to display the list of friends
void displayFriends(const vector<Friend> &phonebook){
  if (phonebook.empty()){//check if you have any friends
    cout << "Phonebook is empty." << endl;
  }else{
    cout << "\nList of Friends:" << endl;
    for (const Friend &friendInfo : phonebook){//prnt out all your friends
      cout << "Name: " << friendInfo.name << "\tIPv6 Address: " << friendInfo.ipv6Address << endl;
    }
  }
}

  // Function to get a friend's IPv6 address by their name
string getFriendIp(const vector<Friend>& phonebook, const string& friendName) {
    for (const Friend& friendInfo : phonebook) {
        if (friendInfo.name == friendName) {
            return friendInfo.ipv6Address;
        }
    }
    return "Friend not found"; // Return a message if the friend is not in the phonebook
}

// Function to delete a friend from the phonebook and the text file
void deleteFriend(vector<Friend> &phonebook, const string &filename, const string &friendName)
{
  for (auto it = phonebook.begin(); it != phonebook.end(); ++it)
  {
    if (it->name == friendName)
    {
      phonebook.erase(it);
      break;
    }
  }

  ofstream outputFile(filename);
  if (!outputFile)
  {
    cerr << "Error opening file for writing." << endl;
    return;
  }

  for (const Friend &friendInfo : phonebook)
  {
    outputFile << friendInfo.name << " " << friendInfo.ipv6Address << endl;
  }

  outputFile.close();
  cout << "Friend '" << friendName << "' deleted from the phonebook and phonebook saved to " << filename << endl;
}
