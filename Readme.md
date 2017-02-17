# Readme

## 功能介绍

扫描目标内网中制定IP的指定端口是否开放,并将扫描数据传回

## 使用方法

请按照以下步骤进行相关配置:

1. ./maker -clear	

   对各配置文档(variables.h num linshi)进行初始化,第一步请务必运行此命令

2. ./maker -myip (ip)

   ip处填写自己的IP地址,或者想要接受记录数据的主机的IP地址,用于记录数据的回传

3. ./maker -ips  (ip1) (ip2)

   设置一组待扫描IP地址,请确保ip1小于ip2,否则将跳过本组扫描.

   ./maker -ip (ip)

   填写一个待扫描的IP

   ./maker -ps (port1) (port2)

   填写一组待扫描的端口范围,请确保port1小于port2,否则将跳过本组端口的扫描

   ./maker -p (port)

   填写一个待扫描的端口

4. ./maker -make

   编译生成scaner

5. 将scaner传到已拿下的对方主机

6. 在本地运行./get  然后在对方主机运行scaner

7. 在本地查看./jilu文件,并记得删除scaner,对方主机上的jilu文件以及各种痕迹

## 注意

在运行过一次./ maker -make后,一定要运行过一次./maker -clear并重新配置后再运行./maker -make,否则将造成scaner编译错误