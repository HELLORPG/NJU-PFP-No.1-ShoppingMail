#include"head3.0.h"
#include<string>
#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<algorithm>


User::User()
{
	char the_store_list_filename[] = ".\\All_File\\Admin\\���.txt";
	char the_pass_check_filename[] = ".\\All_File\\User\\�û��˺�.txt";
	char the_store_sold_filename[] = ".\\All_File\\Admin\\�����嵥.txt";

	user_name = "NULL";
	user_password = "NULL";//��ʵ��������ĸ�ֵ�����վͻ�ı�
	the_store_list_file = the_store_list_filename;
	pass_check_file = the_pass_check_filename;
	the_store_sold_file = the_store_sold_filename;
}

User::~User()
{

}

void User::Init_Filename()
{
	std::string before_add = ".\\All_File\\User\\";//�����ļ���ͳһ·��
	std::string pay_after_add = "_pay.txt";
	std::string wish_after_add = "_wish.txt";//���������ļ�����ǰ�������
	wish_file = before_add + user_name + wish_after_add;
	pay_file = before_add + user_name + pay_after_add;
	return;
}

void User::New_User()
{
	std::string name;
	std::string password;
	char name_get[THE_STR_LEN + 1], password_get[THE_STR_LEN + 1];
	FILE *the_check_file;

	if (fopen_s(&the_check_file, pass_check_file.c_str(), "r+"))
	{
		std::cout << "��������ļ����ã�" << std::endl;
		exit(-1);
	}
	else
	{
		std::cout << "����������û�����";
		std::cin >> name;
		if (name.size() > 20)
		{
			fclose(the_check_file);
			std::cout << "�û�����С��20���ַ�" << std::endl;
			return;
		}
		std::cout << "������������룺";
		std::cin >> password;
		if (password.size() > 20)
		{
			fclose(the_check_file);
			std::cout << "������С��20���ַ�" << std::endl;
			return;
		}

		fscanf_s(the_check_file, "%s%s", name_get, THE_STR_LEN + 1, password_get, THE_STR_LEN + 1);
		while (!feof(the_check_file))
		{
			if (name == name_get)
			{
				fclose(the_check_file);
				std::cout << "�û����ظ���" << std::endl;
				return;
			}
			fscanf_s(the_check_file, "%s%s", name_get, THE_STR_LEN + 1, password_get, THE_STR_LEN + 1);
		}

		user_name = name;
		user_password = password;//�������ĳ�ʼ����ʹ�ú�����ļ������оݿ���

		fprintf_s(the_check_file, "%-32s%-32s\n", name.c_str(), password.c_str());
		std::cout << "���û������ɹ�" << std::endl;
		fclose(the_check_file);
	}

	//�������û����˻���Ϣ������ϣ����滹��Ҫ�����û��Ĺ��ﳵ�ļ���

	this->Init_Filename();//�����ļ�����ʼ�����������趨�����ڵ�һ�ν����û��ļ�
	FILE *wish, *pay;
	if (fopen_s(&wish, wish_file.c_str(), "w") || fopen_s(&pay, pay_file.c_str(), "w"))
	{
		std::cout << "�����ļ����ã�" << std::endl;
		exit(-1);
	}
	else
	{
		fprintf_s(wish, "%-16s%-16s%-16s%-16s%-16s\n", "ID", "����", "Ʒ��", "�۸�", "����");
		fprintf_s(pay, "%-16s%-16s%-16s%-16s%-16s\n", "ID", "����", "Ʒ��", "�۸�", "����");
	}
	fclose(wish);
	fclose(pay);

	std::cout << "�û��ļ�������ϣ�" << std::endl;


	return;
}

bool User::Pass_Check()
{
	std::string name_input;
	std::string password_input;
	char name_in_file[THE_STR_LEN + 1];
	char password_in_file[THE_STR_LEN + 1];
	FILE *the_check_file;

	if (fopen_s(&the_check_file, pass_check_file.c_str(), "r"))
	{
		std::cout << "�޷���ָ�����û��ļ������������ļ����á�" << std::endl;
		return false;
	}
	else
	{
		fscanf_s(the_check_file, "%s", name_in_file, THE_STR_LEN + 1);
		fscanf_s(the_check_file, "%s", password_in_file, THE_STR_LEN + 1);//���ļ���ͷ������������
		std::cout << "�����û�����";
		std::cin >> name_input;//��δ����������Ƚϳ�֮����α���
		std::cout << "�����û����룺";
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
					user_name = name_input;//���û���¼��
					user_password = password_input;
					fclose(the_check_file);
					std::cout << "��¼�ɹ���" << std::endl;
					this->Init_Filename();//******��Ҫ��һ���������û��ļ����ĳ�ʼ��������֮��Ĳ���******
					return true;
				}
			}
		}
	}
	fclose(the_check_file);
	std::cout << "��½ʧ�ܣ����������û��������롣" << std::endl;
	return false;
}

//�����������������д�����Admin���еĸú���һ�����޸�ʱӦ��ͬ���޸�
void User::Init_The_Store_List()
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

void User::Print_List()
{
	std::cout.setf(std::ios::left);//�����
	std::cout << std::setw(THE_TAB) << "ID" << std::setw(THE_TAB) << "����"
		<< std::setw(THE_TAB) << "Ʒ��" << std::setw(THE_TAB) << "�۸�"
		<< std::setw(THE_TAB) << "����" << std::endl;
	for (int i = 0; store_list[i].name != "NULL"; i++)
	{
		if (store_list[i].num > 0)//��������Ѿ��¼ܻ�������Ϊ0����Ʒ
		{
			std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
				<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
				<< std::setw(THE_TAB) << store_list[i].num << std::endl;
		}
	}
	return;
}

//������������ΪAdmin��ֲ�����Ĵ���
void User::Init_Wish_List()
{
	FILE *the_wish_file;//�ļ���
	char get1[THE_STR_LEN + 1], get2[THE_STR_LEN + 1], get3[THE_STR_LEN + 1];
	double get4;
	int get5;
	std::string input;

	if (fopen_s(&the_wish_file, wish_file.c_str(), "r"))
	{
		std::cout << "�޷���ָ���Ĳֿ��ļ������������ļ����á�" << std::endl;
		exit(-1);
	}
	else
	{
		for (int i = 0; i < 5; i++)
			fscanf_s(the_wish_file, "%s", get1, THE_STR_LEN + 1);
		int i = 0;
		fscanf_s(the_wish_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		while (!feof(the_wish_file))
		{
			wish_list[i].ID = get1;
			wish_list[i].name = get2;
			wish_list[i].brand = get3;
			wish_list[i].price = get4;
			wish_list[i].num = get5;
			i++;
			fscanf_s(the_wish_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		}
	}

	fclose(the_wish_file);

	//������һ��������飬���ھ����������ڼ���ܵ��µ������ı�

	//2018.4.10 �����ⶨ�Ż���Ҳ������ɾ�����ﳵ����Ʒ��ʱ��ѯ���û����Ƿ�ɾ���Լ���صĲ���

	//�����������ƵĲ����Ż���Ҳ�����ڹ��ﳵ����Ʒ�������ڿ���ʱ�������ܵ��µ����⣬����2.1�汾���Ż�

	//�����
	bool correct = false;
	bool flag = false;

	for (int i = 0; wish_list[i].ID != "NULL"; i++)
	{
		for (int j = 0; store_list[j].ID != "NULL"; j++)
		{
			if (wish_list[i].ID == store_list[j].ID)
			{

				if (wish_list[i].price != store_list[j].price)
				{
					flag = true;
					std::cout << "��ѡ�е���Ʒ" << wish_list[i].ID << "-" << wish_list[i].name << "-" << wish_list[i].brand << "�۸�䶯Ϊ��" << store_list[j].price << "Ԫ" << std::endl;
					//�����˶���������Ʒ����Ϣ����ϸ����
					//����Ҫ����Ʒ���쳣����
					wish_list[i].price = store_list[j].price;
					correct = true;

				}

				if (wish_list[i].num > store_list[j].num)
				{
					flag = true;
					if (store_list[j].num > 0)
					{
						std::cout << "��Ʒ" << wish_list[i].ID << "-" << wish_list[i].name << "-" << wish_list[i].brand << "��治��" << std::endl;
						//������Ʒ��Ϣ��ʾ���Ż��������û��Ѻ�
						std::cout << "������ѡ��1.�޸��������\t2.����ԭ����" << std::endl;
						do
						{
							std::cin >> input;
							if (input == "1")
							{
								wish_list[i].num = store_list[j].num;
								std::cout << "��Ʒ�������޸�Ϊ" << wish_list[i].num << std::endl;
							}

							else if (input == "2")
							{
								wish_list[i].owner = "NOTENOUGH";//��Ϊ��Ʒ����ı�ʾ���쳣��ʾ
							}

							else
								std::cout<<"��" << input << "��" << "Ϊ�Ƿ����룬���������룺";
						} while (input != "1"&&input != "2");
					}
					else
					{
						//2.0�汾�������޸ģ�*******************************************************************************************


						std::cout << "��Ʒ" << wish_list[i].ID << "-" << wish_list[i].name << "-" << wish_list[i].brand << "�Ŀ�治������Ѿ��¼ܣ�������ѡ��" << std::endl;
						std::cout << "1.ɾ������Ʒ\t2.��������Ʒ" << std::endl;
						std::cout << "��������������";

						do {
							std::cin >> input;
							if (input == "1")
							{
								int ii = i;
								for (; wish_list[ii].ID != "NULL"; ii++)
									wish_list[ii] = wish_list[ii + 1];
								std::cout << "����Ʒ�Ѵӹ��ﳵɾ����" << std::endl;
								correct = true;
								i--;
							}

							else if (input == "2")
							{
								wish_list[i].owner = "DOWN";//��Ϊ��Ʒ�¼ܵı�־
							}

							else
								std::cout << "��" << input << "��" << "Ϊ�Ƿ����룬���������룺";
						} while (input != "1"&&input != "2");

						//2.0�汾�ĸ��½���***********************************************************************************************

					}

				}
				break;
			}
			//���ϵľ���ģ���Ƕ��������Ĳ���

			//���µľ���ģ���Ƕ��ڼ۸�ı䶯
		}
	}
	if (correct)
		this->Write_Wish_File();
	if (flag)
	{
		system("pause");
		system("CLS");//���еȴ������������Ż���հ
	}
	//������һ���������

	return;
}
void User::Init_Pay_List()
{
	FILE *the_pay_file;//�ļ���
	char get1[THE_STR_LEN + 1], get2[THE_STR_LEN + 1], get3[THE_STR_LEN + 1];
	double get4;
	int get5;

	if (fopen_s(&the_pay_file, pay_file.c_str(), "r"))
	{
		std::cout << "�޷���ָ���Ĳֿ��ļ������������ļ����á�" << std::endl;
		exit(-1);
	}
	else
	{
		for (int i = 0; i < 5; i++)
			fscanf_s(the_pay_file, "%s", get1, THE_STR_LEN + 1);
		int i = 0;
		fscanf_s(the_pay_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		while (!feof(the_pay_file))
		{
			pay_list[i].ID = get1;
			pay_list[i].name = get2;
			pay_list[i].brand = get3;
			pay_list[i].price = get4;
			pay_list[i].num = get5;
			i++;
			fscanf_s(the_pay_file, "%s%s%s%lf%d", get1, THE_STR_LEN + 1, get2, THE_STR_LEN + 1, get3, THE_STR_LEN + 1, &get4, &get5);
		}
	}

	fclose(the_pay_file);
	return;
}

void User::Write_List_File() const
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
void User::Write_Wish_File() const
{
	FILE *wish;
	if (fopen_s(&wish, wish_file.c_str(), "w"))
	{
		std::cout << "��������ļ����ã�" << std::endl;
		exit(-1);
	}
	else
	{
		fprintf_s(wish, "%-16s%-16s%-16s%-16s%-16s", "ID", "����", "Ʒ��", "�۸�", "����");
		for (int i = 0; wish_list[i].ID != "NULL"; i++)
		{
			fprintf_s(wish, "\n%-16s%-16s%-16s%-16.1f%-16d", wish_list[i].ID.c_str(), wish_list[i].name.c_str(), wish_list[i].brand.c_str(), wish_list[i].price, wish_list[i].num);
		}
	}
	fclose(wish);
	std::cout << "���ﳵ�ļ�д����ɣ�" << std::endl;
	return;
}
void User::Write_Pay_File() const
{
	FILE *pay;
	if (fopen_s(&pay, pay_file.c_str(), "w"))
	{
		std::cout << "��������ļ����ã�" << std::endl;
		exit(-1);
	}
	else
	{
		fprintf_s(pay, "%-16s%-16s%-16s%-16s%-16s", "ID", "����", "Ʒ��", "�۸�", "����");
		for (int i = 0; pay_list[i].ID != "NULL"; i++)
		{
			fprintf_s(pay, "\n%-16s%-16s%-16s%-16.1f%-16d", pay_list[i].ID.c_str(), pay_list[i].name.c_str(), pay_list[i].brand.c_str(), pay_list[i].price, pay_list[i].num);
		}
	}
	fclose(pay);
	std::cout << "���ջ��ļ�д����ɣ�" << std::endl;
	return;
}

void User::Search()
{
	std::cout.setf(std::ios::left);//����붨��
	std::string kind;
	std::string input;
	bool x = false;




	//3.0�����ģ����ѯ��֧��***************************************************************************************



	bool list[200] = { false };//�������������������һ�����������������������


	/*std::cout << "ID/����/Ʒ��" << std::endl;
	std::cout << "��������Ҫ�����ķ�ʽ��";
	std::cin >> kind;
	if (kind == "ID")
	{
		std::cout << "��������Ʒ��ID��";
		std::cin >> input;
		std::cout << "ID\t\t����\t\tƷ��\t\t�۸�\t\t����\n";
		for (int i = 0; store_list[i].ID != "NULL"; i++)
		{
			if (store_list[i].ID == input && store_list[i].num > 0)
			{
				x = true;
				std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
					<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
					<< std::setw(THE_TAB) << store_list[i].num << std::endl;
			}
		}
		if (!x)
			std::cout << "\nδ�ҵ�ָ��ID��Ʒ��\n";
	}
	else if (kind == "����")
	{
		std::cout << "��������Ʒ�����ƣ�";
		std::cin >> input;
		std::cout << "ID\t\t����\t\tƷ��\t\t�۸�\t\t����\n";
		for (int i = 0; store_list[i].ID != "NULL"; i++)
		{
			if (store_list[i].name == input && store_list[i].num > 0)
			{
				x = true;
				std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
					<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
					<< std::setw(THE_TAB) << store_list[i].num << std::endl;
			}
		}
		if (!x)
			std::cout << "\nδ�ҵ�ָ��������Ʒ��\n";
	}
	else if (kind == "Ʒ��")
	{
		std::cout << "��������Ʒ��Ʒ�ƣ�";
		std::cin >> input;
		std::cout << "ID\t\t����\t\tƷ��\t\t�۸�\t\t����\n";
		for (int i = 0; store_list[i].ID != "NULL"; i++)
		{
			if (store_list[i].brand == input && store_list[i].num > 0)
			{
				x = true;
				std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
					<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
					<< std::setw(THE_TAB) << store_list[i].num << std::endl;
			}
		}
		if (!x)
			std::cout << "\nδ�ҵ�ָ��Ʒ����Ʒ��\n";
	}*/

	std::cout << "��������Ҫ�����Ĺؼ��ʣ�";
	std::cin >> input;
	transform(input.begin(), input.end(), input.begin(), toupper);

	int len = input.length();//��Ϊģ�������ؼ��ʵĳ���

	for (int i = 0; store_list[i].ID != "NULL"; i++)
	{
		if (store_list[i].num <= 0)
			continue;
		for (int j = 0; j < (int)store_list[i].ID.length() - len + 1; j++)
		{
			std::string a = store_list[i].ID;
			transform(a.begin(), a.end(), a.begin(), toupper);
			if (strncmp(input.c_str(), (&a[0] + j), len) == 0)
			{
				list[i] = true;
				x = true;
				break;
			}
		}

		for (int j = 0; j < (int)store_list[i].name.length() - len + 1; j++)
		{
			std::string a = store_list[i].name;
			transform(a.begin(), a.end(), a.begin(), toupper);
			if (strncmp(input.c_str(), (&a[0] + j), len) == 0)
			{
				list[i] = true;
				x = true;
				break;
			}
		}

		for (int j = 0; j < (int)store_list[i].brand.length() - len + 1; j++)
		{
			std::string a = store_list[i].brand;
			transform(a.begin(), a.end(), a.begin(), toupper);
			if (strncmp(input.c_str(), (&a[0] + j), len) == 0)
			{
				list[i] = true;
				x = true;
				break;
			}
		}
	}

	if (!x)
		std::cout << "\nδ�ҵ���Ʒ��\n";
	else
	{
		std::cout << "ID\t\t����\t\tƷ��\t\t�۸�\t\t����\n";//��ͷ
		for (int i = 0; i < 200; i++)
		{
			if (list[i])
			{
				std::cout << std::setw(THE_TAB) << store_list[i].ID << std::setw(THE_TAB) << store_list[i].name
					<< std::setw(THE_TAB) << store_list[i].brand << std::setw(THE_TAB) << store_list[i].price
					<< std::setw(THE_TAB) << store_list[i].num << std::endl;
			}
		}
	}

	return;
}

void User::Add_Wish()
{
	std::string ID;//��Ϊ��ӵ���Ʒ��Ψһ��ʶ
	int num = 0;//��Ϊ��ӵ�����

	std::cout << std::endl;
	this->Print_List();
	std::cout << std::endl;


	std::cout << "��������Ҫ��ӵ���Ʒ��ID��";
	std::cin >> ID;
	std::cout << "��������Ʒ��������";
	std::cin >> num;
	int i = 0;
	for (; wish_list[i].ID != "NULL"; i++)//�����Ƿ��ڹ��ﳵ���Ѿ����˸���Ʒ
	{
		if (wish_list[i].ID == ID)//˵����ԭ���Ĺ��ﳵ�ļ����Ѿ�������һ����Ʒ
			break;

	}

	for (int j = 0; store_list[j].ID != "NULL"; j++)//�ڿ����Ѱ����һ����Ʒ
	{
		if (store_list[j].ID == ID)//�ҵ��������Ʒ
		{
			wish_list[i].ID = ID;//�����ﳵID���и�ֵ
			if (store_list[j].num <= 0)
			{
				wish_list[i] = store_list[j];
				std::cout << "����Ʒ�����¼ܻ����������ⲻ����������Ĺ��ﳵ" << std::endl;
				for (; i < THE_STORE_MAX - 1; i++)//����һ��֮������й��ﳵ��ǰ����
				{
					wish_list[i] = wish_list[i + 1];
				}
			}
			else if (wish_list[i].num + num > store_list[j].num)
			{
				wish_list[i] = store_list[j];
				std::cout << "��Ʒ�����������ƣ��Ѿ��������޸�Ϊ��" << store_list[j].num << std::endl;
				wish_list[i].num = store_list[j].num;
			}
			else
			{
				int save_num = 0;
				save_num = wish_list[i].num;
				wish_list[i] = store_list[j];
				wish_list[i].num = save_num + num;
			}
			this->Write_Wish_File();
			return;
		}
	}
	std::cout << "�޴���Ʒ��" << std::endl;
	return;
}

void User::Print_Wish_List()
{
	std::cout.setf(std::ios::left);//�����
	std::cout << std::setw(THE_TAB) << "ID" << std::setw(THE_TAB) << "����"
		<< std::setw(THE_TAB) << "Ʒ��" << std::setw(THE_TAB) << "�۸�"
		<< std::setw(THE_TAB) << "����" << std::endl;
	for (int i = 0; wish_list[i].name != "NULL"; i++)
	{
		if (wish_list[i].owner == "NOTENOUGH" || wish_list[i].owner == "DOWN")
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
		std::cout << std::setw(THE_TAB) << wish_list[i].ID << std::setw(THE_TAB) << wish_list[i].name
			<< std::setw(THE_TAB) << wish_list[i].brand << std::setw(THE_TAB) << wish_list[i].price
			<< std::setw(THE_TAB) << wish_list[i].num;//<< std::endl;
		if (wish_list[i].owner == "NOTENOUGH")
			std::cout << std::setw(THE_TAB) << "����Ʒ�����������";
		else if (wish_list[i].owner == "DOWN")
			std::cout << std::setw(THE_TAB) << "����Ʒ�Ŀ��Ϊ0�����Ѿ��¼�";
		std::cout << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}
	//std::cout << std::endl;
	//std::cout.setf(std::ios::right);
	return;
}

void User::Change_Wish()//Ŀǰֻ��ɾ�����ܣ��������ܽ������
{
	std::string ID;
	int num = 0;

	std::cout << std::endl;
	this->Print_Wish_List();
	std::cout << std::endl;

	//��3.0�İ汾��ϣ�����Բ�ֹɾ����һ����Ʒ�������Խ��������Ĳ���
	std::cout << "��������Ʒ��ID��";
	std::cin >> ID;

	for (int i = 0; wish_list[i].ID != "NULL"; i++)
	{
		if (wish_list[i].ID == ID)
			//�ҵ�����һ����Ʒ�ڹ��ﳵ��
		{
			int j = 0;
			for (; store_list[j].ID != "NULL"; j++)
				if (store_list[j].ID == ID)//�ڿ����Ҳ�ҵ�����һ����Ʒ
					break;
			//���ϵĴ������仰���Ѿ����̵����ҵ�����һ��Ҫ�޸ĵĹ��ﳵ�����Ʒ������֮��������ݵıȶԺ��޸�

			std::cout << "*********************************************************************" << std::endl;
			std::cout << "���Ĺ��ﳵ��Ϊ��" << wish_list[i].name << "-" << wish_list[i].brand << "��" << wish_list[i].num << "��" << std::endl;
			std::cout << "�������" << store_list[j].num << "��" << std::endl;
			std::cout << "*********************************************************************" << std::endl;

			std::cout << "�����������������޸ĺ����������Ϊ0��ɾ���û�Ʒ����";
			std::cin >> num;


			if (num < 0)
			{
				std::cout << "��������ݲ���Ϊ����������ʧ�ܣ�" << std::endl;
				return;
			}
			else if (num == 0)
			{
				for (; i < THE_STORE_MAX - 1; i++)
					wish_list[i] = wish_list[i + 1];
				std::cout << "��Ʒ" << ID << "�Ѿ��Ƴ�" << std::endl;
			}
			else
			{
				if (store_list[j].num <= 0)
				{
					wish_list[i].num = num;
					wish_list[i].owner = "DOWN";
				}
				else if (num > store_list[j].num)//����޸�֮����������ڿ��
				{
					wish_list[i].num = num;
					wish_list[i].owner = "NOTENOUGH";
				}

				std::cout << "�Ѿ��ɹ��޸ĸ���Ʒ��������" << std::endl;
			}
			this->Write_Wish_File();
			return;
		}
	}
	std::cout << "���Ĺ��ﳵ��û�������Ʒ��" << std::endl;



	return;
}

void User::Pay()
{
	//Ŀǰֻ��ʵ��ȫ������Ĳ��������������ֲ�*************************************
	//bool x = false;
	//bool flag = false;//2.0�汾�������ӵ��±���
	FILE *file;
	if (fopen_s(&file, the_store_sold_file.c_str(), "a"))
	{
		std::cout << "����ϵ����Ա����ļ�����" << std::endl;
		exit(-1);
	}

	//2.0�汾���£�������֮ǰ��ɾ����Ʒ���û����������Ӧ�Ĺ���ʱ��Ҫ��⣬�Ƿ��п���Լ��Ƿ��¼ܣ���ȷ���ɷ���*******************
	int which_pay[200] = { 0 };//�����Щ��Ʒ�ǽ��и����
	int which_pay_i = 0;
	double tot_money = 0;//�����ܼ�
	std::string input;
	/*
	for (int i = 0; wish_list[i].ID != "NULL"; i++)
	{
	int j = 0;
	/*
	for (; pay_list[j].ID != "NULL"; j++)
	{

	if (pay_list[j].ID == wish_list[i].ID)//���������Ѿ�������һ����Ʒ
	{
	x = true;
	for (int k = 0; store_list[k].ID != "NULL"; k++)//���п��ı���
	{
	if (store_list[k].ID == wish_list[i].ID)
	{
	if (store_list[k].num < wish_list[i].num)
	{
	std::cout << "��Ʒ" << store_list[k].ID << "�Ŀ�治�㣬�����޸Ĺ��ﳵ֮���ٽ��и���" << std::endl;
	break;//����ѭ����������һ��Ʒ�ĸ���
	}
	else
	{
	tot_money += wish_list[i].price*wish_list[i].num;
	which_pay[which_pay_i] = i;
	which_pay_i++;
	//pay_list[j].num += wish_list[i].num;
	//store_list[k].num -= wish_list[i].num;//�����޸�
	flag = true;//����ɹ���ʱ����з�ת
	break;
	}
	}
	}
	}


	}

	//ȡ���˴��ջ��嵥�ĺϲ����Ͼ�����ʱ�䲻һ��
	//if (!x)//�����һ���µ���Ʒ�Ļ�

	for (int k = 0; store_list[k].ID != "NULL"; k++)//���п��ı���
	{
	if (store_list[k].ID == wish_list[i].ID)
	{
	if (store_list[k].num < wish_list[i].num)
	{
	std::cout << "��Ʒ" << store_list[k].ID << "�Ŀ�治�㣬�����޸Ĺ��ﳵ֮���ٽ��и���" << std::endl;
	break;//����ѭ����������һ��Ʒ�ĸ���
	}
	else
	{
	tot_money += wish_list[i].num*wish_list[i].price;
	which_pay[which_pay_i] = i;//��¼�¿��Ը���Ķ���
	which_pay_i++;

	//pay_list[j] = wish_list[i];//�ͺ��ȽϺ�
	//store_list[k].num -= wish_list[i].num;//�����޸�
	//flag = true;//����ɹ���ʱ����з�ת
	//break;
	}
	}
	}
	//i--;
	//x = false;



	/*
	if (flag)
	{
	fprintf_s(file, "%-16s%-16s%-16s%-16.1f%-16d%-16s\n", wish_list[i].ID.c_str(), wish_list[i].name.c_str(), wish_list[i].brand.c_str(), wish_list[i].price, wish_list[i].num, user_name.c_str());
	for (int ii = i; wish_list[ii].ID != "NULL"; ii++)//��δ������������ע�͵��Ĵ���Ĺ��ܣ�����Ϊ������2.0���޸ģ����Դ�������˱䶯
	{
	wish_list[ii] = wish_list[ii + 1];
	}
	}
	//wish_list[i] = { "NULL","NULL","NULL",0.0,0 };//�ָ����ﳵ����һλ��

	flag = false;


	}

	*/

	//������3.0���޸ģ����õ��Ǳ�־λ���ж��Ƿ���Խ��и���

	for (int i = 0; wish_list[i].ID != "NULL"; i++)//ֻ�Թ��ﳵ���б����������˺ܶ�Ĺ�����
	{
		if (wish_list[i].owner == "NOTENOUGH")
		{
			std::cout << "��Ʒ" << wish_list[i].ID << "�Ŀ�治�㣬�����޸Ĺ��ﳵ֮���ٽ��и���" << std::endl;
		}
		else if (wish_list[i].owner == "DOWN")
		{
			std::cout << "��Ʒ" << wish_list[i].ID << "�Ŀ�治�㣬�����޸Ĺ��ﳵ֮���ٽ��и���" << std::endl;
		}
		else//����������ǿ��Խ��н����ʱ��
		{
			which_pay[which_pay_i] = i;//�������һ�����Խ��и���
			tot_money += wish_list[i].num*wish_list[i].price;//�����ܿ�ı�ʾ
			which_pay_i++;//+1������
		}

	}



	std::cout << "�ܼ۸���" << tot_money << "Ԫ" << std::endl;
	std::cout << "1.ȷ�ϸ���\t2.ȡ������" << std::endl;
	do
	{
		std::cin >> input;
		if (input == "2")
		{
			fclose(file);
			return;
		}

	} while (input != "1"&&input != "2");

	int pay_i = 0;
	for (; pay_list[pay_i].ID != "NULL"; pay_i++);
	for (int i = which_pay_i - 1; i >= 0; i--)//���и���Ĳ���
	{
		fprintf_s(file, "%-16s%-16s%-16s%-16.1f%-16d%-16s\n", wish_list[which_pay[i]].ID.c_str(), wish_list[which_pay[i]].name.c_str(), wish_list[which_pay[i]].brand.c_str(), wish_list[which_pay[i]].price, wish_list[which_pay[i]].num, user_name.c_str());
		pay_list[pay_i] = wish_list[which_pay[i]];
		for (int k = 0; store_list[k].ID != "NULL"; k++)
		{
			if (store_list[k].ID == wish_list[which_pay[i]].ID)
				store_list[k].num -= wish_list[which_pay[i]].num;
		}
		pay_i++;
		for (int ii = which_pay[i]; wish_list[ii].ID != "NULL"; ii++)//��δ������������ע�͵��Ĵ���Ĺ��ܣ�����Ϊ������2.0���޸ģ����Դ�������˱䶯
		{
			wish_list[ii] = wish_list[ii + 1];
		}
	}

	//2.0�汾��һ�ε��޸Ľ���*********************************************************************************************************

	fclose(file);

	this->Write_List_File();
	this->Write_Pay_File();
	this->Write_Wish_File();
	std::cout << "�Ѿ��ϴ��̼�" << std::endl;
	std::cout << "���ﳵ�����ϣ�" << std::endl;

	return;
}

void User::Change_Password()
{
	FILE *file;
	int i = 2;

	if (fopen_s(&file, pass_check_file.c_str(), "r"))
	{
		std::cout << "�޷���ָ�����û��ļ������������ļ����á�" << std::endl;
		exit(-1);
	}
	else
	{

		fscanf_s(file, "%s", user[0][0], THE_STR_LEN + 1);
		fscanf_s(file, "%s", user[0][1], THE_STR_LEN + 1);//������ͷ

		fscanf_s(file, "%s", user[1][0], THE_STR_LEN + 1);
		fscanf_s(file, "%s", user[1][1], THE_STR_LEN + 1);//����һ��


		while (!feof(file))
		{
			fscanf_s(file, "%s", user[i][0], THE_STR_LEN + 1);
			fscanf_s(file, "%s", user[i][1], THE_STR_LEN + 1);
			i++;
		}

		std::string old_password;
		std::string new_password;

		std::string a;
		int j = 0;
		for (; j < i; j++)
		{
			a = user[j][0];
			if (user_name == a)//�ҵ�����û�
				break;
		}
		a = user[j][1];

		std::cout << "����������룺";
		std::cin >> old_password;
		if (old_password == a)
		{
			std::cout << "�����������룺";
			do
			{
				std::cin >> new_password;
				if (new_password.length() > 20)
					std::cout << "���볤�Ȳ��ܴ���20�����������룺";
			} while (new_password.length() > 20);

			strcpy_s(user[j][1], 21, new_password.c_str());//�����������д
			fclose(file);

		}

		else
		{
			std::cout << "�������" << std::endl;
			fclose(file);
			return;
		}
	}

	//������Ҫ���������д���ļ�

	if (fopen_s(&file, pass_check_file.c_str(), "w"))
	{
		std::cout << "�޷���ָ�����û��ļ������������ļ����á�" << std::endl;
		exit(-1);
	}
	else
	{
		for (int j = 0; j < i - 1; j++)
		{
			fprintf_s(file, "%-32s%-32s\n", user[j][0], user[j][1]);
		}
	}

	fclose(file);

	std::cout << "�����޸ĳɹ���" << std::endl;

	return;
}