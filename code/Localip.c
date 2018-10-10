/*
 * -*- tab-width: 4 -*- coding: utf-8 -*-
 * Copyright (C)：roach<zwq_133@163.com>
 * Author and Maintainer：roach & QQ：56663757 & Email：zwq_133@163.com
 * https://github.com/zwqroach/networktest

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

 * -*- 标签宽度：4 -*- 编码: utf-8 -*-
 * 版权所有 (C)：roach<zwq_133@163.com>
 * 作者和维护：roach & QQ：56663757 & Email：zwq_133@163.com
 * 仓库地址：  https://github.com/zwqroach/networktest

 * 此程序是免费软件：您可以重新分发和/或修改；
 * 根据GNU通用公共许可证的条款发布;
 * 自由软件基金会，许可证的第3版，或任何更新的版本。

 * 该程序的分发是希望它有用，但没有任何担保;
 * 甚至没有暗示的保证适销性或特定用途的适用性。
 * 祥见GNU通用公共许可证了解更多详情。

 * 您应该已收到GNU通用公共许可证的副本以及该计划。
 * 如果没有，请参阅<http://www.gnu.org/licenses/>。
*/

#include <stdio.h>
#include <string.h>
#include <net/if.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <ctype.h>

int getLocalInfo_(void) {
    int fd;
    int interfaceNum = 0;
    struct ifreq buf[16];
    struct ifconf ifc;
    struct ifreq ifrcopy;
    char mac[18] = {0};
    char ip[32] = {0};
    char broadAddr[32] = {0};
    char subnetMask[32] = {0};

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {

        perror("socket");
        close(fd);
        return -1;
    }

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = (caddr_t)buf;
    if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc)) {

        interfaceNum = ifc.ifc_len / sizeof(struct ifreq); // 获取所有接口
        printf("\n网络接口：%d个\n", interfaceNum-1);        // 打印接口数量，排除本地环回
        while (interfaceNum-- > 0) {
            // 排除本地环回
            if(strcmp(buf[interfaceNum].ifr_name,"lo") == 0) {

                continue;
            }

            printf("设备名称: %s\n", buf[interfaceNum].ifr_name);

            //忽略未运行的接口
            ifrcopy = buf[interfaceNum];
            if (ioctl(fd, SIOCGIFFLAGS, &ifrcopy)) {

                printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);
                close(fd);
                return -1;
            }

            //获取MAC地址
            if (!ioctl(fd, SIOCGIFHWADDR, (char *)(&buf[interfaceNum]))) {

                memset(mac, 0, sizeof(mac));
                snprintf(mac, sizeof(mac), "%02X:%02X:%02X:%02X:%02X:%02X",
                    (unsigned char)buf[interfaceNum].ifr_hwaddr.sa_data[0],
                    (unsigned char)buf[interfaceNum].ifr_hwaddr.sa_data[1],
                    (unsigned char)buf[interfaceNum].ifr_hwaddr.sa_data[2],
                    (unsigned char)buf[interfaceNum].ifr_hwaddr.sa_data[3],
                    (unsigned char)buf[interfaceNum].ifr_hwaddr.sa_data[4],
                    (unsigned char)buf[interfaceNum].ifr_hwaddr.sa_data[5]);
                printf("MAC 地址: %s\n", mac);
            }
            else {

                printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);
                close(fd);
                return -1;
            }

            //获取IP地址
            if (!ioctl(fd, SIOCGIFADDR, (char *)&buf[interfaceNum])) {

                snprintf(ip, sizeof(ip), "%s",
                (char *)inet_ntoa(((struct sockaddr_in *)&(buf[interfaceNum].ifr_addr))->sin_addr));
                printf("IP 地 址: %s\n", ip);
            }
            else {

                printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);
                close(fd);
                return -1;
            }

            //获取子网掩码
            if (!ioctl(fd, SIOCGIFNETMASK, &buf[interfaceNum])) {

                snprintf(subnetMask, sizeof(subnetMask), "%s",
                (char *)inet_ntoa(((struct sockaddr_in *)&(buf[interfaceNum].ifr_netmask))->sin_addr));
                printf("子网掩码: %s\n", subnetMask);
            }
            else {

                printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);
                close(fd);
                return -1;
            }

            /*//获取此接口的广播地址
            if (!ioctl(fd, SIOCGIFBRDADDR, &buf[interfaceNum])) {

                snprintf(broadAddr, sizeof(broadAddr), "%s",
                    (char *)inet_ntoa(((struct sockaddr_in *)&(buf[interfaceNum].ifr_broadaddr))->sin_addr));
                printf("广播地址: %s\n", broadAddr);
            }
            else {

                printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);
                close(fd);
                return -1;
            } */
        }
    }
    else {
        printf("ioctl: %s [%s:%d]\n", strerror(errno), __FILE__, __LINE__);
        close(fd);
        return -1;
    }

    close(fd);

    // 获取默认网关
    FILE *fp;
    char bufb[512];
    char cmd[128];
    char gateway[30];
    char *tmp;

    strcpy(cmd, "ip route");
    fp = popen(cmd, "r");
    if(NULL == fp) {

        perror("popen error");
        return -1;
    }
    while(fgets(bufb, sizeof(bufb), fp) != NULL) {

        tmp = bufb;
        while(*tmp && isspace(*tmp))
            tmp++;
        if(strncmp(tmp, "default", strlen("default")) == 0)
            break;
    }
    sscanf(bufb, "%*s%*s%s", gateway);
    printf("默认网关：%s\n", gateway);
    pclose(fp);
}