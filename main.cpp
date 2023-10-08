#include<iostream>
#include<cstring>

using namespace std;
#include "parcial.h"


///a1) Para cada material la cantidad de compras que se hayan realizado entre todas las compras.

void PuntoA(){

ArchivoMaterial archMa("materiales.dat");
int contarMaterial= archMa.contarRegistros();
Material objMate;

ArchivoCompra archCompra("compras.dat");
int contarCompras=archCompra.contarRegistros();
Compra objCompra;

int contador=0;

for (int x=0;x<contarMaterial;x++){

        objMate=archMa.leerRegistro(x);
        contador=0;
    for(int y=0;y<contarCompras;y++){

        objCompra=archCompra.leerRegistro(y);

        if(objMate.getCodigoMaterial()==objCompra.getCodigoMaterial()){

            contador++;


        }

    }

    cout<<"El codigo de material: "<<x+1<<" Tuvo "<<contador<<" compras"<<endl;
}

}


void puntoB(){
///a2) El nombre del proveedor que mayor importe haya obtenido entre todas las compras que se le realizaron.

ArchivoCompra archCompra("compras.dat");
Compra objCompra;
int contarCompras=archCompra.contarRegistros();

ArchivoProveedor archProv("proveedores.dat");
Proveedor objProv;
int contarProv=archProv.contarRegistros();

float Maximo=0;
 char nombreMaximo[30];
float acupro=0;
 for(int y=0;y<contarProv;y++){

    objProv=archProv.leerRegistro(y);
acupro=0;

for(int x=0;x<contarCompras;x++){

    objCompra=archCompra.leerRegistro(x);

    if(objCompra.getNumeroproveedor()==objProv.getNumeroProveedor()){

        acupro+=objCompra.getImporte();
    }

}

if(acupro>Maximo){

    Maximo=acupro;
    strcpy(nombreMaximo, objProv.getNombre());
}
 }

cout<<"El nombre del proveedor que mayor importe gasto fue: "<<nombreMaximo<<" El importe que gasto fue: "<<Maximo<<endl;


}
void puntoC(){

///a3) Los número de los proveedores a los que no se les compró nada el año pasado.

ArchivoCompra archCompra("compras.dat");
Compra objCompra;
int contarCompras=archCompra.contarRegistros();

ArchivoProveedor archProveedor("proveedores.dat");
int contarProv=archProveedor.contarRegistros();
Proveedor objProv;

bool flag=false;
for (int x=0;x<contarProv;x++){
objProv=archProveedor.leerRegistro(x);

flag=false;

for(int y=0;y<contarCompras;y++){

    objCompra=archCompra.leerRegistro(y);

    if(objCompra.getImporte()>1&&objCompra.getNumeroproveedor()==objProv.getNumeroProveedor()){

        flag=true;

    }

}

cout<<endl;
if(flag==false){
        cout<<"El siguiente numero de proveedor no compro nada: "<<objProv.getNombre()<<endl;

}

}

}










void puntoD(){

///a4) El gasto en obra gruesa para cada uno de las obras. (analizar bien.
///Es el punto más complejo porque requiere del uso de 3 archivos)
ArchivoObras ArchivoObras("obras.dat");
Obra objObra;
int cantidadObras= ArchivoObras.contarRegistros();

ArchivoCompra archCompra("compras.dat");
Compra objCompra;
int cantidadCompras=archCompra.contarRegistros();

ArchivoMaterial archMaterial("materiales.dat");
Material objMaterial;
int CantMateriales=archMaterial.contarRegistros();


for(int x=0;x<cantidadObras;x++){

    objObra=ArchivoObras.leerRegistro(x);


    float acu=0;
    for(int y=0;y<cantidadCompras;y++){

        objCompra=archCompra.leerRegistro(y);

         if(objObra.getCodigoObra()==objCompra.getCodigoObra()){

        for(int i=0;i<CantMateriales;i++){

                objMaterial=archMaterial.leerRegistro(i);

                if(objMaterial.getCodigoMaterial()==objCompra.getCodigoMaterial()){

                    if(objMaterial.getTipo()==1){
                acu+=objMaterial.getPU();
                    }
                }

        }
    }

    }
    cout<<"La obra: "<<objObra.getCodigoObra()<<" gasto: "<<acu<<"  en obra gruesa"<<endl;
}





}

void puntoE(){
///a5) La/s provincia/s con más de 22 proveedores

}

int main (){

PuntoA();
puntoB();
puntoC();
puntoD();
puntoE();


return 0;}
