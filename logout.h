#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

//Funcion que monta una particion a memoria
bool cerrarSesion()
{
    if ((usuario != "") && (id!=""))
    {
        usuario = "";
        id="";
        cout << "Sesion Cerrada..." << endl;
        cout << "Hasta pronto..." << endl;
    }
    else
    {
        cout << "Error, NO hay una cuenta de usuario activa, NO se puede cerrar sesion" << endl;
    }
}

void logout(vector<string> partes)
{
    for (int i = 0; i < partes.size(); i++)
    {
        vector<string> componenetes = split(partes[i], "=");
        if (lower(componenetes[0]) == "logout")
        {
            cerrarSesion();
        }
    }
}