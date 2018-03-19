#include <queue>
#include <iostream>
#include "Communication.h"
#include <string>
#include <cstdlib>

using namespace std;

int main(){
    Communication com;
    queue<string> que;
    FILE* fp = fopen("plik", "a");

    //com.csend("siema");
    // com.csend("elo");
    // com.csend("elo2");
    // com.csend("elo30");
    
    char a[6] = {101, 102, 103, 104, 105, 0};
    com.csend(a, 6);
    
    sleep(5);
    
    com.creceive(que);
    
    while(!que.empty()){
        cout << que.front() << endl;
        fwrite(que.front().c_str(), 6/*que.front().length()*/, 1, fp);
        que.pop();
    }

    fclose(fp);
}