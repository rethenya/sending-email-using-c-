#include <iostream>
#include <cstdio>
#include <winsock2.h>
#include <windows.h>
#pragma comment (lib, "ws2_32.lib")

 #include<unistd.h>
  

     using namespace std;
     const int VERSION_MAJOR = 1;
     const int VERSION_MINOR = 1;
     
char *dupcat(const char *s1, ...){
    int len;
    char *p, *q, *sn;
    va_list ap;
 
    len = strlen(s1);
    va_start(ap, s1);
    while (1) {
        sn = va_arg(ap, char *);
        if (!sn)
            break;
        len += strlen(sn);
    }
    va_end(ap);
 
    p = new char[len + 1];
    strcpy(p, s1);
    q = p + strlen(p);
 
    va_start(ap, s1);
    while (1) {
        sn = va_arg(ap, char *);
        if (!sn)
            break;
        strcpy(q, sn);
        q += strlen(q);
    }
    va_end(ap);
 
    return p;
}
 
//Headers
char from[]      = "sendermailid@gmail.com\r\n";
char to[]        = "rceivermailid@gmail.com\r\n";
char subject[]   = "TOP SECRET\r\n";
char data[]      = "This is secret data!\r\n";
 
     


     int main()
     {
        WSADATA WSData;
        SOCKET sock;
        struct sockaddr_in addr;

        WSAStartup(MAKEWORD(VERSION_MAJOR, VERSION_MINOR), &WSData);

        sock = socket(AF_INET, SOCK_STREAM, 0);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(465); 
        hostent *server_adress = gethostbyname("smtp.gmail.com");
        addr.sin_addr.s_addr = *((unsigned long *)server_adress->h_addr_list[0]);   
        int con = connect(sock, (struct sockaddr *) &addr, sizeof(addr));
        if (con==-1){
        	perror("connecting stream socket");
        	exit(1);
		}
		else{
			cout << "Connected\n";
	        printf("Sending data!\n");
	        char *headers = dupcat(from, to, subject, data,0);
	        int sendb = send(sock, headers, strlen(headers), 0);
	        if (sendb > 0){
			
	            printf("Email sent successfuly!\n");
	            //printf("%d",sendb);
	    }
	        else
	            printf("Problem sending email!\n");
    }
    
 
    close(sock);
			
		}
		
    

     
    
