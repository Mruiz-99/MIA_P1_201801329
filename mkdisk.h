#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

void crearDisco(disk disco, int id){
    comprobarDireccion(disco.direccion);
    FILE * archivo;
    if(archivo=fopen(disco.direccion.c_str(),"wb+")){
        int multiplicador = 0;
        if(disco.multiplicador=="k"){
            multiplicador = 1;
        }else if(disco.multiplicador=="m"){
            multiplicador = 1024;
        }else{
            cout<<"La unidad "<<disco.multiplicador<<" no es reconocible"<<endl;
        }
        //crea la variable nulo que son 1024 ceros
        char nulo[1024];
        for(int i=0;i<1024;i++){
            nulo[i]='\0';
        }
        //Ingresa los ceros al archivo (dico)
        for(int i=0;i<(multiplicador*disco.size);i++){
            fwrite(&nulo,sizeof(nulo),1,archivo);
        }
        //se posiciona al principio de archivo 
        fseek(archivo,0,SEEK_SET);
        int tamano = disco.size*multiplicador*1024;
        partition def;
        def.part_status='n';
        //Escribe el struct del MBR en el archivo 
        mbr MBR={tamano,time(0),id,disco.ajuste,def,def,def,def};
        fwrite(&MBR,sizeof(mbr),1,archivo);
        fclose(archivo);
        cout<<"Disco creado exitosamente"<<endl;
    }else{
        cout<<"Error al crear el disco"<<endl;
    }
}
void mkdisk(vector<string>Argumentos, int id){
    disk disco = {0,'f',"m",""};
    bool problem=false;
    for(int i=0;i<Argumentos.size();i++){
        vector<string> componentes = split(Argumentos[i],"=");
        if(lower(componentes[0])=="mkdisk"){

        }else if(lower(componentes[0])=="-size"){
            if(atoi(componentes[1].c_str())>=0){
                disco.size=atoi(componentes[1].c_str());
            }else{
                cout<<"Tamaño del disco no valido"<<endl;
                problem=true;
            }
            disco.size=atoi(componentes[1].c_str());
        }else if(lower(componentes[0])=="-f"){
            if((lower(componentes[1])=="b")||(lower(componentes[1])=="f")||(lower(componentes[1])=="w")||(lower(componentes[1])=="bf")||(lower(componentes[1])=="ff")||(lower(componentes[1])=="wf")){
                char tmp [strlen(componentes[1].c_str())+1];
                strcpy(tmp,lower(componentes[1]).c_str());
                disco.ajuste=tmp[0];
            }else{
                cout<<"Ajuste ingresado no valido"<<endl;
                problem=true;
            }
        }else if(lower(componentes[0])=="-u"){
            if((lower(componentes[1])=="m")||(lower(componentes[1])=="k")){
                disco.multiplicador=lower(componentes[1]);
            }else{
                cout<<"Unidades ingresadas no validas"<<endl;
                problem=true;
            }
        }else if(lower(componentes[0])=="-path"){
            if((split(componentes[1],".")[1]=="dk")||(split(componentes[1],".")[1]=="dk\"")){
                disco.direccion=quitarComillas(componentes[1]);
            }else{
                cout<<"Extesion del disco no valida"<<endl;
                problem=true;
            }
        }else{
            cout<<"Comando mkdisk no valido"<<endl;
                problem=true;
        }
    }
    if(problem==true){
    }else if((disco.size==0)||(disco.direccion=="")){
        cout<<"Parametros obligatorios incompletos"<<endl;
    }else{
        crearDisco(disco,id);
    }
}