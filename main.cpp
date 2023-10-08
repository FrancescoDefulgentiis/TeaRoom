#include "lib.h"

using namespace std;

int main(){
  string MyIp = Get_Public_ipv6();//retrieve my public ipv6

  vector<Friend> phonebook;//define a vector of structs to store friends
  string filename = "phonebook.txt";

  // Load existing phonebook from the file (if any)
  ifstream inputFile(filename);
  if (inputFile){
    string name, ipv6Address;
    while (inputFile >> name >> ipv6Address){
      Friend friendInfo;
      friendInfo.name = name;
      friendInfo.ipv6Address = ipv6Address;
      phonebook.push_back(friendInfo);
    }
    inputFile.close();
  }

  int choice;
  string friendName, friendIp;
  do{
    system("clear");
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
    switch (choice){
    case 1:
      addFriend(phonebook, filename);
      break;
    case 2:
      displayFriends(phonebook);
      cin.ignore();
      getline(cin, friendName);
      break;
    case 3:
      cout << "insert the name or the number of the friend you want to call: ";
      cin.ignore();
      displayFriends(phonebook);
      getline(cin, friendName);
      friendIp = getFriendIp(phonebook, friendName);
      Setup_Call(MyIp, PORT_NUMBER, friendIp, PORT_NUMBER+1);
      break;
    case 4:
      cout << "Enter the name or the number the friend to delete: ";
      cin.ignore();
      displayFriends(phonebook);
      getline(cin, friendName);
      deleteFriend(phonebook, filename, friendName);
      break;
    case 5:
      cout << "Hi!, my ipv6 is: " << MyIp << endl;
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
  //use a windows manager to create a window, and interact with it
  /*
  #code here where i get sender Ip(mine) and receiver Ip, also we agree on wich port to use
  */
  //when the interaction that causes the call to start happen, call Setup_Call to make it happen
}
