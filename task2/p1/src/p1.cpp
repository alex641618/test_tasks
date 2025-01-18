#include <iostream>
#include <funcs.h>
#include <thread>
#include <condition_variable>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <csignal>
#include <cstring>

using namespace std;

bool cexit = false;

condition_variable cv;
mutex m;

string shared_buffer = "";

void sigint_handler(int sig) {
	cout << "\nPress Enter to exit...\n";
	cexit = true;
}

void first_thread(){
	string str;
	bool error_flag;

	cout << "program 1 thread 1: Enter lines:\n";

	while (!cexit){
		error_flag = false;
		getline(cin, str);
		
		if (cin.eof()) {
			rewind(stdin);
			cin.clear();
			continue;
		}

		if (str.length() > 64 and !cexit) {
			cout << "program 1 thread 1: Incorrect string!\n";
			continue;
		}

		for (int i = 0; i < str.length(); i++) {
			if ((str[i] < '0' or str[i] > '9') and !cexit) {
				cout << "program 1 thread 1: Incorrect string!\n";
				error_flag = true;
				break;
			}
		}

		if (error_flag) 
			continue;

		f1(&str);

		lock_guard<mutex> lock(m);
		shared_buffer = str;
		cv.notify_one();
	}
	
	lock_guard<mutex> lock(m);
	if (str == "")
		shared_buffer = "exit";
	cv.notify_one();
	
	cout << "program 1 thread 1: Exit\n";
}

void second_thread(){

	int p1_socket = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in p2_address;
    p2_address.sin_family = AF_INET;
    p2_address.sin_port = htons(7777);
    p2_address.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (!cexit) {
		unique_lock<mutex> ulock(m);
		cv.wait(ulock, 
				[] { return (shared_buffer != "") ? true : false; });

		string str = shared_buffer;
		shared_buffer = "";

		if (!cexit) {

			cout << "program 1 thread 2: " << str << endl;
			
			int f2_res = f2(str);

			string message = to_string(f2_res);
			sendto(p1_socket, message.c_str(), message.size(), 0, (struct sockaddr *)&p2_address, sizeof(p2_address));
		}

	}

	cout << "program 1 thread 2: Exit\n";
	close(p1_socket);
}

int main(int argc, char *argv[]) {
	
	struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigint_handler;
    sigset_t   set; 
    sigemptyset(&set);                                                             
    sigaddset(&set, SIGINT); 
    act.sa_mask = set;
    sigaction(SIGINT, &act, 0);

	thread th2(second_thread);
	thread th1(first_thread);

	th1.join();
	th2.join();

	return 0;
}