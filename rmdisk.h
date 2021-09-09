void rmdisk(vector<string> partes)
{
    if (partes.size() != 2)
    {
        cout << "Error en la entrada" << endl;
    }
    else
    {
        if (lower(split(partes[1], "=")[0]) == "-path")
        {
            string res;
            cout << "Esta seguro que desea eliminar el disco (S/N)" << endl;
            cin >> res;
            if (lower(res) == "s")
            {
                if (remove(quitarComillas(split(partes[1], "=")[1]).c_str()))
                {
                    cout << "Error en la eliminacion" << endl;
                }
                else
                {
                    cout << "Disco eliminado exitosamente" << endl;
                }
            }
            else
            {
                cout << "Operacion cancelada" << endl;
            }
        }
        else
        {
            cout << "Atributo no valido" << endl;
        }
    }
}