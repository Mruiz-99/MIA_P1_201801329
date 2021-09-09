#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

using namespace std;

struct new_carpeta
{
    inode in;
    int start_padre;
};

bool ExisteCarpeta(inode in, FILE *disco, superblock sb, string nombre)
{
    dirBlock b2;

    for (int j = 0; j < 15; j++)
    {
        if (in.i_block[j] >= 0)
        {
            fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
            fread(&b2, sizeof(b2), 1, disco);
            for (int k = 0; k < 4; k++)
            {
                if (strlen(b2.b_content[k].b_name) > 0)
                {
                    string aux = "";
                    for (int i = 0; i < strlen(b2.b_content[k].b_name); i++)
                    {
                        aux += b2.b_content[k].b_name[i];
                    }
                    if (aux == nombre)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//Funcion que crea la carpeta pero antes verifica los permisos
new_carpeta CrearCarpeta(inode in, FILE *disco, superblock sb, string nombre, int start_padre)
{
    new_carpeta aux2;
    inode carpeta;
    string permisos = to_string(in.i_perm);
    bool creado = false;
    dirBlock b2;
    if (in.i_uid == uid)
    {
        if ((permisos[0] == '2') || (permisos[0] == '3') || (permisos[0] == '6') || (permisos[0] == '7'))
        {
            if (!ExisteCarpeta(in, disco, sb, nombre))
            {
                for (int j = 0; j < 15; j++)
                {
                    if ((in.i_block[j] >= 0) && (creado == false))
                    {
                        fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
                        fread(&b2, sizeof(b2), 1, disco);
                        for (int k = 0; k < 4; k++)
                        {
                            if ((strlen(b2.b_content[k].b_name) == 0) && (creado == false))
                            {
                                int no_inodo = 0;
                                char c;
                                for (int i = sb.s_bm_inode_start; i < sb.s_bm_block_start; i++)
                                {
                                    fseek(disco, i, SEEK_SET);
                                    fread(&c, sizeof(char), 1, disco);
                                    if (c == '1')
                                    {
                                        no_inodo++;
                                    }
                                }
                                fseek(disco, sb.s_bm_inode_start + no_inodo, SEEK_SET);
                                c = '1';
                                fwrite(&c, 1, 1, disco);
                                carpeta = {uid, obtenerGID(grupo), sizeof(fileBlock), time(0), time(0), time(0), {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, '0', 664, '/'};
                                strcpy(carpeta.nombre, nombre.c_str());
                                fseek(disco, sb.s_inode_start + (no_inodo * sizeof(inode)), SEEK_SET);
                                fwrite(&carpeta, sizeof(carpeta), 1, disco);
                                start_padre = sb.s_inode_start + (no_inodo * sizeof(inode));
                                b2.b_content[k].b_inode = no_inodo;
                                strcpy(b2.b_content[k].b_name, nombre.c_str());
                                fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
                                fwrite(&b2, sizeof(b2), 1, disco);
                                creado = true;
                                cout << "La carpeta ha sido creada correctamente" << endl;
                                break;
                            }
                        }
                    }
                    else if (creado == false)
                    {
                        int no_bloque = 0;
                        char c2;
                        for (int i = sb.s_bm_block_start; i < sb.s_inode_start; i++)
                        {
                            fseek(disco, i, SEEK_SET);
                            fread(&c2, sizeof(char), 1, disco);
                            if (c2 == '1')
                            {
                                no_bloque++;
                            }
                        }
                        in.i_block[j] = no_bloque;
                        fseek(disco, start_padre, SEEK_SET);
                        fwrite(&in, sizeof(inode), 1, disco);
                        int no_inodo = 0;
                        char c;
                        for (int i = sb.s_bm_inode_start; i < sb.s_bm_block_start; i++)
                        {
                            fseek(disco, i, SEEK_SET);
                            fread(&c, sizeof(char), 1, disco);
                            if (c == '1')
                            {
                                no_inodo++;
                            }
                        }
                        content co1 = {"", no_inodo};
                        strcpy(co1.b_name, nombre.c_str());
                        content co2 = {"", 0};
                        content co3 = {"", 0};
                        content co4 = {"", 0};
                        dirBlock b1 = {{co1, co2, co3, co4}};
                        fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
                        fwrite(&b1, sizeof(b1), 1, disco);

                        no_inodo = 0;
                        for (int i = sb.s_bm_inode_start; i < sb.s_bm_block_start; i++)
                        {
                            fseek(disco, i, SEEK_SET);
                            fread(&c, sizeof(char), 1, disco);
                            if (c == '1')
                            {
                                no_inodo++;
                            }
                        }
                        c = '1';
                        fseek(disco, sb.s_bm_block_start + (no_bloque * sizeof(char)), SEEK_SET);
                        fwrite(&c, sizeof(char), 1, disco);
                        fseek(disco, sb.s_bm_inode_start + (no_inodo * sizeof(char)), SEEK_SET);
                        fwrite(&c, sizeof(char), 1, disco);
                        carpeta = {uid, obtenerGID(grupo), sizeof(fileBlock), time(0), time(0), time(0), {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, '0', 664, '/'};
                        strcpy(carpeta.nombre, nombre.c_str());
                        fseek(disco, sb.s_inode_start + (no_inodo * sizeof(inode)), SEEK_SET);
                        fwrite(&carpeta, sizeof(inode), 1, disco);
                        start_padre = sb.s_inode_start + (no_inodo * sizeof(inode));
                        creado = true;
                        cout << "La carpeta ha sido creada correctamente" << endl;
                        break;
                    }
                }
            }
        }
        else
        {
            cout << "Error, el usuario propietario no tiene permisos de escritura sobre la carpeta padre" << endl;
        }
    }
    else if (obtenerGID(grupo) == in.i_gid)
    {
        if ((permisos[1] == '2') || (permisos[1] == '3') || (permisos[1] == '6') || (permisos[1] == '7'))
        {
            if (!ExisteCarpeta(in, disco, sb, nombre))
            {
                for (int j = 0; j < 15; j++)
                {
                    if ((in.i_block[j] >= 0) && (creado == false))
                    {
                        fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
                        fread(&b2, sizeof(b2), 1, disco);
                        for (int k = 0; k < 4; k++)
                        {
                            if ((strlen(b2.b_content[k].b_name) == 0) && (creado == false))
                            {
                                int no_inodo = 0;
                                char c;
                                for (int i = sb.s_bm_inode_start; i < sb.s_bm_block_start; i++)
                                {
                                    fseek(disco, i, SEEK_SET);
                                    fread(&c, sizeof(char), 1, disco);
                                    if (c == '1')
                                    {
                                        no_inodo++;
                                    }
                                }
                                fseek(disco, sb.s_bm_inode_start + no_inodo, SEEK_SET);
                                c = '1';
                                fwrite(&c, 1, 1, disco);
                                carpeta = {uid, obtenerGID(grupo), sizeof(fileBlock), time(0), time(0), time(0), {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, '0', 664, '/'};
                                strcpy(carpeta.nombre, nombre.c_str());
                                fseek(disco, sb.s_inode_start + (no_inodo * sizeof(inode)), SEEK_SET);
                                fwrite(&carpeta, sizeof(carpeta), 1, disco);
                                start_padre = sb.s_inode_start + (no_inodo * sizeof(inode));
                                b2.b_content[k].b_inode = no_inodo;
                                strcpy(b2.b_content[k].b_name, nombre.c_str());
                                fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
                                fwrite(&b2, sizeof(b2), 1, disco);

                                creado = true;
                                cout << "La carpeta ha sido creada correctamente" << endl;
                                break;
                            }
                        }
                    }
                    else if (creado == false)
                    {
                        int no_bloque = 0;
                        char c2;
                        for (int i = sb.s_bm_block_start; i < sb.s_inode_start; i++)
                        {
                            fseek(disco, i, SEEK_SET);
                            fread(&c2, sizeof(char), 1, disco);
                            if (c2 == '1')
                            {
                                no_bloque++;
                            }
                        }
                        in.i_block[j] = no_bloque;
                        fseek(disco, start_padre, SEEK_SET);
                        fwrite(&in, sizeof(inode), 1, disco);

                        int no_inodo = 0;
                        char c;
                        for (int i = sb.s_bm_inode_start; i < sb.s_bm_block_start; i++)
                        {
                            fseek(disco, i, SEEK_SET);
                            fread(&c, sizeof(char), 1, disco);
                            if (c == '1')
                            {
                                no_inodo++;
                            }
                        }
                        content co1 = {"", no_inodo};
                        strcpy(co1.b_name, nombre.c_str());
                        content co2 = {"", 0};
                        content co3 = {"", 0};
                        content co4 = {"", 0};
                        dirBlock b1 = {{co1, co2, co3, co4}};
                        fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
                        fwrite(&b1, sizeof(b1), 1, disco);

                        no_inodo = 0;
                        for (int i = sb.s_bm_inode_start; i < sb.s_bm_block_start; i++)
                        {
                            fseek(disco, i, SEEK_SET);
                            fread(&c, sizeof(char), 1, disco);
                            if (c == '1')
                            {
                                no_inodo++;
                            }
                        }
                        c = '1';
                        fseek(disco, sb.s_bm_block_start + (no_bloque * sizeof(char)), SEEK_SET);
                        fwrite(&c, sizeof(char), 1, disco);
                        fseek(disco, sb.s_bm_inode_start + (no_inodo * sizeof(char)), SEEK_SET);
                        fwrite(&c, sizeof(char), 1, disco);
                        carpeta = {uid, obtenerGID(grupo), sizeof(fileBlock), time(0), time(0), time(0), {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, '0', 664, '/'};
                        strcpy(carpeta.nombre, nombre.c_str());
                        fseek(disco, sb.s_inode_start + (no_inodo * sizeof(inode)), SEEK_SET);
                        fwrite(&carpeta, sizeof(carpeta), 1, disco);
                        start_padre = sb.s_inode_start + (no_inodo * sizeof(inode));
                        creado = true;
                        cout << "La carpeta ha sido creada correctamente" << endl;
                        break;
                    }
                }
            }
            else
            {
                cout << "Error, el nombre de la carpeta ya es utilizado, intentelo con otro nombre " << endl;
            }
        }
        else
        {
            cout << "Error, el grupo que pertenece el usuario no tiene permisos de escritura sobre la carpeta padre" << endl;
        }
    }
    else
    {
        if ((permisos[2] == '2') || (permisos[2] == '3') || (permisos[2] == '6') || (permisos[2] == '7'))
        {
            if (!ExisteCarpeta(in, disco, sb, nombre))
            {
                for (int j = 0; j < 15; j++)
                {
                    if ((in.i_block[j] >= 0) && (creado == false))
                    {
                        fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
                        fread(&b2, sizeof(b2), 1, disco);
                        for (int k = 0; k < 4; k++)
                        {
                            if ((strlen(b2.b_content[k].b_name) == 0) && (creado == false))
                            {
                                int no_inodo = 0;
                                char c;
                                for (int i = sb.s_bm_inode_start; i < sb.s_bm_block_start; i++)
                                {
                                    fseek(disco, i, SEEK_SET);
                                    fread(&c, sizeof(char), 1, disco);
                                    if (c == '1')
                                    {
                                        no_inodo++;
                                    }
                                }
                                fseek(disco, sb.s_bm_inode_start + no_inodo, SEEK_SET);
                                c = '1';
                                fwrite(&c, 1, 1, disco);
                                carpeta = {uid, obtenerGID(grupo), sizeof(fileBlock), time(0), time(0), time(0), {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, '0', 664, '/'};
                                strcpy(carpeta.nombre, nombre.c_str());
                                fseek(disco, sb.s_inode_start + (no_inodo * sizeof(inode)), SEEK_SET);
                                fwrite(&carpeta, sizeof(carpeta), 1, disco);
                                start_padre = sb.s_inode_start + (no_inodo * sizeof(inode));
                                b2.b_content[k].b_inode = no_inodo;
                                strcpy(b2.b_content[k].b_name, nombre.c_str());
                                fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
                                fwrite(&b2, sizeof(b2), 1, disco);
                                creado = true;
                                cout << "La carpeta ha sido creada correctamente" << endl;
                                break;
                            }
                        }
                    }
                    else if (creado == false)
                    {
                        int no_bloque = 0;
                        char c2;
                        for (int i = sb.s_bm_block_start; i < sb.s_inode_start; i++)
                        {
                            fseek(disco, i, SEEK_SET);
                            fread(&c2, sizeof(char), 1, disco);
                            if (c2 == '1')
                            {
                                no_bloque++;
                            }
                        }
                        in.i_block[j] = no_bloque;
                        fseek(disco, start_padre, SEEK_SET);
                        fwrite(&in, sizeof(inode), 1, disco);

                        int no_inodo = 0;
                        char c;
                        for (int i = sb.s_bm_inode_start; i < sb.s_bm_block_start; i++)
                        {
                            fseek(disco, i, SEEK_SET);
                            fread(&c, sizeof(char), 1, disco);
                            if (c == '1')
                            {
                                no_inodo++;
                            }
                        }
                        content co1 = {"", no_inodo};
                        strcpy(co1.b_name, nombre.c_str());
                        content co2 = {"", 0};
                        content co3 = {"", 0};
                        content co4 = {"", 0};
                        dirBlock b1 = {{co1, co2, co3, co4}};
                        fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
                        fwrite(&b1, sizeof(b1), 1, disco);

                        no_inodo = 0;
                        for (int i = sb.s_bm_inode_start; i < sb.s_bm_block_start; i++)
                        {
                            fseek(disco, i, SEEK_SET);
                            fread(&c, sizeof(char), 1, disco);
                            if (c == '1')
                            {
                                no_inodo++;
                            }
                        }
                        c = '1';
                        fseek(disco, sb.s_bm_block_start + (no_bloque * sizeof(char)), SEEK_SET);
                        fwrite(&c, sizeof(char), 1, disco);
                        fseek(disco, sb.s_bm_inode_start + (no_inodo * sizeof(char)), SEEK_SET);
                        fwrite(&c, sizeof(char), 1, disco);
                        carpeta = {uid, obtenerGID(grupo), sizeof(fileBlock), time(0), time(0), time(0), {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, '0', 664, '/'};
                        strcpy(carpeta.nombre, nombre.c_str());
                        fseek(disco, sb.s_inode_start + (no_inodo * sizeof(inode)), SEEK_SET);
                        fwrite(&carpeta, sizeof(carpeta), 1, disco);
                        start_padre = sb.s_inode_start + (no_inodo * sizeof(inode));
                        creado = true;
                        cout << "La carpeta ha sido creada correctamente" << endl;
                        break;
                    }
                }
            }
            else
            {
                cout << "Error, el nombre de la carpeta ya es utilizado, intentelo con otro nombre " << endl;
            }
        }
        else
        {
            cout << "Error, el usuario no tiene permisos de escritura sobre la carpeta padre" << endl;
        }
    }
    if (creado == false)
    {
        inode in1;
        in1.i_uid = -1;
        aux2.in = in1;
        return aux2;
    }
    else
    {
        aux2.in = carpeta;
        aux2.start_padre = start_padre;
        return aux2;
    }
}

//Funcion que crea una carpeta dentro del sistema
bool mkdirection(part_mkdir dir)
{
    new_carpeta aux2;
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
            fseek(disco, sb.s_inode_start, SEEK_SET);
            fread(&in, sizeof(in), 1, disco);
            vector<string> partes_direccion = split(dir.direccion, "/");
            if (partes_direccion.size() > 1)
            {
                dirBlock b2;
                if (dir.recursivo == false)
                {
                    bool encontrado = false;
                    int start_padre = 0;
                    string aux_nom = "";
                    for (int i = 0; i < partes_direccion.size(); i++)
                    {

                        for (int j = 0; j < 15; j++)
                        {
                            if ((in.i_block[j] >= 0) && (encontrado == false))
                            {
                                fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
                                fread(&b2, sizeof(b2), 1, disco);
                                for (int k = 0; k < 4; k++)
                                {
                                    aux_nom = "";
                                    for (int l = 0; l < strlen(b2.b_content[k].b_name); l++)
                                    {
                                        aux_nom += b2.b_content[k].b_name[l];
                                    }
                                    if (aux_nom == partes_direccion[i].c_str())
                                    {
                                        fseek(disco, sb.s_inode_start + (b2.b_content[k].b_inode * sizeof(inode)), SEEK_SET);
                                        start_padre = sb.s_inode_start + (b2.b_content[k].b_inode * sizeof(inode));
                                        fread(&in, sizeof(inode), 1, disco);
                                        encontrado = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if (encontrado == true)
                        {
                            if ((i + 2) == partes_direccion.size())
                            {
                                aux2 = CrearCarpeta(in, disco, sb, partes_direccion[i + 1].c_str(), start_padre);
                                in = aux2.in;
                                if (in.i_uid == -1)
                                {
                                    cout<<"Error, el nombre ya ha sido creada dentro de esta carpeta"<<endl;
                                }
                                break;
                            }
                            encontrado = false;
                        }
                        else
                        {
                            cout << "Error, la carpeta padre: " << partes_direccion[i].c_str() << " no existe dentro del sistema" << endl;
                            break;
                        }
                    }
                }
                else
                {
                    bool encontrado = false;
                    int start_padre = sb.s_inode_start;
                    string aux_nom;
                    for (int i = 0; i < partes_direccion.size(); i++)
                    {
                        for (int j = 0; j < 15; j++)
                        {
                            if ((in.i_block[j] >= 0) && (encontrado == false))
                            {
                                fseek(disco, sb.s_block_start + (in.i_block[j] * sizeof(dirBlock)), SEEK_SET);
                                fread(&b2, sizeof(b2), 1, disco);
                                for (int k = 0; k < 4; k++)
                                {
                                    aux_nom = "";
                                    for (int l = 0; l < strlen(b2.b_content[k].b_name); l++)
                                    {
                                        aux_nom += b2.b_content[k].b_name[l];
                                    }
                                    if (aux_nom == partes_direccion[i].c_str())
                                    {
                                        fseek(disco, sb.s_inode_start + (b2.b_content[k].b_inode * sizeof(inode)), SEEK_SET);
                                        start_padre = sb.s_inode_start + (b2.b_content[k].b_inode * sizeof(inode));
                                        fread(&in, sizeof(inode), 1, disco);
                                        encontrado = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if (encontrado == true)
                        {
                            if ((i + 2) == partes_direccion.size())
                            {
                                aux2 = CrearCarpeta(in, disco, sb, partes_direccion[i + 1].c_str(), start_padre);
                                in = aux2.in;
                                if (in.i_uid == -1)
                                {
                                    cout<<"Error, el nombre ya ha sido creada dentro de esta carpeta"<<endl;
                                }
                                break;
                            }
                            encontrado = false;
                        }
                        else
                        {
                            aux2 = CrearCarpeta(in, disco, sb, partes_direccion[i].c_str(), start_padre);
                            in = aux2.in;
                            start_padre = aux2.start_padre;
                            if (in.i_uid == -1)
                            {
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                CrearCarpeta(in, disco, sb, partes_direccion[0], sb.s_inode_start);
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
        cout << "Error, NO hay ningun usuario logueado o activo... " << endl;
    }

    return false;
}

void mkdir(vector<string> partes)
{
    bool problem = false;
    part_mkdir dir = {"", false};
    for (int i = 0; i < partes.size(); i++)
    {
        vector<string> componentes = split(partes[i], "=");
        if (lower(componentes[0]) == "mkdir")
        {
        }
        else if (lower(componentes[0]) == "-p")
        {
            dir.recursivo = true;
        }
        else if (lower(componentes[0]) == "-path")
        {
            dir.direccion = lower(quitarComillas(componentes[1]));
        }
        else
        {
            cout << "Comando mkdir no valido" << endl;
            problem = true;
        }
    }
    if (problem == true)
    {
    }
    else if (dir.direccion == "")
    {
        cout << "Parametros obligatorios incompletos" << endl;
    }
    else
    {
        mkdirection(dir);
    }
}
/*
Mkdir -path="/home/sdf/sdf"
*/