// expre_reinterpret_cast_Operator.cpp 
// compile with: /EHsc 

#include <iostream> 

// �������� �ּҿ� ����Ͽ� �ؽ� ���� ��ȯ��.
unsigned short Hash( void *p ) 
{
	// reinterpret_cast�� void* -> int ����ȯ
	// ���� C ��Ÿ�� ĳ���� : val = (unsigned int)p; �ε� �����ϱ� �ϴ�.
	unsigned int val = reinterpret_cast<unsigned int>( p ); 
	return ( unsigned short )( val ^ (val >> 16) ); 
}

int main() 
{ 
	int a[20]; 

	for ( int i = 0; i < 20; i++ ) 
		std::cout << Hash( a + i ) << std::endl; 
}
