#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

//Funcion que busca si una particion ya esta montada en memoria
bool existeMontada(string id){
    for( int i=0; i < particionesMontadas.size();i++){
        if((particionesMontadas[i].id == id)||(particionesMontadas[i].name == id)){
            return true;
        }
    }
    return false;
}
//Funcion que monta una particion a memoria
bool montar(mnt part){
    if (existeMontada(part.name)==false)
    {
        FILE * disco;
        if (disco = fopen(part.path.c_str(),"rb"))
        {
            mbr master;
            fseek(disco,0,SEEK_SET);
            fread(&master,sizeof(master),1,disco);
            if (existeParticion(part.name,master,disco))
            {
                string identificador;
                for (int i = 0; i < letras.size(); i++)
                {
                    identificador = "29";
                    identificador += to_string(master.mbr_disk_signature);
                    identificador += letras[i];
                    if (existeMontada(identificador)==false)
                    {
                        part.id=identificador;
                        particionesMontadas.push_back(part);
                        cout<<"Particion '"<<part.name<<"' montada como '"<<part.id<<"' exitosamente"<<endl;
                        for(mnt mont:particionesMontadas){
                            cout<<"Path:"<<mont.path<<"  |  Nombre:"<<mont.name<<"  |  Id:"<<mont.id<<endl;
                        }
                        return true;
                    }
                }
                cout<<"No se pueden montar mas particiones en este disco"<<endl;
                return false;
            }else{
                cout<<"La particion no existe en el disco"<<endl;
                return false;
            }
               
        }else{
            cout<<"La direccion de disco no es valida"<<endl;
            return false;
        }
    }else{
        cout<<"Esta particion ya esta montada en el sistema"<<endl;
        return false;
    }
    
}

//Funcion de comando mount que verifica los parametros ingresados
void mount (vector<string> partes){
    mnt part = { "", "", "" };
    bool problem = false;
    for(int i=0; i< partes.size();i++){
        vector<string> componenetes = split(partes[i],"=");
        if(lower(componenetes[0])=="mount"){
            //reconoce el primer parametro con la palabra mount
        }else if(lower(componenetes[0])=="-path"){
            part.path = quitarComillas(componenetes[1]);
        }else if (lower(componenetes[0])=="-name")
        {
            part.name = quitarComillas(componenetes[1]);
        }else{
            cout<<"Comando '"<<componenetes[0]<<"' no valido"<<endl;
            problem = true;
        }
    }
    if(problem==true){
    }else if((part.name=="")||(part.path=="")){
        cout<<"Parametros obligatorios incompletos"<<endl;
    }else{
        montar(part);
    }
    
}
/*
mount -path=/home/user/Disco1.dk -name=Particion1
umount -id=291a
*/