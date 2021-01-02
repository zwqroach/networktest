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
void RaisecomLight_() {

    char Cr_File[21];

    printf("\n\n\t  * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("\t *  瑞斯康达光收自动配置程序，适用型号： RC551E-4GE-AC  *\n");
    printf("\t  * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    Login();
    UpVlan();
    // printf("开始配置，请等待下一条提示······\n\n");
    sprintf(Cr_File, "./TpFiles");
    system(Cr_File);
    sprintf(Cr_File, "rm -rf ./TpFiles");
    system(Cr_File); // 配置完成后删除脚本
    printf("\n光收配置完成。");
    PingTest_();
}

/*    创建脚本    */
void Login(void) {

    char DevIp[20] = "192.168.4.28";

    TpFiles = fopen("./TpFiles", "w+");        // 创建脚本文件
    chmod("./TpFiles", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH); // 赋予读、写、执行权限
    fprintf(TpFiles, "#!/usr/bin/expect\nset timeout -1\nspawn telnet %s\n", DevIp);
    fprintf(TpFiles, "expect \"Login:\" {send \"raisecom\\r\"}\nexec sleep 0.5\n");
    fprintf(TpFiles, "expect \"Password:\" {send \"raisecom\\r\"}\nexec sleep 0.5\n");
    fprintf(TpFiles, "expect \"Raisecom>\" {send \"en\\r\"}\nexec sleep 0.5\n");
    fprintf(TpFiles, "expect \"Password:\" {send \"raisecom\\r\"}\nexec sleep 0.5\n");
    fprintf(TpFiles, "expect \"Raisecom#\" {send \"config\\r\"}\nexec sleep 0.5\n");
    fclose(TpFiles);
}

/*    配置vlan    */
void UpVlan(void) { 
    // 写入vlan
    TpFiles = fopen("./TpFiles", "a");
    int VlanID = 0;
    do {
        printf("\n配置业务vlan：");
        scanf(" %d", &VlanID);
        while (getchar() != '\n');
        if (VlanID < 2 || VlanID > 4094) {
            printf("只能输入【2～4094】之间的数字\n");
        }
    } while (VlanID < 2 || VlanID > 4094);

    if(VlanID){
        fprintf(TpFiles, "expect \"Raisecom(config)#\" {send \"create vlan %d active\\r\"}\nexec sleep 0.5\n", VlanID);
    } // 创建业务VLAN并激活

    fprintf(TpFiles, "expect \"Raisecom(config)#\" {send \"interface line 1\\r\"}\nexec sleep 0.5\n"); // 进入光口1配置
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport trunk allowed vlan add %d\\r\"}\nexec sleep 0.5\n", VlanID); // 端口属性TRUNK，并添加网管及业务VALN号
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport trunk untagged vlan remove 1\\r\"}\nexec sleep 0.5\n"); // 禁用默认vlan1
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport mode trunk\\r\"}\nexec sleep 0.5\n"); // 设置光口1为trunk模式
    
    // 配置电口
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"interface client 1\\r\"}\nexec sleep 0.5\n"); // 进入电口1配置
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport mode access\\r\"}\nexec sleep 0.5\n"); // 设置电口1为access模式
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport access vlan %d\\r\"}\nexec sleep 0.5\n", VlanID); // 电口1配置vlan

    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"interface client 2\\r\"}\nexec sleep 0.5\n"); // 进入电口2配置
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport mode access\\r\"}\nexec sleep 0.5\n"); // 设置电口2为access模式
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport access vlan %d\\r\"}\nexec sleep 0.5\n", VlanID); // 电口2配置vlan

    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"interface client 3\\r\"}\nexec sleep 0.5\n"); // 进入电口3配置
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport mode access\\r\"}\nexec sleep 0.5\n"); // 设置电口1为access模式
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport access vlan %d\\r\"}\nexec sleep 0.5\n", VlanID); // 电口3配置vlan

    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"interface client 4\\r\"}\nexec sleep 0.5\n"); // 进入电口4配置
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport mode access\\r\"}\nexec sleep 0.5\n"); // 设置电口4为access模式
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport access vlan %d\\r\"}\nexec sleep 0.5\n", VlanID); // 电口4配置vlan
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"interface line 1\\r\"}\nexec sleep 0.5\n"); // 主用
    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"switchport backup line 2\\r\"}\nexec sleep 0.5\n"); // 备用

    fprintf(TpFiles, "expect \"Raisecom(config-port)#\" {send \"exit\\r\"}\nexec sleep 0.5\n");
    fprintf(TpFiles, "expect \"Raisecom(config)#\" {send \"exit\\r\"}\nexec sleep 0.5\n");
    fprintf(TpFiles, "expect \"Raisecom#\" {send \"write\\r\"}\nexec sleep 0.5\n");
    fprintf(TpFiles, "expect \"Raisecom#\" {send \"show vlan\\r\"}\nexec sleep 0.5\n");
    fprintf(TpFiles, "expect \"Raisecom#\" {send \"exit\\r\"}\n");
    fclose(TpFiles);
}


// 主备设置:interface line 1 (主),   switchport backup line 2(备)
