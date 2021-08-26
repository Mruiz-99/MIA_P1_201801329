void rmdisk(vector<string>partes){
    if(partes.size()!=2){
        cout<<"Error en la entrada"<<endl;
    }else{
        if(lower(split(partes[1],"=")[0])=="-path"){
            if(remove(quitarComillas(split(partes[1],"=")[1]).c_str())){
                cout<<"Error en la eliminacion"<<endl;
            }else{
                cout<<"Disco eliminado exitosamente"<<endl;
            }
        }else{
            cout<<"Atributo no valido"<<endl;
        }
    }
}