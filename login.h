#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

//Funcion que monta una particion a memoria
bool logear(l_user user)
{
    if (usuario == "")
    {
        if (existeMontada(user.id))
        {
            FILE *disco;
            if (disco = fopen(obtenerDireccion(user.id).c_str(), "rb+"))
            {
                mbr master;
                fseek(disco, 0, SEEK_SET);
                fread(&master, sizeof(master), 1, disco);
                partition particion = obtenerParticion(master, obtenerN(user.id));
                superblock sb;
                if (particion.part_status == 'n')
                {
                    partition particion2 = obtenerParticionExtendida(master);
                    ebr aux = obtenerLogica(obtenerN(user.id), particion2.part_start + sizeof(partition) + 1, disco);
                    if (aux.part_status == 'a')
                    {
                        particion.part_status = aux.part_status;
                        particion.part_fit = aux.part_fit;
                        particion.part_start = aux.part_start + sizeof(ebr) + 1;
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
                        fseek(disco, sb.s_block_start + (in.i_block[i]*sizeof(b1)), SEEK_SET);
                        fread(&b2, sizeof(b2), 1, disco);
                        aux2+= b2.b_content;
                    }
                }
                vector<string> usuarios = split(aux2, "\n");
                bool ingreso = false;
                for (int i = 0; i < usuarios.size(); i++)
                {
                    vector<string> partes = split(usuarios[i], ",");
                    if( partes.size() >2){
                        if ((partes[1] == "u") || (partes[1] == "U"))
                    {
                        if (partes[3] == user.user)
                        {
                            if (partes[4] == user.pass)
                            {
                                usuario = user.user;
                                id = user.id;
                                ingreso = true;
                                cout << "Login completado, BIENVENIDO" << endl;
                                break;
                            }
                            else
                            {
                                cout << "Error, la contraseña del usuario es incorrecta" << endl;
                            }
                        }
                    }
                    }
                    
                }
                if (ingreso == false)
                {
                    cout << "Error en inicio de sesion, intentelo de nuevo" << endl;
                }

                fclose(disco);
            }
            else
            {
                cout << "El archivo de disco no existe" << endl;
            }
        }
        else
        {
            cout << "La particion no esta montada" << endl;
        }
    }
    else
    {
        cout << "Error, hay una cuenta de usuario activa, debe cerrar sesion" << endl;
    }
    return false;
}

void login(vector<string> partes)
{
    l_user user = {"", "", ""};
    bool problem = false;
    for (int i = 0; i < partes.size(); i++)
    {
        vector<string> componenetes = split(partes[i], "=");
        if (lower(componenetes[0]) == "login")
        {
            //reconoce el primer parametro con la palabra mount
        }
        else if (lower(componenetes[0]) == "-usr")
        {
            user.user = lower(quitarComillas(componenetes[1]));
        }
        else if (lower(componenetes[0]) == "-pwd")
        {
            user.pass = lower(quitarComillas(componenetes[1]));
        }
        else if (lower(componenetes[0]) == "-id")
        {
            user.id = lower(quitarComillas(componenetes[1]));
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
    else if ((user.user == "") || (user.pass == "") || (user.id == ""))
    {
        cout << "Parametros obligatorios incompletos" << endl;
    }
    else
    {
        logear(user);
    }
}
/*
login -usr=root -pwd=123 -id=291a
login -usr=rot -pwd=123 -id=291A
*/