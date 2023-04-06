#include<bits/stdc++.h>
using namespace std;



//ifstream fin("db.txt");
ifstream fin("db.bin", ios::out | ios::binary);
    

int main(){

    int id;
    double sum;
    char c;
    cout<<"somsome";
    while(fin.read((char*)&id, sizeof(id))){
        cout<<id<<" ";
        fin.read((char*)&c, sizeof(c));
        fin.read((char*)&sum, sizeof(sum));
        cout<<sum<<"\n";
        fin.read((char*)&c, sizeof(c));
    }  
   

    return 0;
}