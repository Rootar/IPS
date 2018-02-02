// #include "Connection.h"

// int main(){
// 	Connection a;// = Connection;
// 	char pustka[] = {'a','b','c','d','e','f'};
// 	char test[50];
// 	a.cwrite(pustka, sizeof(pustka));

// 	while(true){
// 		int x = a.cread(test,sizeof(test));
// 		if(x > 0){
// 			std::cout << test;
// 			for(int i = 0; i < sizeof(test); i++)
// 				test[i] = '\0';
// 		}
// 	}
			
//     return 0;
// }

#include <iostream>
#include "Communication.h"

using namespace std;

int main(){
    //unsigned int crc = 0xf2f3;

    Communication comm;
    comm.csend((const unsigned char*)"siema",6);
    

    //unsigned char b[2] = {0xf3,0xF0};
    //b[0] = 4;
     //b[0] = crc >> 8;
     //b[1] = crc;

    //cout << hex << crc << endl;

    //cout << endl << bitset<8>(b[0]) << endl << bitset<8>(b[1]);// << endl << b[1];
}