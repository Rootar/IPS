#include <queue>
#include <iostream>
#include "Communication.h"
#include <string>

using namespace std;

int main(){
    Communication com;
    queue<string> que;
    com.csend("siema");
    com.csend("elo");
    com.csend("elo2");
    com.csend("elo3");
    
    sleep(5);
    
    com.creceive(que);
    
    while(!que.empty()){
        cout << que.front() << endl;
        que.pop();
    }
}