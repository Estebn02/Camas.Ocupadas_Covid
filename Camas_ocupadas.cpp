#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#define lineas 4486



using namespace std;

struct camas_ocupadas{
    int fecha;
    int codigo_hospital;
    int numero_de_camas;
    struct camas_ocupadas *siguiente;
};

typedef camas_ocupadas *lista;

void leeProcesa(string archivo_nombre, lista &p)
{
    lista x;
    string data;
    ifstream archivo;

    archivo.open(archivo_nombre.c_str(),ios::in);

    if(archivo.fail())
    {
        cout << "no se pudo abrir el archivo" << endl;
        exit(1);
    }

    else
    {
        while(!archivo.eof())
        {

            x = new(camas_ocupadas);
            getline(archivo, data, ';');
            x->fecha = atoi(data.c_str());
           // cout << "fecha: " << x->fecha << " ";

            getline(archivo, data, ';');
            x->codigo_hospital = atoi(data.c_str());
           // cout << "codigo: "<< x->codigo_hospital << " ";

            getline(archivo, data, '\n');
            x->numero_de_camas = atoi(data.c_str());
            //cout << "numerocamas: " << x->numero_de_camas << endl;

            x->siguiente = p;
            p = x;
        }
    }
    archivo.close();
}
void NuevaListaSinDuplicados(lista &p, lista &q)
{
    lista crear;
    lista leer = p;
    if(q == NULL){
        crear = new camas_ocupadas;
        crear->fecha = leer->siguiente->fecha;
        crear->codigo_hospital = leer->siguiente->codigo_hospital;
        crear->numero_de_camas = leer->siguiente->numero_de_camas;
        crear->siguiente = q;
        q = crear;
    }
    while(leer != NULL){
        lista leer_sd = q;
        if(leer->numero_de_camas == 0){
            leer = leer->siguiente;
        }
        else{
            int duplicados=0;
            while(leer_sd != NULL){
                if(leer->numero_de_camas == leer_sd->numero_de_camas && leer->fecha == leer_sd->fecha){
                    ++duplicados;
                    break;
                }
                leer_sd = leer_sd->siguiente;
            }
            if(duplicados == 0){
                crear = new camas_ocupadas;
                crear->fecha = leer->fecha;
                crear->codigo_hospital = leer->codigo_hospital;
                crear->numero_de_camas = leer->numero_de_camas;
                crear->siguiente = q;
                q = crear;
            }
            leer = leer->siguiente;
        }
    }
}
void seleccionar(lista &p, int codigo, lista &q)
{
    lista temp=p;
    while (temp!=NULL)
    {
        if (temp->codigo_hospital==codigo)
        {
            lista temporal=new(camas_ocupadas);
            temporal->codigo_hospital=temp->codigo_hospital;
            temporal->fecha=temp->fecha;
            temporal->numero_de_camas=temp->numero_de_camas;
            temporal->siguiente=q;
            q=temporal;
        }
    temp=temp->siguiente;
   }
}
void estadistica(lista &q)
{
    lista temporal = q;
for(int i=10;i<=20;i++)
    {
        temporal=q;
        int n=0;
        while(temporal!=NULL)
        {
            if(temporal->codigo_hospital==i)
            {
                n++;
            }
            temporal=temporal->siguiente;
        }
        cout<<"El hospital "<<i<<" tiene "<<n<<" camas ocupadas"<<endl;
    }
}

int contar(lista q,int anho,int mes,int dia)
{
    lista p;
    p=q;
    int fechaconmes,fechaconmesydia,contador=0;
    fechaconmes=(anho*100)+mes;
    fechaconmesydia=(fechaconmes*100)+dia;
    while(p!=NULL)
    {
        if(p->fecha==fechaconmesydia)
        {
            contador++;
        }
        p=p->siguiente;
    }
    return contador;
}


void eliminarHospital (lista &p, int identificador){
if (p==NULL) {
   return;
} else {
    if(p->codigo_hospital == identificador) {
      lista nodoEliminar= p;
      p=p->siguiente;
      delete(nodoEliminar);
    }else{
      lista actual = p;
      lista siguiente =p->siguiente;
   while(siguiente!=NULL){
      if(siguiente->codigo_hospital==identificador){

         lista nodoELiminar = siguiente;
         actual->siguiente = siguiente-> siguiente;
         delete (nodoELiminar);
     }else{
         actual=actual->siguiente;
        }
         siguiente=actual->siguiente;
          }
         }
       }

  }

void imprimir(lista &l){
    lista x;
    x=l;
    while(x!=NULL){
        cout<<x->fecha<<"/"<<x->codigo_hospital<<"/"<<x->numero_de_camas<<endl;
        x=x->siguiente;
    }
}



int main()
{
    setlocale(LC_CTYPE, "Spanish");
    string nombre_archivo = "camas_ocupadas.txt";
    lista p = NULL;
    lista q = NULL;
    lista x = NULL;


cout<<"\n\n Ingrese su opcion:\n\n 1)Crear lista desde el archivo\n\n 2)Crear lista sin duplicados\n\n 3)Crear y mostrar una lista con un codigo de hospital seleccionado(10-20) \n\n 4)Mostrar estadisticas de camas ocupadas por cada hospital\n\n 5)Cantidad de camas por fecha escogida \n\n 6)Eliminar camas de un hospital especifico \n\n 7)Salir del programa  ";

    while(true)
    {


      int op=0;
      cout<<"\n\nIngrese su opción: "<<endl;
      cin>>op;

      if(op==1)
      {
        cout<<"\ncrear lista desde archivo"<<endl;
        leeProcesa(nombre_archivo, p);
        cout<<"se creo la lista con exito"<<endl;
      }
      else if(op==2)
      {
        cout<<"\nCrear Lista sin duplicados"<<endl;
        NuevaListaSinDuplicados(p,q);
        cout<<"\nse creo la lista con exito"<<endl;
      }
      else if(op==3)
      {
        cout<<"\nCrear Lista de un Hospita"<<endl;
        int codigo=0;
        cout<<"Código: "<<endl;
        cin>>codigo;
        seleccionar(q, codigo, x);
        imprimir(x);
      }
      else if(op==4)
      {
        cout<<"\nMostrar estadísticas de número de camas por Hospital"<<endl;
        estadistica(q);
        //imprimir(q);
      }
      else if(op==5) 
      {
        {
         int dia = 0;
         int mes = 0;
         int anho = 0;

         cout<<endl;
          cout<<"Ingrese el anho que desea evaluar: ";
           cin>>anho;
          cout<<endl;
           cout<<"Ingrese el mes que desa evaluar: ";
          cin>>mes;
          cout<<endl;
          cout<<"Ingrese el dia que desea evaluar: ";
          cin>>dia;
          cout<<endl;
           cout<<"Las cantidad de camas ocupadas que hubo en la fecha escogida("<<anho<<"/"<<mes<<"/"<<dia<<") es la siguientes: "<<contar(q,anho,mes,dia);
          
        }
      }
      else if(op==6)
      {

        int identificador=0;
        cout<<" Eliminar registros de camas de un hospita"<<endl;
        cout<<"identificador: "<<endl;
        cin>>identificador;
        eliminarHospital(q,identificador);
        imprimir(q);
      }
      else if(op==7)
      {
        cout<<"Ejecución terminada"<<endl;
        break;
      }









    }



 return 0;
}
