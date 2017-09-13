#ifndef GOODS_H
#define GOODS_H

#include<iostream>
#include<string> 
using std::cout;
using std::endl;
using std::string;

bool add_goods( string name, int count );                                      //进数量为count,名称为name的货物
bool increase_count ( int count, int index );                                  //待进货商品在清单中时调用该函数来增加商品数量
bool add_to_list( string name, int count );                                    //待进货商品不在清单中时调用该函数来将商品增加到清单中
bool delete_goods( string name, int count );                                   //出数量为count,名称为name的货物
bool decrease_count( int count, int index );                                   //当待出货商品数量与出货数量不等时调用该函数
bool delete_from_list( int index );                                            //待出货商品数量等于出货数量时调用该函数，移除索引为index的商品
int lsearchName( string name );                                                //在容器中线性搜索商品中名称与name相同的对象
void find_goods( string name );                                                //查找名称为name的货物，查找成功输出名称数量，失败则输出提示
void show_goods();                                                             //展示所有商品
int getRequest();                                                              //需求选项提示，会要求用户输入需求并返回其值
enum RequestType { ADD_GOODS = 1, DELETE_GOODS, SHOW_GOODS, FIND_GOODS, END }; //枚举变量，1至5分别对应进货、出货、展示商品、查找商品、结束

class Goods {
//定义名称为Goods的类
	public:                            //公共成员函数
		Goods( string = "", int = 0 ); //默认构造函数，缺省值为空字符串和0

		void setGoodsName( string );   //设置名称函数
		string getGoodsName() const;   //获取名称函数

		void setGoodsCount( int );     //设置数量函数
		int getGoodsCount() const;     //获取数量函数
	private:                           //私有成员变量
		char name[ 30 ];               //商品名称(加上'\0'不超过30个字符)
		int count;                     //商品数量
};

Goods::Goods( string goodsName, int goodsCount ) {
	setGoodsName( goodsName );
	setGoodsCount( goodsCount );
}

void Goods::setGoodsName( string goodsName ) {
	int length = goodsName.size();
	length = ( length < 30 ? length : 29 );
	goodsName.copy( name, length );
	name[ length ] = '\0';                       //将长度大于30的字符串剪到30
}

void Goods::setGoodsCount( int goodsCount ) {
	if ( goodsCount < 0 ) {
		cout << "\nInvalid count!" << endl
		     << "The count of goods" << "( " << name << " )"
		     << " is set to 0." << endl;
		count = 0;
	}                                             //保证商品初始数量为正
	else
		count = goodsCount;
}

string Goods::getGoodsName() const {
	return name;
}

int Goods::getGoodsCount() const {
	return count;
}

#endif


