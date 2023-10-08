#include "phoneBook.h" 
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

phoneBook::phoneBook(){
  //open database file if it doesn't exist create one
  int rc = sqlite3_open(filename.c_str(),&db);
  if(rc){
    cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << endl << endl;
    sqlite3_close(db);
    return;
  }

  //create table if doesn't exist
  char *zErrMsg = 0;
  rc = sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS phonebook (name TEXT,ipv6Address TEXT,PRIMARY KEY (name, ipv6Address));",NULL,NULL,&zErrMsg);
  if(rc != SQLITE_OK){
    cerr << "Error creating table: " << zErrMsg << endl << endl;
    sqlite3_free(zErrMsg);
    sqlite3_close(db);
    return;
  }
  //load friend list from database
  reloadfriendlist();
}

// Function to display the list of friends
void displayFriends(const vector<Friend> &phonebook){
  if (phonebook.empty()){//check if you have any friends
    cout << "Phonebook is empty." << endl;
  }else{
    cout << "\nList of Friends:" << endl;
    int counter = 0;
    for (const Friend &friendInfo : phonebook){//prnt out all your friends
    counter++;
      cout <<counter <<") Name: " << friendInfo.name << "\tIPv6 Address: " << friendInfo.ipv6Address << endl;
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

void phoneBook::reloadfriendlist(){
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db,"SELECT * FROM phonebook;",-1,&stmt,NULL);
  if(rc != SQLITE_OK){
    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl << endl;
    sqlite3_close(db);
    return;
  }
  phonebook.clear();
  while((rc = sqlite3_step(stmt)) == SQLITE_ROW){
    Friend friendInfo;
    friendInfo.name = (char*)sqlite3_column_text(stmt,0);
    friendInfo.ipv6Address = (char*)sqlite3_column_text(stmt,1);
    phonebook.push_back(friendInfo);
  }
  if(rc != SQLITE_DONE){
    cerr << "Error retrieving data: " << sqlite3_errmsg(db) << endl << endl;
    sqlite3_close(db);
    return;
  }
}

void phoneBook::addFriend(const Friend &friendInfo){
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db,"INSERT INTO phonebook(name,ipv6Address) VALUES(?,?);",-1,&stmt,NULL);
  if(rc != SQLITE_OK){
    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl << endl;
    sqlite3_close(db);
    return;
  }
  sqlite3_bind_text(stmt,1,friendInfo.name.c_str(),-1,SQLITE_STATIC);
  sqlite3_bind_text(stmt,2,friendInfo.ipv6Address.c_str(),-1,SQLITE_STATIC);
  rc = sqlite3_step(stmt);
  if(rc != SQLITE_DONE){
    cerr << "Error inserting data: " << sqlite3_errmsg(db) << endl << endl;
    sqlite3_close(db);
    return;
  }

  this->reloadfriendlist();
  }

void phoneBook::displayFriends(){
    if (this->phonebook.empty()){//check if you have any friends
    cout << "Phonebook is empty." << endl;
  }else{
    cout << "\nList of Friends:" << endl;
    int counter = 0;
    for (const Friend &friendInfo : phonebook){//prnt out all your friends
    counter++;
      cout <<counter <<") Name: " << friendInfo.name << "\tIPv6 Address: " << friendInfo.ipv6Address << endl;
    }
  }

}

string phoneBook::getFriendIp(const string& friendName){
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db,"SELECT ipv6Address FROM phonebook WHERE name = ?;",-1,&stmt,NULL);
  if(rc != SQLITE_OK){
    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl << endl;
    sqlite3_close(db);
    return "Friend not found";
  }
  sqlite3_bind_text(stmt,1,friendName.c_str(),-1,SQLITE_STATIC);
  rc = sqlite3_step(stmt);
  if(rc != SQLITE_ROW){
    cerr << "Error retrieving data: " << sqlite3_errmsg(db) << endl << endl;
    sqlite3_close(db);
    return "Friend not found";
  }
  string ipv6Address = (char*)sqlite3_column_text(stmt,0);
}

void phoneBook::deleteFriend(const string& friendname){
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db,"DELETE FROM phonebook WHERE name = ?;",-1,&stmt,NULL);
  if (rc != SQLITE_OK){
    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl << endl;
    sqlite3_close(db);
    return;
  }
  sqlite3_bind_text(stmt,1,friendname.c_str(),-1,SQLITE_STATIC);
  rc = sqlite3_step(stmt);
  if(rc != SQLITE_DONE){
    cerr << "Error deleting data: " << sqlite3_errmsg(db) << endl << endl;
    sqlite3_close(db);
    return;
  }
  this->reloadfriendlist();
}
