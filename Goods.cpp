#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include"Goods.h"
using namespace std;

vector<Goods> goods;

int main() {
	fstream inOutGoods;                             //创建文件输入输出对象
	inOutGoods.open( "Goods.txt", ios::in );        //关联到文件"Goods.txt"，暂时仅用其输入数据

	Goods blankGoods;                               //创建Goods类的空对象
	string goodsName;                               //商品名称
	int goodsCount;                                 //商品数量

	while( inOutGoods >> goodsName >> goodsCount ) { //从文件中逐个输入商品名称及数量并将其赋给对应变量
		blankGoods.setGoodsName( goodsName );       //设置blankGoods名称
		blankGoods.setGoodsCount( goodsCount );     //设置blankGoods数量
		goods.push_back( blankGoods );	            //将blankGoods压入容器中
	}                                               //21-25行是将文件中的初始数据存入容器中以便接下来的操作

	inOutGoods.close();                              //关闭文件

	cout << "Welcome!" << endl;
	int request;                                     //待用户输入的需求选项(对应上面的枚举变量RequestType)
	request = getRequest();							 //用户输入选项

	while ( request != END ) {                       //用户未选择结束
		switch( request ) {
			case ADD_GOODS: {                                              //进货功能
				cout << "\nPlease enter the name and count of the goods to be added" << endl;
				cout << "Name(no space): ";
				cin >> goodsName;                                          //输入待进货商品名称
				cout << "Count: ";
				cin >> goodsCount;                                         //输入待进货商品数量

				while ( goodsCount <= 0 ) {
					cout << "\nCount should be more than 0" << endl
					     << "Please enter the count again: ";
					cin >> goodsCount;
				}                                                          //42-46行：保证输入的待进货的商品数量为正值

				add_goods( goodsName, goodsCount );
				break;
			}
			case DELETE_GOODS: {                                           //出货功能
				cout << "\nPlease enter the name and count of the goods to be deleted" << endl;
				cout << "Name(no space): ";
				cin >> goodsName;                                          //输入待出货商品名称
				cout << "Count: ";
				cin >> goodsCount;                                         //输入待出货商品数量

				while ( goodsCount <= 0 ) {
					cout << "\nCount should be more than 0" << endl
					     << "Please enter the count again: ";
					cin >> goodsCount;
				}                                                          //58-62行：保证输入的待出货的商品数量为正值

				delete_goods( goodsName, goodsCount );
				break;
			}
			case SHOW_GOODS: {                                             //展示商品功能
				cout << "\nAll the goods are as follows: \n" << endl;
				show_goods();
				break;
			}
			case FIND_GOODS: {                                             //查找商品功能
				cout << "\nPlease enter the name of the goods you want to find" << endl;
				cout << "Name(no space): ";
				cin >> goodsName;
				find_goods( goodsName );
				break;
			}
			default:
				break;
		}

		request = getRequest();                                              //用户再次键入需求
	}

	cout << "\nEnd of run." << endl;                                          //用户键入5(结束)，结束循环
	cout << "\nThanks for using!" << endl;

	inOutGoods.open( "Goods.txt", ios::out );                                //将文件其关联到"Goods.txt"，并向其中输出数据

	for ( int i = 0; i != goods.size(); ++i )
		inOutGoods << left << setw( 30 ) << goods[ i ].getGoodsName()
		           << goods[ i ].getGoodsCount() << endl;                     //91-93行：将容器中的所有数据写入文件保存
	inOutGoods.close();                                                       //关闭文件

	return 0;	                                                               //主函数终结
}

void show_goods() {                                                           //展示所有商品
	cout << left << setw( 30 ) << "Name" << "Count" << endl;
	for ( int i = 0; i != goods.size(); ++i )
		cout << left << setw( 30 ) << goods[ i ].getGoodsName()
		     << right << setw( 5 ) << goods[ i ].getGoodsCount() << endl;      //将容器中的数据输出到屏幕上
}

int getRequest() {                                                            //获得用户输入的需求选项
	char request;

	cout << "\nEnter request" << endl
	     << " 1 - Add goods" << endl
	     << " 2 - Delete goods" << endl
	     << " 3 - Show goods" << endl
	     << " 4 - Find goods" << endl
	     << " 5 - End of run" << endl;                                         //提示用户输入需求选项
	
	cin >> request;
	
	while ( !isdigit( request ) || request - '0' < ADD_GOODS && request - '0' > END )
	{
		cout << "\n? ";
		cin >> request;
	} 														                     //保证用户输入的需求在1-5之间

	return request - '0';                                                           //返回用户输入的需求(一定在1-5间)
}

int lsearchName( string name ) {                                              //在容器中线性搜索商品中名称与name相同的对象
	const char *str1 = name.c_str();                                          //将string转化为const char *
	for ( int i = 0; i != goods.size(); ++i ) {
		const char *str2 =  ( goods[ i ].getGoodsName() ).c_str();
		if ( strcmp( str1, str2 ) == 0 )                                      //字符串比较
			return i;                                                         //若名称相同则返回索引下标
	}

	return -1;                                                                //若没有搜索到则返回-1
}

bool add_goods( string name, int count ) {                                    //进数量为count,名称为name的货物
	int index = lsearchName( name );

	if ( index != -1 )                                                        //若待进货商品在商品清单中
		return increase_count( count, index );                                //增加改商品的数量
	else                                                                      //若待进货商品不再商品清单中
		return add_to_list( name, count );                                    //将该商品增加到清单中
}

bool increase_count( int count, int index ) {                                 //待进货商品在清单中时调用该函数来增加商品数量
	int curCount = goods[ index ].getGoodsCount();                            //获取待进货商品当前数量
	goods[ index ].setGoodsCount( curCount + count );                         //更新待进货商品数量
	cout << "\nThe count of " << goods[ index ].getGoodsName()
	     << " has increased to " << goods[ index ].getGoodsCount() << endl;
	return true;
}

bool add_to_list( string name, int count ) {                                  //待进货商品不在清单中时调用该函数来将商品增加到清单中
	Goods blankGoods;                                                         //创建空的商品对象
	blankGoods.setGoodsName( name );                                          //设置商品名称
	blankGoods.setGoodsCount( count );                                        //设置商品数量
	goods.push_back( blankGoods );                                            //将其加入商品清单
	cout << "\nThe new goods " << name << " has been added to the list" << endl;
	return true;
}

bool delete_goods( string name, int count ) {                                 //出数量为count,名称为name的货
	int index = lsearchName( name );

	if ( index != -1 ) {                                                      //待出货商品在清单中
		int curCount = goods[ index ].getGoodsCount();                        //获取该商品当前的数量

		if ( curCount == count )                                              //若该商品当前数量与要出货的数量相等
			return delete_from_list( index );                                 //将该商品移除出清单
		else                                                                  //否则
			return decrease_count( count, index );                            //减少该商品的数量

	} else if ( index == -1 ) {                                               //若待出货商品不在清单中
		cout << "\nThe goods " << name << " is not in the list." << endl;     //屏幕输出提示
		return false;
	}

}

bool decrease_count( int count, int index ) {                                 //当待出货商品数量与出货数量不等时调用该函数
	int curCount = goods[ index ].getGoodsCount();                            //获取待出货商品当前数量

	if ( curCount > count ) {                                                 //若当前数量大于要出货的数量
		goods[ index ].setGoodsCount( curCount - count );                     //商品数量减少并更新
		cout << "\nThe count of " << goods[ index ].getGoodsName()
		     << " has decreased to " << goods[ index ].getGoodsCount() << endl;
		return true;
	} else {                                                                  //否则
		cout << "\nThe count of " << goods[ index ].getGoodsName()            //输出提示商品数量不足
		     << " is not enough" << endl;
		return false;
	}

}

bool delete_from_list( int index ) {                                          //待出货商品数量等于出货数量时调用该函数，移除索引为index的商品
	cout << "\nThe goods " << goods[ index ].getGoodsName() << " has been deleted from the list" << endl;
	goods.erase( goods.begin() + index );                                     //将索引为index的商品从清单中移除
	return true;
}

void find_goods( string name ) {                                              //查找名称为name的货物
	int index = lsearchName( name );

	if ( index != -1 )                                                        //在清单中找到
		cout << left << setw( 31 ) << "\nName" << "Count" << endl
		     << left << setw( 30 ) << goods[ index ].getGoodsName()
		     << right << setw( 5 ) << goods[ index ].getGoodsCount() << endl;
	else                                                                      //未在清单中找到
		cout << "\nThe goods " << name << " is not in the list." << endl;

}
