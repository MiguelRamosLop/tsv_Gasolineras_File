#include <iostream>
#include <fstream>
using namespace std;

struct gasolinera {
    string provincia;
    string municipio;
    string localidad;
    int codigoPostal;
    string direccion;
    string margen;
    float longitud;
    float latitud;
    float precio95E5;
    float precio95E10;
    float precio95E5Premium;
    float precio98E5;
    float precio98E10;
    float precioGasoleoA;
    float precioGasoleoPremium;
    float precioGasoleoB;
    float precioGasoleoC;
    float precioBioetanol;
    float bioalcohol;
    float precioBiodiesel;
    float estermetilico;
    float precioGasesLicuados;
    float precioGasNaturalComprimido;
    float precioGasNaturalLicuado;
    float precioHidrogeno;
    string rotulo;
    string tipoVenta;
    string rem;
    string horario;
    string tipoServicio;

    gasolinera *next;
};

//Declaramos file como variable de salida y localizamos la ruta del archivo
ofstream salida ("../gasolineras_data.txt");

//Función para crear la lista con los datos del archivo
void readFileDesdeInicio(gasolinera *&lista, gasolinera *&final); //LL
void readFileDesdeFinal(gasolinera *&pila); //pila
void searchMunicipiosProv(gasolinera *lista, string provincia);
void printMunicipiosProv(gasolinera *lista, string provincia);
void EGasofaProv(gasolinera *lista, string provincia, string municipio, string localidad);
void gasolinaMasCara(gasolinera *lista, string provincia, string municipio, string localidad);
void gasolinaMasCheap(gasolinera *lista, string provincia, string municipio, string localidad);
void gasolinaCPMenor(gasolinera *lista, string provincia, string municipio, string localidad);
void gasolinaCPMayor(gasolinera *lista, string provincia, string municipio, string localidad);
void gasolinaPlace(gasolinera *lista, string provincia, string municipio, string localidad);
void gasolinaRepsol(gasolinera *lista, string provincia, string municipio, string localidad);
void direccionDosPrimeras (gasolinera *lista, string localidad);
void gasolinasProxCalleToledo (gasolinera *lista);
void triangularGasolinerasCodigoPostal(gasolinera *lista, int codigopostal);
void leer5primeras (gasolinera *lista);
void leer5ultimas (gasolinera *lista);


void readFileDesdeInicio(gasolinera *&lista, gasolinera *&final){
    //Indicamos al programa la dirección del archivo que tiene que leer
    ifstream read("../hoja_modificada_UK.tsv");
    try{
        //Mientras el archivo no esté vacío
        while(!read.eof()){
            gasolinera *actual= new gasolinera();
            //Creamos un nodo para indicar al programa los datos que se van a encontrar en el archivo y su orden respectivo
            read >>actual->provincia>>actual->municipio>> actual->localidad>> actual->codigoPostal>> actual->direccion>> actual->margen>> actual->longitud>> actual->latitud>> actual->precio95E5>>
                 actual->precio95E10>> actual->precio95E5Premium>> actual->precio98E5>> actual->precio98E10>> actual->precioGasoleoA>> actual->precioGasoleoPremium>>
                 actual->precioGasoleoB>> actual->precioGasoleoC>> actual->precioBioetanol>> actual->bioalcohol>> actual->precioBiodiesel>> actual->estermetilico>>
                 actual->precioGasesLicuados>> actual->precioGasNaturalComprimido>> actual->precioGasNaturalLicuado>> actual->precioHidrogeno>> actual->rotulo>>
                 actual->tipoVenta>> actual->rem>> actual->horario>> actual->tipoServicio;
            //Una vez leído el fichero añadimos el nodo a la lista
            if (lista==NULL){  //  LISTA-ACTUAL-FINAL -> NULL
                actual->next = NULL;
                lista = actual;
                final = actual;
            }else{ // lista -> nodo -> final -> NULL
                //lista->next=actual;
                //actual = lista;
                final -> next = actual;
                final = actual;
                //actual->next = lista;
                //lista = actual;
            }

        }
        int opt;
        cout << "Mostrar por consola (1/) Mostrar en file (2/)";
        cin >> opt;
        if (opt == 1) {
            cout << "El archivo se leyo con exito";
        } if (opt == 2) {
            salida << "El archivo se leyo con exito";
        }
        //Si el archivo no se puede leer, salta la excepción
    }catch(...){
        read.close();
        cout<<"El archivo no se ha podido leer."<<endl;
    }
}

void readFileDesdeFinal(gasolinera *&pila) {
    //Indicamos al programa la dirección del archivo que tiene que leer
    ifstream read("../hoja_modificada_UK.tsv");
    try{
        //Mientras el archivo no esté vacío
        while(!read.eof()){
            gasolinera *actual= new gasolinera();
            //Creamos un nodo para indicar al programa los datos que se van a encontrar en el archivo y su orden respectivo
            read >>actual->provincia>>actual->municipio>> actual->localidad>> actual->codigoPostal>> actual->direccion>> actual->margen>> actual->longitud>> actual->latitud>> actual->precio95E5>>
                 actual->precio95E10>> actual->precio95E5Premium>> actual->precio98E5>> actual->precio98E10>> actual->precioGasoleoA>> actual->precioGasoleoPremium>>
                 actual->precioGasoleoB>> actual->precioGasoleoC>> actual->precioBioetanol>> actual->bioalcohol>> actual->precioBiodiesel>> actual->estermetilico>>
                 actual->precioGasesLicuados>> actual->precioGasNaturalComprimido>> actual->precioGasNaturalLicuado>> actual->precioHidrogeno>> actual->rotulo>>
                 actual->tipoVenta>> actual->rem>> actual->horario>> actual->tipoServicio;
            //Una vez leído el fichero añadimos el nodo a la lista
            if (pila==NULL){
                actual->next = NULL;
                pila = actual;
            }else{
                //lista->next=actual;
                //actual = lista;
                actual->next = pila;
                pila = actual;
            }
        }
        int opt;
        cout << "Mostrar por consola (1/) Mostrar en file (2/)";
        cin >> opt;
        if (opt == 1) {
            cout << "El archivo se leyo con exito";
        } if (opt == 2) {
            salida << "El archivo se leyo con exito";
        }
        //Si el archivo no se puede leer, salta la excepción
    }catch(...){
        read.close();
        cout<<"El archivo no se ha podido leer."<<endl;
    }
}

void searchMunicipiosProv(gasolinera *lista, string provincia) {
    int contadorMunicipiosProv = 0;
    gasolinera *guia = lista;
    do {
        if (guia->provincia == provincia) {
            contadorMunicipiosProv++;
        }
        guia = guia -> next;
    } while (guia != NULL);
    int opt;
    cout << "Mostrar por consola (1/) Mostrar en file (2/)";
    cin >> opt;
    if (opt == 1) {
        cout << "La provincia de " << provincia << " tiene " << contadorMunicipiosProv << " municipios.";
    } if (opt == 2) {
        salida << "La provincia de " << provincia << " tiene " << contadorMunicipiosProv << " municipios.";
    }

}

void printMunicipiosProv(gasolinera *lista, string provincia) {
    gasolinera *guia = lista;
    int opt;
    cout << "Mostrar por consola (1/) Mostrar en file (2/)";
    cin >> opt;
    if (opt == 1) {
        cout << "Para la provincia " << provincia << " son:" << endl;
        do {
            if (guia->provincia == provincia) {
                cout<<guia->municipio<<endl;
            }
            guia = guia->next;
        } while (guia != NULL);
    } if (opt == 2) {
        salida << "Para la provincia " << provincia << " son:" << endl;
        do {
            if (guia->provincia == provincia) {
                salida<<guia->municipio<<endl;
            }
            guia = guia->next;
        } while (guia != NULL);
    }
}

void EGasofaProv(gasolinera *lista, string provincia, string municipio, string localidad) {
    gasolinera *guia = lista;
    int contadorGasofasProv = 0;
    float e = 0;
    do {
        if (guia->provincia == provincia && guia->municipio==municipio && guia->localidad==localidad) {
            contadorGasofasProv++;
            e=e+guia->precio95E5;
        }
        guia = guia->next;
    } while (guia != NULL);
    int opt;
    cout << "Mostrar por consola (1/) Mostrar en file (2/)";
    cin >> opt;
    if (opt == 1) {
        cout << "En " << localidad << " ," << municipio << " ," << provincia << " existen " << contadorGasofasProv << " gasolineras disponibles." << endl;
        cout << "La media de precios de gasolina95E5 es de: " << e/contadorGasofasProv;
    } if (opt == 2) {
        salida << "En " << localidad << " ," << municipio << " ," << provincia << " existen " << contadorGasofasProv << " gasolineras disponibles." << endl;
        salida << "La media de precios de gasolina95E5 es de: " << e/contadorGasofasProv;
    }

}

void gasolinaMasCara(gasolinera *lista, string provincia, string municipio, string localidad) {
    gasolinera *guia = lista;
    float precio = 0;
    do {
        if (guia->provincia == provincia && guia->municipio==municipio && guia->localidad==localidad) {
            if ( guia -> precio95E5 >= precio) {
                precio = guia -> precio95E5;
            }
        }
        guia = guia -> next;
    } while (guia != NULL);
    int opt;
    cout << "Mostrar por consola (1/) Mostrar en file (2/)";
    cin >> opt;
    if (opt == 1) {
        cout << "En " << localidad << " ," << municipio << " ," << provincia << " la gasolina95E5 mas cara esta a " << precio << endl;
    } if (opt == 2) {
        salida << "En " << localidad << " ," << municipio << " ," << provincia << " la gasolina95E5 mas cara esta a " << precio << endl;
    }
}

void gasolinaMasCheap(gasolinera *lista, string provincia, string municipio, string localidad) {
    gasolinera *guia = lista;
    float precio = 100;
    do {
        if (guia->provincia == provincia && guia->municipio==municipio && guia->localidad==localidad) {
            if ( guia -> precio95E5 < precio && guia->precio95E5 != 0) {
                precio = guia -> precio95E5;
            }
        }
        guia = guia -> next;
    } while (guia != NULL);
    int opt;
    cout << "Mostrar por consola (1/) Mostrar en file (2/)";
    cin >> opt;
    if (opt == 1) {
        cout << "En " << localidad << " ," << municipio << " ," << provincia << " la gasolina95E5 mas barata esta a " << precio << endl;
    } if (opt == 2) {
        salida << "En " << localidad << " ," << municipio << " ," << provincia << " la gasolina95E5 mas barata esta a " << precio << endl;
    }

}

void gasolinaCPMenor(gasolinera *lista, string provincia, string municipio, string localidad) {
    gasolinera *guia = lista;
    int codigoPostalMenor = 1000;
    do {
        if (guia->provincia == provincia && guia->municipio==municipio && guia->localidad==localidad) {
            if (codigoPostalMenor < guia->codigoPostal ) {
                codigoPostalMenor = guia->codigoPostal;
            }
        }
        guia = guia -> next;
    } while (guia != NULL);
    int opt;
    cout << "Mostrar por consola (1/) Mostrar en file (2/)";
    cin >> opt;
    if (opt == 1) {
        cout << "En " << localidad << " ," << municipio << " ," << provincia << " la gasolinera con codPostal mas barato es el " << codigoPostalMenor << endl;
    } if (opt == 2) {
        salida << "En " << localidad << " ," << municipio << " ," << provincia << " la gasolinera con codPostal mas barato es el " << codigoPostalMenor << endl;
    }
}

void gasolinaCPMayor(gasolinera *lista, string provincia, string municipio, string localidad) {
    gasolinera *guia = lista;
    int codigoPostalMayor = 0;
    do {
        if (guia->provincia == provincia && guia->municipio==municipio && guia->localidad==localidad) {
            if (guia->codigoPostal > codigoPostalMayor) {
                codigoPostalMayor = guia->codigoPostal;
            }
        }
        guia = guia -> next;
    } while (guia != NULL);
    int opt;
    cout << "Mostrar por consola (1/) Mostrar en file (2/)";
    cin >> opt;
    if (opt == 1) {
        cout << "En " << localidad << " ," << municipio << " ," << provincia << " la gasolinera con codPostal mas barato es el " << codigoPostalMayor << endl;
    } if (opt == 2) {
        salida << "En " << localidad << " ," << municipio << " ," << provincia << " la gasolinera con codPostal mas barato es el " << codigoPostalMayor << endl;
    }
}

void gasolinaPlace(gasolinera *lista, string provincia, string municipio, string localidad) {
    gasolinera *guia = lista;
    int opt;
    cout << "Mostrar por consola (1/) Mostrar en file (2/)";
    cin >> opt;
    if (opt == 1) {
        cout << "los precios de las gasolineras de lo ingresado son: " << endl;
        do {
            if (guia->provincia == provincia && guia->municipio==municipio && guia->localidad==localidad) {
                cout << guia->precio95E5 << endl;
            }
            guia = guia -> next;
        } while (guia != NULL);
    } if (opt == 2) {
        salida << "los precios de las gasolineras de lo ingresado son: " << endl;
        do {
            if (guia->provincia == provincia && guia->municipio==municipio && guia->localidad==localidad) {
                salida << guia->precio95E5 << endl ;
            }
            guia = guia -> next;
        } while (guia != NULL);
    }
}

void gasolinaRepsol(gasolinera *lista, string provincia, string municipio, string localidad) {
    gasolinera *guia = lista;
    int contadorRepsoles=0;
    do {
        if (guia->provincia == provincia && guia->municipio==municipio && guia->localidad==localidad) {
            if (guia ->rotulo == "REPSOL") {
                contadorRepsoles++;
            }
        }
        guia = guia -> next;
    } while (guia != NULL);
    int opt;
    cout << "Mostrar por consola (1/) Mostrar en file (2/)";
    cin >> opt;
    if (opt == 1) {
        cout << "Existen " << contadorRepsoles  << " en: " << localidad << " ," << municipio << " ," << provincia;
    } if (opt == 2) {
        salida << "Existen " << contadorRepsoles  << " en: " << localidad << " ," << municipio << " ," << provincia;
    }
}

void direccionDosPrimeras (gasolinera *lista, string localidad) {
    int contador = 0;

    do {
        if (lista -> localidad == localidad) {
            contador++;
            cout << lista -> direccion;
        }
        if (contador == 2) {
            return;
        }
        lista = lista -> next;
    } while(lista != NULL);
}

void gasolinasProxCalleToledo (gasolinera *lista) {
    gasolinera *guide = new gasolinera();
    guide = lista;
    int contador = 0;
    float lat = 40.40831082064327 + 0.000001;
    float lat2 = 40.40831082064327 - 0.000001;
    float lon = -3.7110372156691955 - 0.000001;
    float lon2 = -3.7110372156691955 + 0.000001;

    do {
        if (lat2 <= guide -> latitud  && guide -> latitud >= lat ) {
            if (lon2 <= guide -> longitud  && guide -> longitud >= lon ) {
                cout << guide -> direccion << endl;
                contador++;
            }
        }
        if (contador == 5) {
            return;
        }
        guide = guide -> next;
    } while (guide != NULL);
}

void triangularGasolinerasCodigoPostal(gasolinera *lista, int codigopostal) {
    gasolinera *guide = new gasolinera();
    guide = lista;
    cout << "las gasolineras que se encuentran dentro del codigo postal " <<codigopostal<< " son: " << endl;
    do {
        if (guide -> codigoPostal == codigopostal) {
            cout << guide -> direccion << endl;
        }
        guide = guide -> next;
    } while (guide != NULL);
}

void leer5primeras (gasolinera *lista) {
    int contadorPrim = 0;
    gasolinera *guia = lista;
    do {
        cout << "Direccion :" << guia -> direccion << endl;
        contadorPrim++;
        guia = guia -> next;
    } while (contadorPrim <= 5);
}

void leer5ultimas (gasolinera *pila) {
    int contadorUlt = 0;
    gasolinera *guia = pila;
    do {
        cout << "Direccion :" << guia -> direccion << endl;
        contadorUlt++;
        guia = guia -> next;
    } while (contadorUlt < 5);
}

int main() {
    gasolinera *iList = NULL;
    gasolinera *iFinal = NULL;
    gasolinera *iPila = NULL;
    string prov, mun, loc, gas;
    int input, inputS, codPos;
    do {
        cout << endl;
        cout << "\n|-------------------------------------|";
        cout << "\n|           - GASOLINERAS -           |";
        cout << "\n|------------------|------------------|";
        cout << "\n| 1. Crear lista enlazada (L->F)      |";
        cout << "\n| 2. Crear pila (F->L)                |";
        cout << "\n| 3. Num municipios en una provincia  |";
        cout << "\n| 4. Municipios de una provincia      |";
        cout << "\n| 5. Media gasolina en provincia      |";
        cout << "\n| 6. Gasolina mas cara                |";
        cout << "\n| 7. Gasolina mas barata              |";
        cout << "\n| 8. Codigo postal menor              |";
        cout << "\n| 9. Codigo postal mayor              |";
        cout << "\n| 10. Gasolinas de un sitio           |";
        cout << "\n| 11. Gasolineras repsol              |";
        cout << "\n| 12. Direccion dos primeras          |";
        cout << "\n| 13. Gasolinas prox calle Toledo 98  |";
        cout << "\n| 14. Triangular gasolineras cerca cp |";
        cout << "\n| 15. Leer las 5 primeras             |";
        cout << "\n| 16. Leer las 5 ultimas              |";
        cout << "\n| 17. Salir                           |";
        cout << "\n|------------------|------------------|";
        cout << "\n\n Escoja una Opcion: ";
        cin >> input;
        switch (input) {
            case 1:
                cout << "Leyendo archivo...\n";
                salida << "Leyendo archivo...\n";
                readFileDesdeInicio(iList, iFinal);
                cout << iList -> municipio;
                break;
            case 2:
                cout << "Leyendo archivo...\n";
                salida << "Leyendo archivo...\n";
                readFileDesdeFinal(iPila);
                cout << iPila -> municipio;
                break;
            case 3:
                cout << "Ingrese provincia: " ;
                cin >> prov;
                searchMunicipiosProv(iList, prov);
                break;
            case 4:
                cout << "Ingrese provincia: ";
                cin >> prov;
                printMunicipiosProv(iList, prov);
                break;
            case 5:
                cout << "Ingrese provincia: ";
                cin >> prov;
                cout << "Ingrese municipio: ";
                cin >> mun;
                cout << "Ingrese localidad: ";
                cin >> loc;
                EGasofaProv(iList,prov,mun,loc);
                break;
            case 6:
                cout << "Ingrese provincia: ";
                cin >> prov;
                cout << "Ingrese municipio: ";
                cin >> mun;
                cout << "Ingrese localidad: ";
                cin >> loc;
                gasolinaMasCara(iList,prov,mun,loc);
                break;
            case 7:
                cout << "Ingrese provincia: ";
                cin >> prov;
                cout << "Ingrese municipio: ";
                cin >> mun;
                cout << "Ingrese localidad: ";
                cin >> loc;
                gasolinaMasCheap(iList,prov,mun,loc);
                break;
            case 8:
                cout << "Ingrese provincia: ";
                cin >> prov;
                cout << "Ingrese municipio: ";
                cin >> mun;
                cout << "Ingrese localidad: ";
                cin >> loc;
                gasolinaCPMenor(iList,prov,mun,loc);
                break;
            case 9:
                cout << "Ingrese provincia: ";
                cin >> prov;
                cout << "Ingrese municipio: ";
                cin >> mun;
                cout << "Ingrese localidad: ";
                cin >> loc;
                gasolinaCPMayor(iList,prov,mun,loc);
                break;
            case 10:
                cout << "Ingrese provincia: ";
                cin >> prov;
                cout << "Ingrese municipio: ";
                cin >> mun;
                cout << "Ingrese localidad: ";
                cin >> loc;
                gasolinaPlace(iList,prov,mun,loc);
                break;
            case 11:
                cout << "Ingrese provincia: ";
                cin >> prov;
                cout << "Ingrese municipio: ";
                cin >> mun;
                cout << "Ingrese localidad: ";
                cin >> loc;
                gasolinaRepsol(iList,prov,mun,loc);
                break;
            case 12:
                cout << "Ingrese localidad: ";
                cin >> loc;
                direccionDosPrimeras(iList,loc);
                break;
            case 13:
                //40.40831082064327, -3.7110372156691955
                gasolinasProxCalleToledo (iList);
                break;
            case 14:
                cout << "Ingrese codigo postal: ";
                cin >> codPos;
                triangularGasolinerasCodigoPostal(iList, codPos);
                break;
            case 15:
                cout << "Imprimiendo las 5 primeras:" << endl;
                leer5primeras(iList);
                break;
            case 16:
                readFileDesdeFinal(iPila);
                cout << "Imprimiendo las 5 ultimas:" << endl;
                leer5ultimas(iPila);
                break;
            case 17:
                cout << "Programa finalizado.";
                break;
            default:
                cout << "A problem ocurred";
                break;
        }
    } while (input != 13);
}