#include<bits/stdc++.h>
using namespace std;



ifstream fin("db.txt");
ofstream fout("db.bin", ios::out | ios::binary);
    

int main(){

    
   long int id;
    double sum;
    while(fin>>id){
        fin>>sum;
        fout.write((char*)&id, sizeof(id));
        fout.write(",", 1);
        fout.write((char*)&sum, sizeof(sum));
        fout.write("\n", 1);
    }

    return 0;
}