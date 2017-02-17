#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int num_ips=0,num_ip=0,num_ports=0,num_port=0;
/*=======函数声明==================*/
void help();
void clear();
void ip(char* ip);
void ips(char* ip1,char* ip2);
void ps(char *p1,char *p2);
void p(char *p1);
void make();
void myip(char *ip);
/*===================================*/
 int main(int argc,char** argv){
    FILE *num=fopen("./num","r");
    fscanf(num,"%d+%d+%d+%d",&num_ips,&num_ip,&num_ports,&num_port);
    fclose(num);
 	//判断命令
    if(!strcmp(argv[1],"-clear")){
        if(argc!=2){
            help();
            return 0;
        }
        clear();
    }else if(!strcmp(argv[1],"-ips")){
        if(argc!=4){
            help();
            return 0;
        }
        ips(argv[2],argv[3]);
    }else if(!strcmp(argv[1],"-ip")){
        if(argc!=3){
            help();
            return 0;
        }
        ip(argv[2]);
    }else if(!strcmp(argv[1],"-ps")){
        if(argc!=4){
            help();
            return 0;
        }
        ps(argv[2],argv[3]);
    }else if(!strcmp(argv[1],"-p")){
        if(argc!=3){
            help();
            return 0;
        }
        p(argv[2]);
    }else if(!strcmp(argv[1],"-make")){
        if(argc!=2){
            help();
            return 0;
        }
        make();
    }else if(!strcmp(argv[1],"-clear")){
    	clear();
    }else if(!strcmp(argv[1],"-myip")){
        if(argc!=3){
            help();
            return 0;
        }
        myip(argv[2]);
    } else{
        help();
    }
    num=fopen("./num","w");
    fprintf(num,"%d+%d+%d+%d",num_ips,num_ip,num_ports,num_port);
    fclose(num);
    return 0;
 }

 /*============================函数定义区===============*/

 /*======clear()=======
 格式化variables.h,并清空linshi
 ====================*/
 void clear(){
    FILE *v=fopen("./variables.h","w");
    FILE *l=fopen("./linshi","w");
    fprintf(v,"#include <string.h>\n int num_ips,num_ip,num_ports,num_port; \n char myip[16]; \n struct {\n char start[16], end[16];\n }ips[255];\n char ip[255][16];\n struct {\n int start, end;\n }ports[255];\n int port[255];");
    fprintf(l,"/*\tO.O\t*/");
    fclose(v);
    fclose(l);
    num_ip=0;
    num_ips=0;
    num_port=0;
    num_ports=0;
 }

/*======help()==============
        显示帮助信息
===========================*/
void help(){
	printf("-myip [ip] \t 设置scaner收集到的数据的接受端IP，即get文件运行的主机的IP\n-clear\t\t格式化variables.h的数据\n-ips [ip1] [ip2]\t在variables.h里的ips数组添加start=[ip1] end=[ip2]的一组数据 (通过num_ips来记录当前ips数组记录的个数)\n-ip [ip]\t\t在variables.h里的ip数组添加数值为[ip]的数据\n-ps [port1] [port2]\t在variables.h的ports数组添加start=[port1] end=[port2]的一组数据(通过num_ports来记录当前ports数组记录的个数)\n-p [port]\t\t在variables.h里的port数组添加数值为[port]的数据\n-make\t\t做最后操作,比如将num_ip与num_port的最终数值写入variables.h,然后调用makefile生成扫描器\n具体使用方法请阅读Readme.md");
	return;
}
/*====ips()============
向variables.h里写ips数组，下面几个函数类似
strcpy(ips[%d].start,%s);
=======================*/
//通过改写init函数,并让scaner在运行时调用init函数来完成变量值的配置,虽然这个方法是绞尽脑汁冥思苦想才想出的解决方案(毕竟赋值等语句在.h文件中是不起作用的,因为.h不会运行吗),但是我总感觉这不是最好的方法(用C++的话应该会有更好的方法)
void ips(char* ip1,char* ip2){
	FILE *fp=fopen("./linshi","a+");//先暂时都写在linshi这个文件中,最后在make的时候全部写进variables.h（虽然我也想直接写进variables。h但在写测试文件地时候，总不能达到要求，只好先这样了.....
    fprintf(fp,"\n strcpy(ips[%d].start,\"%s\");",num_ips,ip1);
    fprintf(fp,"\n strcpy(ips[%d].end,\"%s\");",num_ips,ip2);
    num_ips++;
    fclose(fp);
}

/*====ip()========

==================*/

void ip(char* ip){
    FILE *fp=fopen("./linshi","a+");
    fprintf(fp,"\n strcpy(ip[%d],\"%s\");",num_ip, ip);
    num_ip++;
    fclose(fp);
}
/*=====ps()======

================*/
void ps(char *p1,char *p2){
    FILE *fp=fopen("./linshi","a+");
    fprintf(fp,"\n ports[%d].start=%s;",num_ports,p1);
    fprintf(fp,"\n ports[%d].end=%s;",num_ports,p2);
    num_ports++;
    fclose(fp);
}

/*======p()======

=================*/
void p(char *p1){
    FILE *fp=fopen("./linshi","a+");
    fprintf(fp,"\n port[%d]=%s;",num_port,p1);
    num_port++;
    fclose(fp);
}

/*=======make()====

================*/
void make(){
    FILE *v=fopen("./variables.h","a+");
    FILE *l=fopen("./linshi","r");
    char st[100];
    fprintf(v,"\n void init_(){\n");
    fprintf(v,"\n num_ips=%d;\n num_ip=%d;\n num_ports=%d;\n num_port=%d;",num_ips,num_ip,num_ports,num_port);
    while(!feof(l)){
        fprintf(v,"%s\n",fgets(st,100,l));
    }
    fprintf(v,"}");
    fclose(v);
    fclose(l);
    //用system调用makefile....
    system("make");
}

/*======myip()=========
设置记录文件传回的ip地址
======================*/
void myip(char *ip){
    FILE *fp=fopen("./linshi","a+");
    fprintf(fp,"\n strcpy(myip,\"%s\");",ip);
    fclose(fp);
}

