1. First compile the files (first go into codes and executing files folder)
-for server enter the following command
	g++ tcp_server.cpp -o server 
-for main file enter the following command
	g++ test.cc -o test `pkg-config gtkmm-3.0 --cflags --libs`
(Reminder the gtkmm library needs to be installed before)
(Go through this https://www.gtkmm.org/en/download.html to install gtkmm library in different os)

2.Run the server first by:-
	./server
3.Run the main file for clients by :-
	./test
4.Can execute line 3 in multiple terminal by different clients
5.First register your account and then login.
6.Start chatting and have fun with MORSE Converter.
