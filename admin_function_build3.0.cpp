#include"head3.0.h"
#include<iostream>
#include<string>
#include<iomanip>


Admin::Admin()
{
	char the_store_list_filename[] = ".\\All_File\\Admin\\���.txt";
	char the_store_sold_filename[] = ".\\All_File\\Admin\\�����嵥.txt";
	char pass_check_filename[] = ".\\All_File\\Admin\\����Ա�˺�.txt";
	admin_name = "NULL";
	admin_password = "NULL";//��ʵ��������ĸ�ֵ�����վͻ�ı�
	the_store_list_file = the_store_list_filename;
	the_store_sold_file = the_store_sold_filename;
	pass_check_file = pass_check_filename;
	//�������Ƕ����ļ�·���İ���
}

Admin::~Admin()
{
	//std::cout << "clear" << std::endl;
}

bool Admin::Pass_Check()
{
	std::string name_input;
	std::string password_input;
	char name_in_file[THE_STR_LEN + 1];
	char password_in_file[THE_STR_LEN + 1];
	FILE *the_check_file;

	if (fopen_s(&the_check_file, pass_check_file.c_str(), "r"))
	{
		std::cout << "�޷���ָ���Ĺ���Ա�ļ������������ļ����á�" << std::endl;
		return false;
	}
	else
	{
		fscanf_s(the_check_file, "%s", name_in_file, THE_STR_LEN + 1);
		fscanf_s(the_check_file, "%s", password_in_file, THE_STR_LEN + 1);//���ļ���ͷ������������
		std::cout << "�������Ա�˺ţ�";
		std::cin >> name_input;//��δ����������Ƚϳ�֮����α���
		std::cout << "�������Ա���룺";
		std::cin >> password_input;
		//δ���Ŀ��ܵĶ�ȡ�ظ����⣬��Ϊ��ֻ��ģʽ��������Ӱ�첻��
		while (!feof(the_check_file))
		{
			fscanf_s(the_check_file, "%s", name_in_file, THE_STR_LEN + 1);
			fscanf_s(the_check_file, "%s", password_in_file, THE_STR_LEN + 1);
			if (strcmp(name_in_file, name_input.c_str()) == 0)
			{
				if (strcmp(password_in_file, password_input.c_str()) == 0)
				{
					admin_name = name_input;//������Ա��¼��
					admin_password = password_input;
					fclose(the_check_file);
					std::cout << "��¼�ɹ���" << std::endl;
					return true;
				}
			}
		}
	}
	fclose(the_check_file);
	std::cout << "��½ʧ�ܣ��������Ĺ���ԱID�����롣" << std::endl;
	return false;
}

//�����޸ģ��Ѷ�ȡ��ѭ�����ͺ󣬷�ֹ���һ�����ݵĶ���ظ���ȡ��������
void Admin::Init_The_Store_List()
{
	FILE *the_list_file;//�ļ���
	char get1[THE_STR_LEN + 1], get2[THE_STR_LEN + 1], get3[THE_STR_LEN + 1];
	double get4;
	int get5;

	if (fopen_s(&the_list_file, the_store_list_file.c_str(), "r"))
	{
		std::cout << "�޷���ָ���Ĳֿ��ļ������������ļ����á�" << std::endl;
		exit(-1);
	}
	else
	{
		for (int i = 0; i < 5; i++)
			fscanf_s(the_list_file, "%s", get1, THE_STR_LEN + 1);
		int i = 0;
		fscanf_s(the_list_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		while (!feof(the_list_file))
		{
			store_list[i].ID = get1;
			store_list[i].name = get2;
			store_list[i].brand = get3;
			store_list[i].price = get4;
			store_list[i].num = get5;
			i++;
			fscanf_s(the_list_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		}
	}

	fclose(the_list_file);
	return;
}

void Admin::Print_List()
{
	std::cout.setf(std::ios::left);//�����
	std::cout << std::setw(THE_TAB) << "ID" << std::setw(THE_TAB) << "����"
		<< std::setw(THE_TAB) << "Ʒ��" << std::setw(THE_TAB) << "�۸�"
		<< std::setw(THE_TAB) << "����" << std::endl;
	for (int i = 0; store_list[i].name != "NULL"; i++)
		std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
		<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
		<< std::setw(THE_TAB) << store_list[i].num << std::endl;
	return;
}

void Admin::Add_List()
{
	std::string name, brand;
	double price;
	int num;
	std::cout << "��������Ʒ�����ƣ�";
	std::cin >> name;
	std::cout << "��������Ʒ��Ʒ�ƣ�";
	std::cin >> brand;
	std::cout << "��������Ʒ�ļ۸�";
	std::cin >> price;
	std::cout << "��������Ʒ��������";
	std::cin >> num;

	int i = 0;
	for (; store_list[i].ID != "NULL"; i++)
	{
		if (store_list[i].name == name && store_list[i].brand == brand && store_list[i].price == price)
		{
			store_list[i].num += num;
			std::cout << "����Ʒ�Ѿ������ڿ�棬�������޸�Ϊ" << store_list[i].num << std::endl;
			this->Write_List_File();
			return;
		}
	}
	//������û�и���Ʒ��������
	int n = 0;
	char add[10];
	n = atoi(&(store_list[i - 1].ID[1]));
	n++;
	if (n > 999)
		sprintf_s(add, 10, "F%d", n);
	else if (n > 99)
		sprintf_s(add, 10, "F0%d", n);
	else if (n > 9)
		sprintf_s(add, 10, "F00%d", n);
	else
		sprintf_s(add, 10, "F000%d", n);

	store_list[i].ID = add;
	store_list[i].name = name;
	store_list[i].brand = brand;
	store_list[i].price = price;
	store_list[i].num = num;
	std::cout << "�������½�����Ʒ��" << std::endl;
	std::cout << "ID��" << store_list[i].ID << "  ���ƣ�" << store_list[i].name << "  Ʒ�ƣ�"
		<< store_list[i].brand << "  �۸�" << store_list[i].price << "  ������" << store_list[i].num << std::endl;
	this->Write_List_File();
	return;
}

void Admin::Write_List_File() const
{
	FILE *list_file;
	if (fopen_s(&list_file, the_store_list_file.c_str(), "w"))
	{
		std::cout << "��������ļ����ã�" << std::endl;
		exit(-1);
	}
	else
	{
		fprintf_s(list_file, "%-16s%-16s%-16s%-16s%-16s", "ID", "����", "Ʒ��", "�۸�", "����");
		for (int i = 0; store_list[i].ID != "NULL"; i++)
		{
			fprintf_s(list_file, "\n%-16s%-16s%-16s%-16.1f%-16d", store_list[i].ID.c_str(), store_list[i].name.c_str(), store_list[i].brand.c_str(), store_list[i].price, store_list[i].num);
		}
	}
	fclose(list_file);
	std::cout << "����ļ�д����ɣ�" << std::endl;
	return;
}

void Admin::Delete_Thing()
{
	std::string ID;
	bool x = false;

	this->Print_List();//������е���Ʒ

	std::cout << "��������Ҫ�¼ܵ���ƷID��";
	std::cin >> ID;

	for (int i = 0; store_list[i].ID != "NULL"; i++)
	{
		if (store_list[i].ID == ID)
		{
			store_list[i].num = -1;
			std::cout << "��Ʒ " << store_list[i].name << "-" << store_list[i].brand << " �¼�" << std::endl;
			x = true;
			break;
		}
	}
	if (x)
		this->Write_List_File();
	return;
}

void Admin::Change_List()
{
	std::string ID, input;

	this->Print_List();
	std::cout << "��������Ҫ�޸ĵ���ƷID��";
	std::cin >> ID;

	for (int i = 0; store_list[i].ID != "NULL"; i++)
	{
		if (store_list[i].ID == ID)
		{
			std::cout << "��Ʒ " << store_list[i].name << "�ļ۸�Ϊ��" << store_list[i].price
				<< "Ԫ���޸�Ϊ��";
			std::cin >> input;
			store_list[i].price = atof(input.c_str());//ʹ��atof��string��Ϊfloat��
			std::cout << "��Ʒ " << store_list[i].name << "������Ϊ��" << store_list[i].num
				<< "���޸�Ϊ��";
			std::cin >> input;
			store_list[i].num = atoi(input.c_str());
			this->Write_List_File();
			return;
		}
	}

	std::cout << "����Ҫ�޸ĵ���Ʒ�����ڣ�" << std::endl;

	return;
}

void Admin::Init_Sold_List()
{
	FILE *file;
	char get1[THE_STR_LEN + 1], get2[THE_STR_LEN + 1], get3[THE_STR_LEN + 1], get6[THE_STR_LEN + 1];
	double get4;
	int get5;

	if (fopen_s(&file, the_store_sold_file.c_str(), "r"))
	{
		std::cout << "��������ļ����ã�" << std::endl;
		exit(-1);
	}
	else
	{
		for (int i = 0; i < 6; i++)
			fscanf_s(file, "%s", get1, THE_STR_LEN + 1);
		int i = 0;
		fscanf_s(file, "%s%s%s%lf%d%s", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5, get6, THE_STR_LEN + 1);
		while (!feof(file))
		{
			list[i].ID = get1;
			list[i].name = get2;
			list[i].brand = get3;
			list[i].price = get4;
			list[i].num = get5;
			list[i].owner = get6;//����һ��ȫ�µ����ݣ����������ﲢû�����ã�ֻ�Ǽ�һ���ӿڣ��Ա�֮��ĸ��ӹ���
			i++;
			fscanf_s(file, "%s%s%s%lf%d%s", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5, get6, THE_STR_LEN + 1);
		}
	}

	fclose(file);
	return;
}

void Admin::Print_Sold_List() const
{
	std::cout.setf(std::ios::left);//�����
	std::cout << std::setw(THE_TAB) << "ID" << std::setw(THE_TAB) << "����"
		<< std::setw(THE_TAB) << "Ʒ��" << std::setw(THE_TAB) << "�۸�"
		<< std::setw(THE_TAB) << "����" << std::endl;//��ӡͷ***********************
	for (int i = 0; store_list[i].ID != "NULL"; i++)//��store_list��Ϊ����Ļ���
	{
		double price_list[200][2] = { 0 };
		for (int j = 0; list[j].ID != "NULL"; j++)//4.7���ӹ��ܣ������ͬ�۸��ͬ��Ʒ���۳�
		{
			bool px = false;

			if (list[j].ID == store_list[i].ID)
			{
				int pi = 0;
				for (; price_list[pi][0] != 0; pi++)
				{
					if (list[j].price == price_list[pi][0])
					{
						px = true;
						price_list[pi][1] += list[j].num;
					}
				}
				if (!px)
				{
					price_list[pi][0] = list[j].price;
					price_list[pi][1] = list[j].num;
				}
			}
			px = false;
		}
		for (int pi = 0; price_list[pi][0] != 0; pi++)
		{
			if (price_list[pi][1] != 0)
			{
				std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
					<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << price_list[pi][0]
					<< std::setw(THE_TAB) << price_list[pi][1] << std::endl;
			}
		}
	}
	return;
}
//�����ǹ���Ա���ܵĺ������죬�������û��ĺ�������

