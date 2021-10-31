#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

int main(){
    string a = "891454.9039";
    float b;
   
    b = 891454.9039;
    cout<<stof(a)<<endl;
    cout<<fixed<<setprecision(8);
    cout<<b<<endl;

}