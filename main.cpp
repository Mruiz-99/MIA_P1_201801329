//Mynor Ruiz 201801329

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;





int main(){
    string cmd;
    //Ciclo infinito para que la terminal pueda estar siempre en funcion
    while(true){
        getline(cin,cmd);   cout<<endl;
        //verifica si se desea salir del programa 
        getline(cin,cmd);cout<<endl;
        if((lower(cmd).compare("exit")==0)||(lower(cmd).compare("quit")==0)||(lower(cmd).compare("close")==0)||(lower(cmd).compare("salir")==0)){
            return 0;
        }else if(cmd==""){
        }else{

        }
    }
}