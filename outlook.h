#pragma once

#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<ctime>
#include<cstdlib>





class Outlook
{
private:
	std::string start_1[17];//��һ�ֿ�������
	std::string start_2[10];

	std::string second[20];//��Ϊ��ӭ����

	std::string logo[20];//��Ϊ�ᴩ��logo���
	std::string short_logo[10];

	std::string end[10];//��Ϊ���Ĺػ�����
public:
	Outlook();
	void print_start(int mode);
	void main_menu();
	void user_menu();
	void admin_menu();
	void low();
	void goodbye();
};