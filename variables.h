#include <string.h>
 int num_ips,num_ip,num_ports,num_port; 
 char myip[16]; 
 struct {
 char start[16], end[16];
 }ips[255];
 char ip[255][16];
 struct {
 int start, end;
 }ports[255];
 int port[255];
 void init_(){

 num_ips=0;
 num_ip=1;
 num_ports=0;
 num_port=1;/*	O.O	*/

 port[0]=2333;
 strcpy(ip[0],"127.0.0.1");
 strcpy(myip,"127.0.0.1");
}
