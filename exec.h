
#include <iostream>
using namespace std;

string automata(string comando){
    int state = 0;
    string salida = "";
    for(int i =0; i < comando.size(); i++){
        if(state==0){
            if(comando[i]=='#'){
                state=1;
            }else{
                salida += comando[i];
            }
        }
    } 
    return salida;
}