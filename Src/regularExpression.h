/****************************************************
 * Author: Jin Jay
 * Created On: 2014-10-23
 * Last-Modified: 2014-10-23
 */

#ifndef _REGULAREXPRESSION_H
#define _REGULAREXPRESSION_H 
#endif

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/****************************************************
 * 外部接口函数patternSearch，完成串的匹配工作
 * 输入参数：
 *		const char *pattern: 模式串
 *		const char *str:	 待匹配串
 * 输出参数：
 * 		char *result:		 匹配结果
 * 返回值：
 *      0：					 匹配失败
 *      1：					 匹配成功
 */
int patternSearch(const char *pattern, const char *str, char *result);

// 重复次数的枚举
enum eMulTimes {
	one = 0,	// 不重复
	zero2one, 	// 重复0-1次
	one2n,		// 重复1-n次
	zero2n,		// 重复0-n次
	n,			// 重复n次
	n2more,		// 重复n-更多次
	n2m 		// 重复n-m次
};
// 词性的枚举
enum eWord {
	dot      = 256,	 // 点
	word     = 257,  // 字母或数字
	space    = 258,  // 空格
	digit    = 259,  // 数字
	begin    = 260,  // 一行开头
	stOrEnd  = 261,  // 单词开始或结尾
	dollar   = 262,  // 结尾
	range    = 263,  // 范围选择
	nonWord   = 265, // 非字母或数字
	nonSpace  = 266, // 非空白
	nonDigit  = 267, // 非数字
	nonStOrEnd= 268, // 非开始或结束的位置
	nonRange  = 270, // 范围内不选择
};
/****************************************************
 * 记录每个节点的结构体
 */
typedef struct WordNode {
	char content[20];
	int contentLen;
	int type;
	int (*pCompareFunc)(char, ...);
}WordNode;

/****************************************************
 * 内部数据结构State
 * 		记录当前的状态信息
 */
typedef struct State {
	WordNode word;			// 当前待匹配单词
	enum eMulTimes type;	// 当前状态重复信息
	struct State *next;		// 下一个状态节点
} State, *pStateNode;

/****************************************************
 * 匹配头结点结构
 * 结构体参数：
 * 		State *head;	头结点数组不存储节点信息，只作为指针
 * 		int len;			头结点包含的基本元素个数，匹配时的最小可匹配串长度
 */
typedef struct Head {
	State *head;		// 头结点
	int len;			// 字符串长度
} Head, *pHeadNode;

/****************************************************
 * 分支匹配头结点结构，在模式串中含有'|'时使用
 * 结构体参数：
 * 		Head h[10];			分支数组
 * 		int len;			分支个数
 */
typedef struct Branch{
	Head h[10];
	int num;
} Branch;

typedef struct Patterns
{
	char pattern[100];
	int  p;
}Patterns;
