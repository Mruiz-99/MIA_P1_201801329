#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

string salida2 = "";
int c_ebr, c_disk;

//Funcion que obtiene la direccion de una particion montada en el sistema
string obtenerDireccion(string id)
{
    for (int i = 0; i < particionesMontadas.size(); i++)
    {
        if (particionesMontadas[i].id == id)
        {
            return particionesMontadas[i].path;
        }
    }
    return "";
}
//Funcion que genera las tablas de EBR para el reporte del MBR
string agregarEBR(int part_start, FILE *disco)
{
    ebr ebr;
    fseek(disco, part_start, SEEK_SET);
    fread(&ebr, sizeof(ebr), 1, disco);
    if (ebr.part_status == 'a')
    {
        c_ebr += 1;
        salida2 += "n" + to_string(c_ebr) + "[label=<<table border=\"1\"><tr><td border=\"0\">EBR</td><td border=\"0\"></td></tr>\n<tr><td>Nombre</td><td>Valor</td></tr>\n";
        salida2 += "<tr><td>part_status</td><td>";
        salida2 += char(ebr.part_status);
        salida2 += "</td></tr>\n";
        salida2 += "<tr><td>part_fit</td><td>";
        salida2 += char(ebr.part_fit);
        salida2 += "</td></tr>\n";
        salida2 += "<tr><td>part_start</td><td>" + to_string(ebr.part_start) + "</td></tr>\n";
        salida2 += "<tr><td>part_size</td><td>" + to_string(ebr.part_size) + "</td></tr>\n";
        salida2 += "<tr><td>part_next</td><td>" + to_string(ebr.part_next) + "</td></tr>\n";
        salida2 += "<tr><td>part_name</td><td>" + convertToString(ebr.part_name, 16) + "</td></tr>\n";
        salida2 += "</table>>];\n";
        if (ebr.part_next > 0)
        {
            agregarEBR(ebr.part_next, disco);
        }
        else
        {

            return salida2;
        }
    }
    else if (ebr.part_next > 0)
    {
        agregarEBR(ebr.part_next, disco);
    }
    else
    {
        return salida2;
    }
    return salida2;
}
//Funcion genera la tabla del reporte del MBR
string generarTablaMBR(mbr master, string path)
{
    string salida = "n1[label=<<table border=\"1\"><tr><td border=\"0\">MBR " + obtenerNombre(path) + "</td><td border=\"0\"></td></tr>\n<tr><td>Nombre</td><td>Valor</td></tr>\n";
    salida += "<tr><td>mbr_tamano</td><td>" + to_string(master.mbr_tamano) + "</td></tr>\n";
    char fecha[20];
    tm *reg = localtime(&master.mbr_fecha_creacion);
    strftime(fecha, 20, "%d/%m/%Y %H:%M:%S", reg);
    salida += "<tr><td>mbr_fecha_creacion</td><td>" + convertToString(fecha, 20) + "" + "</td></tr>\n";
    salida += "<tr><td>mbr_disk_signature</td><td>" + to_string(master.mbr_disk_signature) + "</td></tr>\n";
    salida += "<tr><td>disk_fit</td><td>";
    salida += char(master.disk_fit);
    salida += "</td></tr>\n";
    if (master.mbr_partition_1.part_status == 'a')
    {
        salida += "<tr><td>part_status_1</td><td>";
        salida += char(master.mbr_partition_1.part_status);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_type_1</td><td>";
        salida += char(master.mbr_partition_1.part_type);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_fit_1</td><td>";
        salida += char(master.mbr_partition_1.part_fit);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_start_1</td><td>" + to_string(master.mbr_partition_1.part_start) + "</td></tr>\n";
        salida += "<tr><td>part_size_1</td><td>" + to_string(master.mbr_partition_1.part_size) + "</td></tr>\n";
        salida += "<tr><td>part_name_1</td><td>" + convertToString(master.mbr_partition_1.part_name, 16) + "</td></tr>\n";
    }
    if (master.mbr_partition_2.part_status == 'a')
    {
        salida += "<tr><td>part_status_2</td><td>";
        salida += char(master.mbr_partition_2.part_status);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_type_2</td><td>";
        salida += char(master.mbr_partition_2.part_type);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_fit_2</td><td>";
        salida += char(master.mbr_partition_2.part_fit);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_start_2</td><td>" + to_string(master.mbr_partition_2.part_start) + "</td></tr>\n";
        salida += "<tr><td>part_size_2</td><td>" + to_string(master.mbr_partition_2.part_size) + "</td></tr>\n";
        salida += "<tr><td>part_name_2</td><td>" + convertToString(master.mbr_partition_2.part_name, 16) + "</td></tr>\n";
    }
    if (master.mbr_partition_3.part_status == 'a')
    {
        salida += "<tr><td>part_status_3</td><td>";
        salida += char(master.mbr_partition_3.part_status);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_type_3</td><td>";
        salida += char(master.mbr_partition_3.part_type);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_fit_3</td><td>";
        salida += char(master.mbr_partition_3.part_fit);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_start_3</td><td>" + to_string(master.mbr_partition_3.part_start) + "</td></tr>\n";
        salida += "<tr><td>part_size_3</td><td>" + to_string(master.mbr_partition_3.part_size) + "</td></tr>\n";
        salida += "<tr><td>part_name_3</td><td>" + convertToString(master.mbr_partition_3.part_name, 16) + "</td></tr>\n";
    }
    if (master.mbr_partition_4.part_status == 'a')
    {
        salida += "<tr><td>part_status_4</td><td>";
        salida += char(master.mbr_partition_4.part_status);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_type_4</td><td>";
        salida += char(master.mbr_partition_4.part_type);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_fit_4</td><td>";
        salida += char(master.mbr_partition_4.part_fit);
        salida += "</td></tr>\n";
        salida += "<tr><td>part_start_4</td><td>" + to_string(master.mbr_partition_4.part_start) + "</td></tr>\n";
        salida += "<tr><td>part_size_4</td><td>" + to_string(master.mbr_partition_4.part_size) + "</td></tr>\n";
        salida += "<tr><td>part_name_4</td><td>" + convertToString(master.mbr_partition_4.part_name, 16) + "</td></tr>\n";
    }
    salida += "</table>>];\n";
    return salida;
}

string generarTablaSB(superblock sb, string path)
{
    string salida = "n1[label=<<table border=\"1\"><tr><td border=\"0\">Super Bloque " + obtenerNombre(path) + "</td><td border=\"0\"></td></tr>\n<tr><td>Nombre</td><td>Valor</td></tr>\n";
    salida += "<tr><td>s_inodes_count</td><td>" + to_string(sb.s_inodes_count) + "</td></tr>\n";
    salida += "<tr><td>s_blocks_count</td><td>" + to_string(sb.s_blocks_count) + "</td></tr>\n";
    salida += "<tr><td>s_free_blocks_count</td><td>" + to_string(sb.s_free_blocks_count) + "</td></tr>\n";
    salida += "<tr><td>s_free_inodes_count</td><td>" + to_string(sb.s_free_inodes_count) + "</td></tr>\n";
    char fecha[20];
    tm *reg = localtime(&sb.s_mtime);
    strftime(fecha, 20, "%d/%m/%Y %H:%M:%S", reg);
    salida += "<tr><td>s_mtime</td><td>" + convertToString(fecha, 20) + "" + "</td></tr>\n";
    char fecha2[20];
    tm *reg2 = localtime(&sb.s_umtime);
    strftime(fecha2, 20, "%d/%m/%Y %H:%M:%S", reg2);
    salida += "<tr><td>s_umtime</td><td>" + convertToString(fecha2, 20) + "" + "</td></tr>\n";
    salida += "<tr><td>s_mnt_count</td><td>" + to_string(sb.s_mnt_count) + "</td></tr>\n";
    salida += "<tr><td>s_magic</td><td>" + to_string(sb.s_magic) + "xEF53</td></tr>\n";
    salida += "<tr><td>s_inode_size</td><td>" + to_string(sb.s_inode_size) + "</td></tr>\n";
    salida += "<tr><td>s_block_size</td><td>" + to_string(sb.s_block_size) + "</td></tr>\n";
    salida += "<tr><td>s_first_ino</td><td>" + to_string(sb.s_first_ino) + "</td></tr>\n";
    salida += "<tr><td>s_first_blo</td><td>" + to_string(sb.s_first_blo) + "</td></tr>\n";
    salida += "<tr><td>s_bm_inode_start</td><td>" + to_string(sb.s_bm_inode_start) + "</td></tr>\n";
    salida += "<tr><td>s_bm_block_start</td><td>" + to_string(sb.s_bm_block_start) + "</td></tr>\n";
    salida += "<tr><td>s_inode_start</td><td>" + to_string(sb.s_inode_start) + "</td></tr>\n";
    salida += "<tr><td>s_block_start</td><td>" + to_string(sb.s_block_start) + "</td></tr>\n";
    salida += "</table>>];\n";
    return salida;
}

void reportarMBR(report reporte)
{
    if (obtenerDireccion(reporte.id) != "")
    {
        string salida = "graph grafo{\nnode[shape=plaintext];\n";
        FILE *disco;
        if (disco = fopen(obtenerDireccion(reporte.id).c_str(), "rb"))
        {
            mbr master;
            fseek(disco, 0, SEEK_SET);
            fread(&master, sizeof(master), 1, disco);
            salida += generarTablaMBR(master, obtenerDireccion(reporte.id));
            if (existe_extendida(master))
            {
                c_ebr = 1;
                salida2 = "";
                partition extendida = obtenerParticionExtendida(master);
                salida += agregarEBR((extendida.part_start + sizeof(partition) + 1), disco);
            }
            salida += "\n}";
            fclose(disco);
            string dot = split(reporte.path, ".")[0] + ".dot";
            ofstream grafo;
            grafo.open(dot);
            grafo << "" + salida + "\n";
            grafo.close();
            string cmd = "dot -T" + lower(split(reporte.path, ".")[1]) + " \"" + dot + "\" -o \"" + reporte.path + "\"";
            system(cmd.c_str());
            cout << "Reporte MBR generado exitosamente" << endl;
        }
        else
        {
            cout << "Error al leer disco" << endl;
        }
    }
    else
    {
        cout << "Identificador de particion no valido" << endl;
    }
}
//Funcion que grafica la particion extendida
string generarExtend(int part_start, float p, FILE *disco, partition extendida)
{
    ebr ebr;
    fseek(disco, part_start, SEEK_SET);
    fread(&ebr, sizeof(ebr), 1, disco);
    c_disk += 1;
    if ((ebr.part_status == 'n') && (ebr.part_next == 0))
    {
        float porcentaje = ((float)((extendida.part_start + sizeof(partition) + extendida.part_size) - (ebr.part_start + sizeof(ebr) + 1)) / (float)(extendida.part_size)) * 100;
        salida2 += "l" + to_string(c_disk) + "[ shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
    }
    else if ((ebr.part_next > 0) && (ebr.part_status == 'n'))
    {
        float porcentaje = ((float)(ebr.part_next - (ebr.part_start + sizeof(ebr) + 1)) / (float)(extendida.part_size)) * 100;
        salida2 += "l" + to_string(c_disk) + "[ shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
        generarExtend(ebr.part_next,porcentaje, disco, extendida);
    }
    else if ((ebr.part_status == 'a') && (ebr.part_next == 0))
    {
        float porcentaje = ((float)((ebr.part_size) / (float)(extendida.part_size))) * 100;
        salida2 += "ebr"+to_string(c_disk)+"[shape=record label=\"EBR\"];\n";
        salida2 += "l" + to_string(c_disk) + "[ shape=record label=<<table border=\"0\"><tr><td>"+convertToString(ebr.part_name, 16)+"</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
        if(((extendida.part_start + sizeof(partition) + extendida.part_size)- (ebr.part_start + ebr.part_size + sizeof(ebr) +1))>0){
            c_disk+=1;
             float porcentaje = ((float)((extendida.part_start + sizeof(partition) + extendida.part_size) - (ebr.part_start + ebr.part_size+ sizeof(ebr) + 1)) / (float)(extendida.part_size)) * 100;
            salida2 += "l" + to_string(c_disk) + "[ shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
        }
    
    }
    else if ((ebr.part_status == 'a') && (ebr.part_next > 0))
    {
        float porcentaje = ((float)((ebr.part_size) / (float)(extendida.part_size))) * 100;
        salida2 += "ebr"+to_string(c_disk)+"[shape=record label=\"EBR\"];\n";
        salida2 += "l" + to_string(c_disk) + "[ shape=record label=<<table border=\"0\"><tr><td>"+convertToString(ebr.part_name, 16)+"</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
        if((ebr.part_next- (ebr.part_start + ebr.part_size + sizeof(ebr) +1))>0){
            c_disk+=1;
             float porcentaje = ((float)((ebr.part_next) - (ebr.part_start + ebr.part_size+ sizeof(ebr) + 1)) / (float)(extendida.part_size)) * 100;
            salida2 += "l" + to_string(c_disk) + "[ shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
        }
        generarExtend(ebr.part_next, porcentaje, disco, extendida);
    }
    return salida2;
}
//Funcion que grafica el disco
string graficarDisco(mbr master, FILE *disco)
{
    string salida = "";
    salida2;
    c_disk = 0;
    if (master.mbr_partition_1.part_status == 'n')
    {
        if (master.mbr_partition_2.part_status == 'a')
        {
            if (master.mbr_partition_3.part_status == 'n')
            {
                if (master.mbr_partition_4.part_status == 'a')
                {
                    float porcentaje = ((float)(master.mbr_partition_2.part_start - sizeof(master)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                    salida += "p1[ shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    if (master.mbr_partition_2.part_type == 'p')
                    {
                        porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p2[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_2.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_2.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_2);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    porcentaje = ((float)(master.mbr_partition_4.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                    salida += "p3[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    if (master.mbr_partition_4.part_type == 'p')
                    {
                        porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p4[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_4.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {

                        porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_4.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_4);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                }
                else if (master.mbr_partition_4.part_status == 'n')
                {
                    float porcentaje = ((float)(master.mbr_partition_2.part_start - sizeof(master)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                    salida += "p1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    if (master.mbr_partition_2.part_type == 'p')
                    {
                        porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p2[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_2.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_2.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_2);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                    salida += "p3[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                }
            }
            else if (master.mbr_partition_3.part_status == 'a')
            {
                if (master.mbr_partition_4.part_status == 'a')
                {
                    float porcentaje = ((float)(master.mbr_partition_2.part_start - sizeof(master)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                    salida += "p1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    if (master.mbr_partition_2.part_type == 'p')
                    {
                        porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p2[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_2.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_2.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_2);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_3.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) > 0)
                    {
                        porcentaje = ((float)(master.mbr_partition_3.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_3.part_type == 'p')
                    {
                        porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p3[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_3.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_3.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_3);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_4.part_start - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > 0)
                    {
                        porcentaje = ((float)(master.mbr_partition_4.part_start - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp2[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_4.part_type == 'p')
                    {
                        porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p2[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_4.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_4.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_4);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) > 0)
                    {
                        porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp3[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                }
                else if (master.mbr_partition_4.part_status == 'n')
                {
                    float porcentaje = ((float)(master.mbr_partition_2.part_start - sizeof(master)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                    salida += "p1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    if (master.mbr_partition_2.part_type == 'p')
                    {
                        porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p2[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_2.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_2.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_2);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_3.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) > 0)
                    {
                        porcentaje = ((float)(master.mbr_partition_3.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_3.part_type == 'p')
                    {
                        porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p3[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_3.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_3.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_3);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > 0)
                    {
                        porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp2[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
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
                    float porcentaje = ((float)(master.mbr_tamano - sizeof(master)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                    salida += "sp1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                }
                else if (master.mbr_partition_4.part_status == 'a')
                {
                    if ((master.mbr_partition_4.part_start - sizeof(master)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_start - sizeof(master)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_4.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_4.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_4.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_4);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp2[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                }
            }
            else if (master.mbr_partition_3.part_status == 'a')
            {
                if (master.mbr_partition_4.part_status == 'a')
                {
                    if ((master.mbr_partition_3.part_start - sizeof(master)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_start - sizeof(master)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_3.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_3.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_3.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_3);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_4.part_start - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_start - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp2[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_4.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_4.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_4.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_4);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp3[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                }
                else if (master.mbr_partition_4.part_status == 'n')
                {
                    if ((master.mbr_partition_3.part_start - sizeof(master)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_start - sizeof(master)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_3.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_3.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_3.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_3);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp2[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
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
                    if (master.mbr_partition_1.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_1.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_1.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_1);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_2.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_2.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p2[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_2.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_2.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_2);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_4.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_4.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p2[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_4.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_4.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_4);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp3[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                }
                else if (master.mbr_partition_4.part_status == 'n')
                {

                    if (master.mbr_partition_1.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_1.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_1.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_1);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_2.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_2.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p2[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_2.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_2.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_2);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp2[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                }
            }
            else if (master.mbr_partition_3.part_status == 'a')
            {
                if (master.mbr_partition_4.part_status == 'a')
                {
                    if (master.mbr_partition_1.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_1.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_1.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_1);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_2.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_2.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p2[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_2.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_2.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_2);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_3.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp2[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_3.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p3[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_3.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_3.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_3);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_4.part_start - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_start - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp3[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_4.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p4[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_4.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_4.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_4);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp4[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                }
                else if (master.mbr_partition_4.part_status == 'n')
                {
                    if (master.mbr_partition_1.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_1.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_1.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_1);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_2.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp1[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_2.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p2[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_2.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_2.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_2.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_2);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_3.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_start - (master.mbr_partition_2.part_start + master.mbr_partition_2.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp2[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_3.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p3[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_3.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_3.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_3);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp4[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
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
                    if (master.mbr_partition_1.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_1.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_1.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_1);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp4[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                }
                else if (master.mbr_partition_4.part_status == 'a')
                {
                    if (master.mbr_partition_1.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_1.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_1.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_1);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_4.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp3[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_4.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p4[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_4.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_4.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_4);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp4[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                }
            }
            else if (master.mbr_partition_3.part_status == 'a')
            {
                if (master.mbr_partition_4.part_status == 'a')
                {
                    if (master.mbr_partition_1.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_1.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_1.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_1);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_3.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp2[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_3.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p3[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_3.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_3.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_3);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_4.part_start - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_start - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp3[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_4.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p4[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_4.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_4.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_4.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_4);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_4.part_start + master.mbr_partition_4.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp4[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                }
                else if (master.mbr_partition_4.part_status == 'n')
                {
                    if (master.mbr_partition_1.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p1[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_1.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_1.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_1.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_1);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_partition_3.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_start - (master.mbr_partition_1.part_start + master.mbr_partition_1.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp2[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    if (master.mbr_partition_3.part_type == 'p')
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "p3[shape=record label=<<table border=\"0\"><tr><td>" + convertToString(master.mbr_partition_3.part_name, 16) + "</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                    else
                    {
                        float porcentaje = ((float)(master.mbr_partition_3.part_size) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "subgraph clusterp2{ \n";
                        salida += generarExtend(master.mbr_partition_3.part_start + sizeof(partition) + 1, porcentaje, disco, master.mbr_partition_3);
                        salida += "\nlabel = \"Extendida\";color=black;\n}";
                    }
                    if ((master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) > 0)
                    {
                        float porcentaje = ((float)(master.mbr_tamano - (master.mbr_partition_3.part_start + master.mbr_partition_3.part_size)) / (float)(master.mbr_tamano - sizeof(master))) * 100;
                        salida += "sp4[shape=record label=<<table border=\"0\"><tr><td>Libre</td></tr><tr><td>" + to_string(porcentaje) + "% del disco</td></tr></table>>];\n";
                    }
                }
            }
        }
    }
    return salida;
}
void reportarDisk(report reporte)
{
    if (obtenerDireccion(reporte.id) != "")
    {
        string salida = "graph grafo{\n compound=true;\nnode[shape=plaintext border=\"1\" margin=\"0\"];\n";
        FILE *disco;
        if (disco = fopen(obtenerDireccion(reporte.id).c_str(), "rb"))
        {
            mbr master;
            fseek(disco, 0, SEEK_SET);
            fread(&master, sizeof(master), 1, disco);

            vector<string> nombre = split(obtenerDireccion(reporte.id), "/");
            string tmp = nombre[nombre.size() - 1];
            salida += "subgraph clusterp1{\nlabel=\"" + tmp + "\"; \n";
            salida += "mbr[shape=record label=\"MBR\"];\n";
            salida += graficarDisco(master, disco);
            salida += "\n}";
            salida += "\n}";
            string dot = split(reporte.path, ".")[0] + ".dot";
            ofstream grafo;
            fclose(disco);
            grafo.open(dot);
            grafo << "" + salida + "\n";
            grafo.close();
            string cmd = "dot -T" + lower(split(reporte.path, ".")[1]) + " \"" + dot + "\" -o \"" + reporte.path + "\"";
            system(cmd.c_str());
            cout << "Reporte de disco generado exitosamente" << endl;
        }
        else
        {
            cout << "Error al leer disco" << endl;
        }
    }
    else
    {
        cout << "Identificador de particion no valido" << endl;
    }
}

void sb(report reporte)
{
    if (obtenerDireccion(reporte.id) != "")
    {
        FILE *disco;
        string dir = obtenerDireccion(reporte.id);
        if (disco = fopen(dir.c_str(), "rb+"))
        {
            mbr master;
            fseek(disco, 0, SEEK_SET);
            fread(&master, sizeof(mbr), 1, disco);
            partition particion = obtenerParticion(master, obtenerN(reporte.id));
            superblock sb;
            fseek(disco, particion.part_start, SEEK_SET);
            fread(&sb, sizeof(superblock), 1, disco);
            fclose(disco);
            ofstream salida;
            string dot = split(reporte.path, ".")[0] + ".dot";
            salida.open(dot);
            string txt = "graph grafo{\nnode[shape=plaintext];\n";
            txt += generarTablaSB(sb, obtenerDireccion(reporte.id));
            txt += "\n}";
            salida << "" + txt + "\n";
            salida.close();
            string cmd = "dot -T" + lower(split(reporte.path, ".")[1]) + " \"" + dot + "\" -o \"" + reporte.path + "\"";
            system(cmd.c_str());
            cout << "Reporte generado exitosamente" << endl;
        }
        else
        {
            cout << "No existe el disco" << endl;
        }
    }
    else
    {
        cout << "La direccion del disco no fue encontrada" << endl;
    }
}
void block(report reporte)
{
    if (obtenerDireccion(reporte.id) != "")
    {
        FILE *disco;
        string dir = obtenerDireccion(reporte.id);
        if (disco = fopen(dir.c_str(), "rb+"))
        {
            mbr master;
            fseek(disco, 0, SEEK_SET);
            fread(&master, sizeof(mbr), 1, disco);
            partition particion = obtenerParticion(master, obtenerN(reporte.id));
            superblock sb;
            fseek(disco, particion.part_start, SEEK_SET);
            fread(&sb, sizeof(superblock), 1, disco);
            char bm[sb.s_blocks_count];
            fseek(disco, sb.s_bm_block_start, SEEK_SET);
            for (int i = 0; i < sb.s_blocks_count; i++)
            {
                fread(&bm[i], sizeof(char), 1, disco);
            }
            string salida = "digraph grafo{\nrankdir=LR;\nnode[shape=plaintext];\n";
            for (int i = 0; i < strlen(bm); i++)
            {
                if (bm[i] == '1')
                {
                    if (i == 0)
                    {
                        fseek(disco, sb.s_block_start + (int)(i * sizeof(dirBlock)), SEEK_SET);
                        dirBlock temp;
                        fread(&temp, sizeof(temp), 1, disco);
                        salida += "n" + to_string(i) + "[label=<<table border=\"1\">";
                        salida += "<tr><td border=\"0\">Bloque Carpeta 1</td><td border=\"0\"></td></tr>\n";
                        salida += "<tr><td border=\"0\">b_name</td><td border=\"0\">b_inodo</td></tr>\n";
                        for (int i = 0; i < (int)(sizeof(temp.b_content) / sizeof(content)); i++)
                        {
                            if (i == 3)
                            {
                                salida += "<tr><td border=\"0\"></td><td border=\"0\">-1</td></tr>\n";
                            }
                            else
                            {
                                salida += "<tr><td border=\"0\">" + convertToString(temp.b_content[i].b_name, 12) + "</td><td border=\"0\">" + to_string(temp.b_content[i].b_inode) + "</td></tr>\n";
                            }
                        }
                        salida += "</table>>];\n";
                        if (i != 0)
                        {
                            salida += "n" + to_string(i - 1) + " -> n" + to_string(i) + ";\n";
                        }
                    }
                    else if (i == 1)
                    {
                        fseek(disco, sb.s_block_start + (int)(i * sizeof(fileBlock)), SEEK_SET);
                        fileBlock temp;
                        fread(&temp, sizeof(temp), 1, disco);
                        salida += "n" + to_string(i) + "[label=<<table border=\"1\">";
                        salida += "<tr><td border=\"0\">Bloque Archivo 1</td></tr>\n";
                        salida += "<tr><td border=\"0\">" + convertToString(temp.b_content, 64) + "</td></tr>\n";
                        salida += "</table>>];\n";
                        if (i != 0)
                        {
                            salida += "n" + to_string(i - 1) + " -> n" + to_string(i) + ";\n";
                        }
                    }
                }
            }
            salida += "\n}";
            string dot = split(reporte.path, ".")[0] + ".dot";
            fclose(disco);
            ofstream grafo;
            grafo.open(dot);
            grafo << "" + salida + "\n";
            grafo.close();
            string cmd = "dot -T" + lower(split(reporte.path, ".")[1]) + " \"" + dot + "\" -o \"" + reporte.path + "\"";
            system(cmd.c_str());
            cout << "Reporte creado exitosamente" << endl;
        }
        else
        {
            cout << "No existe el disco" << endl;
        }
    }
    else
    {
        cout << "La direccion del disco no fue encontrada" << endl;
    }
}
string generarTI(inode temporal, int num)
{
    string aux;
    if (temporal.i_type=='0')
    {
        aux = "Carpeta";
    }else{
        aux = "Archivo";
    }
    string salida = "<tr><td border=\"1\">"+to_string(num)+"</td><td border=\"1\">"+aux+"</td><td border=\"1\"> "+temporal.nombre+"</td></tr>\n";
    return salida;
}
bool in(report reporte)
{
    if (obtenerDireccion(reporte.id) != "")
    {
        FILE *disco;
        string dir = obtenerDireccion(reporte.id);
        if (disco = fopen(dir.c_str(), "rb+"))
        {
            mbr master;
            fseek(disco, 0, SEEK_SET);
            fread(&master, sizeof(mbr), 1, disco);
            partition particion = obtenerParticion(master, obtenerN(reporte.id));
            superblock sb;
            fseek(disco, particion.part_start, SEEK_SET);
            fread(&sb, sizeof(superblock), 1, disco);
            char bm[sb.s_inodes_count];
            fseek(disco, sb.s_bm_inode_start, SEEK_SET);
            for (int i = 0; i < sb.s_inodes_count; i++)
            {
                fread(&bm[i], sizeof(char), 1, disco);
            }
            inode temp;
            string salida = "digraph grafo{\nrankdir=LR;\nnode[shape=plaintext];\n";
            salida += "p1[shape=record label=<<table>\n<tr><td border=\"1\">Index</td><td border=\"1\">Tipo</td><td border=\"1\">Nombre</td></tr>\n";
            for (int i = 0; i < strlen(bm); i++)
            {
                if (bm[i] == '1')
                {
                    fseek(disco, sb.s_inode_start + (int)(i * sizeof(inode)), SEEK_SET);
                    fread(&temp, sizeof(inode), 1, disco);
                    salida += generarTI(temp, i);
                }
            }
            salida += "</table>>];";
            salida += "\n}";
            string dot = split(reporte.path, ".")[0] + ".dot";
            fclose(disco);
            ofstream grafo;
            grafo.open(dot);
            grafo << "" + salida + "\n";
            grafo.close();
            string cmd = "dot -T" + lower(split(reporte.path, ".")[1]) + " \"" + dot + "\" -o \"" + reporte.path + "\"";
            system(cmd.c_str());
            cout << "Reporte creado exitosamente" << endl;
            return false;
        }
        else
        {
            cout << "No existe el disco" << endl;
        }
    }
    else
    {
        cout << "La direccion del disco no fue encontrada" << endl;
    }
    return false;
}
//Funcion de comando rep que verifica los parametros ingresados
void rep(vector<string> partes)
{
    report reporte = {"", "", "", ""};
    bool probelm = false;
    for (string parte : partes)
    {
        vector<string> componentes = split(parte, "=");
        if (lower(componentes[0]) == "rep")
        {
        }
        else if (lower(componentes[0]) == "-name")
        {
            if ((lower(componentes[1]) == "mbr") || (lower(componentes[1]) == "disk") || (lower(componentes[1]) == "inode") || (lower(componentes[1]) == "journaling") || (lower(componentes[1]) == "block") || (lower(componentes[1]) == "bm_inode") || (lower(componentes[1]) == "bm_block") || (lower(componentes[1]) == "tree") || (lower(componentes[1]) == "sb") || (lower(componentes[1]) == "file") || (lower(componentes[1]) == "ls"))
            {
                reporte.name = componentes[1];
            }
            else
            {
                cout << "Nombre del reporte no válido" << endl;
                probelm = true;
            }
        }
        else if (lower(componentes[0]) == "-path")
        {
            reporte.path = quitarComillas(componentes[1]);
        }
        else if (lower(componentes[0]) == "-id")
        {
            reporte.id = lower(componentes[1]);
        }
        else if (lower(componentes[0]) == "-ruta")
        {
            reporte.ruta = quitarComillas(componentes[1]);
        }
        else
        {
            cout << "Atributo " + componentes[0] + " no valido" << endl;
            probelm = true;
        }
    }
    if (probelm == true)
    {
    }
    else if ((reporte.name == "") || (reporte.path == "") || (reporte.id == ""))
    {
        cout << "Parametros obligatorios incompletos" << endl;
    }
    else if(((lower(reporte.name)=="file")||(lower(reporte.name)=="ls"))&&(reporte.ruta=="")){
        cout<<"Ruta del archivo o carpeta no especificada"<<endl;
    }
    else
    {
        if (lower(reporte.name) == "mbr")
        {
            reportarMBR(reporte);
        }
        else if (lower(reporte.name) == "disk")
        {
            reportarDisk(reporte);
        }
        else if (lower(reporte.name) == "block")
        {
            block(reporte);
        }
        else if (lower(reporte.name) == "inode")
        {
            in(reporte);
        }
        else if (lower(reporte.name) == "sb")
        {
            sb(reporte);
        }
        else
        {
            cout << "Tipo de reporte invalido, no existe ningun reporte con ese nombre" << endl;
        }
    }
}
/*
mount -path=/home/user/Disco1.dk -name=Particion1
rep -id=291A -Path=/home/user/reportes/reporteMBR.jpg -name=mbR
rep -id=291A -Path=/home/user/reportes/reporteDisco.jpg -name=DISK
rep -id=291A -Path=/home/user/reportes/reporteInodo.jpg -name=Inode
rep -id=291A -Path=/home/user/reportes/reporteSB.jpg -name=sb
*/