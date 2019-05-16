#include <gtkmm.h>
#include <iostream>
#include "login.h"
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <map>
#include "morse_code.h"
// #include "tcp_client.h"
// #include "tcp_client.h"


class new_window:public Gtk::Window{
public:
  std::string message;
  std::string User;
  new_window();
  virtual ~new_window();
  void chat_box();
  void morse_window();
  void register_clicked();
  bool message_receive();
  void activate_register();
  void run_background_socket();
  void temporary();
  void supply_message_to_server();
  void upload_file();
  void morse_input_to_char();
  void char_input_to_morse();
  void morse_play_function();
  void morse_close_function();

  int sock;
  int port;
  string ipAddress;
  char buf[4096];
  struct sockaddr_in hint;
  std::string user_name;
  std::string temp_char_input;
  //solely for menu bar
  // void on_action_file_new();
protected:
  void on_new_close();
  void send_message();
  void fill_buffers();
  Gtk::Button m_button,*send_button,*b_open;
  Gtk::Label *label;
  Gtk::Entry *text;
  Gtk::Entry *entry_pass,*register_pass;
  Gtk::Entry *entry_user,*register_user;
  void login_check();
  Gtk::Box *box,*morse_box,*file_box;
  Glib::RefPtr<Gtk::TextBuffer> morse_refTextBuffer1,morse_refTextBuffer2;
  Gtk::TextView *morse_TextView,*char_TextView;
  Gtk::ScrolledWindow *morse_scrolledwindow,*char_scrolledwindow;
  Gtk::Entry *char_entry;
  Gtk::Entry *morse_entry;

  //solely for menu
  // Glib::RefPtr <Gtk::Builder>m_refBuilder;
  // Glib::RefPtr <Gio::SimpleActionGroup>m_refActionGroup;


  class ModelColumns:public Gtk::TreeModel::ColumnRecord{
  public:
    ModelColumns(){
       add(col_name);
      add(col_text);
    }
   Gtk::TreeModelColumn<Glib::ustring>col_name;
    Gtk::TreeModelColumn<Glib::ustring>col_text;
  };
  ModelColumns columns;
  Glib::RefPtr<Gtk::ListStore>refTreeModel;
};


new_window::new_window():
  m_button("Close"){

    // Glib::ListHandle<Widget*> childList = this->get_children();
    // Glib::ListHandle<Widget*>::iterator it = childList.begin();
    //  while (it != childList.end())
    //   {
    //       Gtk::Container::remove(*(*it));
    //       it++;
    //   }

    set_default_size(600,400);
    set_position(Gtk::WIN_POS_CENTER);
    set_title("Socket Chat");
    Gtk::Box *vbox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,0));
    add(*vbox);
    Gtk::Label *frame_label=Gtk::manage(new Gtk::Label);
    // vbox->add(*frame_label);
    frame_label->set_markup("<big><span color='green'>Login to chat</span></big>");
    Gtk::Grid *login_grid=Gtk::manage(new Gtk::Grid);
    Gtk::Label *user=Gtk::manage(new Gtk::Label);
    Gtk::Label *pass=Gtk::manage(new Gtk::Label);
    Gtk::Label *reg_ister=Gtk::manage(new Gtk::Label);
    Gtk::Image *Image=Gtk::manage(new Gtk::Image);
    Image->set("icon.png");
    user->set_text("Username:");
    pass->set_text("Password:");
    reg_ister->set_markup("Not a member yet?");
    // reg_ister->signal_activate_link().connect(sigc::mem_fun(*this,&new_window::register_clicked));
    entry_user=Gtk::manage(new Gtk::Entry);
    entry_pass = Gtk::manage(new Gtk::Entry);
    vbox->add(*login_grid);
    login_grid->set_border_width(10);
    login_grid->set_row_spacing(10);
    login_grid->attach(*frame_label,1,0,1,1);
    login_grid->attach(*Image,2,0,1,1);
    login_grid->attach(*user,1,1,1,1);
    login_grid->attach(*entry_user,2,1,1,1);
    login_grid->attach(*pass,1,2,1,1);
    entry_pass->set_visibility(false);
    login_grid->attach(*entry_pass,2,2,1,1);
    entry_user->set_hexpand(true);
    Gtk::Separator *separate = Gtk::manage(new Gtk::Separator);
    login_grid->attach(*separate,0,3,4,1);
    login_grid->attach(*reg_ister,1,5,1,1);
    Gtk::Button *b_register=Gtk::manage(new Gtk::Button("Register"));
    login_grid->attach(*b_register,2,5,1,1);
    Gtk::Button *b_open=Gtk::manage(new Gtk::Button("Login"));
    login_grid->attach(*b_open,2,4,1,1);
    login_grid->attach(m_button,2,6,1,1);
    b_open->signal_clicked().connect(sigc::mem_fun(*this,&new_window::login_check));

    b_register->signal_clicked().connect(sigc::mem_fun(*this,&new_window::register_clicked));
    // add(m_button);
    m_button.signal_clicked().connect(sigc::mem_fun(*this,&new_window::on_new_close));
    // chat_box();
    // show_all();
    vbox->show_all();


  }

void new_window::on_new_close(){
  hide();
}

void new_window::chat_box(){
  //run_background_socket();

  Glib::ListHandle<Widget*> childList = this->get_children();
  Glib::ListHandle<Widget*>::iterator it = childList.begin();
   while (it != childList.end())
    {
        Gtk::Container::remove(*(*it));
        it++;
    }
  Gtk::Box *vbox=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,0));
  set_title("Chat Box");
  set_default_size(400,400);
  add(*vbox);
  Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
  grid->set_border_width(10);
  grid->set_row_spacing(10);
  vbox->add(*grid);
  Gtk::TreeView *treeview=Gtk::manage(new Gtk::TreeView);
  treeview->set_hexpand(true);
  treeview->set_vexpand(true);
  Gtk::ScrolledWindow *scroll = Gtk::manage(new Gtk::ScrolledWindow);
  scroll->add(*treeview);
  grid->attach(*scroll,0,0,3,1);
  refTreeModel=Gtk::ListStore::create(columns);
  treeview->set_model(refTreeModel);
 treeview->append_column("Username",columns.col_name);
  treeview->append_column("Message",columns.col_text);
  label=Gtk::manage(new Gtk::Label);
  label->set_markup("<big>Enter message: </big>");
  grid->attach(*label,0,1,1,1);
  text=Gtk::manage(new Gtk::Entry);
  send_button=Gtk::manage(new Gtk::Button("Send"));
  Gtk::Button *btn = Gtk::manage(new Gtk::Button("Quit"));
  Gtk::Button *btn_morse=Gtk::manage(new Gtk::Button("Morse Chat"));
  // Gtk::Button *refresh=Gtk::manage(new Gtk::Button("Refresh"));
  Gtk::Button *btn_file_upload=Gtk::manage(new Gtk::Button("Upload file"));


  send_button->signal_clicked().connect(sigc::mem_fun(*this,&new_window::send_message));
  text->signal_activate().connect(sigc::mem_fun(*this,&new_window::send_message));
  btn->signal_clicked().connect(sigc::mem_fun(*this,&new_window::on_new_close));
  btn_morse->signal_clicked().connect(sigc::mem_fun(*this,&new_window::morse_window));
  // refresh->signal_clicked().connect(sigc::mem_fun(*this,&new_window::message_receive));
  btn_file_upload->signal_clicked().connect(sigc::mem_fun(*this,&new_window::upload_file));
  Glib::signal_timeout().connect( sigc::mem_fun(*this, &new_window::message_receive),100);


  grid->attach(*text,0,2,2,1);
  grid->attach(*send_button,2,2,2,1);
  grid->attach(*btn,2,4,1,1);
  grid->attach(*btn_morse,1,3,1,1);
  // grid->attach(*refresh,1,4,1,1);
  grid->attach(*btn_file_upload,2,3,1,1);
  vbox->show_all();




}

  new_window::~new_window(){
    std::cout<<"new_window destruction"<<std::endl;
  }

  void new_window::send_message(){
    User=entry_user->get_text();
    message=text->get_text();
    Gtk::TreeModel::Row row = *(refTreeModel->append());
    row[columns.col_name]=User;
    row[columns.col_text]=message;
    text->set_text("");
    std::cout<<message<<std::endl;
    std::string userInput=user_name+" @ "+message;
    int sendRes=send(sock,userInput.c_str(),userInput.size()+1,0);
    if(sendRes==-1){
      std::cout<<"Didnt send to server!!";
    }
//    Glib::signal_timeout().connect( sigc::mem_fun(*this, &new_window::message_receive),100 );

  }

  int main(int argc,char *argv[]){
    Glib::RefPtr<Gtk::Application>app=Gtk::Application::create(argc,argv);
    new_window newWindow;
    newWindow.run_background_socket();
    app->run(newWindow);

  }
  //
  // void new_window::on_action_file_new(){
  //   std::cout<<"A menu item was selected."<<std::endl;
  // }

  void new_window::register_clicked(){

    Glib::ListHandle<Widget*> childList = this->get_children();
    Glib::ListHandle<Widget*>::iterator it = childList.begin();
     while (it != childList.end())
      {
          Gtk::Container::remove(*(*it));
          it++;
      }
    // Gtk::MessageDialog dg(*this,"yesssss");
    // Gtk::Button *b = Gtk::manage(new Gtk::Button("hello"));
    // dg.add_button(*b,1);
    // dg.run();
      set_title("Register account");
      set_default_size(40,40);
    box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,0));
    add(*box);
    Gtk::Grid *register_grid = Gtk::manage(new Gtk::Grid);
    box->add(*register_grid);
    register_grid->set_border_width(20);
    register_grid->set_row_spacing(30);
    register_user=Gtk::manage(new Gtk::Entry);
    register_pass=Gtk::manage(new Gtk::Entry);
    Gtk::Label *l_user=Gtk::manage(new Gtk::Label);
    Gtk::Label *l_pass=Gtk::manage(new Gtk::Label);
    Gtk::Button *register_button=Gtk::manage(new Gtk::Button("Register"));
    // Gtk::Button *register_close=Gtk::manage(new Gtk::Button("Close"));
    l_user->set_text("Enter the username:");
    l_pass->set_text("Enter the password:");
    register_grid->attach(*l_user,0,0,2,1);
    register_grid->attach(*l_pass,0,1,2,1);
    register_grid->attach(*register_user,3,0,4,1);
    register_grid->attach(*register_pass,3,1,4,1);
    register_grid->attach(*register_button,3,2,2,1);
    box->show_all();
    register_button->signal_clicked().connect(sigc::mem_fun(*this,&new_window::activate_register));


    // std::cout<<"Registered"<<std::endl;
    // Gtk::MessageDialog dialog(*this,"This is a dialog");
    // dialog.run();

  }

  void new_window::morse_window(){
    Glib::ListHandle<Widget*> childList = this->get_children();
      Glib::ListHandle<Widget*>::iterator it = childList.begin();
     while (it != childList.end())
      {
          Gtk::Container::remove(*(*it));
          it++;
      }
    set_title("Morse Code Conversion");
    set_default_size(300,300);
    morse_box=Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,0));
    morse_entry=Gtk::manage(new Gtk::Entry);
    char_entry=Gtk::manage(new Gtk::Entry);
    Gtk::Grid  *morse_grid=Gtk::manage(new Gtk::Grid);
    Gtk::Label *morse_input_label=Gtk::manage(new Gtk::Label("Enter you morse chat in .(dit) or -(dah) form"));
    Gtk::Label *char_input_label=Gtk::manage(new Gtk::Label("Enter characters to convert it into morse form"));
    Gtk::Label *morse_output_label=Gtk::manage(new Gtk::Label("The equivalent character is-"));
    Gtk::Label *char_output_label=Gtk::manage(new Gtk::Label("The equivalent morse is-"));
    Gtk::Button *morse_send=Gtk::manage(new Gtk::Button("Enter"));
    Gtk::Button *char_send=Gtk::manage(new Gtk::Button("Enter"));
    Gtk::Button *morse_play=Gtk::manage(new Gtk::Button("Play Morse"));
    Gtk::Button *morse_close=Gtk::manage(new Gtk::Button("Close Morse"));
    Gtk::Separator *morse_separator = Gtk::manage(new Gtk::Separator);
    add(*morse_box);
    morse_grid->set_row_spacing(10);
    morse_grid->set_border_width(60);
    morse_box->add(*morse_grid);
    morse_entry->set_hexpand(true);
    char_entry->set_hexpand(true);
    morse_TextView=Gtk::manage(new Gtk::TextView);
    char_TextView=Gtk::manage(new Gtk::TextView);
    morse_scrolledwindow=Gtk::manage(new Gtk::ScrolledWindow);
    char_scrolledwindow=Gtk::manage(new Gtk::ScrolledWindow);


    morse_scrolledwindow->add(*morse_TextView);
    // morse_scrolledwindow->get_shadow_type();
    char_scrolledwindow->add(*char_TextView);
    morse_scrolledwindow->set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    char_scrolledwindow->set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);

    // morse_entry->get_entry();
    morse_grid->attach(*morse_input_label,0,0,2,1);
    morse_grid->attach(*morse_entry,0,1,1,1);
    morse_grid->attach(*morse_send,2,1,1,1);
    morse_grid->attach(*morse_output_label,0,2,2,1);
    morse_grid->attach(*morse_scrolledwindow,0,3,1,1);
    morse_grid->attach(*morse_separator,0,4,2,1);
    morse_grid->attach(*char_input_label,0,5,2,1);
    morse_grid->attach(*char_entry,0,6,1,1);
    morse_grid->attach(*char_send,2,6,1,1);
    morse_grid->attach(*char_output_label,0,7,2,1);
    morse_grid->attach(*char_scrolledwindow,0,8,1,1);
    morse_grid->attach(*morse_play,0,9,1,1);
    morse_grid->attach(*morse_close,0,10,1,1);
    show_all();

    //signals
    fill_buffers();
    morse_send->signal_clicked().connect(sigc::mem_fun(*this,&new_window::morse_input_to_char));
    char_send->signal_clicked().connect(sigc::mem_fun(*this,&new_window::char_input_to_morse));
    morse_play->signal_clicked().connect(sigc::mem_fun(*this,&new_window::morse_play_function));
    morse_close->signal_clicked().connect(sigc::mem_fun(*this,&new_window::morse_close_function));
  }

  void new_window::login_check(){
    std::string temp_user;
    std::string temp_pass;
    temp_user=entry_user->get_text();
    temp_pass=entry_pass->get_text();

     user_name=temp_user;
     std::cout<<user_name<<endl;
    if(login(temp_user,temp_pass)){
      chat_box();
    }
    else{
      Gtk::MessageDialog dlg(*this,"Not registered account");
      dlg.set_secondary_text("Please do register first");
      dlg.run();
    }
  }

  void new_window::activate_register(){
    std::string a=register_user->get_text();
    std::string b=register_pass->get_text();
    ofstream create_account;
    create_account.open("userdata/"+a+".txt");
    create_account<<a<<endl;
    create_account<<b;
    create_account.close();
    box->hide();
    auto *ns=new new_window();
    ns->run_background_socket();
    ns->show();//closes the whole process when register window is closed


  }

  void new_window::run_background_socket(){
    sock=socket(AF_INET,SOCK_STREAM,0);
    port=9034;
    ipAddress="127.0.0.1";

    hint.sin_family =AF_INET;
    hint.sin_port=htons(port);
    inet_pton(AF_INET,ipAddress.c_str(),&hint.sin_addr);
    // if(sock==-1){
    //   return -1;
    // }
    // fdmax=sock;
    //Create  hint structure for the server while connecting
    //int port=atoi(argv[1]);

    //Connect to the server on the socket
    int connectRes=connect(sock,(sockaddr *)&hint,sizeof(hint));
    // if (connectRes == -1 ){
    //   return 1;
    // ;
  }

  bool new_window::message_receive(){
    // memset(buf,0,4096);
    std::string tmp_string;
    while(recv(sock,buf,4096,MSG_DONTWAIT)>0){
      Gtk::TreeModel::Row row = *(refTreeModel->append());
      tmp_string=string(buf);
      int a=tmp_string.find(" @ ");
      std::string user=tmp_string.substr(0,a);
      std::string msg=tmp_string.substr(a+2,tmp_string.length());
      row[columns.col_text]=msg;
      row[columns.col_name]=user;
    }
    return true;
    }
    //Display response
    //cout<<string(buf,0,bytesReceived)<<"\r\n";
    // if(bytesReceived==-1){
    //   // cout<<"Error getting response!";
    //   // return false;
    // }
    // else
    // return true;

    void new_window::upload_file(){
      Gtk::FileChooserDialog file_dialog("Please choose a file",
          Gtk::FILE_CHOOSER_ACTION_OPEN);
      file_dialog.set_transient_for(*this);
      file_dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
      file_dialog.add_button("_Open", Gtk::RESPONSE_OK);
      file_dialog.run();
      std::string filename=file_dialog.get_filename();
      std::cout<<filename<<std::endl;
      }

      void new_window::fill_buffers(){
        morse_refTextBuffer1=Gtk::TextBuffer::create();

        morse_refTextBuffer2=Gtk::TextBuffer::create();
      }

      void new_window::morse_input_to_char(){
        std::string temp_morse_input =morse_entry->get_text();
        std::string temp_char_output= convert_morse_to_character(temp_morse_input);
        morse_refTextBuffer1->set_text(temp_char_output);
        morse_TextView->set_buffer(morse_refTextBuffer1);
      }

      void new_window::char_input_to_morse(){
        temp_char_input =char_entry->get_text();
        std::string temp_morse_output= convert_character_to_morse(temp_char_input);
        morse_refTextBuffer2->set_text(temp_morse_output);
        char_TextView->set_buffer(morse_refTextBuffer2);

      }

      // void new_window::char_input_to_morse_sound(){
      //   std::string temp_char_input =char_entry->get_text();
      //   std::string temp_morse_output= convert_character_to_morse(temp_char_input);
      //   morse_refTextBuffer2->set_text(temp_morse_output);
      //   char_TextView->set_buffer(morse_refTextBuffer2);
      // }


      // void new_window::initialize_morse(){
      //
      // }

      void new_window::morse_play_function(){
        convert_character_to_morse_sound(char_entry->get_text());
         // std::cout<<"text->get_text()";

      }

      void new_window::morse_close_function(){
        chat_box();
        // std::cout<<"text->get_text()";
      }
