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

#include "stated.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>    // 调用系统命令

/********************    ping测试    ********************/
void PingTest_(void) {

    int    frequency = 1000, bytes = 1000; // 设置ping包次数和字节大小默认值，如果要每次都清空输入值
                                           // 把它放到while循环里面即可
    int    a, b, c, d;
    char   len = 0, str[20], IpAddr[20], Ping_Test[45];
    time_t start, end;

    printf("\n输入要测试的地址：");
    while (Enter_() != '\n') {
        fgets(str, 20, stdin);
        len = strlen(str);
        if (str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        if (sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d)==4
            && a >= 0 && a <= 255 && b >= 0 && b <= 255
            && c >= 0 && c <= 255 && d >= 0 && d <= 255) {
            sprintf(IpAddr, "%d.%d.%d.%d", a, b, c, d);
            printf("\n默认发送1000次数据包、每包1000字节 按回车使用默认值\n");
            printf("数据包次数：");
            while (Enter_() != '\n') {
                scanf("%d", &frequency);
                if (0 >= frequency) {
                    printf("只能是大于0的数字：");
                    while (getchar() != '\n');
                }
            } while(getchar()!='\n');

            printf("数据包大小：");
            while (Enter_() != '\n') {
                scanf("%d", &bytes);
                if (bytes < 64 || bytes > 1005) {
                    printf("不能小于64或大于1004字节:");
                    while (getchar() != '\n');
                }
            } while(getchar()!='\n');

            if (strcmp(IpAddr, str) == 0) {
                time(&start); // 计时开始
                sprintf(Ping_Test, "sudo ping -c%d -s%d -i0.01 %s", frequency, bytes-8, IpAddr);
                system(Ping_Test);
                time(&end); // 计时结束
                int minute = (end - start) / 60;
                int second = (end - start) % 60;
                printf("\n测试完成，用时");
                if (minute <= 0) {
                    printf("%d秒。", second);
                }
                else {
                    if (second < 10) {
                        printf("%d分0%d秒。", minute, second);
                    }
                    else {
                        printf("%d分%d秒。", minute, second);
                    }
                }
            }
            else {
                printf("ip地址的格式不对！");
            }
            printf(" 按回车返回主菜单......\n输入新的地址继续测试：");
        }
        else {
            printf("该地址无效，再试一次：");
        }
    }
}