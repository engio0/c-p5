// expre_reinterpret_cast_Operator.cpp 
// compile with: /EHsc 

#include <iostream> 

// 포인터의 주소에 기반하여 해쉬 값을 반환함.
unsigned short Hash( void *p ) 
{
	// reinterpret_cast로 void* -> int 형변환
	// 물론 C 스타일 캐스팅 : val = (unsigned int)p; 로도 가능하긴 하다.
	unsigned int val = reinterpret_cast<unsigned int>( p ); 
	return ( unsigned short )( val ^ (val >> 16) ); 
}

int main() 
{ 
	int a[20]; 

	for ( int i = 0; i < 20; i++ ) 
		std::cout << Hash( a + i ) << std::endl; 
}
