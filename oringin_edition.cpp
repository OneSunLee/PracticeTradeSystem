#include<stdio.h>//商品库存排序文件首行中多了一行0 
#include<stdlib.h> 
#include<string.h> 
//商品信息 
typedef struct _commodity{
	char number[128];//商品编号 
	char name[128];//商品名称 
	double inprice;//商品进价 
	double outprice;//商品售价 
	char origin[128];//商品产地 
	int  inventory;//商品库存; 
}commodity;
//所需功能函数 
void showmenu(int cnt);//菜单栏 
void lr(int n,int cnt);//录入商品 
int sc(int cnt);//删除商品 
int xg(int cnt);//修改商品 
void cx(int cnt);//商品查询 
void sppx(int cnt);//商品库存排序 
void xssp(int cnt);//显示商品 
/*void bctc(int);//保存信息并退出系统 */
//主函数 
int main(){
//----------------统计文件中已有商品的个数并且存放至结构体商品数组中-------------------- 
	int cnt=0;//记录文件中商品个数 
	commodity shop[100];
	FILE *fp;
	fp=fopen("sp.txt","a+");
	if(fp==NULL){
		printf("打开文件失败，请重试！\n");
		system("pause");
		fclose(fp);
		exit(0);
	}
	fscanf(fp,"%s%s%lf%lf%s%d",&shop[cnt].number,&shop[cnt].name,&shop[cnt].inprice,&shop[cnt].outprice,&shop[cnt].origin,&shop[cnt].inventory); 
	while(!feof(fp)){
	cnt++;
	fscanf(fp,"%s%s%lf%lf%s%d",&shop[cnt].number,&shop[cnt].name,&shop[cnt].inprice,&shop[cnt].outprice,&shop[cnt].origin,&shop[cnt].inventory);     

	}
	fclose(fp);
//---------------------------------------------------------------------
	showmenu(cnt);
	return 0;
}
//-----------------菜单栏函数------------------------------------------
void showmenu(int cnt){
	system("cls"); 
	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("★              欢迎使用超市商品管理系统              ★\n");
	printf("★☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆★\n");
	printf("★               1： 录入商品                         ★\n");
	printf("★               2： 删除商品                         ★\n");
	printf("★               3： 修改商品                         ★\n");
	printf("★               4： 商品查询                         ★\n");
	printf("★               5： 商品库存并排序                   ★\n");
	printf("★               6： 显示商品信息                     ★\n");
	printf("★               0： 保存信息并退出系统               ★\n");
	printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("选择操作<0-6>                                         \n");
	//--------------------------------------------------------------------
	int choose,n=0;
	do{
		scanf("%d",&choose);//选择操作 
		switch(choose){
			case 1://录入商品
				system("pause");
				system("cls");
				printf("请选择录入商品的个数:"); 
				scanf("%d",&n);
				lr(n,cnt);
				cnt+=n;
				break;
			case 2://删除商品
				system("pause");
				system("cls");
				cnt=sc(cnt);
				break;
			case 3://修改商品
				system("pause");
				system("cls");
				xg(cnt);
				break;
			case 4://商品查询 
				system("pause");
				system("cls");
				cx(cnt);
				break;
			case 5://商品库存并排序   
				system("pause");
				system("cls");
				sppx(cnt);
				break;
			case 6://显示商品信息  
				system("pause");
				system("cls");
				xssp(cnt);
				break;
		/*	case 0://保存信息并退出系统
				system("pause");
				system("cls");
				bctc();
				break;
			default :
				printf("输出错误，请重试！\n");
				system("pause");
				system("cls");
				break; */
				
		}
	}while(choose!=0);
	system("pause");
}
//----------------录入商品信息函数---------------------------------------
void lr(int n,int cnt){//录入商品的个数 n为录入商品个数，cnt为已经有了的商品个数 
	FILE *fp;
	commodity shop[100];
	fp=fopen("sp.txt","a+");
	if(fp==NULL){
		printf("打开文件失败，请重试！\n");
		system("pause");
		fclose(fp);
		exit(0);
	}
	printf("请输入这%d个商品的\t编号名称\t进价\t售价\t产地\t库存\n",n);
	int i;
	for(i=0;i<n;i++){
		printf("----第%d个商品----\n", i+1);
		printf("商品编号:");
		scanf("%s",&shop[i+cnt].number);
		
		printf("商品名称：");
		scanf("%s,",&shop[i+cnt].name);
		
		printf("商品进价：");
		scanf("%lf",&shop[i+cnt].inprice);
		
		printf("商品售价：");
		scanf("%lf",&shop[i+cnt].outprice);
		
		printf("商品产地：");
		scanf("%s",&shop[i+cnt].origin);
		
		printf("商品产库存：");
		scanf("%d",&shop[i+cnt].inventory);
	} 
	for(i=0;i<n;i++){
		fprintf(fp,"%s\t%s\t%.2lf\t%.2lf\t%s\t%d\n",shop[i+cnt].number,shop[i+cnt].name,shop[i+cnt].inprice,shop[i+cnt].outprice,shop[i+cnt].origin,shop[i+cnt].inventory);
	}
	fclose(fp);
	printf("添加商品信息成功！按任意键返回菜单栏！\n");
	system("pause"); 
	showmenu(cnt);
}
//----------------------------删除信息函数-----------------------------------------
int sc(int cnt){//已知道的商品信息个数； 
	char a[128];
	commodity shop1[100],shop[100];//删除数据以后的结构体数组;
	printf("请输入要删除的商品信息的编号:");
	scanf("%s",a); 
	FILE *fp;
	fp=fopen("sp.txt","r");
	if(fp==NULL){
		printf("打开文件失败，请重试！\n");
		system("pause");
		fclose(fp);
		return -1; 
	}
	int c=0,flag,wz;
	while(!feof(fp)){
		fscanf(fp,"%s%s%lf%lf%s%d",&shop[c].number,&shop[c].name,&shop[c].inprice,&shop[c].outprice,&shop[c].origin,&shop[c].inventory);
		if(strcmp(a,shop[c].number)==0){
			flag=1;
			wz=c;
		}
		c++;
	}
	c--;//注意我们需要输出的数据赋值数，如果不减去就会多一组数据导致0的出现；出现多余一组 
	fclose(fp);
	if(cnt==0){
		printf("已经没有商品信息了,请按任意键返回\n");
		system("pause");
		showmenu(cnt);
		return cnt;
	}
	if(flag==0){
		printf("没有该商品信息,请按任意键返回\n");
		system("pause");
		showmenu(cnt);
		return cnt;
	}else{//删除商品信息； wz=c;shop1[100];
		int i;
		for(i=0;i<c;i++){//8
			if(i<wz){//3
				shop1[i]=shop[i];
			}
			else{
				shop1[i]=shop[i+1];//将搜索到名字的位置后面的结构体数组往前一位顶掉搜索到达成删除效果；
			}
		}
		//写入数据; 
		fp=fopen("sp.txt","w"); 
		for(i=0;i<c-1;i++){
			fprintf(fp,"%s\t%s\t%.2lf\t%.2lf\t%s\t%d\n",shop1[i].number,shop1[i].name,shop1[i].inprice,shop1[i].outprice,shop1[i].origin,shop1[i].inventory);
		}
		fclose(fp);
		printf("编号为%s的商品信息删除成功,请按任意键返回\n",a);
		system("pause");
		showmenu(cnt);
		return	cnt-1;
	}
}
//-------------------------------修改信息函数---------------------------------------
int xg(int cnt){//修改商品函数;
	FILE *fp;
	commodity shop1[100];
	int c=0,flag=0;//c:商品个数，flag：是否找到标志; 
	char a[128];//修改商品的编号 
	printf("请输入要修改的商品信息的编号:");
	scanf("%s",a);
	fp=fopen("sp.txt","r");
	if(fp==NULL){
		printf("打开文件失败，请重试！\n");
		system("pause");
		fclose(fp);
		return -1;
	}
//--------------------------选择修改哪项信息--------------------------------
	while(!feof(fp)){
		int choose=0;
		fscanf(fp,"%s%s%lf%lf%s%d",&shop1[c].number,&shop1[c].name,&shop1[c].inprice,&shop1[c].outprice,&shop1[c].origin,&shop1[c].inventory);
		if(strcmp(a,shop1[c].number)==0){
			printf("找到了你要修改商品信息的有以下内容:\n");
			do{
				flag=1;
				printf("请输入修改信息类型!\n"); 
				printf("★★★★★★★★★★★★\n"); 
				printf("★1.修改商品编号信息! ★\n");
				printf("★☆☆☆☆☆☆☆☆☆☆★\n"); 
				printf("★2.修改商品名称信息！★\n");
				printf("★☆☆☆☆☆☆☆☆☆☆★\n"); 
				printf("★3.修改商品进价信息！★\n");
				printf("★☆☆☆☆☆☆☆☆☆☆★\n"); 
				printf("★4.修改商品售价信息！★\n");
				printf("★☆☆☆☆☆☆☆☆☆☆★\n"); 
				printf("★5.修改商品产地信息！★\n");
				printf("★☆☆☆☆☆☆☆☆☆☆★\n"); 
				printf("★6.修改商品库存信息！★\n");
				printf("★★★★★★★★★★★★\n");
				printf("请选择1~6\n"); 
				scanf("%d",&choose);
				switch(choose){
					case 1:
							printf("商品编号:%s,新编号为:",shop1[c].number);
							scanf("%s",&shop1[c].number);
							break;
					case 2:
							printf("商品名称:%s，新名称为:",shop1[c].name);
							scanf("%s",&shop1[c].name);
							break;
					case 3:
							printf("商品进价:%lf,新进价为:",shop1[c].inprice);
							scanf("%lf",&shop1[c].inprice);
							break;
					case 4:
							printf("商品售价:%lf,新售价为:",shop1[c].outprice);
							scanf("%lf",&shop1[c].outprice);
							break;
					case 5:
							printf("商品产地:%s,新产地为:",shop1[c].origin);
							scanf("%s",&shop1[c].origin);
							break;
					case 6:
							printf("商品库存:%d,新库存为:",shop1[c].inventory);
							scanf("%d",&shop1[c].inventory);
							break;
					case 0:
						printf("输入完毕，停止输入！\n"); 
						break; 
					default :
						printf("输入错误选项，请按任意键重新输入！\n");
						system("pause");
						system("cls");
						break; 
				}
			}while(choose!=0);	
		}
		c++;//商品个数 
	}
	fclose(fp);	
	c--;
//-------------------------修改数据----------------------------------
	int i;
	if(flag==0){
		printf("没有找到该商品，请按任意键退出！\n");
		system("pause"); 
	}else{
		fp=fopen("sp.txt","w");
		for(i=0;i<c;i++){
			fprintf(fp,"%s\t%s\t%.2lf\t%.2lf\t%s\t%d\n",shop1[i].number,shop1[i].name,shop1[i].inprice,shop1[i].outprice,shop1[i].origin,shop1[i].inventory);
		}
		fclose(fp);
		printf("商品信息已经修改完毕，请按任意键返回!\n");
		system("pause");
		}
	showmenu(cnt);
	return 1;
} 
//--------------------------商品查询 ------------------------------------
void cx(int cnt){
	commodity shop[100];
	char a[128];
	FILE *fp;
	fp=fopen("sp.txt","r");
	if(fp==NULL){
		printf("打开文件失败，请重试！\n");
		system("pause");
		fclose(fp);
		exit(0);
	}
	int c=0,i,flag=0;
	//读取商品信息； 
	while(!feof(fp)){
		fscanf(fp,"%s%s%lf%lf%s%d",&shop[c].number,&shop[c].name,&shop[c].inprice,&shop[c].outprice,&shop[c].origin,&shop[c].inventory);
		c++;
	}
	fclose(fp);
	int choose;
	do{
			printf("请输入查询方式!\n"); 
			printf("★★★★★★★★★★★★★★★\n"); 
			printf("★1.按商品编号查询商品信息！★\n");
			printf("★☆☆☆☆☆☆☆☆☆☆☆☆☆★\n"); 
			printf("★2.按商品名称查询商品信息！★\n");
			printf("★☆☆☆☆☆☆☆☆☆☆☆☆☆★\n"); 
			printf("★3.按商品产地查询商品信息！★\n");
			printf("★☆☆☆☆☆☆☆☆☆☆☆☆☆★\n"); 
			printf("★0.按0退出查询系统！QAQ-QVQ★\n");
			printf("★★★★★★★★★★★★★★★\n"); 
			printf("请选择0~3\n"); 
			scanf("%d",&choose);
			switch(choose){
				case 1:
					system("pause");
					printf("请输入商品编号:");
					scanf("%s",a);
					for(i=0;i<c;i++){
						if(strcmp(a,shop[i].number)==0){
							flag=1;
							break;
						}else{
							flag=0;	
						}		
					}
					if(flag==1){
						printf("该商品的信息如下：\n");
						printf("商品编号\t商品名称\t商品进价\t商品售价\t商品产地\t商品库存\t\n"); 
						printf("%s\t\t%s\t\t%.2lf\t\t%.2lf\t\t%s\t\t%d\t\t\n",shop[i].number,shop[i].name,shop[i].inprice,shop[i].outprice,shop[i].origin,shop[i].inventory); 
					}else if(flag==0){
						printf("查无此商品！\n");
						system("pause");
					}
					break;
				case 2:
				system("pause");
					printf("请输入商品名称:");
					scanf("%s",a);
					for(i=0;i<c;i++){
						if(strcmp(a,shop[i].name)==0){
							flag=1;
							break;
						}else{
							flag=0;	
						}		
					}
					if(flag==1){
						printf("该商品的信息如下：\n");
						printf("商品编号\t商品名称\t商品进价\t商品售价\t商品产地\t商品库存\t\n"); 
						printf("%s\t\t%s\t\t%.2lf\t\t%.2lf\t\t%s\t\t%d\t\t\n",shop[i].number,shop[i].name,shop[i].inprice,shop[i].outprice,shop[i].origin,shop[i].inventory); 
					}else if(flag==0){
						printf("查无此商品！\n");
						system("pause");
					}
					break;
				case 3:
					system("pause");
					printf("请输入商品产地:");
					scanf("%s",a);
					for(i=0;i<c;i++){
						if(strcmp(a,shop[i].origin)==0){
							flag=1;
							break;
						}else{
							flag=0;	
						}		
					}
					if(flag==1){
						printf("该商品的信息如下：\n");
						printf("商品编号\t商品名称\t商品进价\t商品售价\t商品产地\t商品库存\t\n"); 
						printf("%s\t\t%s\t\t%.2lf\t\t%.2lf\t\t%s\t\t%d\t\t\n",shop[i].number,shop[i].name,shop[i].inprice,shop[i].outprice,shop[i].origin,shop[i].inventory); 
					}else if(flag==0){
						printf("查无此商品！\n");
						system("pause");
					}
					break;
				case 0:
					printf("成功退出商品查询系统！\n"); 
					system("pause");
					break;
				default :
					printf("输入错误选项，请按任意键重新输入！\n");
					system("pause");
					system("cls");
					break; 				
		}
		if(choose!=0){
		printf("按任意键继续进行查询！\n");
		system("pause");
		system("cls");
		}		
	}while(choose!=0);
	showmenu(cnt); 
}
//--------------------商品排序函数-------------------------------------- 
void sppx(int cnt){
	FILE *fp;
	commodity shop[100],t;
	int c=0,min=0;
	fp=fopen("sp.txt","r");
	if(fp==NULL){
		printf("打开文件失败，请重试！\n");
		system("pause");
		fclose(fp);
		exit(0);
	}
	while(!feof(fp)){
		fscanf(fp,"%s%s%lf%lf%s%d",&shop[c].number,&shop[c].name,&shop[c].inprice,&shop[c].outprice,&shop[c].origin,&shop[c].inventory);
		c++;
	}
	fclose(fp);
	int choose,i,j;
	do{
			printf("请输入排序方式!\n"); 
			printf("★★★★★★★★★★★★\n"); 
			printf("★1.按商品的进价排序！★\n");
			printf("★☆☆☆☆☆☆☆☆☆☆★\n"); 
			printf("★2.按商品的售价排序！★\n");
			printf("★☆☆☆☆☆☆☆☆☆☆★\n"); 
			printf("★3.按商品库存量排序！★\n");
			printf("★☆☆☆☆☆☆☆☆☆☆★\n"); 
			printf("★0.按0-退出排序系统！★\n");
			printf("★★★★★★★★★★★★★★★\n"); 
			printf("请选择0~3\n"); 
			scanf("%d",&choose);
			switch(choose){
				case 1://运用了选择排序思想 
					system("pause");
					for(i=0;i<c-1;i++){//c=6
						min=i;//最进价最高的商品; 
						for(j=i+1;j<c;j++){//c=7;
							if(shop[min].inprice>shop[j].inprice){//如果较小，排名下降一名； 
								min=j;
							}
						}
						t=shop[i];
						shop[i]=shop[min];
						shop[min]=t;
						}
					fp=fopen("sp.txt","w");
					if(fp==NULL){
						printf("打开文件失败，请重试！\n");
						system("pause");
						fclose(fp);
						exit(0);
					}
					for(i=0;i<c;i++){
						fprintf(fp,"%s\t%s\t%.2lf\t%.2lf\t%s\t%d\n",shop[i].number,shop[i].name,shop[i].inprice,shop[i].outprice,shop[i].origin,shop[i].inventory);
					}
					fclose(fp);
					printf("按进价排序完成！按任意键返回！\n");
					system("pause");
					system("cls");
					break;
				case 2:
					system("pause");
					for(i=0;i<c-1;i++){//c=6
						min=i;//最售价最高的商品; 
						for(j=i+1;j<c;j++){//c=7;
							if(shop[min].outprice>shop[j].outprice){//如果较小，排名下降一名； 
								min=j;
							}
						}
						t=shop[i];
						shop[i]=shop[min];
						shop[min]=t;
						}
					fp=fopen("sp.txt","w");
					if(fp==NULL){
						printf("打开文件失败，请重试！\n");
						system("pause");
						fclose(fp);
						exit(0);
					}
					for(i=0;i<c;i++){
						fprintf(fp,"%s\t%s\t%.2lf\t%.2lf\t%s\t%d\n",shop[i].number,shop[i].name,shop[i].inprice,shop[i].outprice,shop[i].origin,shop[i].inventory);
					}
					fclose(fp); 
					printf("按售价排序完成！按任意键返回！\n");
					system("pause");
					system("cls");
					break;
				case 3:
					system("pause");
					for(i=0;i<c-1;i++){//c=6
						min=i;//库存量最高的商品; 
						for(j=i+1;j<c;j++){//c=7;
							if(shop[min].inventory>shop[j].inventory){//如果较小，排名下降一名； 
								min=j;
							}
						}
						t=shop[i];
						shop[i]=shop[min];
						shop[min]=t;
						}
					fp=fopen("sp.txt","w");
					if(fp==NULL){
						printf("打开文件失败，请重试！\n");
						system("pause");
						fclose(fp);
						exit(0);
					}
					for(i=0;i<c;i++){
						fprintf(fp,"%s\t%s\t%.2lf\t%.2lf\t%s\t%d\n",shop[i].number,shop[i].name,shop[i].inprice,shop[i].outprice,shop[i].origin,shop[i].inventory);	
					}
					fclose(fp); 
					printf("按库存量排序完成！按任意键返回！\n");
					system("pause");
					system("cls");
					break;
				case 0:
					printf("成功退出排序系统！\n");
					system("pause");
					break;
				default :
					printf("输入错误选项，请按任意键重新输入！\n");
					system("pause");
					system("cls");
					break; 
			}
		}while(choose!=0);
	showmenu(cnt); 
}
//-------------------显示商品函数---------------------------- 
void xssp(int cnt){
	FILE *fp;
	commodity shop[100];
	int c=0; 
	fp=fopen("sp.txt","r");
	if(fp==NULL){
		printf("打开文件失败，请重试！\n");
		system("pause");
		fclose(fp);
		exit(0);
	}
	while(!feof(fp)){
		fscanf(fp,"%s%s%lf%lf%s%d",&shop[c].number,&shop[c].name,&shop[c].inprice,&shop[c].outprice,&shop[c].origin,&shop[c].inventory);
		c++;
	}
	int i;
	for(i=0;i<c;i++){
		printf("第%d个商品信息为:\n",i+1);
		printf("%s\t%s\t%.2lf\t%.2lf\t%s\t%d\n",shop[i].number,shop[i].name,shop[i].inprice,shop[i].outprice,shop[i].origin,shop[i].inventory);	
					}
	printf("\n商品信息显示完毕！\n");
	system("pause");
	showmenu(cnt);
} 


