#include"outlook.h"
#include"head3.0.h"

using namespace std;

/*
��֮ǰ��1.X�汾���Ѿ����Ż���������˻�������Ҫ������й���
���ԣ���֮���2.X�汾�У������й��ܵ�С����Լ�������Ż�
��Ϊ�ڶ�����汾�ĸ���
*/

/*
�Ͻ��ĵ�һ��������ִ�д�����2.0�汾
��2.0�Ĵ����У��������ڸ����ʱ����еĽ��Ľ��㣬����ѯ���Ƿ���и������ȡ������Ĺ���



*/


/*
��֮ǰ�İ汾2.1�У��Ѿ������̽�������ʾ��Ҳ�޸��˿���޷��ı��bug��
����ε�3.X�汾�У���Ҫ���и��ӹ��ܵı�д������һЩϸ�ڵ��޸ģ�����   2018.4.17
*/


int main()
{
	Outlook UI;
	string input;



	UI.print_start(1);

	UI.main_menu();//���˵�


	cin >> input;

	while (input != "0")
	{
		Admin the_admin;
		User the_user;
		if (input == "1")
		{
			if (the_user.Pass_Check())
			{
				//std::cout << "�û���¼�ɹ���" << std::endl;

				system("pause");
				system("CLS");

				the_user.Init_The_Store_List();
				the_user.Init_Wish_List();//�̵�ĳ�ʼ��һ��Ҫ����ǰ�棬��Ϊ֮��Ĺ��ﳵ��һ����������Ҫ����
				the_user.Init_Pay_List();

				UI.user_menu();
				cout << "���������Ĳ�����";
				cin >> input;
				while (input != "0")//0Ϊע������
				{
					if (input == "1")
					{
						the_user.Print_List();
					}
					else if (input == "2")
					{
						the_user.Search();
					}
					else if (input == "3")
					{
						the_user.Add_Wish();
					}

					else if (input == "4")
					{
						the_user.Print_Wish_List();
					}
					else if (input == "5")
					{
						the_user.Change_Wish();
					}
					else if (input == "6")
					{
						the_user.Pay();
					}
					else if (input == "7")
					{
						the_user.Change_Password();
					}
					else
					{
						cout << "��" << input << "��Ϊ���Ϸ������룬���������룺";
					}
					UI.low();
					cin >> input;
					system("CLS");
					UI.user_menu();
				}
				cout << "�����˻��Ѿ�ע����" << endl;
			}
		}
		else if (input == "2")
		{
			the_user.New_User();
		}
		else if (input == "3")
		{
			

			if (the_admin.Pass_Check())
			{
				system("pause");
				system("CLS");
				the_admin.Init_Sold_List();
				the_admin.Init_The_Store_List();//��Ϊһ��ʼ������Ϣ�ĳ�ʼ��
				
				UI.admin_menu();
				cout << "�����������";
				cin >> input;
				//�����Ƕ���Ŀ¼�Ĳ���������������ѡ��
				while (input != "0")
				{
					if (input == "1")//��ѯ��Ʒ
					{
						the_admin.Print_List();
					}
					else if (input == "2")
					{
						the_admin.Add_List();
					}
					else if (input == "3")
					{
						the_admin.Delete_Thing();
					}
					else if (input == "4")
					{
						the_admin.Change_List();
					}
					else if (input == "5")
					{
						the_admin.Print_Sold_List();
					}
					else
					{
						cout << "��" << input << "��" << "Ϊ���Ϸ��Ĳ�������" << endl;
					}
					UI.low();
					cin >> input;
					system("CLS");
					UI.admin_menu();

				}
				cout << "���Ѿ�ע���˺ţ�" << endl;
			}
		}


		else
		{
			cout << "��" << input << "��Ϊ���Ϸ������룬���������룺";
		}

		the_admin.~Admin();//��������������
		the_user.~User();
		system("pause");
		system("CLS");
		UI.main_menu();
		cin >> input;
	}

	system("CLS");
	UI.goodbye();
	std::cout << "ϵͳ�رգ�" << std::endl;
	system("pause");

	return 0;
}