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
                fseek(disco, particion.part_start, SEEK_SET);
                fread(&sb, sizeof(sb), 1, disco);
                dirBlock b1;
                fileBlock b2;
                fseek(disco, sb.s_block_start + sizeof(b1), SEEK_SET);
                fread(&b2, sizeof(b2), 1, disco);
                vector<string> usuarios = split(b2.b_content, "\n");
                bool ingreso = false;
                for (int i = 0; i < usuarios.size(); i++)
                {
                    vector<string> partes = split(usuarios[i], ",");
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
                            }
                            else
                            {
                                cout << "Error, la contraseña del usuario es incorrecta" << endl;
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
login -usr=root -pwd=123 -id=291A
login -usr=rot -pwd=123 -id=291A
*/