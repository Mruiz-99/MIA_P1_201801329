#include <vector>
#include <iostream>
#include <string.h>

using namespace std;
bool res;
//Funcion que obtiene una particion en un disco en especifico
partition obtenerParticion(mbr master, string name)
{
    if (master.mbr_partition_1.part_status = 'a')
    {
        if (master.mbr_partition_1.part_name == name)
        {
            return master.mbr_partition_1;
        }
    }
    if (master.mbr_partition_2.part_status = 'a')
    {
        if (master.mbr_partition_2.part_name == name)
        {
            return master.mbr_partition_2;
        }
    }
    if (master.mbr_partition_3.part_status = 'a')
    {
        if (master.mbr_partition_3.part_name == name)
        {
            return master.mbr_partition_3;
        }
    }
    if (master.mbr_partition_4.part_status = 'a')
    {
        if (master.mbr_partition_4.part_name == name)
        {
            return master.mbr_partition_4;
        }
    }
    partition nueva;
    nueva.part_status = 'n';
    return nueva;
}

//Metodo que inserta una particion logica en formato ft
void free_space(ebr inicio, int realSize, partition extendida, part entrada, FILE *disco)
{
    ebr aux, siguiente;
    if ((inicio.part_status == 'n') && (inicio.part_next == 0))
    {
        if (((extendida.part_start + extendida.part_size) - (inicio.part_start + inicio.part_size + sizeof(ebr))) > realSize)
        {
            inicio = {'a', entrada.ajuste, inicio.part_start, realSize, 0, 0, 'a'};
            strcpy(inicio.part_name, entrada.nombre.c_str());
            fseek(disco, inicio.part_start, SEEK_SET);
            fwrite(&inicio, sizeof(inicio), 1, disco);
            cout << "Particion '" << entrada.nombre << "' creada correctamente" << endl;
        }
        else
        {
            cout << "Espacio de la particion extendida insuficiente" << endl;
        }
    }
    else if ((inicio.part_next > 0) && (inicio.part_status == 'n'))
    {
        if (((inicio.part_next - (inicio.part_start + inicio.part_size + sizeof(ebr)))) > realSize)
        {
            inicio = {'a', entrada.ajuste, inicio.part_start, realSize, inicio.part_next, 'a'};
            strcpy(inicio.part_name, entrada.nombre.c_str());
            fseek(disco, inicio.part_start, SEEK_SET);
            fwrite(&inicio, sizeof(inicio), 1, disco);
            cout << "Particion '" << entrada.nombre << "' creada correctamente" << endl;
        }
        else
        {
            fseek(disco, inicio.part_next, SEEK_SET);
            fread(&siguiente, sizeof(siguiente), 1, disco);
            free_space(siguiente, realSize, extendida, entrada, disco);
        }
    }
    else if ((inicio.part_status == 'a') && (inicio.part_next == 0))
    {
        if (((extendida.part_start + extendida.part_size) - (inicio.part_start + inicio.part_size + sizeof(ebr))) > realSize)
        {
            aux = {'a', entrada.ajuste, int(inicio.part_start + inicio.part_size + sizeof(ebr) + 1), realSize, 0, 'a'};
            strcpy(aux.part_name, entrada.nombre.c_str());
            inicio.part_next = inicio.part_start + inicio.part_size + sizeof(ebr) + 1;
            fseek(disco, inicio.part_start, SEEK_SET);
            fwrite(&inicio, sizeof(inicio), 1, disco);
            fseek(disco, (inicio.part_start + inicio.part_size + sizeof(ebr) + 1), SEEK_SET);
            fwrite(&aux, sizeof(aux), 1, disco);
            cout << "Particion '" << entrada.nombre << "' creada correctamente" << endl;
        }
        else
        {
            cout << "Espacio de la particion extendida insuficiente" << endl;
        }
    }
    else if ((inicio.part_status == 'a') && (inicio.part_next > 0))
    {
        if (((inicio.part_next) - (inicio.part_start + inicio.part_size + sizeof(ebr))) > realSize)
        {
            aux = {'a', entrada.ajuste, int(inicio.part_start + inicio.part_size + sizeof(ebr) + 1), realSize, inicio.part_next, 'a'};
            strcpy(aux.part_name, entrada.nombre.c_str());
            inicio.part_next = inicio.part_start + inicio.part_size + sizeof(ebr) + 1;
            fseek(disco, inicio.part_start, SEEK_SET);
            fwrite(&inicio, sizeof(inicio), 1, disco);
            fseek(disco, inicio.part_next, SEEK_SET);
            fwrite(&aux, sizeof(aux), 1, disco);
            cout << "Particion '" << entrada.nombre << "' creada correctamente" << endl;
        }
        else
        {
            fseek(disco, inicio.part_next, SEEK_SET);
            fread(&siguiente, sizeof(siguiente), 1, disco);
            free_space(siguiente, realSize, extendida, entrada, disco);
        }
    }
}

//Funcion que verifica si existe una particion extendida
bool existe_extendida(mbr master)
{
    if (master.mbr_partition_1.part_status == 'a')
    {
        if (master.mbr_partition_1.part_type == 'e')
        {
            return true;
        }
    }
    if (master.mbr_partition_2.part_status == 'a')
    {
        if (master.mbr_partition_2.part_type == 'e')
        {
            return true;
        }
    }
    if (master.mbr_partition_3.part_status == 'a')
    {
        if (master.mbr_partition_3.part_type == 'e')
        {
            return true;
        }
    }
    if (master.mbr_partition_4.part_status == 'a')
    {
        if (master.mbr_partition_4.part_type == 'e')
        {
            return true;
        }
    }
    return false;
}

//Funcion que obtiene la particion extendida del disco
partition obtenerParticionExtendida(mbr master)
{
    if (master.mbr_partition_1.part_status = 'a')
    {
        if (master.mbr_partition_1.part_type == 'e')
        {
            return master.mbr_partition_1;
        }
    }
    if (master.mbr_partition_2.part_status = 'a')
    {
        if (master.mbr_partition_2.part_type == 'e')
        {
            return master.mbr_partition_2;
        }
    }
    if (master.mbr_partition_3.part_status = 'a')
    {
        if (master.mbr_partition_3.part_type == 'e')
        {
            return master.mbr_partition_3;
        }
    }
    if (master.mbr_partition_4.part_status = 'a')
    {
        if (master.mbr_partition_4.part_type == 'e')
        {
            return master.mbr_partition_4;
        }
    }
    partition nueva;
    nueva.part_status = 'n';
    return nueva;
}
//Funcion que verifica si existe una particion logica en especifico
bool existeLogica(string nombre, int part_start, FILE *disco)
{
    ebr ebr;
    fseek(disco, part_start, SEEK_SET);
    fread(&ebr, sizeof(ebr), 1, disco);
    if (ebr.part_status == 'a')
    {
        if (ebr.part_name == nombre)
        {
            res = true;
        }
        else if (ebr.part_next > 0)
        {
            existeLogica(nombre, ebr.part_next, disco);
        }
        else
        {
            res = false;
        }
    }
    else if (ebr.part_next > 0)
    {
        existeLogica(nombre, ebr.part_next, disco);
    }
    else
    {
        res = false;
    }
    return res;
}
//Funcion que verifica si existe una particion en especifico
bool existeParticion(string nombre, mbr master, FILE *disco)
{
    if (master.mbr_partition_1.part_status == 'a')
    {
        if (master.mbr_partition_1.part_name == nombre)
        {
            return true;
        }
        else if (master.mbr_partition_1.part_type == 'e')
        {
            bool res = bool(existeLogica(nombre, master.mbr_partition_1.part_start + sizeof(partition) + 1, disco));
            if (res == true)
            {
                return true;
            }
        }
    }
    if (master.mbr_partition_2.part_status == 'a')
    {
        if (master.mbr_partition_2.part_name == nombre)
        {
            return true;
        }
        else if (master.mbr_partition_2.part_type == 'e')
        {
            if (existeLogica(nombre, master.mbr_partition_2.part_start + sizeof(partition) + 1, disco))
            {
                return true;
            }
        }
    }
    if (master.mbr_partition_3.part_status == 'a')
    {
        if (master.mbr_partition_3.part_name == nombre)
        {
            return true;
        }
        else if (master.mbr_partition_3.part_type == 'e')
        {
            if (existeLogica(nombre, master.mbr_partition_3.part_start + sizeof(partition) + 1, disco))
            {
                return true;
            }
        }
    }
    if (master.mbr_partition_4.part_status == 'a')
    {
        if (master.mbr_partition_4.part_name == nombre)
        {
            return true;
        }
        else if (master.mbr_partition_4.part_type == 'e')
        {
            if (existeLogica(nombre, master.mbr_partition_4.part_start + sizeof(partition) + 1, disco))
            {
                return true;
            }
        }
    }

    return false;
}

void crearParticion(part entrada)
{
    int realSize = entrada.size;
    if (lower(entrada.unidades) == "b")
    {
        realSize = entrada.size;
    }
    else if (lower(entrada.unidades) == "k")
    {
        realSize = 1024 * entrada.size;
    }
    else if (lower(entrada.unidades) == "m")
    {
        realSize = 1024 * 1024 * entrada.size;
    }
    mbr master;
    partition aux;
    FILE *disco = fopen(entrada.direccionDisco.c_str(), "rb+");
    fseek(disco, 0, SEEK_SET);
    fread(&master, sizeof(master), 1, disco);
    if ((entrada.tipo == 'p') || (entrada.tipo == 'e'))
    {
        if (realSize < (master.mbr_tamano - sizeof(mbr)))
        {
            if (existeParticion(entrada.nombre, master, disco) == false)
            {
                if ((existe_extendida(master) && entrada.tipo == 'e') == false)
                {
                    bool creada = false;
                    if (master.disk_fit == 'f')
                    {
                        if (master.mbr_partition_1.part_status == 'n')
                        {
                            if (master.mbr_partition_2.part_status == 'a')
                            {
                                if ((master.mbr_partition_2.part_start - sizeof(master)) > realSize)
                                {
                                    master.mbr_partition_1 = {'a', entrada.tipo, entrada.ajuste, sizeof(master) + 1, realSize, 'a'};
                                    aux = master.mbr_partition_1;
                                    strcpy(master.mbr_partition_1.part_name, entrada.nombre.c_str());
                                    creada = true;
                                }
                                else if (master.mbr_partition_3.part_status == 'n')
                                {
                                    if (master.mbr_partition_4.part_status == 'a')
                                    {
                                        if ((master.mbr_partition_4.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) > realSize)
                                        {
                                            master.mbr_partition_3 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_2.part_start + master.mbr_partition_2.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_3;
                                            strcpy(master.mbr_partition_3.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                    else if (master.mbr_partition_4.part_status == 'n')
                                    {
                                        if ((master.mbr_tamano - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) > realSize)
                                        {
                                            master.mbr_partition_3 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_2.part_start + master.mbr_partition_2.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_3;
                                            strcpy(master.mbr_partition_3.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                }
                                else if (master.mbr_partition_3.part_status == 'a')
                                {
                                    if (master.mbr_partition_4.part_status == 'a')
                                    {
                                        cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                    }
                                    else if (master.mbr_partition_4.part_status == 'n')
                                    {
                                        if ((master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > realSize)
                                        {
                                            master.mbr_partition_4 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_3.part_start + master.mbr_partition_3.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_4;
                                            strcpy(master.mbr_partition_4.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                }
                            }
                            else if (master.mbr_partition_2.part_status == 'n')
                            {
                                if (master.mbr_partition_3.part_status == 'n')
                                {
                                    if (master.mbr_partition_4.part_status == 'n')
                                    {
                                        if ((master.mbr_tamano - sizeof(master)) > realSize)
                                        {
                                            master.mbr_partition_1 = {'a', entrada.tipo, entrada.ajuste, sizeof(master) + 1, realSize, 'a'};
                                            aux = master.mbr_partition_1;
                                            strcpy(master.mbr_partition_1.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                    else if (master.mbr_partition_4.part_status == 'a')
                                    {
                                        if ((master.mbr_partition_4.part_start - sizeof(master)) > realSize)
                                        {
                                            master.mbr_partition_1 = {'a', entrada.tipo, entrada.ajuste, sizeof(master) + 1, realSize, 'a'};
                                            aux = master.mbr_partition_1;
                                            strcpy(master.mbr_partition_1.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                }
                                else if (master.mbr_partition_3.part_status == 'a')
                                {
                                    if (master.mbr_partition_4.part_status == 'a')
                                    {
                                        if ((master.mbr_partition_3.part_start - sizeof(master)) > realSize)
                                        {
                                            master.mbr_partition_1 = {'a', entrada.tipo, entrada.ajuste, sizeof(master) + 1, realSize, 'a'};
                                            aux = master.mbr_partition_1;
                                            strcpy(master.mbr_partition_1.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                    else if (master.mbr_partition_4.part_status == 'n')
                                    {
                                        if ((master.mbr_partition_3.part_start - sizeof(master)) > realSize)
                                        {
                                            master.mbr_partition_1 = {'a', entrada.tipo, entrada.ajuste, sizeof(master) + 1, realSize, 'a'};
                                            aux = master.mbr_partition_1;
                                            strcpy(master.mbr_partition_1.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else if ((master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > realSize)
                                        {
                                            master.mbr_partition_4 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_3.part_start + master.mbr_partition_3.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_4;
                                            strcpy(master.mbr_partition_4.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                }
                            }
                        }
                        else if (master.mbr_partition_1.part_status == 'a')
                        {
                            if (master.mbr_partition_2.part_status == 'a')
                            {
                                if (master.mbr_partition_3.part_status == 'n')
                                {
                                    if (master.mbr_partition_4.part_status == 'a')
                                    {
                                        if ((master.mbr_partition_4.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) > realSize)
                                        {
                                            master.mbr_partition_3 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_2.part_start + master.mbr_partition_2.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_3;
                                            strcpy(master.mbr_partition_3.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                    else if (master.mbr_partition_4.part_status == 'n')
                                    {
                                        if ((master.mbr_tamano - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) > realSize)
                                        {
                                            master.mbr_partition_3 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_2.part_start + master.mbr_partition_2.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_3;
                                            strcpy(master.mbr_partition_3.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                }
                                else if (master.mbr_partition_3.part_status == 'a')
                                {
                                    if (master.mbr_partition_4.part_status == 'a')
                                    {
                                        if (entrada.tipo == 'e')
                                        {
                                            cout << "No es posible crear mas particiones extendidas en este disco" << endl;
                                        }
                                        else if (entrada.tipo == 'p')
                                        {
                                            cout << "No es posible crear mas particiones primarias en este disco" << endl;
                                        }
                                    }
                                    else if (master.mbr_partition_4.part_status == 'n')
                                    {
                                        if ((master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > realSize)
                                        {
                                            master.mbr_partition_4 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_3.part_start + master.mbr_partition_3.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_4;
                                            strcpy(master.mbr_partition_4.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                }
                            }
                            else if (master.mbr_partition_2.part_status == 'n')
                            {
                                if (master.mbr_partition_3.part_status == 'n')
                                {
                                    if (master.mbr_partition_4.part_status == 'n')
                                    {
                                        if ((master.mbr_tamano - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > realSize)
                                        {
                                            master.mbr_partition_2 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_1.part_start + master.mbr_partition_1.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_2;
                                            strcpy(master.mbr_partition_2.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                    else if (master.mbr_partition_4.part_status == 'a')
                                    {
                                        if ((master.mbr_partition_4.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > realSize)
                                        {
                                            master.mbr_partition_2 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_1.part_start + master.mbr_partition_1.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_2;
                                            strcpy(master.mbr_partition_2.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                }
                                else if (master.mbr_partition_3.part_status == 'a')
                                {
                                    if (master.mbr_partition_4.part_status == 'a')
                                    {
                                        if ((master.mbr_partition_3.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > realSize)
                                        {
                                            master.mbr_partition_2 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_1.part_start + master.mbr_partition_1.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_2;
                                            strcpy(master.mbr_partition_2.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                    else if (master.mbr_partition_4.part_status == 'n')
                                    {
                                        if ((master.mbr_partition_3.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > realSize)
                                        {
                                            master.mbr_partition_2 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_1.part_start + master.mbr_partition_1.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_2;
                                            strcpy(master.mbr_partition_2.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else if ((master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > realSize)
                                        {
                                            master.mbr_partition_4 = {'a', entrada.tipo, entrada.ajuste, master.mbr_partition_3.part_start + master.mbr_partition_3.part_size + 1, realSize, 'a'};
                                            aux = master.mbr_partition_4;
                                            strcpy(master.mbr_partition_4.part_name, entrada.nombre.c_str());
                                            creada = true;
                                        }
                                        else
                                        {
                                            cout << "La particion no ha podido crearse debido a que no hay espacio entre particiones disponible" << endl;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if (master.disk_fit == 'b')
                    {
                        //No se calificaran
                    }
                    else if (master.disk_fit == 'w')
                    {
                        //No se calificaran
                    }
                    if (creada == true)
                    {
                        fseek(disco, 0, SEEK_SET);
                        fwrite(&master, sizeof(master), 1, disco);
                        if (entrada.tipo == 'e')
                        {
                            fseek(disco, (aux.part_start + sizeof(partition) + 1), SEEK_SET);
                            ebr inicio;
                            inicio = {'n', '0', aux.part_start + sizeof(partition) + 1, 0, 0, 'a'};
                            fwrite(&inicio, sizeof(inicio), 1, disco);
                        }
                        cout << "Particion '" << entrada.nombre << "' creada correctamente" << endl;
                    }
                }
                else
                {
                    cout << "Ya existe una particion extendida en el disco" << endl;
                }
            }
            else
            {
                cout << "Ya existe una particion en el disco con ese nombre" << endl;
            }
        }
        else
        {
            cout << "Espacio en disco insuficiente" << endl;
        }
    }
    else if (entrada.tipo == 'l')
    {
        partition extendida;
        extendida = obtenerParticionExtendida(master);
        if (existeParticion(entrada.nombre, master, disco) == false)
        {
            if (extendida.part_status == 'a')
            {
                ebr inicio;
                fseek(disco, extendida.part_start + sizeof(partition) + 1, SEEK_SET);
                fread(&inicio, sizeof(inicio), 1, disco);
                if (extendida.part_fit == 'w')
                {
                    free_space(inicio, realSize, extendida, entrada, disco);
                }
            }
            else
            {
                cout << "Error, particion logica no creada, no exite particion extendida" << endl;
            }
        }
        else
        {
            cout << "Ya existe una particion en el disco con ese nombre" << endl;
        }
    }
    fclose(disco);
}

bool eliminarLogica(string nombre, int part_start, FILE *disco, part entrada, string tipo)
{
    ebr ebr;
    fseek(disco, part_start, SEEK_SET);
    fread(&ebr, sizeof(ebr), 1, disco);
    if (ebr.part_status == 'a')
    {
        if (ebr.part_name == nombre)
        {
            //eliminar
            if (tipo == "fast")
            {

                ebr = {'n', NULL, ebr.part_start, 0, ebr.part_next, 'a'};
                fseek(disco, part_start, SEEK_SET);
                fwrite(&ebr, sizeof(ebr), 1, disco);
            }
            else if (tipo == "full")
            {
                char nulo = '\0';
                for (int i = 0; i < ebr.part_size; i++)
                {
                    fseek(disco, part_start + i, SEEK_SET);
                    fwrite(&nulo, sizeof(nulo), 1, disco);
                }
                ebr = {'n', NULL, ebr.part_start, 0, ebr.part_next, 'a'};
                fseek(disco, part_start, SEEK_SET);
                fwrite(&ebr, sizeof(ebr), 1, disco);
            }
            return true;
        }
        else if (ebr.part_next > 0)
        {
            eliminarLogica(nombre, ebr.part_next, disco, entrada, tipo);
        }
        else
        {
            res = false;
        }
    }
    else if (ebr.part_next > 0)
    {
        eliminarLogica(nombre, ebr.part_next, disco, entrada, tipo);
    }
    else
    {
        res = false;
    }
    return res;
}
//Funcion que elimina una particion en especifico
void eliminarParticion(part entrada)
{
    mbr master;
    FILE *disco = fopen(entrada.direccionDisco.c_str(), "rb+");
    fseek(disco, 0, SEEK_SET);
    fread(&master, sizeof(master), 1, disco);
    char nombre[16] = {0};
    for (int i = 0; i < entrada.nombre.size(); i++)
    {
        nombre[i] = entrada.nombre[i];
    }
    if (convertToString(nombre, 16) == convertToString(master.mbr_partition_1.part_name, 16))
    {
        if (entrada.del == "fast")
        {
            partition nuevo;
            nuevo.part_status = 'n';
            nuevo.part_type = NULL;
            master.mbr_partition_1 = nuevo;
            fseek(disco, 0, SEEK_SET);
            fwrite(&master, sizeof(master), 1, disco);
            cout << "Particion '" << nombre << "' eliminada correctamente" << endl;
        }
        else if (entrada.del == "full")
        {
            char nulo = '\0';
            for (int i = 0; i < master.mbr_partition_1.part_size; i++)
            {
                fseek(disco, master.mbr_partition_1.part_start + i, SEEK_SET);
                fwrite(&nulo, sizeof(nulo), 1, disco);
            }
            partition nuevo;
            nuevo.part_status = 'n';
            nuevo.part_type = NULL;
            master.mbr_partition_1 = nuevo;
            fseek(disco, 0, SEEK_SET);
            fwrite(&master, sizeof(master), 1, disco);
            cout << "Particion '" << nombre << "' eliminada correctamente" << endl;
        }
    }
    else if (convertToString(nombre, 16) == convertToString(master.mbr_partition_2.part_name, 16))
    {
        if (entrada.del == "fast")
        {
            partition nuevo;
            nuevo.part_status = 'n';
            nuevo.part_type = NULL;
            master.mbr_partition_2 = nuevo;
            fseek(disco, 0, SEEK_SET);
            fwrite(&master, sizeof(master), 1, disco);
            cout << "Particion '" << nombre << "' eliminada correctamente" << endl;
        }
        else if (entrada.del == "full")
        {
            char nulo = '\0';
            for (int i = 0; i < master.mbr_partition_2.part_size; i++)
            {
                fseek(disco, master.mbr_partition_2.part_start + i, SEEK_SET);
                fwrite(&nulo, sizeof(nulo), 1, disco);
            }
            partition nuevo;
            nuevo.part_status = 'n';
            nuevo.part_type = 's';
            master.mbr_partition_2 = nuevo;
            fseek(disco, 0, SEEK_SET);
            fwrite(&master, sizeof(master), 1, disco);
            cout << "Particion '" << nombre << "' eliminada correctamente" << endl;
        }
    }
    else if (convertToString(nombre, 16) == convertToString(master.mbr_partition_3.part_name, 16))
    {
        if (entrada.del == "fast")
        {
            partition nuevo;
            nuevo.part_status = 'n';
            nuevo.part_type = NULL;
            master.mbr_partition_3 = nuevo;
            fseek(disco, 0, SEEK_SET);
            fwrite(&master, sizeof(master), 1, disco);
            cout << "Particion '" << nombre << "' eliminada correctamente" << endl;
        }
        else if (entrada.del == "full")
        {
            char nulo = '\0';
            for (int i = 0; i < master.mbr_partition_3.part_size; i++)
            {
                fseek(disco, master.mbr_partition_3.part_start + i, SEEK_SET);
                fwrite(&nulo, sizeof(nulo), 1, disco);
            }
            partition nuevo;
            nuevo.part_status = 'n';
            nuevo.part_type = NULL;
            master.mbr_partition_3 = nuevo;
            fseek(disco, 0, SEEK_SET);
            fwrite(&master, sizeof(master), 1, disco);
            cout << "Particion '" << nombre << "' eliminada correctamente" << endl;
        }
    }
    else if (convertToString(nombre, 16) == convertToString(master.mbr_partition_4.part_name, 16))
    {
        if (entrada.del == "fast")
        {
            partition nuevo;
            nuevo.part_status = 'n';
            nuevo.part_type = NULL;
            master.mbr_partition_4 = nuevo;
            fseek(disco, 0, SEEK_SET);
            fwrite(&master, sizeof(master), 1, disco);
            cout << "Particion '" << nombre << "' eliminada correctamente" << endl;
        }
        else if (entrada.del == "full")
        {
            char nulo = '\0';
            for (int i = 0; i < master.mbr_partition_4.part_size; i++)
            {
                fseek(disco, master.mbr_partition_4.part_start + i, SEEK_SET);
                fwrite(&nulo, sizeof(nulo), 1, disco);
            }
            partition nuevo;
            nuevo.part_status = 'n';
            nuevo.part_type = NULL;
            master.mbr_partition_4 = nuevo;
            fseek(disco, 0, SEEK_SET);
            fwrite(&master, sizeof(master), 1, disco);
            cout << "Particion '" << nombre << "' eliminada correctamente" << endl;
        }
    }
    else if (existe_extendida(master))
    {
        partition extendida = obtenerParticionExtendida(master);
        if (eliminarLogica(nombre, extendida.part_start + sizeof(partition) + 1, disco, entrada, entrada.del))
        {
            cout << "Particion '" << nombre << "' eliminada correctamente" << endl;
        }
        else
        {
            cout << "Particion no encontrada" << endl;
        }
    }
    else
    {
        cout << "Particion no encontrada" << endl;
    }
    fclose(disco);
}
bool addLogica(string nombre, int part_start, FILE *disco, part entrada, int anadir, partition extendida)
{
    ebr ebr;
    fseek(disco, part_start, SEEK_SET);
    fread(&ebr, sizeof(ebr), 1, disco);
    if (ebr.part_status == 'a')
    {
        if (ebr.part_name == nombre)
        {
            //anadir
            if (ebr.part_next > 0)
            {
                if ((ebr.part_start + sizeof(ebr) + ebr.part_size + anadir + 1) < ebr.part_next)
                {
                    ebr.part_size += anadir;
                    fseek(disco, part_start, SEEK_SET);
                    fwrite(&ebr, sizeof(ebr), 1, disco);
                    res = true;
                }
                else
                {
                    cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
                    res = false;
                }
            }
            else if ((extendida.part_start + sizeof(partition) + extendida.part_size) > (ebr.part_start + sizeof(ebr) + ebr.part_size + 1 + anadir))
            {
                ebr.part_size += anadir;
                fseek(disco, part_start, SEEK_SET);
                fwrite(&ebr, sizeof(ebr), 1, disco);
                res = true;
            }
            else
            {
                cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
                res = false;
            }

        }
        else if (ebr.part_next > 0)
        {
            addLogica(nombre, ebr.part_next, disco, entrada, anadir, extendida);
        }
        else
        {
            res = false;
        }
    }
    else if (ebr.part_next > 0)
    {
        addLogica(nombre, ebr.part_next, disco, entrada, anadir, extendida);
    }
    else
    {
        res = false;
    }
    return res;
}
//Funcion para agregar o quitar espacion de una particion
void addParticion(part entrada)
{
    int anadir = 1;
    if (entrada.unidades == "b")
    {
        anadir = entrada.add;
    }
    else if (entrada.unidades == "k")
    {
        anadir = entrada.add * 1024;
    }
    else if (entrada.unidades == "m")
    {
        anadir = entrada.add * 1024 * 1024;
    }
    mbr master;
    FILE *disco = fopen(entrada.direccionDisco.c_str(), "rb+");
    fseek(disco, 0, SEEK_SET);
    fread(&master, sizeof(master), 1, disco);
    char nombre[16] = {0};
    for (int i = 0; i < entrada.nombre.size(); i++)
    {
        nombre[i] = entrada.nombre[i];
    }
    if (convertToString(nombre, 16) == convertToString(master.mbr_partition_1.part_name, 16))
    {
        if (master.mbr_partition_2.part_status == 'a')
        {
            if (((master.mbr_partition_1.part_size + anadir) > 0) && ((master.mbr_partition_1.part_start + master.mbr_partition_1.part_size + anadir) < master.mbr_partition_2.part_start))
            {
                master.mbr_partition_1.part_size += anadir;
                fseek(disco, 0, SEEK_SET);
                fwrite(&master, sizeof(master), 1, disco);
                cout << "Redimension completada exitosamente" << endl;
            }
            else
            {
                cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
            }
        }
        else if (master.mbr_partition_3.part_status == 'a')
        {
            if (((master.mbr_partition_1.part_size + anadir) > 0) && ((master.mbr_partition_1.part_start + master.mbr_partition_1.part_size + anadir) < master.mbr_partition_3.part_start))
            {
                master.mbr_partition_1.part_size += anadir;
                fseek(disco, 0, SEEK_SET);
                fwrite(&master, sizeof(master), 1, disco);
                cout << "Redimension completada exitosamente" << endl;
            }
            else
            {
                cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
            }
        }
        else if (master.mbr_partition_4.part_status == 'a')
        {
            if (((master.mbr_partition_1.part_size + anadir) > 0) && ((master.mbr_partition_1.part_start + master.mbr_partition_1.part_size + anadir) < master.mbr_partition_4.part_start))
            {
                master.mbr_partition_1.part_size += anadir;
                fseek(disco, 0, SEEK_SET);
                fwrite(&master, sizeof(master), 1, disco);
                cout << "Redimension completada exitosamente" << endl;
            }
            else
            {
                cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
            }
        }
        else
        {
            if (((master.mbr_partition_1.part_size + anadir) > 0) && ((master.mbr_partition_1.part_start + master.mbr_partition_1.part_size + anadir) < (master.mbr_tamano - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size))))
            {
                master.mbr_partition_1.part_size += anadir;
                fseek(disco, 0, SEEK_SET);
                fwrite(&master, sizeof(master), 1, disco);
                cout << "Redimension completada exitosamente" << endl;
            }
            else
            {
                cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
            }
        }
    }
    else if (convertToString(nombre, 16) == convertToString(master.mbr_partition_2.part_name, 16))
    {
        if (master.mbr_partition_3.part_status == 'a')
        {
            if (((master.mbr_partition_2.part_size + anadir) > 0) && ((master.mbr_partition_2.part_start + master.mbr_partition_2.part_size + anadir) < master.mbr_partition_3.part_start))
            {
                master.mbr_partition_2.part_size += anadir;
                fseek(disco, 0, SEEK_SET);
                fwrite(&master, sizeof(master), 1, disco);
                cout << "Redimension completada exitosamente" << endl;
            }
            else
            {
                cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
            }
        }
        else if (master.mbr_partition_4.part_status == 'a')
        {
            if (((master.mbr_partition_2.part_size + anadir) > 0) && ((master.mbr_partition_2.part_start + master.mbr_partition_2.part_size + anadir) < master.mbr_partition_4.part_start))
            {
                master.mbr_partition_2.part_size += anadir;
                fseek(disco, 0, SEEK_SET);
                fwrite(&master, sizeof(master), 1, disco);
                cout << "Redimension completada exitosamente" << endl;
            }
            else
            {
                cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
            }
        }
        else
        {
            if (((master.mbr_partition_2.part_size + anadir) > 0) && ((master.mbr_partition_2.part_start + master.mbr_partition_2.part_size + anadir) < (master.mbr_tamano - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size))))
            {
                master.mbr_partition_2.part_size += anadir;
                fseek(disco, 0, SEEK_SET);
                fwrite(&master, sizeof(master), 1, disco);
                cout << "Redimension completada exitosamente" << endl;
            }
            else
            {
                cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
            }
        }
    }
    else if (convertToString(nombre, 16) == convertToString(master.mbr_partition_3.part_name, 16))
    {
        if (master.mbr_partition_4.part_status == 'a')
        {
            if (((master.mbr_partition_3.part_size + anadir) > 0) && ((master.mbr_partition_3.part_start + master.mbr_partition_3.part_size + anadir) < master.mbr_partition_4.part_start))
            {
                master.mbr_partition_3.part_size += anadir;
                fseek(disco, 0, SEEK_SET);
                fwrite(&master, sizeof(master), 1, disco);
                cout << "Redimension completada exitosamente" << endl;
            }
            else
            {
                cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
            }
        }
        else
        {
            if (((master.mbr_partition_3.part_size + anadir) > 0) && ((master.mbr_partition_3.part_start + master.mbr_partition_3.part_size + anadir) < (master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size))))
            {
                master.mbr_partition_3.part_size += anadir;
                fseek(disco, 0, SEEK_SET);
                fwrite(&master, sizeof(master), 1, disco);
                cout << "Redimension completada exitosamente" << endl;
            }
            else
            {
                cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
            }
        }
    }
    else if (convertToString(nombre, 16) == convertToString(master.mbr_partition_4.part_name, 16))
    {
        if (((master.mbr_partition_4.part_size + anadir) > 0) && ((master.mbr_partition_4.part_start + master.mbr_partition_4.part_size + anadir) < master.mbr_tamano))
        {
            master.mbr_partition_4.part_size += anadir;
            fseek(disco, 0, SEEK_SET);
            fwrite(&master, sizeof(master), 1, disco);
            cout << "Redimension completada exitosamente" << endl;
        }
        else
        {
            cout << "No se pudo redimensionar la particion '" << entrada.nombre << "'" << endl;
        }
    }
    else if (existe_extendida(master))
    {
        partition extendida = obtenerParticionExtendida(master);
        if (addLogica(nombre, extendida.part_start + sizeof(partition) + 1, disco, entrada, anadir, extendida))
        {
            cout << "Particion '" << nombre << "' redimensionada correctamente" << endl;
        }
        else
        {
            cout << "Error no se pudo redimensionar la particion" << endl;
        }
    }
    else
    {
        cout << "Particion no encontrada" << endl;
    }
    fclose(disco);
}

//Funcion Fdisk que analiza los parametros del comando respectivo
void fdisk(vector<string> partes)
{
    part particion = {0, "k", "", 'p', 'w', 1, "", "", 0};
    bool problem = false;
    for (int i = 0; i < partes.size(); i++)
    {
        vector<string> componentes = split(partes[i], "=");
        if (lower(componentes[0]) == "fdisk")
        {
        }
        else if (lower(componentes[0]) == "-size")
        {
            if (atoi(componentes[1].c_str()) > 0)
            {
                particion.size = atoi(componentes[1].c_str());
            }
            else
            {
                cout << "Tamaño de la particion invalido" << endl;
                problem = true;
            }
        }
        else if (lower(componentes[0]) == "-u")
        {
            if ((lower(componentes[1]) == "b") || (lower(componentes[1]) == "k") || (lower(componentes[1]) == "m"))
            {
                particion.unidades = lower(componentes[1]);
            }
            else
            {
                cout << "Unidades ingresadas no validas" << endl;
                problem = true;
            }
        }
        else if (lower(componentes[0]) == "-path")
        {
            if (exists(quitarComillas(componentes[1])))
            {
                particion.direccionDisco = quitarComillas(componentes[1]);
            }
            else
            {
                cout << "Direccion de disco invalida" << endl;
                problem = true;
            }
        }
        else if (lower(componentes[0]) == "-type")
        {
            if ((lower(componentes[1]) == "p") || (lower(componentes[1]) == "e") || (lower(componentes[1]) == "l"))
            {
                char tmp[strlen(componentes[1].c_str()) + 1];
                strcpy(tmp, lower(componentes[1]).c_str());
                particion.tipo = tmp[0];
            }
            else
            {
                cout << "Tipo de particion invalido" << endl;
                problem = true;
            }
        }
        else if (lower(componentes[0]) == "-f")
        {
            if ((lower(componentes[1]) == "ff") || (lower(componentes[1]) == "bf") || (lower(componentes[1]) == "wf"))
            {
                char tmp[strlen(componentes[1].c_str()) + 1];
                strcpy(tmp, lower(componentes[1]).c_str());
                particion.ajuste = tmp[0];
            }
            else
            {
                cout << "Ajuste de la particion invalido" << endl;
                problem = true;
            }
        }
        else if (lower(componentes[0]) == "-delete")
        {
            if ((lower(componentes[1]) == "fast") || (lower(componentes[1]) == "full"))
            {
                particion.del = lower(componentes[1]);
                particion.delAdd = 2;
            }
            else
            {
                particion.delAdd = -2;
                cout << "Error en el comando " << componentes[1] << endl;
                problem = true;
            }
        }
        else if (lower(componentes[0]) == "-name")
        {
            particion.nombre = quitarComillas(componentes[1]);
        }
        else if (lower(componentes[0]) == "-add")
        {
            particion.add = atoi(componentes[1].c_str());
            particion.delAdd = 3;
        }
        else
        {
            cout << "Comando no valido" << endl;
        }
    }
    if (problem == true)
    {
    }
    else if (((particion.size == 0) || (particion.direccionDisco == "") || (particion.nombre == "")) && (particion.delAdd == 1))
    {
        cout << "Parametros obligatorios incompletos" << endl;
    }
    else
    {
        if (particion.delAdd == 1)
        {
            crearParticion(particion);
        }
        else if (particion.delAdd == 2)
        {
            string res;
            cout << "Esta seguro que desea eliminar la particion '" << particion.nombre << "' (S/N)" << endl;
            cin >> res;
            if (lower(res) == "s")
            {
                eliminarParticion(particion);
            }
            else
            {
                cout << "Operacion cancelada" << endl;
            }
        }
        else if (particion.delAdd == 3)
        {
            addParticion(particion);
        }
    }
}
