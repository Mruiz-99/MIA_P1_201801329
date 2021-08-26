#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

//Funcion que desmonta una particion de la memoria
void desmontar(string id){
    if(existeMontada(id)){
        vector<mnt>temporal;
        for(int i=0;i<particionesMontadas.size();i++){
            if((particionesMontadas[i].id!=id)){
                temporal.push_back(particionesMontadas[i]);
            }
        }
        particionesMontadas = temporal;
        cout<<"La particion '"<<id<<"' fue desmontada con exito"<<endl;
    }else{
        cout<<"La particion '"<<id<<"' no esta montada"<<endl;
    }
}
//Funcion de comando umount que verifica los parametros ingresados
void umount(vector<string>partes){
    string id="";
    bool problem = false;
    for(int i=0;i<partes.size();i++){
        vector<string> componentes = split(partes[i],"=");
        if(lower(componentes[0])=="umount"){
        }else if(lower(componentes[0])=="-id"){
            id = quitarComillas(componentes[1]);
        }else{
            cout<<"Comando '"<<componentes[0]<<"' no valido"<<endl;
            problem = true;
        }
    }
    if(problem==true){
    }else if(id==""){
        cout<<"Parametros obligatorios incompletos"<<endl;
    }else{
        desmontar(lower(id));
    }
}