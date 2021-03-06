

#include "stdafx.h"
#include<iostream>
#include<Windows.h>
#include <unordered_map>
#include <fstream>
#include <string>
using namespace std;

wchar_t *transfer(char sBuf[4], UINT CodePage) {
	//获取输入缓存大小
	int sBufSize = strlen(sBuf);

	//CodePage选择代码页 936:GBK   950:BIG-5
	DWORD dBufSize = MultiByteToWideChar(CodePage, 0, sBuf, sBufSize, NULL, 0);
	wchar_t * dBuf = new wchar_t[dBufSize];
	wmemset(dBuf, 0, dBufSize);

	//进行转换
	int nRet = MultiByteToWideChar(CodePage, 0, sBuf, sBufSize, dBuf, dBufSize);
	return dBuf;
}




int main() {
	/*wcout.imbue(locale("chs"));*/
	wchar_t * dBuf = NULL;
	char sBuf[4] = { 0 };

	unordered_map<wstring, string>map;
	unordered_map<string, string>map2;
	ofstream outfile("abc.txt");
	ofstream outfile2("abc2.txt");
	string jianBuf;
	int count = 0;
	int count2 = 0;
	int not_found = 0;
	unordered_map<wstring, string>::const_iterator got;

	for (int i = 0x81; i <= 0xFE; ++i)
	{
		for (int j = 0x40; j <= 0xFE; ++j)
		{
			if (j == 0x7F) continue;
			sBuf[0] = i;
			sBuf[1] = j;
			outfile << sBuf;
			dBuf = transfer(sBuf, 936);
			outfile << *dBuf << endl;			//转换表输出到abc.txt中.
			string ssBuf = sBuf;
			map.insert(make_pair(dBuf, ssBuf));
			count++;
		}

	}
	for (int i = 0x81; i <= 0xFE; ++i)
	{
		for (int j = 0x40; j <= 0x7E; ++j)
		{
			sBuf[0] = i;
			sBuf[1] = j;

			dBuf = transfer(sBuf, 950);
			wstring d = dBuf;
			got = map.find(d);
			if (got == map.end())
				not_found++;
			else {
				jianBuf = got->second;
				string sb = sBuf;
				map2.insert(make_pair(jianBuf, sb));
				outfile2 << sBuf << "	" << jianBuf << endl;
				count2++;
			}
		}
		for (int j = 0xA1; j <= 0xFE; ++j)
		{
			sBuf[0] = i;
			sBuf[1] = j;

			dBuf = transfer(sBuf, 950);
			wstring d = dBuf;
			got = map.find(d);
			if (got == map.end())
				not_found++;
			else {
				jianBuf = got->second;
				string sb = sBuf;
				map2.insert(make_pair(jianBuf, sb));
				outfile2 << sBuf << "	" << jianBuf << endl;
				count2++;
			}
		}
	}

	cout << count << endl << count2 << endl;

	delete dBuf;

}