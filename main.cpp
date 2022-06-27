
/*我重写这个是为了练习c++。

原版的实现是个本科生，用c，每个函数都打开文件，统计行数，存入数组，存数组的开销很大;
函数没有返回，是靠调用showmenu实现到达初始界面，最终内存占用越来越大，改成主函数中的循环;
原版是静态数组，改成了vector<>。

原版c没有用传址，我c++传引用，没太大差别。

原版的实现add_items中有个scanf，如果%lf的是字符串，会陷入死循环，改成了ostream。

原版的修改是跳转到指定行覆写。

删除部分直接重写。*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>
//商品信息
struct glocery_item
{
	char number[128];	  //商品编号
	char name[128];		  //商品名称
	double buying_price;  //商品进价
	double selling_price; //商品售价
	char origin[128];	  //商品产地
	int inventory;		  //商品库存;
};

//所需功能函数id
void init_load_items(std::vector<glocery_item> &shop); //初始化加载
void save_file(std::vector<glocery_item> &shop);	   //保存数据
void showmenu(std::vector<glocery_item> &shop);		   //菜单栏
void show_items(std::vector<glocery_item> &shop);	   //显示商品
void add_items(std::vector<glocery_item> &shop);	   //录入商品
void remove_item(std::vector<glocery_item> &shop);	   //删除商品
void modify_item(std::vector<glocery_item> &shop);	   //修改商品
void search_item(std::vector<glocery_item> &shop);	   //商品查询
void sort_items(std::vector<glocery_item> &shop);	   //商品库存排序
/*void bctc(int);//保存信息并退出系统 */
//主函数
int main()
{
	//---------初始化加载---------
	std::vector<glocery_item> shop;
	shop.reserve(128); //先预先分配一段内存
	init_load_items(shop);
	//----------------------------------------------------------
	while (1)
		showmenu(shop);
	return 0;
}
//--------------------------初始化加载--------------------------
void init_load_items(std::vector<glocery_item> &shop)
{
	int i[10];
	FILE *fp;
	glocery_item temp_shop;
	int count_items = 0;
	fp = fopen("items.csv", "r");
	if (fp == NULL)
	{
		std::cout << "打开文件失败，请重试！" << std::endl;
		std::cin.get();
		fclose(fp);
		exit(0);
	}
	while (!feof(fp))
	{
		shop.emplace_back();
		fscanf(fp, "%s%s%lf%lf%s%d", shop[count_items].number, shop[count_items].name, &shop[count_items].buying_price, &shop[count_items].selling_price, shop[count_items].origin, &shop[count_items].inventory);
		++count_items;
	}
	fclose(fp);
}
//--------------------------保存数据--------------------------
void save_file(std::vector<glocery_item> &shop)
{

	std::ofstream ostrm("items.csv", std::ios::binary);
	if (ostrm.fail())
	{
		std::cout << "无法打开商品数据文件items.csv，退出程序。";
		exit(0);
	}
	for (std::vector<glocery_item>::iterator iter = shop.begin(); iter != shop.end(); iter++)
	{
		ostrm << (*iter).number << '\t' << (*iter).name
			  << '\t' << (*iter).buying_price << '\t' << (*iter).selling_price
			  << '\t' << (*iter).origin << '\t' << (*iter).inventory;
		if (iter != shop.end() - 1)
			ostrm << '\n';
	}
}
//--------------------------菜单栏函数----------------------------
void showmenu(std::vector<glocery_item> &shop)
{
	system("clear");
	std::cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n";
	std::cout << "★              欢迎使用超市商品管理系统       ★\n";
	std::cout << "★☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆★\n";
	std::cout << "★               1： 显示所有商品信息          ★\n";
	std::cout << "★               2： 录入商品                  ★\n";
	std::cout << "★               3： 删除商品                  ★\n";
	std::cout << "★               4： 修改商品                  ★\n";
	std::cout << "★               5： 商品查询                  ★\n";
	std::cout << "★               6： 商品库存排序              ★\n";
	std::cout << "★               0： 保存信息并退出系统        ★\n";
	std::cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n";
	std::cout << "选择操作<0-6>                                    " << std::endl;
	//--------------------------------------------------------------------
	int choose;
	std::cin >> choose; //选择操作
	system("clear");
	switch (choose)
	{
	case 0: //退出
		save_file(shop);
		exit(0);
	case 1: //显示商品信息
		show_items(shop);
		break;
	case 2: //录入商品
		add_items(shop);
		save_file(shop);
		break;
	case 3: //删除商品
		remove_item(shop);
		save_file(shop);
		break;
	case 4: //修改商品
		modify_item(shop);
		save_file(shop);
		break;
	case 5: //商品查询
		search_item(shop);
		break;
	case 6: //商品库存排序
		sort_items(shop);
		save_file(shop);
		break;
	default:
		std::cout << "输入错误，请重试！" << std::endl;
		std::cin.ignore();
		std::cin.get();
		break;
	}
}
//--------------------------显示商品--------------------------
void show_items(std::vector<glocery_item> &shop)
{
	int i;
	std::cout << "\t\t\t"
			  << "编号" << '\t' << "名称" << '\t' << "买价" << '\t' << "卖价" << '\t' << "产地" << '\t' << "库存" << std::endl;
	for (i = 0; i < shop.size(); i++)
	{
		std::cout << "第" << i + 1 << "个商品信息为：\t";
		std::cout << shop[i].number << '\t' << shop[i].name << '\t' << shop[i].buying_price << '\t' << shop[i].selling_price << '\t' << shop[i].origin << '\t' << shop[i].inventory << std::endl;
	}
	std::cout << "\n商品信息显示完毕！按任意键返回。" << std::endl;
	std::cin.ignore();
	std::cin.get();
}

//--------------------------录入商品信息函数-----------------------
void add_items(std::vector<glocery_item> &shop)
{
	std::cout << "请输入这<<n<<个商品的\t编号名称\t进价\t售价\t产地\t库存" << std::endl;
	int index_new_item = shop.size() - 1;
	char on_flag = 'y';
	while (on_flag == 'y')
	{
		shop.emplace_back();
		++index_new_item;
		std::cout << "----第" << index_new_item + 1 << "个商品----" << std::endl;
		std::cout << "商品编号： " << std::endl;
		std::cin >> shop[index_new_item].number;

		std::cout << "商品名称：" << std::endl;
		std::cin >> shop[index_new_item].name;

		std::cout << "商品进价：" << std::endl;
		std::cin >> shop[index_new_item].buying_price;

		std::cout << "商品售价：" << std::endl;
		std::cin >> shop[index_new_item].selling_price;

		std::cout << "商品产地：" << std::endl;
		std::cin >> shop[index_new_item].origin;

		std::cout << "商品库存：" << std::endl;
		std::cin >> shop[index_new_item].inventory;

		std::cout << "是否继续添加商品条目？y继续；0退出。\n";
		std::cin >> on_flag;
	}

	std::cout << "添加商品信息成功！按任意键返回菜单栏！" << std::endl;
	std::cin.ignore();
	std::cin.get();
}
//--------------------------删除信息函数--------------------------
void remove_item(std::vector<glocery_item> &shop)
{
	std::string cmp;
	bool find_flag = false;
	std::vector<glocery_item>::iterator iter;
	std::cout << "请输入要删除的商品的编号或名称：" << std::endl;
	std::cin >> cmp;
	for (iter = shop.begin(); iter != shop.end(); iter++)
	{
		if (!cmp.compare((*iter).number) || !cmp.compare((*iter).name))
		{
			find_flag = true;
			std::cout << "找到商品：" << std::endl;
			std::cout << (*iter).number << '\t' << (*iter).name
					  << '\t' << (*iter).buying_price << '\t' << (*iter).selling_price
					  << '\t' << (*iter).origin << '\t' << (*iter).inventory << std::endl;
			std::cout << "是否删除商品条目？y删除，0不删除。" << std::endl;
			std::cin.ignore();
			if (std::cin.get() == 'y')
			{
				iter = shop.erase(iter);
				--iter;
				std::cout << "已删除。" << std::endl;
			}
			std::cout << "是否继续查找？y继续；0退出。" << std::endl;
			std::cin.ignore();
			if (std::cin.get() != 'y')
				break;
		}
	}
	if (find_flag == false)
	{
		std::cout << "没有找到相应条目，按任意键退出。" << std::endl;
		std::cin.ignore();
		std::cin.get();
	}
	else if(iter==shop.end())
	{
		std::cout << "已遍历全部商品。按任意键退出。" << std::endl;
		std::cin.ignore();
		std::cin.get();
	}
}
//--------------------------修改信息函数--------------------------
void modify_item(std::vector<glocery_item> &shop)
{

	std::string cmp;
	bool find_flag = false;//是否找到
	int choose = 0;//选择第几项
	std::vector<glocery_item>::iterator iter;
	std::cout << "请输入要修改的商品的编号或名称：" << std::endl;
	std::cin >> cmp;
	for (iter = shop.begin(); iter != shop.end(); iter++)
	{
		if (!cmp.compare((*iter).number) || !cmp.compare((*iter).name))
		{
			find_flag = true;
			std::cout << "找到商品：" << std::endl;
			std::cout << (*iter).number << '\t' << (*iter).name
					  << '\t' << (*iter).buying_price << '\t' << (*iter).selling_price
					  << '\t' << (*iter).origin << '\t' << (*iter).inventory << std::endl;
			std::cout << "是否修改商品条目？y修改，n不修改。" << std::endl;
			std::cin.ignore();
			if (std::cin.get() == 'y')
			{
				do
				{
					std::cout << "★★★★★★★★★★★★★★★★★★★★★★" << std::endl;
					std::cout << "★请输入修改信息类型：★" << std::endl;
					std::cout << "★☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆★" << std::endl;
					std::cout << "★1.修改商品编号信息! ★" << std::endl;
					std::cout << "★2.修改商品名称信息！★" << std::endl;
					std::cout << "★3.修改商品进价信息！★" << std::endl;
					std::cout << "★4.修改商品售价信息！★" << std::endl;
					std::cout << "★5.修改商品产地信息！★" << std::endl;
					std::cout << "★6.修改商品库存信息！★" << std::endl;
					std::cout << "★0.结束本条修改输入！★" << std::endl;
					std::cout << "★★★★★★★★★★★★★★★★★★★★★★" << std::endl;
					std::cout << "请选择1~6" << std::endl;
					std::cin >> choose;
					system("clear");
					std::cout << (*iter).number << '\t' << (*iter).name
						  << '\t' << (*iter).buying_price << '\t' << (*iter).selling_price
						  << '\t' << (*iter).origin << '\t' << (*iter).inventory << std::endl;
					switch (choose)
					{
					case 1:
						std::cout << "商品编号：" << (*iter).number << "，新编号为：" << std::endl;
						std::cin >> (*iter).number;
						break;
					case 2:
						std::cout << "商品名称：" << (*iter).name << "，新名称为：" << std::endl;
						std::cin >> (*iter).name;
						break;
					case 3:
						std::cout << "商品进价：" << (*iter).buying_price << "，新进价为：" << std::endl;
						std::cin >> (*iter).buying_price;
						break;
					case 4:
						std::cout << "商品售价：" << (*iter).selling_price << "，新售价为：" << std::endl;
						std::cin >> (*iter).selling_price;
						break;
					case 5:
						std::cout << "商品产地：" << (*iter).origin << "，新产地为：" << std::endl;
						std::cin >> (*iter).origin;
						break;
					case 6:
						std::cout << "商品库存：" << (*iter).inventory << "，新库存为：" << std::endl;
						std::cin >> (*iter).inventory;
						break;
					case 0:
						std::cout << "输入完毕，停止输入！" << std::endl;
						break;
					default:
						std::cout << "结束本条修改输入！" << std::endl;
					}
				} while (choose != 0);
			}
			std::cout << "是否继续查找\""<<cmp<<"\"？y继续；0退出。" << std::endl;
			std::cin.ignore();
			if (std::cin.get() != 'y')
				break;
		}
	}
	if (find_flag == false)
	{
		std::cout << "没有找到相应条目，按任意键退出。" << std::endl;
		std::cin.ignore();
		std::cin.get();
	}
	else if(iter==shop.end())
	{
		std::cout << "已遍历全部商品。按任意键退出。" << std::endl;
		std::cin.ignore();
		std::cin.get();
	}
}
//--------------------------商品查询-----------------------------
void search_item(std::vector<glocery_item> &shop)
{
	char a[128];
	FILE *fp;
	fp = fopen("items.csv", "r");
	if (fp == NULL)
	{
		std::cout << "打开文件失败，请重试！" << std::endl;
		std::cin.get();
		fclose(fp);
		exit(0);
	}
	int c = 0, i, flag = 0;
	//读取商品信息；
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%lf%s%d", shop[c].number, shop[c].name, &shop[c].buying_price, &shop[c].selling_price, shop[c].origin, &shop[c].inventory);
		c++;
	}
	fclose(fp);
	int choose;
	do
	{
		std::cout << "请输入查询方式！" << std::endl;
		std::cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★★★" << std::endl;
		std::cout << "★1.按商品编号查询商品信息！★" << std::endl;
		std::cout << "★☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆★" << std::endl;
		std::cout << "★2.按商品名称查询商品信息！★" << std::endl;
		std::cout << "★☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆★" << std::endl;
		std::cout << "★3.按商品产地查询商品信息！★" << std::endl;
		std::cout << "★☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆★" << std::endl;
		std::cout << "★0.按0退出查询系统！QAQ-QVQ★" << std::endl;
		std::cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★★★" << std::endl;
		std::cout << "请选择0~3" << std::endl;
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			std::cin.get();
			std::cout << "请输入商品编号：" << std::endl;
			scanf("%s", a);
			for (i = 0; i < c; i++)
			{
				if (strcmp(a, shop[i].number) == 0)
				{
					flag = 1;
					break;
				}
				else
				{
					flag = 0;
				}
			}
			if (flag == 1)
			{
				std::cout << "该商品的信息如下：" << std::endl;
				std::cout << "商品编号\t商品名称\t商品进价\t商品售价\t商品产地\t商品库存\t" << std::endl;
				std::cout << shop[i].number << "\t\t" << shop[i].name << "\t\t" << shop[i].buying_price << "\t\t" << shop[i].selling_price << "\t\t" << shop[i].origin << "\t\t" << shop[i].inventory << "\t\t" << std::endl;
			}
			else if (flag == 0)
			{
				std::cout << "查无此商品！" << std::endl;
				std::cin.get();
			}
			break;
		case 2:
			std::cin.get();
			std::cout << "请输入商品名称：" << std::endl;
			scanf("%s", a);
			for (i = 0; i < c; i++)
			{
				if (strcmp(a, shop[i].name) == 0)
				{
					flag = 1;
					break;
				}
				else
				{
					flag = 0;
				}
			}
			if (flag == 1)
			{
				std::cout << "该商品的信息如下：" << std::endl;
				std::cout << "商品编号\t商品名称\t商品进价\t商品售价\t商品产地\t商品库存\t" << std::endl;
				std::cout << shop[i].number << "\t\t" << shop[i].name << "\t\t" << shop[i].buying_price << "\t\t" << shop[i].selling_price << "\t\t" << shop[i].origin << "\t\t" << shop[i].inventory << "\t\t" << std::endl;
			}
			else if (flag == 0)
			{
				std::cout << "查无此商品！" << std::endl;
				std::cin.get();
			}
			break;
		case 3:
			std::cin.get();
			std::cout << "请输入商品产地：" << std::endl;
			scanf("%s", a);
			for (i = 0; i < c; i++)
			{
				if (strcmp(a, shop[i].origin) == 0)
				{
					flag = 1;
					break;
				}
				else
				{
					flag = 0;
				}
			}
			if (flag == 1)
			{
				std::cout << "该商品的信息如下：" << std::endl;
				std::cout << "商品编号\t商品名称\t商品进价\t商品售价\t商品产地\t商品库存\t" << std::endl;
				std::cout << shop[i].number << "\t\t" << shop[i].name << "\t\t" << shop[i].buying_price << "\t\t" << shop[i].selling_price << "\t\t" << shop[i].origin << "\t\t" << shop[i].inventory << "\t\t" << std::endl;
			}
			else if (flag == 0)
			{
				std::cout << "查无此商品！" << std::endl;
				std::cin.get();
			}
			break;
		case 0:
			std::cout << "成功退出商品查询系统！" << std::endl;
			std::cin.get();
			break;
		default:
			std::cout << "输入错误选项，请按任意键重新输入！" << std::endl;
			std::cin.get();
			system("clear");
			break;
		}
		if (choose != 0)
		{
			std::cout << "按任意键继续进行查询！" << std::endl;
			std::cin.get();
			system("clear");
		}
	} while (choose != 0);
}
//--------------------------商品排序函数--------------------------
void sort_items(std::vector<glocery_item> &shop)
{
	FILE *fp;
	glocery_item t;
	int c = 0, min = 0;
	fp = fopen("items.csv", "r");
	if (fp == NULL)
	{
		std::cout << "打开文件失败，请重试！" << std::endl;
		std::cin.get();
		fclose(fp);
		exit(0);
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%lf%lf%s%d", shop[c].number, shop[c].name,
		&shop[c].buying_price, &shop[c].selling_price,
		shop[c].origin, &shop[c].inventory);
		c++;
	}
	fclose(fp);
	int choose, i, j;
	do
	{
		std::cout << "请输入排序方式!" << std::endl;
		std::cout << "★★★★★★★★★★★★★★★★★★★" << std::endl;
		std::cout << "★1.按商品的进价排序！★" << std::endl;
		std::cout << "★☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆★" << std::endl;
		std::cout << "★2.按商品的售价排序！★" << std::endl;
		std::cout << "★☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆★" << std::endl;
		std::cout << "★3.按商品库存量排序！★" << std::endl;
		std::cout << "★☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆★" << std::endl;
		std::cout << "★0.按0-退出排序系统！★" << std::endl;
		std::cout << "★★★★★★★★★★★★★★★★★★★" << std::endl;
		std::cout << "请选择0~3" << std::endl;
		scanf("%d", &choose);
		switch (choose)
		{
		case 1: //运用了选择排序思想
			for (i = 0; i < c - 1; i++)
			{ // c=6
				min = i; //最进价最高的商品;
				for (j = i + 1; j < c; j++)
				{ // c=7;
					if (shop[min].buying_price > shop[j].buying_price)
					{ //如果较小，排名下降一名；
						min = j;
					}
				}
				t = shop[i];
				shop[i] = shop[min];
				shop[min] = t;
			}
			fp = fopen("items.csv", "w");
			if (fp == NULL)
			{
				std::cout << "打开文件失败，请重试！" << std::endl;
				std::cin.get();
				fclose(fp);
				exit(0);
			}
			for (i = 0; i < c; i++)
			{
				fprintf(fp, "%s\t%s\t%.2lf\t%.2lf\t%s\t%d\n", shop[i].number, shop[i].name, shop[i].buying_price, shop[i].selling_price, shop[i].origin, shop[i].inventory);
			}
			fclose(fp);
			std::cout << "按进价排序完成！按任意键返回！" << std::endl;
			std::cin.get();
			system("clear");
			break;
		case 2:
			for (i = 0; i < c - 1; i++)
			{			 // c=6
				min = i; //最售价最高的商品;
				for (j = i + 1; j < c; j++)
				{ // c=7;
					if (shop[min].selling_price > shop[j].selling_price)
					{ //如果较小，排名下降一名；
						min = j;
					}
				}
				t = shop[i];
				shop[i] = shop[min];
				shop[min] = t;
			}
			fp = fopen("items.csv", "w");
			if (fp == NULL)
			{
				std::cout << "打开文件失败，请重试！" << std::endl;
				std::cin.get();
				fclose(fp);
				exit(0);
			}
			for (i = 0; i < c; i++)
			{
				fprintf(fp, "%s\t%s\t%.2lf\t%.2lf\t%s\t%d\n", shop[i].number, shop[i].name, shop[i].buying_price, shop[i].selling_price, shop[i].origin, shop[i].inventory);
			}
			fclose(fp);
			std::cout << "按售价排序完成！按任意键返回！" << std::endl;
			std::cin.get();
			system("clear");
			break;
		case 3:
			for (i = 0; i < c - 1; i++)
			{			 // c=6
				min = i; //库存量最高的商品;
				for (j = i + 1; j < c; j++)
				{ // c=7;
					if (shop[min].inventory > shop[j].inventory)
					{ //如果较小，排名下降一名；
						min = j;
					}
				}
				t = shop[i];
				shop[i] = shop[min];
				shop[min] = t;
			}
			fp = fopen("items.csv", "w");
			if (fp == NULL)
			{
				std::cout << "打开文件失败，请重试！" << std::endl;
				std::cin.get();
				fclose(fp);
				exit(0);
			}
			for (i = 0; i < c; i++)
			{
				fprintf(fp, "%s\t%s\t%.2lf\t%.2lf\t%s\t%d\n", shop[i].number, shop[i].name, shop[i].buying_price, shop[i].selling_price, shop[i].origin, shop[i].inventory);
			}
			fclose(fp);
			std::cout << "按库存量排序完成！按任意键返回！" << std::endl;
			std::cin.get();
			system("clear");
			break;
		case 0:
			std::cout << "成功退出排序系统！" << std::endl;
			std::cin.get();
			system("clear");
			break;
		default:
			std::cout << "输入错误选项，请按任意键重新输入！" << std::endl;
			std::cin.get();
			system("clear");
		}
	} while (choose != 0);
}
