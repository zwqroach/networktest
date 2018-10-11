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
#include <stdio.h>
#include <stdlib.h>	// 调用系统命令
#include <unistd.h>	// 调用geteuid()函数

int main(void) {

	while(1){
	/*	// 检查权限
		char quanxian[8];
		if (geteuid() != 0) {
			sprintf(quanxian, "sudo -v");
			system(quanxian);
		}
	*/
		printf("\n\n\t👉 【1】 ping 测试 【2】查看在线主机  【3】配置华环智能光收\n\n\t"
					 "👉 【4】显示本机IP 【5】退出");
		printf("\n\n输入序号选择任务：");

		int Xuan_Ze = 0;
		while (Xuan_Ze != 1 && Xuan_Ze != 2 && Xuan_Ze != 3) {
			scanf(" %d", &Xuan_Ze);
			while (getchar() != '\n'); // 防止输入非法字符造成死循环
			switch (Xuan_Ze) {
				case 1:
					PingTest_();
					break;
				case 2:
					FindHost_();
					break;
				case 3:
					system("clear");
					HuahuanLight_();
					break;
				case 4:
					getLocalInfo_();
					main();
				case 5:
					return 0;
				default:
					printf("只接受数字１～５：");
					continue;
			}
		}
	}
}