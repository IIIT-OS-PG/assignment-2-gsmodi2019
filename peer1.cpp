
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>


using namespace std;
typedef struct
{
int sock;
struct sockaddr address;
socklen_t addr_len;
} connection_t;
void * thr(void * ptr)
{


	 char buffer[50];
	 int len;
	 char c1[100]="a.txt";
	 connection_t *conn;
	 long addr =0;
	 FILE *f1;
	 char bu[50];

	if (!ptr) pthread_exit(0);
	conn = (connection_t *)ptr;
	cout<<"in process";
	//recv(conn->sock,bu,sizeof(char),0);
    	f1=fopen("d.txt","r");
    	fseek(f1,0,SEEK_END);
	int size=ftell(f1);
	fseek(f1,0,SEEK_SET);
	int offset[3]={1,3,5};
	send(conn->sock,&size,sizeof(int),0);
	cout<<size;
	int n;
	int pt=0;
	send(conn->sock,&offset,sizeof(int)*3,0);
	while(1)
	{   if(pt<3)
	    fseek(f1,offset[pt++]*50,SEEK_SET);
	    else
	    break;
        if((n=fread(bu,sizeof(char),50,f1))>0 &&size>0)
        {
            cout<<bu[0];
            send(conn->sock,bu,n,0);
            size=size-n;
        }
        else
        {
            break;
        }
	}
	close(conn->sock);
    	fclose(f1);
	free(conn);
	pthread_exit(0);
}
void* server(void *o)
{
    int sock = -1;
	struct sockaddr_in address;
	int port=80808;
	connection_t * connection;
	pthread_t thread;

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <= 0)
	{
		cout<<"error";
	}

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
			else
			{

				pthread_create(&thread, 0, thr, (void *)connection);
				pthread_detach(thread);
			}
		}

    }
}
void* client(void *c)
{
    	int sockfd;
	int sockcli;
	struct sockaddr_in server,client;
	unsigned int len;
	while(1){
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: ");
		exit(1);
	}

	server.sin_family=AF_INET;

	int p;
	cout<<"enter port of the peer server you want to connect: ";
	cin>>p;
	server.sin_port=htons(p);
	server.sin_addr.s_addr=INADDR_ANY;
	bzero(&server.sin_zero,8);

	len=sizeof(server);
	if(connect(sockfd,(struct sockaddr*)&server,len)==-1)
	{
		perror("connect: ");
	 	exit(1);
	}

	FILE *fp=fopen("d.txt","r+a");
		char Buffer[50];
		int file_size;
		memset(Buffer,0,50);
		recv(sockfd,&file_size,sizeof(int),0);
		cout<<file_size<<"\n ";
		sleep(2);
		int n,i;
		recv(sockfd,&i,sizeof(int),0);
		i=file_size*(i-1);
		fseek(fp,i,SEEK_SET);



		while((n=recv(sockfd,Buffer,50,0))>0 &&file_size>0){
			//sleep(1);
		//	cout<<"bufsize "<<buf<<endl;
			fwrite(Buffer,sizeof(char),n,fp);
			//memset(Buffer,'\0',25);
			file_size=file_size-n;
			// if(file_size>0)
			//   recv(sockfd,&buf,sizeof(buf),0);
		}
		close(sockfd);
		fclose(fp);
	}





}
/*void *download()
{   int port=80881;
	int sock = -1;
	struct sockaddr_in address;
	struct hostent * host;
	int len;


	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <= 0)
	{
		cout<<"error";
	}
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	host = gethostbyname("rent_01");
	if (!host)
	{
		fprintf(stderr, "error: unknown host\n");

	}
	memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);

	if (connect(sock, (struct sockaddr *)&address, sizeof(address)))
	{
		fprintf(stderr, " error: cannot connect to host \n");

	}
	len = strlen("gw.txt");
	FILE *fp;
	fp=fopen("t.txt","r");
	char bu[45];
	fseek(fp,0,SEEK_END);
	int size=ftell(fp);
	fseek(fp,0,SEEK_SET);
	send(sock,&size,sizeof(int),0);
	int n;
	while((n=fread(bu,sizeof(char),45,fp))>0&&size>0)
	{
		send(sock,bu,n,0);
		size=size-n;
	}
	fclose(fp);
	close(sock);

}
*/


int main()
{
    pthread_t t1;
    pthread_t t2;
    //string p=argv[1];
    //int port=atoi(argv[1]);
pthread_create(&t1,0,server,(void *)NULL);

pthread_create(&t2,0,client,(void *)NULL);


		pthread_join(t1,NULL);
		pthread_join(t2,NULL);
return 0;
}
