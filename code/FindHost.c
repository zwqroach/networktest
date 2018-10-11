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
#include <stdlib.h>

/********************	查找在线主机	********************/
void FindHost_(void) {

	int  a = 0, b = 0, c = 0;
	char len = 0;
	char segment[20], intranet[20];

	printf("\n输入网段，不包含地址：");
	while (fgets(segment, 20, stdin)) {
		len = strlen(segment);
		if (segment[len - 1] == '\n') {
			segment[len - 1] = '\0';
		}

		if (sscanf(segment, "%d.%d.%d", &a, &b, &c)==3
			&& a >= 0 && a <= 255 && b >= 0 && b <= 255 && c >= 0 && c <= 255) {
			sprintf(intranet, "%d.%d.%d", a, b, c);
			break;
		}
		else {
			printf("网段不正确，重新输入：");
		}
	}

	int min = 1, max = 254;
	printf("默认查找范围 1～254 ：");
	while (Enter_() != '\n') {
		scanf("%d %d", &min, &max);
		if (min < 1 )	   {
			printf("起始地址小于  1	 ：");
		}
		else if (min > 254) {
			printf("起始地址大于 254	：");
		}
		else if (max < 1)   {
			printf("结束地址小于  1	 ：");
		}
		else if (max > 254) {
			printf("结束地址大于 254	：");
		}
		else if (min > max) {
			printf("起始地址大于结束地址：" );
		}
		else {
			break;
		}
	} while (getchar()!='\n');

	time_t start, end;
	int	Lian_Ji = 0, Tuo_Ji = 0;
	char   HostIP[20], Cha_Zhao[50];
	// 查找主机并统计消耗时间
	printf("\n");
	time(&start);
	for (int addr = min; addr <= max; addr++) {
		sprintf(HostIP, "%s.%d", intranet, addr);
		sprintf(Cha_Zhao, "ping -c1 -w1 -i0.2 %s > /dev/null", HostIP);
		if (WEXITSTATUS(system(Cha_Zhao)) == 0) {	// WEXITSTATUS()函数 判断ping命令的返回值
			printf("	已上线ip >  %-15s\n", HostIP);
			Lian_Ji++;
		}
		else {
			// printf("	%-15s ···离线\n", HostIP);
			Tuo_Ji++;
		}
	}
	system(Cha_Zhao);
	time(&end);
	int minute = (end - start) / 60;
	int second = (end - start) % 60;
	printf("\n----- %s.%d～%d -----\n", intranet, min, max);
	printf("用时");
	if (minute <= 0) {
		printf("%d秒", second);
	}
	else {
		if (second < 10) {
			printf("%d分0%d秒", minute, second);
		}
		else {
			printf("%d分%d秒", minute, second);
		}
	}
	printf("  查找%d个主机，%d个在线，%d个离线", Lian_Ji+Tuo_Ji, Lian_Ji, Tuo_Ji);
}