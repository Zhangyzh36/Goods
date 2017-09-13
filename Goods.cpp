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
	fstream inOutGoods;                             //�����ļ������������
	inOutGoods.open( "Goods.txt", ios::in );        //�������ļ�"Goods.txt"����ʱ��������������

	Goods blankGoods;                               //����Goods��Ŀն���
	string goodsName;                               //��Ʒ����
	int goodsCount;                                 //��Ʒ����

	while( inOutGoods >> goodsName >> goodsCount ) { //���ļ������������Ʒ���Ƽ����������丳����Ӧ����
		blankGoods.setGoodsName( goodsName );       //����blankGoods����
		blankGoods.setGoodsCount( goodsCount );     //����blankGoods����
		goods.push_back( blankGoods );	            //��blankGoodsѹ��������
	}                                               //21-25���ǽ��ļ��еĳ�ʼ���ݴ����������Ա�������Ĳ���

	inOutGoods.close();                              //�ر��ļ�

	cout << "Welcome!" << endl;
	int request;                                     //���û����������ѡ��(��Ӧ�����ö�ٱ���RequestType)
	request = getRequest();							 //�û�����ѡ��

	while ( request != END ) {                       //�û�δѡ�����
		switch( request ) {
			case ADD_GOODS: {                                              //��������
				cout << "\nPlease enter the name and count of the goods to be added" << endl;
				cout << "Name(no space): ";
				cin >> goodsName;                                          //�����������Ʒ����
				cout << "Count: ";
				cin >> goodsCount;                                         //�����������Ʒ����

				while ( goodsCount <= 0 ) {
					cout << "\nCount should be more than 0" << endl
					     << "Please enter the count again: ";
					cin >> goodsCount;
				}                                                          //42-46�У���֤����Ĵ���������Ʒ����Ϊ��ֵ

				add_goods( goodsName, goodsCount );
				break;
			}
			case DELETE_GOODS: {                                           //��������
				cout << "\nPlease enter the name and count of the goods to be deleted" << endl;
				cout << "Name(no space): ";
				cin >> goodsName;                                          //�����������Ʒ����
				cout << "Count: ";
				cin >> goodsCount;                                         //�����������Ʒ����

				while ( goodsCount <= 0 ) {
					cout << "\nCount should be more than 0" << endl
					     << "Please enter the count again: ";
					cin >> goodsCount;
				}                                                          //58-62�У���֤����Ĵ���������Ʒ����Ϊ��ֵ

				delete_goods( goodsName, goodsCount );
				break;
			}
			case SHOW_GOODS: {                                             //չʾ��Ʒ����
				cout << "\nAll the goods are as follows: \n" << endl;
				show_goods();
				break;
			}
			case FIND_GOODS: {                                             //������Ʒ����
				cout << "\nPlease enter the name of the goods you want to find" << endl;
				cout << "Name(no space): ";
				cin >> goodsName;
				find_goods( goodsName );
				break;
			}
			default:
				break;
		}

		request = getRequest();                                              //�û��ٴμ�������
	}

	cout << "\nEnd of run." << endl;                                          //�û�����5(����)������ѭ��
	cout << "\nThanks for using!" << endl;

	inOutGoods.open( "Goods.txt", ios::out );                                //���ļ��������"Goods.txt"�����������������

	for ( int i = 0; i != goods.size(); ++i )
		inOutGoods << left << setw( 30 ) << goods[ i ].getGoodsName()
		           << goods[ i ].getGoodsCount() << endl;                     //91-93�У��������е���������д���ļ�����
	inOutGoods.close();                                                       //�ر��ļ�

	return 0;	                                                               //�������ս�
}

void show_goods() {                                                           //չʾ������Ʒ
	cout << left << setw( 30 ) << "Name" << "Count" << endl;
	for ( int i = 0; i != goods.size(); ++i )
		cout << left << setw( 30 ) << goods[ i ].getGoodsName()
		     << right << setw( 5 ) << goods[ i ].getGoodsCount() << endl;      //�������е������������Ļ��
}

int getRequest() {                                                            //����û����������ѡ��
	char request;

	cout << "\nEnter request" << endl
	     << " 1 - Add goods" << endl
	     << " 2 - Delete goods" << endl
	     << " 3 - Show goods" << endl
	     << " 4 - Find goods" << endl
	     << " 5 - End of run" << endl;                                         //��ʾ�û���������ѡ��
	
	cin >> request;
	
	while ( !isdigit( request ) || request - '0' < ADD_GOODS && request - '0' > END )
	{
		cout << "\n? ";
		cin >> request;
	} 														                     //��֤�û������������1-5֮��

	return request - '0';                                                           //�����û����������(һ����1-5��)
}

int lsearchName( string name ) {                                              //������������������Ʒ��������name��ͬ�Ķ���
	const char *str1 = name.c_str();                                          //��stringת��Ϊconst char *
	for ( int i = 0; i != goods.size(); ++i ) {
		const char *str2 =  ( goods[ i ].getGoodsName() ).c_str();
		if ( strcmp( str1, str2 ) == 0 )                                      //�ַ����Ƚ�
			return i;                                                         //��������ͬ�򷵻������±�
	}

	return -1;                                                                //��û���������򷵻�-1
}

bool add_goods( string name, int count ) {                                    //������Ϊcount,����Ϊname�Ļ���
	int index = lsearchName( name );

	if ( index != -1 )                                                        //����������Ʒ����Ʒ�嵥��
		return increase_count( count, index );                                //���Ӹ���Ʒ������
	else                                                                      //����������Ʒ������Ʒ�嵥��
		return add_to_list( name, count );                                    //������Ʒ���ӵ��嵥��
}

bool increase_count( int count, int index ) {                                 //��������Ʒ���嵥��ʱ���øú�����������Ʒ����
	int curCount = goods[ index ].getGoodsCount();                            //��ȡ��������Ʒ��ǰ����
	goods[ index ].setGoodsCount( curCount + count );                         //���´�������Ʒ����
	cout << "\nThe count of " << goods[ index ].getGoodsName()
	     << " has increased to " << goods[ index ].getGoodsCount() << endl;
	return true;
}

bool add_to_list( string name, int count ) {                                  //��������Ʒ�����嵥��ʱ���øú���������Ʒ���ӵ��嵥��
	Goods blankGoods;                                                         //�����յ���Ʒ����
	blankGoods.setGoodsName( name );                                          //������Ʒ����
	blankGoods.setGoodsCount( count );                                        //������Ʒ����
	goods.push_back( blankGoods );                                            //���������Ʒ�嵥
	cout << "\nThe new goods " << name << " has been added to the list" << endl;
	return true;
}

bool delete_goods( string name, int count ) {                                 //������Ϊcount,����Ϊname�Ļ�
	int index = lsearchName( name );

	if ( index != -1 ) {                                                      //��������Ʒ���嵥��
		int curCount = goods[ index ].getGoodsCount();                        //��ȡ����Ʒ��ǰ������

		if ( curCount == count )                                              //������Ʒ��ǰ������Ҫ�������������
			return delete_from_list( index );                                 //������Ʒ�Ƴ����嵥
		else                                                                  //����
			return decrease_count( count, index );                            //���ٸ���Ʒ������

	} else if ( index == -1 ) {                                               //����������Ʒ�����嵥��
		cout << "\nThe goods " << name << " is not in the list." << endl;     //��Ļ�����ʾ
		return false;
	}

}

bool decrease_count( int count, int index ) {                                 //����������Ʒ�����������������ʱ���øú���
	int curCount = goods[ index ].getGoodsCount();                            //��ȡ��������Ʒ��ǰ����

	if ( curCount > count ) {                                                 //����ǰ��������Ҫ����������
		goods[ index ].setGoodsCount( curCount - count );                     //��Ʒ�������ٲ�����
		cout << "\nThe count of " << goods[ index ].getGoodsName()
		     << " has decreased to " << goods[ index ].getGoodsCount() << endl;
		return true;
	} else {                                                                  //����
		cout << "\nThe count of " << goods[ index ].getGoodsName()            //�����ʾ��Ʒ��������
		     << " is not enough" << endl;
		return false;
	}

}

bool delete_from_list( int index ) {                                          //��������Ʒ�������ڳ�������ʱ���øú������Ƴ�����Ϊindex����Ʒ
	cout << "\nThe goods " << goods[ index ].getGoodsName() << " has been deleted from the list" << endl;
	goods.erase( goods.begin() + index );                                     //������Ϊindex����Ʒ���嵥���Ƴ�
	return true;
}

void find_goods( string name ) {                                              //��������Ϊname�Ļ���
	int index = lsearchName( name );

	if ( index != -1 )                                                        //���嵥���ҵ�
		cout << left << setw( 31 ) << "\nName" << "Count" << endl
		     << left << setw( 30 ) << goods[ index ].getGoodsName()
		     << right << setw( 5 ) << goods[ index ].getGoodsCount() << endl;
	else                                                                      //δ���嵥���ҵ�
		cout << "\nThe goods " << name << " is not in the list." << endl;

}
