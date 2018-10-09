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

/* 定义一些函数原型和文件 */
#include <stdio.h>


/** 临时文件 **/
FILE *TempFiles;


/** 华环光收 **/
void HuaHuan_();             // 华环主函数
void Deploy_();              // 配置光收
void AlterIp_();             // 更换设备IP
void Login_();               // 登录设备
void Ordinary_();            // 配置普通模式
void UpVlan_();              // 配置vlan
void Save_();                // 保存配置

/** ping测试和查找主机 **/
void PingTest_();            // ping测试
void FindHost_();            // 查找在线主机

/** 获取本地网络信息 **/
int  getLocalInfo_();        // 获取MAC地址、IP、掩码
char GetGateWay_();          // 获取默认网关

/** 回车键 用于跳过配置 **/
char Enter_();

/** 按任意键继续 **/
int  pause_( char* str);