#include <vector>
#include <iostream>
#include <string.h>
#include <cstring>

using namespace std;

int obtenerGID(string nombre){
    FILE *disco;
        if (disco = fopen(obtenerDireccion(id).c_str(), "rb+"))
        {
            mbr master;
            fseek(disco, 0, SEEK_SET);
            fread(&master, sizeof(master), 1, disco);
            partition particion = obtenerParticion(master, obtenerN(id));
            superblock sb;
            if (particion.part_status == 'n')
            {
                partition particion2 = obtenerParticionExtendida(master);
                ebr aux = obtenerLogica(obtenerN(id), particion2.part_start + sizeof(partition) + 1, disco);
                if (aux.part_status == 'a')
                {
                    particion.part_status = aux.part_status;
                    particion.part_fit = aux.part_fit;
                    particion.part_start = aux.part_start + sizeof(ebr) + 1;
                    ;
                    particion.part_size = aux.part_size;
                }
                else
                {
                    cout << "Error, no se encontro ninguna particion" << endl;
                }
            }
            fseek(disco, particion.part_start, SEEK_SET);
            fread(&sb, sizeof(sb), 1, disco);
            inode in;
            fseek(disco, sb.s_inode_start + sizeof(inode), SEEK_SET);
            fread(&in, sizeof(in), 1, disco);
            string aux2 = "";
            dirBlock b1;
            fileBlock b2;
            for (int i = 0; i < 15; i++)
            {
                if (in.i_block[i] >= 0)
                {
                    fseek(disco, sb.s_block_start + (in.i_block[i] * sizeof(b1)), SEEK_SET);
                    fread(&b2, sizeof(b2), 1, disco);
                    aux2 += b2.b_content;
                }
            }
            vector<string> usuarios = split(aux2, "\n");
            for (int i = 0; i < usuarios.size(); i++)
            {
                vector<string> partes = split(usuarios[i], ",");
                if ((partes[1] == "g") || (partes[1] == "G"))
                {
                    if (partes[2] == nombre)
                    {
                        return atoi(partes[0].c_str());
                    }
                }
            }
            fclose(disco);
        }
        else
        {
            cout << "El archivo de disco no existe" << endl;
        }
        fclose(disco);
        return 0;
}

//Funcion que monta una particion a memoria
bool mkgroup(string nombre)
{
    if (usuario == "root")
    {
        FILE *disco;
        if (disco = fopen(obtenerDireccion(id).c_str(), "rb+"))
        {
            mbr master;
            fseek(disco, 0, SEEK_SET);
            fread(&master, sizeof(master), 1, disco);
            partition particion = obtenerParticion(master, obtenerN(id));
            superblock sb;
            if (particion.part_status == 'n')
            {
                partition particion2 = obtenerParticionExtendida(master);
                ebr aux = obtenerLogica(obtenerN(id), particion2.part_start + sizeof(partition) + 1, disco);
                if (aux.part_status == 'a')
                {
                    particion.part_status = aux.part_status;
                    particion.part_fit = aux.part_fit;
                    particion.part_start = aux.part_start + sizeof(ebr) + 1;
                    ;
                    particion.part_size = aux.part_size;
                }
                else
                {
                    cout << "Error, no se encontro ninguna particion" << endl;
                }
            }
            fseek(disco, particion.part_start, SEEK_SET);
            fread(&sb, sizeof(sb), 1, disco);
            inode in;
            fseek(disco, sb.s_inode_start + sizeof(inode), SEEK_SET);
            fread(&in, sizeof(in), 1, disco);
            string aux2 = "";
            dirBlock b1;
            fileBlock b2;
            for (int i = 0; i < 15; i++)
            {
                if (in.i_block[i] >= 0)
                {
                    fseek(disco, sb.s_block_start + (in.i_block[i] * sizeof(b1)), SEEK_SET);
                    fread(&b2, sizeof(b2), 1, disco);
                    aux2 += b2.b_content;
                }
            }
            vector<string> usuarios = split(aux2, "\n");
            bool existe = false;
            string aux = "";
            int ultimo_grp = 0;
            for (int i = 0; i < usuarios.size(); i++)
            {
                vector<string> partes = split(usuarios[i], ",");
                if ((partes[1] == "g") || (partes[1] == "G"))
                {
                    if (partes[2] == nombre)
                    {
                        existe = true;
                    }
                    else
                    {
                        ultimo_grp = stoi(partes[0]);
                        aux += partes[0] + "," + partes[1] + "," + partes[2] + "\n";
                    }
                }
                else
                {
                    aux += partes[0] + "," + partes[1] + "," + partes[2] + "," + partes[3] + "," + partes[4] + "\n";
                }
            }
            if (existe == false)
            {
                ultimo_grp += 1;
                aux += to_string(ultimo_grp) + ",G," + nombre + "\n";
                vector<string> usuarios_bloques = split_bloque(aux);
                for (int i = 0; i < 15; i++)
                {
                    if (i < usuarios_bloques.size())
                    {
                        if ((in.i_block[i] >= 0) && (usuarios_bloques[i].length() > 0))
                        {
                            fseek(disco, sb.s_block_start + (in.i_block[i] * sizeof(b1)), SEEK_SET);
                            memmove(b2.b_content, usuarios_bloques[i].c_str(), usuarios_bloques[i].length());
                            fwrite(&b2, sizeof(b2), 1, disco);
                            memset(b2.b_content, 0, 64);
                        }
                        else if ((in.i_block[i] == -1) && (usuarios_bloques[i].length() > 0))
                        {
                            int bloque = 0, num;
                            char res;
                            for (int i = sb.s_bm_block_start; i < sb.s_inode_start; i++)
                            {
                                fseek(disco, i, SEEK_SET);
                                fread(&res, sizeof(char), 1, disco);
                                if (res == '0')
                                {
                                    num = bloque;
                                    break;
                                }
                                bloque++;
                            }
                            in.i_block[i] = num;
                            fseek(disco, sb.s_bm_block_start + (num), SEEK_SET);
                            char c = '1';
                            fwrite(&c, 1, 1, disco);
                            fseek(disco, sb.s_inode_start + sizeof(inode), SEEK_SET);
                            fwrite(&in, sizeof(in), 1, disco);
                            fseek(disco, sb.s_block_start + (in.i_block[i] * sizeof(b1)), SEEK_SET);
                            memmove(b2.b_content, usuarios_bloques[i].c_str(), usuarios_bloques[i].length());
                            fwrite(&b2, sizeof(b2), 1, disco);
                            memset(b2.b_content, 0, 64);
                        }
                    }
                }
                cout << "Grupo creado, proceso realizado exitosamente" << endl;
            }
            else
            {
                cout << "Error, existe un grupo actualmente con ese nombre, intentelo de nuevo" << endl;
            }

            fclose(disco);
        }
        else
        {
            cout << "El archivo de disco no existe" << endl;
        }
    }
    else if (usuario != "")
    {
        cout << "Error, este comando solo puede utilizarlo el usuario root" << endl;
    }
    else
    {
        cout << "Error, NO existe ningun usuario activo, haga un login" << endl;
    }
}

void mkgrp(vector<string> partes)
{
    string nombre = "";
    bool problem = false;
    for (int i = 0; i < partes.size(); i++)
    {
        vector<string> componenetes = split(partes[i], "=");
        if (lower(componenetes[0]) == "mkgrp")
        {
            //reconoce el primer parametro con la palabra mount
        }
        else if (lower(componenetes[0]) == "-name")
        {
            nombre = lower(quitarComillas(componenetes[1]));
        }
        else
        {
            cout << "Comando '" << componenetes[0] << "' no valido" << endl;
            problem = true;
        }
    }
    if (problem == true)
    {
    }
    else if (nombre == "")
    {
        cout << "Parametros obligatorios incompletos" << endl;
    }
    else
    {
        mkgroup(nombre);
    }
}