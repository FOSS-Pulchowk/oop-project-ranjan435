#ifndef MORSE_CODE
#define MORSE_CODE

// #include <iostream>
// #include <string>
// #include <cstring>
// #include <cstdlib>
// #include <map>
//
// using namespace std;

string convert_character_to_morse(string message){
  //For morse code
  char alphabets[26],digits[10],upper_alpha[26];
  map<char,string> character_to_morse;
  map<string,char> morse_to_character;
  map<char,string *> character_to_morse_sound;

  int i;
  for(i=0;i<26;i++){
    alphabets[i]=i+97;
  }
  for(i=0;i<26;i++){
    upper_alpha[i]=i+65;
  }
  for(i=0;i<10;i++){
    digits[i]=i+48;
  }

  string morse_num[10]={
    "_____",
    ".____",
    "..___",
    "...__",
    "...._",
    ".....",
    "_....",
    "__...",
    "___..",
    "____."
  };
  // string sound_morse_num[10][5]={
  //   {dah,dah,dah,dah,dah},
  //   {dit,dah,dah,dah,dah},
  //   {dit,dit,dah,dah,dah},
  //   {dit,dit,dit,dah,dah},
  //   {dit,dit,dit,dit,dah},
  //   {dit,dit,dit,dit,dit},
  //   {dah,dit,dit,dit,dit},
  //   {dah,dah,dit,dit,dit},
  //   {dah,dah,dah,dit,dit},
  //   {dah,dah,dah,dah,dit}
  // };

  // string sound_morse_alpha[26][5]={
  //   {dit,dah},
  //   {dah,dit,dit,dit},
  //   {dah,dit,dah,dit},
  //   {dah,dit,dit},
  //   {dit},
  //   {dit,dit,dah,dit},
  //   {dah,dah,dit},
  //   {dit,dit,dit,dit},
  //   {dit,dit},
  //   {dit,dah,dah,dah},
  //   {dah,dit,dah},
  //   {dit,dah,dit,dit},
  //   {dah,dah},
  //   {dah,dit},
  //   {dah,dah,dah},
  //   {dit,dah,dah,dit},
  //   {dah,dah,dit,dah},
  //   {dit,dah,dit},
  //   {dit,dit,dit},
  //   {dah},
  //   {dit,dit,dah},
  //   {dit,dit,dit,dah},
  //   {dit,dah,dah},
  //   {dah,dit,dit,dah},
  //   {dah,dit,dah,dah},
  //   {dah,dah,dit,dit}
  // };

  string morse_alpha[26]={
    "._",
    "_...",
    "_._.",
    "_..",
    ".",
    ".._.",
    "__.",
    "....",
    "..",
    ".___",
    "_._",
    "._..",
    "__",
    "_.",
    "___",
    ".__.",
    "__._",
    "._.",
    "...",
    "_",
    ".._",
    "..._",
    ".__",
    "_.._",
    "_.__",
    "__..",
  };
  for(i=0;i<26;i++){
    character_to_morse[alphabets[i]]=morse_alpha[i];
    character_to_morse[upper_alpha[i]]=morse_alpha[i];
    morse_to_character[morse_alpha[i]]=alphabets[i];
    // character_to_morse_sound.insert(pair<char,string *>(alphabets[i],sound_morse_alpha[i]));
    // character_to_morse_sound.insert(pair<char,string *>(upper_alpha[i],sound_morse_alpha[i]));
  //  cout<<alphamorse[alphabets[i]]<<endl;
  }
  // for(i=0;i<26;i++){
  //   cout<<morse_to_character[morse_alpha[i]]<<endl;
  // //  cout<<alphamorse[alphabets[i]]<<endl;
  // }
  //Assigning digits their respective morse code values
  for(i=0;i<10;i++){
    character_to_morse[digits[i]]=morse_num[i];
    morse_to_character[morse_num[i]]=digits[i];
    // character_to_morse_sound.insert(pair<char,string *>(digits[i],sound_morse_num[i]));
  }

  //For morse code
  string conv_morse;
  for(int i=0;i<message.length();i++){
    char temp=message.at(i);
    //cout<<alphamorse[temp]<<" ";
    conv_morse+=character_to_morse[temp]+" ";
  }
  cout<<conv_morse<<endl;
  return conv_morse;
  // conv_morse.erase(0,conv_morse.length());
}

string convert_morse_to_character(string message){
  //For morse code
  char alphabets[26],digits[10],upper_alpha[26];
  map<char,string> character_to_morse;
  map<string,char> morse_to_character;
  map<char,string *> character_to_morse_sound;

  int i;
  for(i=0;i<26;i++){
    alphabets[i]=i+97;
  }
  for(i=0;i<26;i++){
    upper_alpha[i]=i+65;
  }
  for(i=0;i<10;i++){
    digits[i]=i+48;
  }

  string morse_num[10]={
    "_____",
    ".____",
    "..___",
    "...__",
    "...._",
    ".....",
    "_....",
    "__...",
    "___..",
    "____."
  };
  // string sound_morse_num[10][5]={
  //   {dah,dah,dah,dah,dah},
  //   {dit,dah,dah,dah,dah},
  //   {dit,dit,dah,dah,dah},
  //   {dit,dit,dit,dah,dah},
  //   {dit,dit,dit,dit,dah},
  //   {dit,dit,dit,dit,dit},
  //   {dah,dit,dit,dit,dit},
  //   {dah,dah,dit,dit,dit},
  //   {dah,dah,dah,dit,dit},
  //   {dah,dah,dah,dah,dit}
  // };

  // string sound_morse_alpha[26][5]={
  //   {dit,dah},
  //   {dah,dit,dit,dit},
  //   {dah,dit,dah,dit},
  //   {dah,dit,dit},
  //   {dit},
  //   {dit,dit,dah,dit},
  //   {dah,dah,dit},
  //   {dit,dit,dit,dit},
  //   {dit,dit},
  //   {dit,dah,dah,dah},
  //   {dah,dit,dah},
  //   {dit,dah,dit,dit},
  //   {dah,dah},
  //   {dah,dit},
  //   {dah,dah,dah},
  //   {dit,dah,dah,dit},
  //   {dah,dah,dit,dah},
  //   {dit,dah,dit},
  //   {dit,dit,dit},
  //   {dah},
  //   {dit,dit,dah},
  //   {dit,dit,dit,dah},
  //   {dit,dah,dah},
  //   {dah,dit,dit,dah},
  //   {dah,dit,dah,dah},
  //   {dah,dah,dit,dit}
  // };

  string morse_alpha[26]={
    "._",
    "_...",
    "_._.",
    "_..",
    ".",
    ".._.",
    "__.",
    "....",
    "..",
    ".___",
    "_._",
    "._..",
    "__",
    "_.",
    "___",
    ".__.",
    "__._",
    "._.",
    "...",
    "_",
    ".._",
    "..._",
    ".__",
    "_.._",
    "_.__",
    "__..",
  };
  for(i=0;i<26;i++){
    character_to_morse[alphabets[i]]=morse_alpha[i];
    character_to_morse[upper_alpha[i]]=morse_alpha[i];
    morse_to_character[morse_alpha[i]]=alphabets[i];
    // character_to_morse_sound.insert(pair<char,string *>(alphabets[i],sound_morse_alpha[i]));
    // character_to_morse_sound.insert(pair<char,string *>(upper_alpha[i],sound_morse_alpha[i]));
  //  cout<<alphamorse[alphabets[i]]<<endl;
  }
  // for(i=0;i<26;i++){
  //   cout<<morse_to_character[morse_alpha[i]]<<endl;
  // //  cout<<alphamorse[alphabets[i]]<<endl;
  // }
  //Assigning digits their respective morse code values
  for(i=0;i<10;i++){
    character_to_morse[digits[i]]=morse_num[i];
    morse_to_character[morse_num[i]]=digits[i];
    // character_to_morse_sound.insert(pair<char,string *>(digits[i],sound_morse_num[i]));
  }

  //For morse code
i=0;

//int start_positions[20];
//start_positions[0]=0;
//int count=1;
string result,input_morse,sub_string,sub_string_converted;
input_morse=message;
int start=0,end;
cout<<input_morse<<endl;

do{
  //temp_part=input_morse;
  //cout<<temp_part<<endl;
  i++;
  if(input_morse[i]==' ' || input_morse[i]=='\n' || input_morse[i]=='\0'){
    end=i-start;
    cout<<"end"<<end<<endl;
    cout<<"start"<<start<<endl;
    sub_string=input_morse.substr(start,end);
    cout<<"Sub string:"<<sub_string<<endl;
    sub_string_converted=string(1,morse_to_character[sub_string]);
    cout<<"Sub string converted:"<<sub_string_converted<<endl;
    result+=sub_string_converted;
    start =i+1;
   //cout<<morse_to_character[temp_part]<<endl;
  //   result=string(1,morse_to_character[temp_part]);
  //   //one_by_one=input_morse[i];
}

  cout<<i<<endl;
}while(input_morse[i]!='\0');
return result;
}


void convert_character_to_morse_sound(string message){
  //For morse code
  string dit="(speaker-test -t sine -f 1000 )& pid=$! ; sleep 0.1s ; kill -9 $pid";
  string dah="(speaker-test -t sine -f 1000 )& pid=$! ; sleep 0.3s ; kill -9 $pid";
  string small_gap="sleep 0.3s";
  string long_gap="sleep 1s";
  char alphabets[26],digits[10],upper_alpha[26];
  map<char,string> character_to_morse;
  map<string,char> morse_to_character;
  map<char,string *> character_to_morse_sound;

  int i;
  for(i=0;i<26;i++){
    alphabets[i]=i+97;
  }
  for(i=0;i<26;i++){
    upper_alpha[i]=i+65;
  }
  for(i=0;i<10;i++){
    digits[i]=i+48;
  }

  string morse_num[10]={
    "_____",
    ".____",
    "..___",
    "...__",
    "...._",
    ".....",
    "_....",
    "__...",
    "___..",
    "____."
  };

  string sound_morse_num[10][5]={
    {dah,dah,dah,dah,dah},
    {dit,dah,dah,dah,dah},
    {dit,dit,dah,dah,dah},
    {dit,dit,dit,dah,dah},
    {dit,dit,dit,dit,dah},
    {dit,dit,dit,dit,dit},
    {dah,dit,dit,dit,dit},
    {dah,dah,dit,dit,dit},
    {dah,dah,dah,dit,dit},
    {dah,dah,dah,dah,dit}
  };

  string sound_morse_alpha[26][5]={
    {dit,dah},
    {dah,dit,dit,dit},
    {dah,dit,dah,dit},
    {dah,dit,dit},
    {dit},
    {dit,dit,dah,dit},
    {dah,dah,dit},
    {dit,dit,dit,dit},
    {dit,dit},
    {dit,dah,dah,dah},
    {dah,dit,dah},
    {dit,dah,dit,dit},
    {dah,dah},
    {dah,dit},
    {dah,dah,dah},
    {dit,dah,dah,dit},
    {dah,dah,dit,dah},
    {dit,dah,dit},
    {dit,dit,dit},
    {dah},
    {dit,dit,dah},
    {dit,dit,dit,dah},
    {dit,dah,dah},
    {dah,dit,dit,dah},
    {dah,dit,dah,dah},
    {dah,dah,dit,dit}
  };

  string morse_alpha[26]={
    "._",
    "_...",
    "_._.",
    "_..",
    ".",
    ".._.",
    "__.",
    "....",
    "..",
    ".___",
    "_._",
    "._..",
    "__",
    "_.",
    "___",
    ".__.",
    "__._",
    "._.",
    "...",
    "_",
    ".._",
    "..._",
    ".__",
    "_.._",
    "_.__",
    "__..",
  };
  for(i=0;i<26;i++){
    character_to_morse[alphabets[i]]=morse_alpha[i];
    character_to_morse[upper_alpha[i]]=morse_alpha[i];
    morse_to_character[morse_alpha[i]]=alphabets[i];
    character_to_morse_sound.insert(pair<char,string *>(alphabets[i],sound_morse_alpha[i]));
    character_to_morse_sound.insert(pair<char,string *>(upper_alpha[i],sound_morse_alpha[i]));
  //  cout<<alphamorse[alphabets[i]]<<endl;
  }
  // for(i=0;i<26;i++){
  //   cout<<morse_to_character[morse_alpha[i]]<<endl;
  // //  cout<<alphamorse[alphabets[i]]<<endl;
  // }
  //Assigning digits their respective morse code values
  for(i=0;i<10;i++){
    character_to_morse[digits[i]]=morse_num[i];
    morse_to_character[morse_num[i]]=digits[i];
    character_to_morse_sound.insert(pair<char,string *>(digits[i],sound_morse_num[i]));
  }

  //For morse code
     for(i=0;i<message.length();i++){
       char temp=message.at(i);
       //cout<<alphamorse[temp]<<" ";

       for(int j=0;j<5;j++){
         system((character_to_morse_sound[temp])[j].c_str());
         system("sleep 0.3s");
       }
       system("sleep 0.3s");
     }
}























#endif
