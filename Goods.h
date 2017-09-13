#ifndef GOODS_H
#define GOODS_H

#include<iostream>
#include<string> 
using std::cout;
using std::endl;
using std::string;

bool add_goods( string name, int count );                                      //������Ϊcount,����Ϊname�Ļ���
bool increase_count ( int count, int index );                                  //��������Ʒ���嵥��ʱ���øú�����������Ʒ����
bool add_to_list( string name, int count );                                    //��������Ʒ�����嵥��ʱ���øú���������Ʒ���ӵ��嵥��
bool delete_goods( string name, int count );                                   //������Ϊcount,����Ϊname�Ļ���
bool decrease_count( int count, int index );                                   //����������Ʒ�����������������ʱ���øú���
bool delete_from_list( int index );                                            //��������Ʒ�������ڳ�������ʱ���øú������Ƴ�����Ϊindex����Ʒ
int lsearchName( string name );                                                //������������������Ʒ��������name��ͬ�Ķ���
void find_goods( string name );                                                //��������Ϊname�Ļ�����ҳɹ��������������ʧ���������ʾ
void show_goods();                                                             //չʾ������Ʒ
int getRequest();                                                              //����ѡ����ʾ����Ҫ���û��������󲢷�����ֵ
enum RequestType { ADD_GOODS = 1, DELETE_GOODS, SHOW_GOODS, FIND_GOODS, END }; //ö�ٱ�����1��5�ֱ��Ӧ������������չʾ��Ʒ��������Ʒ������

class Goods {
//��������ΪGoods����
	public:                            //������Ա����
		Goods( string = "", int = 0 ); //Ĭ�Ϲ��캯����ȱʡֵΪ���ַ�����0

		void setGoodsName( string );   //�������ƺ���
		string getGoodsName() const;   //��ȡ���ƺ���

		void setGoodsCount( int );     //������������
		int getGoodsCount() const;     //��ȡ��������
	private:                           //˽�г�Ա����
		char name[ 30 ];               //��Ʒ����(����'\0'������30���ַ�)
		int count;                     //��Ʒ����
};

Goods::Goods( string goodsName, int goodsCount ) {
	setGoodsName( goodsName );
	setGoodsCount( goodsCount );
}

void Goods::setGoodsName( string goodsName ) {
	int length = goodsName.size();
	length = ( length < 30 ? length : 29 );
	goodsName.copy( name, length );
	name[ length ] = '\0';                       //�����ȴ���30���ַ�������30
}

void Goods::setGoodsCount( int goodsCount ) {
	if ( goodsCount < 0 ) {
		cout << "\nInvalid count!" << endl
		     << "The count of goods" << "( " << name << " )"
		     << " is set to 0." << endl;
		count = 0;
	}                                             //��֤��Ʒ��ʼ����Ϊ��
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


