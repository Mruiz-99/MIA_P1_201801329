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
#include "fdisk.h"

int discos=1;

void ejecutar (string cmd){
    if(cmd.size()!=0){
        vector<string> partes = splitt(cmd, tieneComillas(cmd));
        if(lower(partes[0])=="mkdisk"){
            mkdisk(partes, discos);
            discos++;
        }else if(lower(partes[0])=="rmdisk"){
            rmdisk(partes);
        }else if(lower(partes[0])=="fdisk"){
            fdisk(partes);
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
/*
MKdisk -size=3000 -u=k -path=/home/user/Disco1.dk
fdisk -type=e -path=/home/user/Disco1.dk -u=k -size=300 -name=Particion1
fdisk -size=600 -type=l  -u=B -f=ff -path=/home/user/Disco1.dk -name=Particion2
fdisk -size=1 -type=p -u=k -f=ff -path=/home/user/Disco1.dk -name=Particion2
fdisk -delete=fast -path=/home/user/Disco1.dk -name=Particion2
fdisk -add=50 -u=B -path=/home/user/Disco1.dk -name=Particion4

*/