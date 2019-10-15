#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include <string>
#include <thread>
#include <bits/stdc++.h>
using namespace std;
typedef struct
{
int sock;
struct sockaddr address;
socklen_t addr_len;
} connection_t;

map<string ,vector<string>> m1;



int main()
{

	int sock = -1;
	struct sockaddr_in address;
	int port=80809;
	connection_t * connection;
	pthread_t thread;
	vector<int> v;





	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <= 0)
	{
		cout<<"error";
	}
	//cout<<m1["d.txt"].front();

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if(bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
	{
		fprintf(stderr, "error: cannot bind socket to port\n");
	}


        if (listen(sock, 5) < 0)
		{
			//fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
			//return -5;
		}
        while(1)
		{

			connection = (connection_t *)malloc(sizeof(connection_t));
			cout<<"OK"<<endl;
			connection->sock =accept(sock, &connection->address, &connection->addr_len);
			cout<<connection->sock;
{

			if (connection->sock <0)
			{
				free(connection);
			}
			int ch;
			recv(connection->sock,&ch,sizeof(int),0);
			if(ch==1)
			{
                char name[100];
                int port1;
                recv(connection->sock,name,100,0);
                recv(connection->sock,&port1,sizeof(int),0);
                string str=to_string(port);
                string fname(name);
                m1[fname].push_back(str);

			}
			else if(ch==2)
			{
			   char name[100];
			   int port;
			   recv(connection->sock,name,100,0);
			   string str(name);
			   int da[m1[str].size()];

			   for(int i=0;i<m1[str].size();i++)
			   {
                 da[i]=stoi(m1[str][i]);

			   }

                send(connection->sock,da,sizeof(int)*(m1[str].size()),0);

			}

		}
		close(connection->sock);
		}
return 0;
}

