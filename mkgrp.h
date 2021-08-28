#include <vector>
#include <iostream>
#include <string.h>
#include <cstring>

using namespace std;

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
            fseek(disco, particion.part_start, SEEK_SET);
            fread(&sb, sizeof(sb), 1, disco);
            dirBlock b1;
            fileBlock b2;
            fseek(disco, sb.s_block_start + sizeof(b1), SEEK_SET);
            fread(&b2, sizeof(b2), 1, disco);
            vector<string> usuarios = split(b2.b_content, "\n");
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
                fseek(disco, sb.s_block_start + sizeof(b1), SEEK_SET);
                memmove(b2.b_content, aux.c_str(), aux.length());
                fwrite(&b2, sizeof(b2), 1, disco);
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
/*
login -usr=root -pwd=123 -id=291A
login -usr=rot -pwd=123 -id=291A
*/