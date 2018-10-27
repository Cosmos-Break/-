// 简繁转换.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<Windows.h>
#include<wchar.h>
#include<stdlib.h>
using namespace std;

wchar_t *transfer(char sBuf[3]) {
	//获取输入缓存大小
	int sBufSize = strlen(sBuf);
	//获取输出缓存大小
	printf("%d\n", sBufSize);
	//VC++ 默认使用ANSI，故取第一个参数为CP_ACP
	DWORD dBufSize = MultiByteToWideChar(CP_ACP, 0, sBuf, sBufSize, NULL, 0);
	wchar_t * dBuf = new wchar_t[dBufSize];
	wmemset(dBuf, 0, dBufSize);

	//进行转换
	int nRet = MultiByteToWideChar(CP_ACP, 0, sBuf, sBufSize, dBuf, dBufSize);

	if (nRet <= 0)
	{
		printf("转换失败\n");
	}
	else
	{
		printf("转换成功\n");
	}
	return dBuf;
}

int main() {
	wchar_t * dBuf;
	char sBuf[3] = { 0 };
	/*char a[3] = { (char)0x32,(char)0x55,(char)(0xff) };*/
	/*sBuf[0] = (char)0xB4, (char)0xBA;*/
	sBuf[0]=0x81;
	sBuf[1]=0x40;
	cout << sBuf << endl;

	dBuf = transfer(sBuf);
	cout << dBuf << endl;

	delete(dBuf);

}


