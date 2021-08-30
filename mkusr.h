#include <vector>
#include <iostream>
#include <string.h>
#include <cstring>

using namespace std;

bool existeGrupo(vector<string> usuarios, string grupo)
{
    for (int i = 0; i < usuarios.size(); i++)
    {
        vector<string> partes = split(usuarios[i], ",");
        if ((partes[1] == "g") || (partes[1] == "G"))
        {
            if (partes[2] == grupo)
            {
                return true;
            }
        }
    }
    return false;
}

//Funcion que monta una particion a memoria
bool mkuser(new_user us)
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
            string aux;
            int ultimo_grp = 0;
            vector<string> partes;
            for (int i = 0; i < usuarios.size(); i++)
            {
                partes = split(usuarios[i], ",");
                if ((partes[1] == "u") || (partes[1] == "U"))
                {
                    if (partes[3] == us.user)
                    {
                        existe = true;
                    }
                    else
                    {
                        ultimo_grp = stoi(partes[0]);
                        aux += partes[0] + "," + partes[1] + "," + partes[2] + "," + partes[3] + "," + partes[4] + "\n";
                    }
                }
                else
                {
                    aux += partes[0] + "," + partes[1] + "," + partes[2] + "\n";
                }
            }
            if (existe == false)
            {
                if ((us.user.size() < 11) || (us.pass.size() < 11) || (us.group.size() < 11))
                {
                    if (existeGrupo(usuarios, us.group))
                    {
                        ultimo_grp += 1;
                        aux += to_string(ultimo_grp) + ",U," + us.group + ","+us.user+ ","+us.pass+"\n";
                        fseek(disco, sb.s_block_start + sizeof(b1), SEEK_SET);
                        fileBlock b3;
                        cout << aux.size() << endl;
                        cout << aux.length() << endl;
                        memmove(b3.b_content, aux.c_str(), aux.length());
                        fwrite(&b3, sizeof(b3), 1, disco);
                        cout << "Usuario creado, proceso realizado exitosamente" << endl;
                    }
                    else
                    {
                        cout << "Error, el grupo no existe en el sistema de archivos " << endl;
                    }
                }
                else
                {
                    cout << "Error, cada parametro tiene limite de 10 caracteres maximo  " << endl;
                }
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
    return false;
}

void mkusr(vector<string> partes)
{
    new_user usuario = {"", "", ""};
    bool problem = false;
    for (int i = 0; i < partes.size(); i++)
    {
        vector<string> componenetes = split(partes[i], "=");
        if (lower(componenetes[0]) == "mkusr")
        {
            //reconoce el primer parametro con la palabra mount
        }
        else if (lower(componenetes[0]) == "-usr")
        {
            usuario.user = lower(quitarComillas(componenetes[1]));
        }
        else if (lower(componenetes[0]) == "-grp")
        {
            usuario.group = lower(quitarComillas(componenetes[1]));
        }
        else if (lower(componenetes[0]) == "-pwd")
        {
            usuario.pass = lower(quitarComillas(componenetes[1]));
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
    else if ((usuario.user == "") || (usuario.pass == "") || (usuario.group == ""))
    {
        cout << "Parametros obligatorios incompletos" << endl;
    }
    else
    {
        mkuser(usuario);
    }
}