
// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 MediaTek Inc.
 */
#define LOG_TAG "LCM"
#ifndef BUILD_LK
#include <linux/string.h>
#include <linux/kernel.h>
#endif
#include "lcm_drv.h"
#ifdef BUILD_LK
#include <platform/upmu_common.h>
#include <platform/mt_gpio.h>
#include <platform/mt_i2c.h>
#include <platform/mt_pmic.h>
#include <string.h>
#elif defined(BUILD_UBOOT)
#include <asm/arch/mt_gpio.h>
#else
#include "disp_dts_gpio.h"
#endif
#ifndef MACH_FPGA
#include <lcm_pmic.h>
#endif
#ifdef BUILD_LK
#define LCM_LOGI(string, args...)  dprintf(0, "[LK/"LOG_TAG"]"string, ##args)
#define LCM_LOGD(string, args...)  dprintf(1, "[LK/"LOG_TAG"]"string, ##args)
#else
#define LCM_LOGI(fmt, args...)  pr_debug("[KERNEL/"LOG_TAG"]"fmt, ##args)
#define LCM_LOGD(fmt, args...)  pr_debug("[KERNEL/"LOG_TAG"]"fmt, ##args)
#endif

extern char *saved_command_line;

static struct LCM_UTIL_FUNCS lcm_util;
#define SET_RESET_PIN(v)	(lcm_util.set_reset_pin((v)))
#define MDELAY(n)		(lcm_util.mdelay(n))
#define UDELAY(n)		(lcm_util.udelay(n))
#define dsi_set_cmdq_V22(cmdq, cmd, count, ppara, force_update) \
	lcm_util.dsi_set_cmdq_V22(cmdq, cmd, count, ppara, force_update)
#define dsi_set_cmdq_V2(cmd, count, ppara, force_update) \
	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update) \
		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd) lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums) \
		lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd) \
	  lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size) \
		lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)
#ifndef BUILD_LK
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/irq.h>
/* #include <linux/jiffies.h> */
/* #include <linux/delay.h> */
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#endif
#define LCM_DSI_CMD_MODE									0
#define FRAME_WIDTH										(720)
#define FRAME_HEIGHT									(1600)
//+S96818AA1-1936,liyuhong1.wt,modify,2023/06/14,nt36528 modify the physical size of the screen
#define LCM_PHYSICAL_WIDTH								(70380)
#define LCM_PHYSICAL_HEIGHT								(156240)
//-S96818AA1-1936,liyuhong1.wt,modify,2023/06/14,nt36528 modify the physical size of the screen
#define REGFLAG_DELAY			0xFFFC
#define REGFLAG_UDELAY			0xFFFB
#define REGFLAG_END_OF_TABLE	0xFFFD
#define REGFLAG_RESET_LOW		0xFFFE
#define REGFLAG_RESET_HIGH		0xFFFF
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
struct LCM_setting_table {
	unsigned int cmd;
	unsigned char count;
	unsigned char para_list[256];
};
static struct LCM_setting_table lcm_suspend_setting[] = {
	{0x28, 0,{0x00}},
	{REGFLAG_DELAY, 20,{}},
	{0x10, 0,{0x00}},
	{REGFLAG_DELAY, 120,{}},
};
//+S96818AA1-1936,liyuhong1.wt,modify,2023/07/28,n28-lcd modify gamma
static struct LCM_setting_table init_setting_vdo[] = {
	{0xB0, 1, {0x04}},
	{0xB6, 6, {0x30, 0x62, 0x00, 0x86, 0xC3, 0x03}}, //mipi recovery
	{0xB7, 4, {0x31, 0x00, 0x00, 0x00}},
	{0xB8, 6, {0x00, 0x78, 0x64, 0x10, 0x64, 0xB4}},
	{0xB9, 6, {0x00, 0x78, 0x64, 0x10, 0x64, 0xB4}},
	{0xBA, 6, {0x00, 0x78, 0x64, 0x10, 0x64, 0xB4}},
	{0xBB, 3, {0x00, 0xB4, 0xA0}},
	{0xBC, 3, {0x00, 0xB4, 0xA0}},
	{0xBD, 3, {0x00, 0xB4, 0xA0}},
	{0xBE, 13, {0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0xC0, 24, {0x00, 0x92, 0x33, 0x06, 0x40, 0x00, 0x08, 0x06, 0x98, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}, //modify ic vbp time
	{0xC1, 39, {0x30, 0x11, 0x50, 0xFA, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x40, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x07, 0x08, 0x07, 0xD0, 0x0A, 0xBE}},
	{0xC2, 100, {0x08, 0xC0, 0x8B, 0x14, 0x05, 0x10, 0x0C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xC0, 0x78, 0x08, 0x08, 0x05, 0x05, 0xC5, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x80, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0xC3, 105, {0x08, 0xC0, 0x7A, 0x01, 0x02, 0x76, 0x78, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x08, 0xC0, 0x7A, 0x01, 0x02, 0x76, 0x78, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08, 0xC0, 0x7A, 0x01, 0x02, 0x76, 0x78, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0xC4, 84, {0x00, 0x02, 0x5E, 0x64, 0x07, 0x03, 0x05, 0x13, 0x15, 0x17, 0x19, 0x5D, 0x5F, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x5F, 0x5D, 0x1A, 0x18, 0x16, 0x14, 0x06, 0x04, 0x07, 0x64, 0x5E, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x55, 0x55, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x55, 0x55, 0xD5}},
	{0xC5, 5, {0x08, 0x00, 0x00, 0x00, 0x00}},
	{0xC6, 76, {0x00, 0x00, 0x00, 0x00, 0x01, 0x22, 0x04, 0x22, 0x01, 0x00, 0x61, 0x00, 0x00, 0x00, 0x01, 0x00, 0x61, 0x00, 0x01, 0x05, 0x01, 0x0B, 0x01, 0x35, 0xFF, 0x0F, 0x06, 0x05, 0x01, 0xC0, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x00, 0xC0, 0x11, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x50, 0x00, 0x33, 0x03, 0x00, 0x00}},
	{0xC7, 76, {0x00, 0x00, 0x00, 0x2F, 0x00, 0x68, 0x00, 0xA3, 0x00, 0xF6, 0x01, 0x1E, 0x01, 0x1B, 0x01, 0x2C, 0x01, 0x33, 0x01, 0x41, 0x01, 0x50, 0x01, 0x61, 0x01, 0x75, 0x01, 0x73, 0x01, 0x98, 0x02, 0x37, 0x02, 0x66, 0x02, 0x96, 0x02, 0xB2, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x68, 0x00, 0xA3, 0x00, 0xF6, 0x01, 0x1E, 0x01, 0x1B, 0x01, 0x2C, 0x01, 0x33, 0x01, 0x41, 0x01, 0x50, 0x01, 0x61, 0x01, 0x75, 0x01, 0x73, 0x01, 0x98, 0x02, 0x37, 0x02, 0x66, 0x02, 0x96, 0x02, 0xB2}},
	{0xCA, 68, {0x1C, 0xFC, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00}},
	{0xCB, 30, {0x02, 0xD0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff}},
	{0xCE, 24, {0x5D, 0x40, 0x43, 0x49, 0x55, 0x62, 0x71, 0x82, 0x94, 0xA8, 0xB9, 0xCB, 0xDB, 0xE9, 0xF5, 0xFC, 0xFF, 0x09, 0x46, 0x08, 0x08, 0x00, 0x04, 0x8C}}, //modify dimming
	{0xCF, 1, {0x00}},
	{0xD0, 20, {0xC1, 0x32, 0x81, 0x66, 0x09, 0x90, 0x00, 0xCC, 0xF2, 0xFF, 0x11, 0x46, 0x06, 0x7E, 0x09, 0x08, 0xCC, 0x1B, 0xF0, 0x06}},
	{0xD1, 37, {0xCE, 0xD8, 0x1B, 0x33, 0x33, 0x17, 0x07, 0xBB, 0x33, 0x33, 0x33, 0x33, 0x00, 0x3B, 0x77, 0x07, 0x3B, 0x30, 0x06, 0x72, 0x33, 0x13, 0x00, 0xD7, 0x0C, 0x33, 0x02, 0x00, 0x18, 0x70, 0x18, 0x77, 0x11, 0x11, 0x11, 0x20, 0x20}},  //modify panel timming
	{0xD2, 3, {0x00, 0x00, 0x00}},
	{0xD3, 153, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF}},
	{0xD4, 23, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0xD6, 1, {0x00}},
	{0xD7, 46, {0x01, 0x00, 0x12, 0x12, 0x00, 0x62, 0x00, 0x08, 0x00, 0x62, 0x00, 0x08, 0x03, 0x83, 0x80, 0x85, 0x85, 0x85, 0x87, 0x84, 0x05, 0x86, 0x87, 0x80, 0x88, 0x86, 0x89, 0x83, 0x83, 0x87, 0x84, 0x88, 0x90, 0x0C, 0x0B, 0x0A, 0x0A, 0x0A, 0x07, 0x07, 0x06, 0x06, 0x00, 0x08, 0x0A, 0x0A}},
	{0xD8, 22, {0x40, 0x99, 0x26, 0xED, 0x16, 0x6C, 0x16, 0x6C, 0x16, 0x6C, 0x00, 0x14, 0x00, 0x14, 0x00, 0x14, 0x01, 0x0C, 0x00, 0x00, 0x01, 0x00}},
	{0xD9, 40, {0x00, 0x02, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0xDD, 4, {0x30, 0x06, 0x23, 0x65}},
	{0xDE, 14, {0x00, 0x00, 0x00, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00}},
	{0xE6, 8, {0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00}},
	{0xEA, 35, {0x02, 0x07, 0x07, 0x04, 0x80, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x23, 0x00, 0x07, 0x00, 0xED, 0x00, 0xED, 0x00, 0xED, 0x01, 0x28, 0x01, 0x28, 0x00, 0x62, 0x00, 0x62, 0x00, 0x62, 0x01, 0x0F, 0x01, 0x00}},
	{0xEB, 8, {0x06, 0x00, 0x60, 0x06, 0x01, 0x01, 0x08, 0x00}},
	{0xEC, 23, {0x02, 0xD0, 0x01, 0x70, 0x73, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{0xED, 33, {0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0xC6, 0xE4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x10, 0x01}},
	{0xEE, 121, {0x05, 0x40, 0x01, 0x00, 0xC0, 0x16, 0x00, 0x00, 0x17, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0xC0, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x40, 0x17, 0x04, 0x67, 0x80, 0x00, 0x00, 0x00, 0x17, 0x04, 0x67, 0x80, 0x00, 0x00, 0x55, 0x17, 0x04, 0x67, 0x80, 0x00, 0x00, 0x40, 0x03, 0x04, 0x67, 0x80, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x40, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02}},
	{0xB0, 1, {0x03}},
	{0x35, 1, {0x00}},//TE
	{0x51, 2, {0x0F, 0xFF}},//CABC 12bit
	{0x53, 1, {0x2C}},
	{0x55, 1, {0x00}},
	//{0xBA, 1, {0x03}},//default=03h MIPI 4lane
	{0x11, 0, {0x00}},
	{REGFLAG_DELAY, 100,{}},
	{0x29, 0, {0x00}},
	{REGFLAG_DELAY, 20,{}},
	{ REGFLAG_END_OF_TABLE, 0x00, {}}
};
//-S96818AA1-1936,liyuhong1.wt,modify,2023/07/28,n28-lcd modify gamma
static struct LCM_setting_table bl_level[] = {
	{ 0x51, 0x02, {0x0F,0xFF} },
	{ REGFLAG_END_OF_TABLE, 0x00, {} }
};
static void push_table(void *cmdq, struct LCM_setting_table *table,
	unsigned int count, unsigned char force_update)
{
	unsigned int i;
	unsigned cmd;
	for (i = 0; i < count; i++) {
		cmd = table[i].cmd;
		switch (cmd) {
		case REGFLAG_DELAY:
			if (table[i].count <= 10)
				MDELAY(table[i].count);
			else
				MDELAY(table[i].count);
			break;
		case REGFLAG_UDELAY:
			UDELAY(table[i].count);
			break;
		case REGFLAG_END_OF_TABLE:
			break;
		default:
			dsi_set_cmdq_V22(cmdq, cmd, table[i].count, table[i].para_list, force_update);
		}
	}
}
static void lcm_set_util_funcs(const struct LCM_UTIL_FUNCS *util)
{
	memcpy(&lcm_util, util, sizeof(struct LCM_UTIL_FUNCS));
}
static void lcm_get_params(struct LCM_PARAMS *params)
{
	memset(params, 0, sizeof(struct LCM_PARAMS));
	params->type = LCM_TYPE_DSI;
	params->width = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;
	params->physical_width = LCM_PHYSICAL_WIDTH/1000;
	params->physical_height = LCM_PHYSICAL_HEIGHT/1000;
	params->physical_width_um = LCM_PHYSICAL_WIDTH;
	params->physical_height_um = LCM_PHYSICAL_HEIGHT;
#if (LCM_DSI_CMD_MODE)
	params->dsi.mode = CMD_MODE;
	params->dsi.switch_mode = SYNC_PULSE_VDO_MODE;
#else
	params->dsi.mode = SYNC_PULSE_VDO_MODE;
	params->dsi.switch_mode = CMD_MODE;
#endif
	params->dsi.switch_mode_enable = 0;
	/* DSI */
	/* Command mode setting */
	params->dsi.LANE_NUM = LCM_FOUR_LANE;
	/* The following defined the fomat for data coming from LCD engine. */
	params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq = LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding = LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format = LCM_DSI_FORMAT_RGB888;
	/* Highly depends on LCD driver capability. */
	params->dsi.packet_size = 256;
	/* video mode timing */
	params->dsi.PS = LCM_PACKED_PS_24BIT_RGB888;
	//+BUG S96818AA1-1936,liyuhong1.wt,modify,2023/07/10,modify portch
	params->dsi.vertical_sync_active = 4;
	params->dsi.vertical_backporch = 48;
	params->dsi.vertical_frontporch = 114;
	//params->dsi.vertical_frontporch_for_low_power = 540;/*disable dynamic frame rate*/
	params->dsi.vertical_active_line = FRAME_HEIGHT;
	params->dsi.horizontal_sync_active = 4;
	params->dsi.horizontal_backporch = 70;
	params->dsi.horizontal_frontporch = 180;
	//-BUG S96818AA1-1936,liyuhong1.wt,modify,2023/07/10,modify portch
	params->dsi.horizontal_active_pixel = FRAME_WIDTH;
	params->dsi.ssc_range = 4;
	params->dsi.ssc_disable = 1;
#ifndef CONFIG_FPGA_EARLY_PORTING
#if (LCM_DSI_CMD_MODE)
	params->dsi.PLL_CLOCK = 282;	/* this value must be in MTK suggested table */
#else
	params->dsi.PLL_CLOCK = 330;	/* this value must be in MTK suggested table */
	params->dsi.data_rate = 660;
#endif
	//params->dsi.PLL_CK_CMD = 220;
	//params->dsi.PLL_CK_VDO = 255;
#else
	params->dsi.pll_div1 = 0;
	params->dsi.pll_div2 = 0;
	params->dsi.fbk_div = 0x1;
#endif
	/* mipi hopping setting params */
	params->dsi.dynamic_switch_mipi = 0;	/* turn off frequency hopping */
	params->dsi.data_rate_dyn = 610;
	params->dsi.PLL_CLOCK_dyn = 305;
	params->dsi.horizontal_sync_active_dyn = 4;
	params->dsi.horizontal_backporch_dyn = 84;
	params->dsi.horizontal_frontporch_dyn  = 88;

	params->dsi.clk_lp_per_line_enable = 0;
	params->dsi.esd_check_enable = 1;
	params->dsi.customization_esd_check_enable = 1;
	params->dsi.lcm_esd_check_table[0].cmd = 0x0A;
	params->dsi.lcm_esd_check_table[0].count = 1;
	params->dsi.lcm_esd_check_table[0].para_list[0] = 0x9C;
#ifdef CONFIG_MTK_ROUND_CORNER_SUPPORT
	params->round_corner_en = 0;
	params->corner_pattern_width = 720;
	params->corner_pattern_height = 32;
#endif
}
enum Color {
	LOW,
	HIGH
};
static void lcm_init_power(void)
{
	int ret = 0;
	pr_err("[LCM]td4160_boe_boe lcm_init_power !\n");
    lcm_reset_pin(LOW);
	ret = lcm_power_enable();
    MDELAY(11);
}

extern bool ovt_gesture_flag;
static void lcm_suspend_power(void)
{
    if (ovt_gesture_flag == 1) {
               pr_err("[LCM] td4160_boe_boe lcm_suspend_power ovt_gesture_flag = 1!\n");
	} else {
		int ret  = 0;
                pr_err("[LCM] td4160_boe_boe lcm_suspend_power ovt_gesture_flag = 0!\n");
		lcm_reset_pin(LOW); //reduce flight standby power consumption
		MDELAY(2);
		ret = lcm_power_disable();
		MDELAY(10);
	}
}

static void lcm_resume_power(void)
{
	pr_err("[LCM]td4160_boe_boe lcm_resume_power !\n");
	lcm_init_power();
}

static void lcm_init(void)
{
	pr_err("[LCM] td4160_boe_boe lcm_init\n");
	lcm_reset_pin(HIGH);
	MDELAY(5);
	lcm_reset_pin(LOW);
	MDELAY(5);
	lcm_reset_pin(HIGH);
	MDELAY(10);
	MDELAY(1);
	push_table(NULL, init_setting_vdo, sizeof(init_setting_vdo) / sizeof(struct LCM_setting_table), 1);
	pr_err("[LCM] td4160_boe_boe----init success ----\n");
}
static void lcm_suspend(void)
{
	pr_err("[LCM] lcm_suspend\n");
	push_table(NULL, lcm_suspend_setting, sizeof(lcm_suspend_setting) / sizeof(struct LCM_setting_table), 1);
}
static void lcm_resume(void)
{
	pr_err("[LCM] lcm_resume\n");
	lcm_init();
}
static unsigned int lcm_compare_id(void)
{
	return 1;
}
static unsigned int lcm_ata_check(unsigned char *buffer)
{
#ifndef BUILD_LK
	unsigned int ret = 0;
	unsigned int x0 = FRAME_WIDTH / 4;
	unsigned int x1 = FRAME_WIDTH * 3 / 4;
	unsigned char x0_MSB = ((x0 >> 8) & 0xFF);
	unsigned char x0_LSB = (x0 & 0xFF);
	unsigned char x1_MSB = ((x1 >> 8) & 0xFF);
	unsigned char x1_LSB = (x1 & 0xFF);
	unsigned int data_array[3];
	unsigned char read_buf[4];
	pr_err("ATA check size = 0x%x,0x%x,0x%x,0x%x\n", x0_MSB, x0_LSB, x1_MSB, x1_LSB);
	data_array[0] = 0x0005390A;	/* HS packet */
	data_array[1] = (x1_MSB << 24) | (x0_LSB << 16) | (x0_MSB << 8) | 0x2a;
	data_array[2] = (x1_LSB);
	dsi_set_cmdq(data_array, 3, 1);
	data_array[0] = 0x00043700;	/* read id return two byte,version and id */
	dsi_set_cmdq(data_array, 1, 1);
	read_reg_v2(0x2A, read_buf, 4);
	if ((read_buf[0] == x0_MSB) && (read_buf[1] == x0_LSB)
	    && (read_buf[2] == x1_MSB) && (read_buf[3] == x1_LSB))
		ret = 1;
	else
		ret = 0;
	x0 = 0;
	x1 = FRAME_WIDTH - 1;
	x0_MSB = ((x0 >> 8) & 0xFF);
	x0_LSB = (x0 & 0xFF);
	x1_MSB = ((x1 >> 8) & 0xFF);
	x1_LSB = (x1 & 0xFF);
	data_array[0] = 0x0005390A;	/* HS packet */
	data_array[1] = (x1_MSB << 24) | (x0_LSB << 16) | (x0_MSB << 8) | 0x2a;
	data_array[2] = (x1_LSB);
	dsi_set_cmdq(data_array, 3, 1);
	return ret;
#else
	return 0;
#endif
}
static void lcm_setbacklight_cmdq(void* handle,unsigned int level)
{
	unsigned int bl_lvl;
	bl_lvl = wingtech_bright_to_bl(level,255,10,4095,48);
	pr_err("%s,td4160_boe_boe backlight: level = %d,bl_lvl=%d\n", __func__, level,bl_lvl);
	// set 12bit
	bl_level[0].para_list[0] = (bl_lvl & 0xF00) >> 8;
	bl_level[0].para_list[1] = (bl_lvl & 0xFF);
	pr_err("td4160_boe_boe backlight: para_list[0]=%x,para_list[1]=%x\n",bl_level[0].para_list[0],bl_level[0].para_list[1]);
	push_table(handle, bl_level, sizeof(bl_level) / sizeof(struct LCM_setting_table), 1);
}
struct LCM_DRIVER n28_td4160_dsi_vdo_hdp_boe_boe_drv = {
	.name = "n28_td4160_dsi_vdo_hdp_boe_boe",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params = lcm_get_params,
	.init = lcm_init,
	.suspend = lcm_suspend,
	.resume = lcm_resume,
	.compare_id = lcm_compare_id,
	.init_power = lcm_init_power,
	.resume_power = lcm_resume_power,
	.suspend_power = lcm_suspend_power,
	.set_backlight_cmdq = lcm_setbacklight_cmdq,
	.ata_check = lcm_ata_check,
};
