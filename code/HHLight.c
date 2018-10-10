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
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  // 调用chmod()函数，赋予文件执行权限

/********************    配置光收    ********************/
void HuahuanLight_() {

	int  mode = 0;
	char proceed = 'y';
	char Cr_De_File[21];

	printf("\n\n\t * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t*  华环光收自动配置程序，适用型号： 1101S4N 11000S4P  *\n");
	// printf("\t*\t\t\t\t    1101S4N 11000S4P  *\n");
	printf("\t * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");

	printf("\n     👉 【1】单次配置一个设备 【2】连续配置多个设备 【3】返回主菜单\n\n选择配置方式：");
	while (mode != 1 && mode != 2) {
		scanf("%d", &mode);
		while (getchar() != '\n');
		switch (mode) {
			case 1:
					Deploy_();
					printf("\n\n\t 配 置 完 成 ，请 链 接 对 应 业 务 端 口 进 行 测 试\n");
					printf("\n按回车返回主菜单");
					PingTest_();
					break;
			case 2:
					do{
						Deploy_();
						printf("\n按回车返回主菜单\n按‘y’配置下一个：");
						scanf("%c", &proceed);
					} while (proceed == 'y' || proceed == 'Y');
					break;
			case 3:
					system("clear");
					return;
			default:
					printf("选择一种方式：");
		}
	}
}

/********************    配置光收    ********************/
void Deploy_(void) {

	int Xuan_Ze = 0;
	char Cr_De_File[21];

	Login_();
	printf("\n\n\t👉 【1】配置普通模式   【2】配置业务vlan   【3】 修改设备ip");

	printf("\n\n输入序号选择配置方式：");
	while (Xuan_Ze != 1 && Xuan_Ze != 2 && Xuan_Ze != 3) {

		scanf(" %d", &Xuan_Ze);
		while (getchar() != '\n');
		switch (Xuan_Ze) {
			case 1:
					Ordinary_();
					break;
			case 2:
					UpVlan_();
					break;
			case 3:
					AlterIp_();
					sprintf(Cr_De_File, "./TempFiles");
					system(Cr_De_File);
					sprintf(Cr_De_File, "rm -rf ./TempFiles");
					system(Cr_De_File);
					// printf("\n\t\t地址修改完成，修改本机ip后重新链接设备\n\n");
					return;
			default:
					printf("只接受数字１～３，请重试：");
		}
	}

	Save_();
	printf("开始配置，请等待下一条提示······\n\n");
	sprintf(Cr_De_File, "./TempFiles");
	system(Cr_De_File);
	sprintf(Cr_De_File, "rm -rf ./TempFiles");
	system(Cr_De_File);
}

/*    创建自动登录    */
void Login_(void) {

	char Dev_Ip[20] = "192.192.4.2";
 /*
	char len = 0;
	int  a, b, c, d;

	printf("\n     telnet默认地址：%s\t请确保设备'NM'接口已正确链接"
		   "\n     本机ip设置：192.192.4.5~254/24\n", Dev_Ip);
	printf("\n按‘回车’键使用默认地址   ↓ ·新的ip· ↓\n若设备地址已变更，输入：");
	while (Enter_() != '\n') {

		fgets(Dev_Ip, 20, stdin);
		len = strlen(Dev_Ip);
		if (Dev_Ip[len - 1] == '\n') {

			Dev_Ip[len - 1] = '\0'; // 末位的换行符替换为结束符
		}

		if(sscanf(Dev_Ip, "%d.%d.%d.%d", &a, &b, &c, &d)==4
			&& a >= 0 && a <= 255 && b >= 0 && b <= 255
			&& c >= 0 && c <= 255 && d >= 0 && d <= 255) {

			sprintf(Dev_Ip, "%d.%d.%d.%d", a, b, c, d); // 把格式化的数据写入字符串 Dev_Ip
			break;
		}
		else {

			printf("ip地址错误，请重新输入：");
		}
	}
 */
	TempFiles = fopen("./TempFiles", "w+");		// 创建脚本文件
	chmod("./TempFiles", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH); // 赋予读、写、执行权限
	fprintf(TempFiles, "#!/usr/bin/expect\nset timeout -1\nspawn telnet %s\n", Dev_Ip);
	fprintf(TempFiles, "expect \"Username:\" {send \"admin\\r\"}\nexec sleep 0.5\n");
	fprintf(TempFiles, "expect \"Password:\" {send \"admin\\r\"}\nexec sleep 0.5\n");
	fprintf(TempFiles, "expect \"CLI>\" {send \"enable\\r\"}\nexec sleep 0.5\n");
	fprintf(TempFiles, "expect \"Password:\" {send \"HuaHuan_.com\\r\"}\nexec sleep 0.5\n");
	fprintf(TempFiles, "expect \"CLI#\" {send \"configure\\r\"}\nexec sleep 0.5\n");
	fprintf(TempFiles, "expect \"CLI(config)#\" {send \"no ip address dhcp\\r\"}\nexec sleep 0.5\n");
	fclose(TempFiles);
}

/*    配置为普通模式    */
void Ordinary_(void) {

	TempFiles = fopen("./TempFiles", "a");
	fprintf(TempFiles, "expect \"CLI(config)#\" {send \"no vlan all\\r\"}\nexec sleep 0.5\n");
	fprintf(TempFiles, "expect \"CLI(config)#\" {send \"vlan mode disable\\r\"}\nexec sleep 0.5\n");
	fclose(TempFiles);
}

/*    配置vlan    */
void UpVlan_(void) {

	int Dian_Kou1 = 0, Dian_Kou2 = 0, Dian_Kou3 = 0;
	printf("\n提示：若无需配置tx2和tx3，按‘回车’键跳过\n");
	do {

		printf("\n配置业务vlan —> 电口tx１：");
		scanf(" %d", &Dian_Kou1);
		while (getchar() != '\n');
		if (Dian_Kou1 < 2 || Dian_Kou1 > 4094) {

			printf("电口１只能输入【2～4094】之间的数字\n");
		}
	} while (Dian_Kou1 < 2 || Dian_Kou1 > 4094);

	printf("配置业务vlan —> 电口tx２：");
	while (Enter_() != '\n') {

		scanf(" %d", &Dian_Kou2);
		if (Dian_Kou2 < 2 || Dian_Kou2 > 4094) {

			printf("电口２只能输入【2～4094】之间的数字\n\n配置业务vlan —> 电口tx２：");
			while (getchar() != '\n');
		}
		else {

			break;
		}

	} while (getchar() != '\n'); // 防止跳过电口２同时跳过电口３

 /*
	// 写死管理
	char Pei_Zhi = 'y';
	printf("按ｙ配置电口tx３管理vlan：");
	while (Enter_() != '\n') {

		scanf(" %c", &Pei_Zhi);
		if (Pei_Zhi == 'y' || Pei_Zhi == 'Y') {

			Dian_Kou3 = 0000;
			break;
		}
		else {

			printf("输入的‘ｙ’不对，把输入法设置为半角，或切换为英文状态\n\n按ｙ配置电口tx３管理vlan：");
			while (getchar() != '\n');
		}

	}while (getchar() != '\n');
 */

	// 填写管理
	printf("配置管理vlan —> 电口tx３：");
	while (Enter_() != '\n') {

	scanf(" %d", &Dian_Kou3);
		if (Dian_Kou3 < 2 || Dian_Kou3 > 4094) {

			printf("电口３只能输入【2～4094】之间的数字\n\n配置管理vlan —> 电口tx３：");
			while (getchar() != '\n');
		}
		else {

			break;
		}
	} while (getchar() != '\n');

	// 写入vlan
	TempFiles = fopen("./TempFiles", "a");
	fprintf(TempFiles, "expect \"CLI(config)#\" {send \"vlan mode 802.1Q\\r\"}\nexec sleep 0.9\n"); // 保留启用vlan，以防vlan被禁用
	fprintf(TempFiles, "expect \"CLI(config)#\" {send \"no vlan all\\r\"}\nexec sleep 0.9\n");
	if (Dian_Kou1) {

		fprintf(TempFiles, "expect \"CLI(config)#\" {send \"vlan %d\\r\"}\nexec sleep 0.9\n", Dian_Kou1);
	}
	if (Dian_Kou2) {

		fprintf(TempFiles, "expect \"CLI(config)#\" {send \"vlan %d\\r\"}\nexec sleep 0.9\n", Dian_Kou2);
	}
	if (Dian_Kou3) {

		fprintf(TempFiles, "expect \"CLI(config)#\" {send \"vlan %d\\r\"}\nexec sleep 0.9\n", Dian_Kou3);
	}

	// 启用光口,设置为 trunk 模式
	fprintf(TempFiles, "expect \"CLI(config)#\" {send \"interface fx1\\r\"}\nexec sleep 0.9\n");
	fprintf(TempFiles, "expect \"CLI(config-if.fx.1)#\" {send \"speed 100\\r\"}\nexec sleep 0.9\n");
	fprintf(TempFiles, "expect \"CLI(config-if.fx.1)#\" {send \"port link-type trunk\\r\"}\nexec sleep 0.9\n");
	if (Dian_Kou1) {

		fprintf(TempFiles, "expect \"CLI(config-if.fx.1)#\" {send \"port trunk add-vlan %d\\r\"}\nexec sleep 0.9\n", Dian_Kou1);
	}
	if (Dian_Kou2) {

		fprintf(TempFiles, "expect \"CLI(config-if.fx.1)#\" {send \"port trunk add-vlan %d\\r\"}\nexec sleep 0.9\n", Dian_Kou2);
	}
	if (Dian_Kou3) {

		fprintf(TempFiles, "expect \"CLI(config-if.fx.1)#\" {send \"port trunk add-vlan %d\\r\"}\nexec sleep 0.9\n", Dian_Kou3);
	}
	fprintf(TempFiles, "expect \"CLI(config-if.fx.1)#\" {send \"exit\\r\"}\nexec sleep 0.9\n");

	// 启用电口,设置为 access 模式
	if (Dian_Kou1) {

		fprintf(TempFiles, "expect \"CLI(config)#\" {send \"interface tx1\\r\"}\nexec sleep 0.9\n");
		fprintf(TempFiles, "expect \"CLI(config-if.tx.1)#\" {send \"port link-type access\\r\"}\nexec sleep 0.9\n");
		fprintf(TempFiles, "expect \"CLI(config-if.tx.1)#\" {send \"port pvid %d\\r\"}\nexec sleep 0.9\n", Dian_Kou1);
		fprintf(TempFiles, "expect \"CLI(config-if.tx.1)#\" {send \"exit\\r\"}\nexec sleep 0.9\n");
	}
	if (Dian_Kou2) {

		fprintf(TempFiles, "expect \"CLI(config)#\" {send \"interface tx2\\r\"}\nexec sleep 0.9\n");
		fprintf(TempFiles, "expect \"CLI(config-if.tx.2)#\" {send \"port link-type access\\r\"}\nexec sleep 0.9\n");
		fprintf(TempFiles, "expect \"CLI(config-if.tx.2)#\" {send \"port pvid %d\\r\"}\nexec sleep 0.9\n", Dian_Kou2);
		fprintf(TempFiles, "expect \"CLI(config-if.tx.2)#\" {send \"exit\\r\"}\nexec sleep 0.9\n");
	}
	if (Dian_Kou3) {

		fprintf(TempFiles, "expect \"CLI(config)#\" {send \"interface tx3\\r\"}\nexec sleep 0.9\n");
		fprintf(TempFiles, "expect \"CLI(config-if.tx.3)#\" {send \"port link-type access\\r\"}\nexec sleep 0.9\n");
		fprintf(TempFiles, "expect \"CLI(config-if.tx.3)#\" {send \"port pvid %d\\r\"}\nexec sleep 0.9\n", Dian_Kou3);
		fprintf(TempFiles, "expect \"CLI(config-if.tx.3)#\" {send \"exit\\r\"}\nexec sleep 0.9\n");
		fprintf(TempFiles, "expect \"CLI(config)#\" {send \"management-vlan %d\\r\"}\nexec sleep 0.9\n", Dian_Kou3);
	}
	fclose(TempFiles);
}

/*    保存配置并退出    */
void Save_(void) {

	TempFiles = fopen("./TempFiles", "a");
	fprintf(TempFiles, "expect \"CLI(config)#\" {send \"write config-to curr\\r\"}\nexec sleep 1.5\n");
	fprintf(TempFiles, "expect \"Are you sure to write the configure to flash ? (Y/N)\" {send \"y\\r\"}\nexec sleep 1.5\n");
	fprintf(TempFiles, "expect \"CLI(config)#\" {send \"show ip\\r\"}\nexec sleep 1.5\n");
	fprintf(TempFiles, "expect \"CLI(config)#\" {send \"show vlan\\r\"}\nexec sleep 0.5\n");
	fprintf(TempFiles, "expect \"CLI(config)#\" {send \"exit\\r\"}\nexec sleep 0.5\n");
	fprintf(TempFiles, "expect \"CLI#\" {send \"exit\\r\"}");
	fclose(TempFiles);
}

/*    更改设备ip地址    */
void AlterIp_(void) {

	char New_Ip[35];
	char len = 0;
	int  a, b, c, d, e, f, g, h;

	printf("\n\t\t示例：192.192.192.192 255.255.255.255");
	printf("\n\t\t为避免输入ip有误，配置光收时需手动确认\n\n根据示例，输入新的ip和掩码：");
	while (fgets(New_Ip, 35, stdin)) {

		len = strlen(New_Ip);
		if (New_Ip[len - 1] == '\n') {

			New_Ip[len - 1] = '\0';
		}

		if (sscanf(New_Ip, "%d.%d.%d.%d %d.%d.%d.%d", &a, &b, &c, &d ,&e, &f, &g, &h)==8
									  && a >= 0 && a <= 255 && b >= 0 && b <= 255
									  && c >= 0 && c <= 255 && d >= 0 && d <= 255
									  && e >= 0 && e <= 255 && f >= 0 && f <= 255
									  && g >= 0 && g <= 255 && h >= 0 && h <= 255) {

			sprintf(New_Ip, "%d.%d.%d.%d %d.%d.%d.%d", a, b, c, d, e, f, g, h);
			printf("\n");
			TempFiles = fopen("./TempFiles", "a");
			fprintf(TempFiles, "expect \"CLI(config)#\" {send \"ip address %s\\r\"}\n", New_Ip);
			fprintf(TempFiles, "interact");
			fclose(TempFiles);
			break;
		}
		else {

			printf("地址或掩码错误，请重新输入：");
		}
	}
}