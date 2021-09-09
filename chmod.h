#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

//Funcion que monta una particion a memoria
bool changeMod(chmod_perm perm)
{
    if ((usuario != "") && (id != ""))
    {
        FILE *disco;
        if (disco = fopen(obtenerDireccion(id).c_str(), "rb+"))
        {
            mbr master;
            fseek(disco, 0, SEEK_SET);
            fread(&master, sizeof(master), 1, disco);
            superblock sb;
            partition particion = obtenerParticion(master, obtenerN(id));
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
            int c=0;
            char res;
            for (int i = sb.s_bm_inode_start; i < sb.s_bm_block_start; i++)
            {
                fseek(disco, i, SEEK_SET);
                fread(&res, sizeof(char), 1, disco);
                if (res == '1')
                {
                    fseek(disco,sb.s_inode_start + (c * sizeof(inode)), SEEK_SET);
                    fread(&in, sizeof(inode), 1, disco);
                    if(in.nombre == perm.direccion){

                    }
                    break;
                }
                c++;
            }
        }
        else
        {
            cout << "El archivo de disco no existe" << endl;
        }
    }
    else
    {
        cout << "Error, NO hay ningun usuario logueado o activo... " << endl;
    }

    return false;
}

void chmod(vector<string> partes)
{
    bool problem = false;
    chmod_perm perm = {"", 0, false};
    for (int i = 0; i < partes.size(); i++)
    {
        vector<string> componentes = split(partes[i], "=");
        if (lower(componentes[0]) == "chmod")
        {
        }
        else if (lower(componentes[0]) == "-r")
        {
            perm.recursivo = true;
        }
        else if (lower(componentes[0]) == "-path")
        {
            perm.direccion = quitarComillas(componentes[1]);
        }
        else if (lower(componentes[0]) == "-ugo")
        {
            string numero = componentes[1];
            if (numero.size() == 3)
            {
                int n1 = componentes[1][0] - '0';
                int n2 = componentes[1][1] - '0';
                int n3 = componentes[1][2] - '0';
                if ((n1 >= 0) && (n1 < 8) && (n2 >= 0) && (n2 < 8) && (n3 >= 0) && (n3 < 8))
                {
                    perm.ugo = atoi(numero.c_str());
                }
                else
                {
                    cout << "Comando no valido, los digitos de los permisos deben entrar en el rango de 0 - 7" << endl;
                    problem = true;
                }
            }
            else
            {
                cout << "Comando no valido el permiso tiene que ser un numero de 3 digitos" << endl;
                problem = true;
            }
        }
        else
        {
            cout << "Comando chmod no valido" << endl;
            problem = true;
        }
    }
    if (problem == true)
    {
    }
    else if ((perm.ugo == 0) || (perm.direccion == ""))
    {
        cout << "Parametros obligatorios incompletos" << endl;
    }
    else
    {
        changeMod(perm);
    }
}
/*
chmod -path=/home -ugo=777
*/