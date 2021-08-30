#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void ext2(fs sistema){
    if(existeMontada(sistema.id)){
        FILE * disco;
        if(disco = fopen(obtenerDireccion(sistema.id).c_str(),"rb+")){
            mbr master;
            fseek(disco,0,SEEK_SET);
            fread(&master,sizeof(master),1,disco);
            partition particion = obtenerParticion(master,obtenerN(sistema.id));
            superblock sb;
            int n = (int) ((float)(particion.part_size-sizeof(sb)-(100*sizeof(fileBlock)))/(float)(sizeof(inode)+(3*sizeof(fileBlock))+4));
            sb.s_filesystem_type = 2;
            sb.s_inodes_count = n;
            sb.s_blocks_count = 3*n;
            sb.s_free_blocks_count = 3*n-2;
            sb.s_free_inodes_count = n-2;
            sb.s_mtime = time(0);
            sb.s_umtime = time(0);
            sb.s_mnt_count = 1;
            sb.s_magic = fsys;
            fsys++;
            sb.s_inode_size = sizeof(inode);
            sb.s_block_size = sizeof(fileBlock);
            sb.s_first_ino = 2;
            sb.s_first_blo = 2;
            sb.s_bm_inode_start = particion.part_start+sizeof(superblock);
            sb.s_bm_block_start = particion.part_start+sizeof(superblock)+(sizeof(char)*n);
            sb.s_inode_start = particion.part_start+sizeof(superblock)+(sizeof(char)*n)+(sizeof(char)*3*n);
            sb.s_block_start = particion.part_start+sizeof(superblock)+(sizeof(char)*n)+(sizeof(char)*3*n)+(sizeof(inode)*n);
            char bm_inodes [n];
            for(int i=0;i<n;i++){
                bm_inodes[i]='0';
            }
            bm_inodes[0]='1';
            bm_inodes[1]='1';
            char bm_blocks [3*n];
            for(int i=0;i<(3*n);i++){
                bm_blocks[i]='0';
            }
            bm_blocks[0]='1';
            bm_blocks[1]='1';
            fseek(disco,particion.part_start,SEEK_SET);
            fwrite(&sb,sizeof(sb),1,disco);
            fseek(disco,sb.s_bm_inode_start,SEEK_SET);
            fwrite(bm_inodes,sizeof(bm_inodes),1,disco);
            fseek(disco,sb.s_bm_block_start,SEEK_SET);
            fwrite(bm_blocks,sizeof(bm_blocks),1,disco);
            if(sistema.type=="full"){
                inode def;
                fseek(disco,sb.s_inode_start,SEEK_SET);
                for(int i=0;i<n;i++){
                    fwrite(&def,sizeof(def),1,disco);
                }
                fileBlock bloque;
                fseek(disco,sb.s_block_start,SEEK_SET);
                for(int i=0;i<(3*n);i++){
                    fwrite(&bloque,sizeof(bloque),1,disco);
                }
            }
            inode root = {0,0,sizeof(fileBlock),time(0),time(0),time(0),{0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},'0',0,'/'};
            content c1 = {".",0};
            content c2 = {"..",-1};
            content c3 = {"user.txt",1};
            content c4;
            dirBlock b1 = {{c1,c2,c3,c4}};
            inode usr = {0,0,sizeof(fileBlock),time(0),time(0),time(0),{1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},'1',0,"/user.txt"};
            fileBlock b2 = {"1,G,root\n1,U,root,root,123"};
            fseek(disco,sb.s_inode_start,SEEK_SET);
            fwrite(&root,sizeof(root),1,disco);
            fwrite(&usr,sizeof(usr),1,disco);
            fseek(disco,sb.s_block_start,SEEK_SET);
            fwrite(&b1,sizeof(b1),1,disco);
            fwrite(&b2,sizeof(b2),1,disco);
            fclose(disco);
            cout<<"Sistema de archivos creado correctamente"<<endl;
        }else{
            cout<<"El archivo de disco no existe"<<endl;
        }
    }else{
        cout<<"La particion no esta montada"<<endl;
    }
}

//Funcion que formatea una particion con formato ext3
void ext3(fs sistema){

}

//Funcion de comando mkfs que verifica los parametros ingresados
void mkfs(vector<string>partes){
    fs sistema = {"","full","2fs"};
    bool problem = false;
    for(int i=0;i<partes.size();i++){
        vector<string> componentes = split(partes[i],"=");
        if(lower(componentes[0])=="mkfs"){
        }else if(lower(componentes[0])=="-id"){
            sistema.id = lower(componentes[1]);
        }else if(lower(componentes[0])=="-type"){
            if((lower(componentes[1])=="fast")||(lower(componentes[1])=="full")){
                sistema.type = lower(componentes[1]);
            }else{
                cout<<"Tipo de formato '"<<componentes[1]<<"' invalido"<<endl;
                problem=true;
            }
        }else if(lower(componentes[0])=="-fs"){
            if((lower(componentes[1])=="2fs")||(lower(componentes[1])=="3fs")){
                sistema.fileS = lower(componentes[1]);
            }else{
                cout<<"Sistema de archivos '"<<componentes[1]<<"' invalido"<<endl;
                problem=true;
            }
        }else{
            cout<<"Atributo '"<<componentes[0]<<"' invalido"<<endl;
            problem = true;
        }
    }
    if(problem==true){
    }else if(sistema.id==""){
        cout<<"Parametros obligatorios incompletos"<<endl;
    }else{
        if(sistema.fileS=="2fs"){
            ext2(sistema);
        }else if(sistema.fileS=="3fs"){
            ext3(sistema);
        }
    }
}