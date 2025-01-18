#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <csignal>
#include <cstring>
#include <funcs.h>

using namespace std;

short cexit = 0;

void sigint_handler(int sig) {
    cout << "\nExit from program 2\n";
    cexit = 1;
}

int main()
{
    
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigint_handler;
    sigset_t   set; 
    sigemptyset(&set);                                                             
    sigaddset(&set, SIGINT); 
    act.sa_mask = set;
    sigaction(SIGINT, &act, 0);

    sockaddr_in p1_address;

    int p2_socket = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(7777);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(p2_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    char buffer[4] = { '\0' };
    int fromlen = sizeof(p1_address);

    while (!cexit) {

        int ret = recvfrom(p2_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&p1_address, (socklen_t*)&fromlen);

        if (ret != 0 and !cexit) {
            string f3_res = f3(buffer);

            if (f3_res == "истина"){
                cout << "program 2: Message from program 1: " << buffer << endl;
            } else {
                cout << "program 2: Error: incorrect data!\n";
            }

            for (int i = 0; i < sizeof(buffer); i++){
                buffer[i] = '\0';
            }


        }
    }

    close(p2_socket);

    return 0;
}