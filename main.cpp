//Mynor Ruiz 201801329

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>



using namespace std;

#include "structures.h"
#include "exec.h"
#include "mkdisk.h"
#include "rmdisk.h"

int discos=1;

void ejecutar (string cmd){
    if(cmd.size()!=0){
        vector<string> partes = splitt(cmd, tieneComillas(cmd));
        if(lower(partes[0])=="mkdisk"){
            mkdisk(partes, discos);
            discos++;
        }else if(lower(partes[0])=="rmdisk"){
            rmdisk(partes);
        }
    }    
}

int main(){
    string cmd;
    //Ciclo infinito para que la terminal pueda estar siempre en funcion
    while(true){
        //verifica si se desea salir del programa 
        getline(cin,cmd);cout<<endl;
        if((lower(cmd).compare("exit")==0)||(lower(cmd).compare("quit")==0)||(lower(cmd).compare("close")==0)||(lower(cmd).compare("salir")==0)){
            return 0;
        }else if(cmd==""){
        }else{
            ejecutar(automata(cmd));
        }
    }
}