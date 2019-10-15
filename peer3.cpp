
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
#include <vector>


using namespace std;
typedef struct
{
int sock;
struct sockaddr address;
socklen_t addr_len;
} connection_t;
typedef struct data
{
    int d[100];
    int port;
};
void trackerc()
{
    int sock1;
	int sock2;
	struct sockaddr_in server,client;
	unsigned int len;
	if((sock1=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
        perror("socket: ");
        exit(1);
	}
	server.sin_family=AF_INET;
	int p=80809;
	server.sin_port=htons(p);
	server.sin_addr.s_addr=INADDR_ANY;
	bzero(&server.sin_zero,8);
	len=sizeof(server);
	if(connect(sock1,(struct sockaddr*)&server,len)==-1)
	{
		perror("connect: ");
	 	exit(1);
	}
    char Buffer[50];
    string s1;
    char name[100];
    int port;
    int ch=1;
    cout<<"Enter the File name you need to upload";
    cin>>s1;
    cout<<"Enter the port number";
    cin>>port;
    send(sock1,&ch,sizeof(int),0);
    strcpy(name,s1.c_str());
    send(sock1,&port,sizeof(int),0);
    sleep(1);
    send(sock1,name,sizeof(char)*50,0);
    memset(Buffer,0,50);
    close(sock1);
}
void * thr(void *ptr)
{

     char buffer[45];
	 int len;
	 char c1[100];
	 connection_t *conn;
	 long addr =0;
	 FILE *f1;
	 char bu[50];
	 int flag;

	 if (!ptr) pthread_exit(0);
	 conn = (connection_t *)ptr;
	 cout<<"in process";
	 recv(conn->sock,&flag,sizeof(char),0);
	 if(flag==1)
	 {   FILE *f4;
         int present_chunk[4];
         int nchunk;
         send(conn->sock,present_chunk,sizeof(int)*nchunk,0);
    }
    f1=fopen(bu,"a+r");
    fseek(f1,0,SEEK_END);
	int size=ftell(f1);
	fseek(f1,0,SEEK_SET);
	send(conn->sock,&size,sizeof(int),0);
	cout<<size;
	int n;
	while((n=fread(bu,sizeof(char),50,f1))>0&&size>0)
	{
		cout<<bu[0];
		send(conn->sock,bu,n,0);
		size=size-n;
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
	int port=80806;
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
void* client(void *c)
{
    int sockfd;
	int sockcli;
	struct sockaddr_in server,client;
	unsigned int len;
	int *x=(int*)c;
	int p=*x;

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket: ");
		exit(1);
	}

	server.sin_family=AF_INET;
	server.sin_port=htons(p);
	server.sin_addr.s_addr=INADDR_ANY;
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
		int nchunk;
		int buf[3];
		memset(Buffer,0,50);
		recv(sockfd,&file_size,sizeof(int),0);
		cout<<file_size<<"\n ";
		recv(sockfd,&nchunk,sizeof(int),0);
		int chunk[nchunk];
        recv(sockfd,chunk,sizeof(int)*nchunk,0);

		int n;
        recv(sockfd,buf,sizeof(int)*3,0);
        int point=0;
        while((n=recv(sockfd,Buffer,50,0))>0 &&file_size>0)
        {
            if(point>2)
                break;
            fseek(fp,buf[point++]*50,SEEK_SET);
			fwrite(Buffer,sizeof(char),n,fp);
			file_size=file_size-n;
		}
		close(sockfd);
		fclose(fp);
}
int main()
{
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    pthread_t t4;
    pthread_t t5;
//make connection to tracker
while(1)
{
int ch;
cout<<"enter the choice"<<endl;
cout<<"1.upload//2.download";
cin>>ch;
switch(ch)
{
    case 1:cout<<"Upload";
           trackerc();
           break;
    case 2:string name;
           cout<<"Enter the name";
           cin>>name;

           int po[10]={80808,80807,80806};
           int a[3][5];

           data k[3];
           vector<vector<int>> v;
           for(int i=0;i<3;i++)
          {
              int sockfd;
              int sockcli;
              struct sockaddr_in server,client;
              unsigned int len;
              if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
              {
                 perror("socket: ");
                 exit(1);
              }
            int p=80809;
             server.sin_family=AF_INET;
             server.sin_port=htons(p);
             server.sin_addr.s_addr=INADDR_ANY;
             bzero(&server.sin_zero,8);
             len=sizeof(server);
             if(connect(sockfd,(struct sockaddr*)&server,len)==-1)
             {
                perror("connect: ");
                exit(1);
             }
             int gs=1;
             send(sockfd,&gs,sizeof(int),0);
             send(sockfd,name.c_str(),100,0);
             sleep(1);
             int nchunk;
             recv(sockfd,&nchunk,sizeof(int),0);
             int chunk[nchunk];
             recv(sockfd,chunk,sizeof(int)*nchunk,0);
             close(sockfd);
             //a[i]=chunk;

        int count=0;
        for(int i=0;i<4;i++)//put nuber of chunks here number of chunks are 5
        {
            for(int j=0 ;j<2 ;j++)//if at any peer chunk is not present
            {
                if(a[j][i]==0)
                count++;

            if(count==2)
            continue;

            while(1)//number of server
            {
                int ra=rand()%3;
                if(a[ra][i]==1)
                    {
                        v[j].push_back(i);
                        break;
                    }
                else
                {
                    continue;
                }
            }}
        }
}
    for(int i=0;i<v.size();i++)
    {
        for(int j=0;j<v[i].size();j++)
        {
                                     //store each element in 2-D array so that we can tranfer it to tracker
        }
    }
    pthread_create(&t1,0,server,(void *)NULL);
    for(int i=0;i<2;i++)
    {
        //pthread_create(&t2[i],0,client,(void *)po);
    }
    pthread_join(t1,NULL);
    for(int i=0;i<2;i++)
    {
       //pthread_join(t2[i],NULL);
    }

           break;
}
}
return 0;
}
