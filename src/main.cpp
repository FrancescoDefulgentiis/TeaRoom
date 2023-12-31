#include "main.h"
#include "phonebook/phoneBook.h"
#include "networking/Networking.h"
#include "networking/Protocols/GetIp.h"

using namespace std;

int main(){
  string MyIp = Get_Public_ipv4();//retrieve my public ipv4

  phoneBook phonebook;

  int choice;
  string friendName, friendIp;
  do{
    cout << "\nPhonebook Menu:" << endl;
    cout << "1. Add a friend and save phonebook" << endl;
    cout << "2. Display Friends" << endl;
    cout << "3. Call a friend" << endl;
    cout << "4. delete a friend from the phonebook" << endl;
    cout << "5. share your contact" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    system("clear");

    Friend friendInfo;

    switch (choice){
    case 1:
      //addFriend(phonebook, filename);
      std::cout << "Enter friend's name: ";
      cin>>friendInfo.name;
      cout << "Enter friend's ip address: ";
      cin>>friendInfo.ipAddress;
      phonebook.addFriend(friendInfo);
      break;
    case 2:
      //displayFriends(phonebook);
      phonebook.displayFriends();
      cin.ignore();
      getline(cin, friendName);
      break;
    case 3:
      cout << "Enter the name or the number the friend to call: ";
      cin.ignore();
      phonebook.displayFriends();
      getline(cin, friendInfo.name);
      friendInfo.ipAddress = phonebook.getFriendIp(friendInfo.name);
      startConnection(friendInfo.ipAddress);
      break;
    case 4:
      cout << "Enter the name or the number the friend to delete: ";
      cin.ignore();
      phonebook.displayFriends();
      getline(cin, friendName);
      phonebook.deleteFriend(friendName);
      break;
    case 5:
      cout << "Hi!, my ip address is: " << MyIp << endl;
      cin.ignore();
      getline(cin, friendName);
      break;
    case 6:
      cout << "Exiting program." << endl;
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  } while (choice != 6);

  return 0;
}
