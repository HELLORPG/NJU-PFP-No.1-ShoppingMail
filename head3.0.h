#pragma once
#include<iostream>
#include<string>

#define THE_STORE_MAX 200
#define THE_STR_LEN 20
#define THE_TAB 16

struct LIST
{
	std::string ID = "NULL";
	std::string name = "NULL";
	std::string brand = "NULL";
	double price = 0.0;
	int num = 0;//һ���Ǵ���0��-1Ϊ�����ǣ���ʾ����Ʒ�Ѿ��¼�
	std::string owner = "NULL";//һ��ָ���û�������Ʒ�Ķ�ȡ��ʱ�򲻽���ʹ��
							   //��2.1�İ汾�У����˶�����������������֮�⣬������Ϊһ�����õĽӿڣ���wish_list�У�����Ϊһ����־����ʾ����Ʒ�Ƿ��쳣
};

class Admin
{
private:
	std::string admin_name;
	std::string admin_password;
	std::string the_store_list_file;//��Ϊ���е���Ʒ�Ĵ���Ŀ¼
	std::string the_store_sold_file;//��Ϊ���е�������Ʒ��Ŀ¼
	std::string pass_check_file;//��Ϊ��¼��Ϣ�ļ��
	LIST store_list[THE_STORE_MAX];
	LIST list[10 * THE_STORE_MAX];//��Ϊ�����嵥���б�
public:
	Admin();
	~Admin();
	bool Pass_Check();
	void Init_The_Store_List();
	void Print_List();
	void Add_List();
	void Write_List_File() const;
	void Delete_Thing();
	void Change_List();
	void Init_Sold_List();
	void Print_Sold_List() const;
};

class User
{
private:
	std::string user_name;
	std::string user_password;
	std::string the_store_list_file;
	std::string pass_check_file;
	std::string wish_file;
	std::string pay_file;
	std::string the_store_sold_file;
	LIST store_list[THE_STORE_MAX];
	LIST wish_list[THE_STORE_MAX];
	LIST pay_list[THE_STORE_MAX];
	char user[101][2][21];
public:
	User();
	~User();
	void New_User();
	void Init_Filename();
	bool Pass_Check();
	void Init_The_Store_List();
	void Init_Wish_List();
	void Init_Pay_List();
	void Print_List();//��ӡ��Ʒ�������嵥
	void Print_Wish_List();
	void Write_List_File() const;
	void Write_Wish_File() const;
	void Write_Pay_File() const;
	void Search();
	void Add_Wish();
	void Change_Wish();
	void Pay();
	void Change_Password();
};


