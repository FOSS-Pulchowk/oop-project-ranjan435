#include <iostream>
#include <fstream>
#include <string>

using namespace std;


bool login(string username,string password){
   string un,pw;
   ifstream details("userdata/"+username+".txt");
   getline(details,un);
   getline(details,pw);
   details.close();
   if(username==un && password==pw ){
    // cout<<"You have successfully logged in !"<<endl;
     return true;
   }
   else{
     //cout<<"Account details don't match any !"<<endl;
     return false;
   }
}

// void reg(){
//   cout<<"Enter your account details"<<endl;
//   cout<<"Create a username:"<<endl;
//   string username;
//   cin>>username;
//   cout<<"Create a password:"<<endl;
//   string password;
//   cin>>password;
//
//   ofstream create_account;
//   create_account.open("userdata/"+username+".txt");
//   create_account<<username<<endl;
//   create_account<<password;
//   create_account.close();
// }
// void login_main(){
//   int choice;
//   cout<<"Enter your choice:\n1.Login\n2.Register\n3.Exit\n";
//   cin>>choice;
//   if(choice==1){
//     if(login()){
//       cout<<"You have successfully logged in !"<<endl;
//     }
//     else{
//       cout<<"Account details don't match any !"<<endl;
//     }
//   }
//   else if(choice==2){
//     reg();
//   }
//   else if(choice==3){
//     cout<<"Exiting!"<<endl;
//   }
//   else{
//     cout<<"Enter a valid choice!"<<endl;
//     continue;
//   }
// }
// }
