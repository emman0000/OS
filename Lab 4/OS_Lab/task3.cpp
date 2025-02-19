#include<iostream>
#include<unistd.h>
using namespace std;

void printUserID(){
cout<<"UID: "<<getuid()<<endl;}

int main(){
cout<<"Current PID: "<<getpid()<<endl;
cout<<"Parent  PID: "<<getppid()<<endl;

printUserID();
return 0;
}
