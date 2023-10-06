#include "lib.h"

using namespace std;

int main(){
  string MyIp = Get_Public_ipv6();//retrieve my public ipv6
  
  //use a windows manager to create a window, and interact with it
  /*
  #code here where i get sender Ip(mine) and receiver Ip, also we agree on wich port to use
  */
  //when the interaction that causes the call to start happen, call Setup_Call to make it happen
  Setup_Call(MyIp, 8888, "::1", 8889);
}
