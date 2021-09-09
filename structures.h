struct disk{
    int size;
    char ajuste;
    string multiplicador;
    string direccion;
};
struct partition{
	char part_status;
	char part_type;
	char part_fit;
	int part_start;
	int part_size;
	char part_name[16];
};
struct mbr{
    int mbr_tamano;
	time_t mbr_fecha_creacion;
	int mbr_disk_signature;
    char disk_fit;
    partition mbr_partition_1;
    partition mbr_partition_2;
    partition mbr_partition_3;
    partition mbr_partition_4;
};
struct part{
    int size;
    string unidades;
    string direccionDisco;
    char tipo;
    char ajuste;
    int delAdd;
    string del;
    string nombre;
    int add;
};

struct ebr{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
};
struct mnt{
    string id;
    string path;
    string name;
};
struct l_user{
    string user;
    string pass;
    string id;
};
struct new_user{
    string user;
    string pass;
    string group;
};

struct fs{
    string id;
    string type;
    string fileS;
};

struct report{
    string name;
    string path;
    string id;
    string ruta;
};

struct superblock{
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    time_t s_mtime;
    time_t s_umtime;
    int s_mnt_count;
    int s_magic;
    int s_inode_size;
    int s_block_size;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
};
struct inode{
    int i_uid;
    int i_gid;
    int i_size;
    time_t i_atime;
    time_t i_ctime;
    time_t i_mtime;
    int i_block[15];
    char i_type;
    int i_perm;
    char nombre[15];
};
struct content{
    char b_name[12];
    int b_inode;
};
struct dirBlock{
    content b_content[4];
};
struct fileBlock{
    char b_content[64];
};
struct JOURNAL{
    char tipo_operacion[10];
    char tipo;
    char nombre[200];
    char contenido[200];
    char fecha[16];
    char propietario[10];
    int permisos;
};
 
 struct chmod_perm{
    string direccion;
    int ugo;
    bool recursivo;
};

 struct part_mkdir{
    string direccion;
    bool recursivo;
};

#include <iostream>
#include <vector>
#include <dirent.h>

using namespace std;


//Funcion para volver todas las cadenas de entrada en minusculas 

string lower(string cadena ){
    for (int i=0; i< cadena.length();i++){
        int ascii = cadena[i];
        if((ascii>=65) && (ascii<=90))
        {
            ascii+=32;
            cadena[i] = ascii;
        }
    }
    return cadena;
}
 //Funcion que retorna si tiene comillas o no 
 bool tieneComillas(string cadena){
     if(cadena.find("\"") != string ::npos){
         return true;
     }else{
         return false;
     }
 }

//Funcion splitt... realiza todos los split de espacios en blanco para separar la linea de comandos y atributos
 vector<string> splitt(string cadena, bool comillas){
     vector<string> array;
     int tamano = cadena.length();
     if(comillas == false ){
         string temporal = "";
         int elementos =0;
         bool esp = false ;
         for(int i=0; i< tamano ; i++){
             int ascii = cadena[i];
             if(ascii == 32){
                 if(esp == false){
                     array.push_back(temporal);
                     temporal = "" ; 
                     elementos++;
                     esp = true;
                 }
             }else{
                 esp = false;
                 temporal += cadena[i];
             }

         }
         if(temporal.length()>0){
             array.push_back(temporal);
             temporal = "";
         }
     }else{
         string temporal = "";
         int elementos = 0 ; 
         bool com = false ;
         bool esp = false ;
         for(int i = 0; i < tamano; i++){
             int ascii = cadena[i];
             if (ascii == 34){
                 esp = false; 
                 if(com == false){
                     temporal += cadena[i];
                     com = true;
                 } else{
                     temporal += cadena[i];
                     com = false;
                 }
             }else{
                 if(ascii == 32 ){
                     if(esp == false){
                         if(com == false ){
                             array.push_back(temporal);
                             temporal = "";
                             elementos++;
                             esp = true;
                         }else{
                             temporal += cadena[i];
                         }
                     }
                 }else{
                     esp = false;
                     temporal += cadena[i];
                 }
             }
        }
        if(temporal.length()>0){
            array.push_back(temporal);
            temporal = "";
        }
     }

     return array;
 }

//Funcion split... separa las cadenas segun un separador
 vector<string> split(string cadena, string separador){
    vector<string> array;
    string temporal = "";
    for(int i=0;i<cadena.length();i++){
        int ascii = cadena[i];
        int ascii2 = separador[0];
        if(ascii==ascii2){
            if(temporal!=""){
                array.push_back(temporal);
                temporal = "";
            }
        }else{
            temporal += cadena[i];
        }
    }
    if(temporal.length()>0){
        array.push_back(temporal);
    }
    return array;
}
//Funcion split_bloque... separa las cadenas segun un separador
 vector<string> split_bloque(string cadena){
    vector<string> array;
    string temporal = "";
    for(int i=0;i<cadena.length();i++){
        int ascii = cadena[i];
        if(((i+1) % 64) == 0 ){

            temporal += cadena[i];
            
            array.push_back(temporal);
                        temporal ="";
        }else if((i+1) == cadena.length()){
            temporal += cadena[i];
            array.push_back(temporal);
            temporal ="";
            break;
        }else{
            temporal += cadena[i];
        }
    }
    return array;
}
//Comprobar direccion dentro de la computadora
void comprobarDireccion(string direccion){
    vector<string> lista = split(direccion,"/");
    string path = "";
    for(int i=1;i<lista.size();i++){
        path += "/"+lista[i-1];
        DIR * directorio;
        if(directorio=opendir(path.c_str())){
        }else{
            //mkdir(path.c_str(),ACCESSPERMS);
        }
    }
}
string quitarComillas(string cadena){
    string salida= "";
    for(int i=0;i<cadena.length();i++){
        if(cadena[i]!='\"'){
            salida+=cadena[i];
        }
    }
    return salida;
}
//verifica si existe un disco
bool exists(string path){
    FILE * disco;
    if(disco = fopen(path.c_str(),"r")){
        fclose(disco);
        return true;
    }
    return false;
}
//Convertir informacion de disco en texto
string convertToString(char * entrada, int size){
    string salida = "";
    for(int i=0;i<size;i++){
        if(entrada[i]!='\0'){
            salida += entrada[i];
        }
    }
    return salida;
}
//Funcion que retorna el nombre de archivo 
string obtenerNombre(string dir){
    vector<string>temporal = split(dir, "/");
    return temporal[temporal.size()-1];
}