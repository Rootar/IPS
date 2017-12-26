#include "Connection.h"

//const void* buff

int main(){
    // char pustka[] = {'a','b','c','d','e'};
    // //int *wskPustka = &pustka; 
    // //int liczba = 5;
    // //int* pustka = &liczba;
    // write (fd, pustka, sizeof(pustka));           // send 7 character greeti$

    // usleep ((7 + 25) * 1000);             // sleep enough to transmit the 7 $
    //                                     // receive 25:  approx 100 uS per c$
    // char buf [100];
    // //int n = read (fd, buf, sizeof buf);  // read up to 100 characters if r$

    // while(true){
    //         read(fd,buf,sizeof(buf));
    //         std::cout << buf << std::endl;
    // }

	Connection a;// = Connection;
	char pustka[] = {'a','b','c','d','e','f'};
	char test[3] = {'e','l','o'};
	a.cwrite(pustka, sizeof(pustka));
    return 0;
}
