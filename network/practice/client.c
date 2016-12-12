//
//  main.c
//  test_socket
//
//  Created by felix on 2016/12/7.
//  Copyright © 2016年 felix. All rights reserved.
//

//(1)声明一些必要的头文件并设置
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch = 'C';
    
    // （2）为客户创建一个套接字
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
//    使用套接字函数socket创建，不过传递的参数与网络套接字不同。域参数应该是PF_LOCAL或者PF_UNIX，而不能用PF_INET之类。本地套接字的通讯类型应该是SOCK_STREAM或SOCK_DGRAM，协议为默认协议。例如：
    
//   (3) 根据服务器的情况给套接字命名
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path,"server_socket");
    len = sizeof(address);
    
//    (4) 将我们的套接字连接到服务器的套接字
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("oops : client1");
        exit(1);
    }
    
//    (5)  现在就可以通过sockfd 进行读写操作了；
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n ",ch);
    close(sockfd);
    exit(0);
    
    return 0;
}
