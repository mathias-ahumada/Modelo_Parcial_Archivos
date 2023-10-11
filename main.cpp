#include<iostream>
#include<cstring>

using namespace std;
#include "parcial.h"



bool sobreEscribirRegistro(Compra reg, int pos){
    FILE *p;
    p=fopen("compras.dat", "rb+");///+ agrega al modo lo que le falta
    if(p==NULL){
        return false;
    }
    fseek(p,sizeof (reg)*pos,0);
    bool escribio=fwrite(&reg,sizeof reg,1,p);
    fclose(p);
    return escribio;
}


bool sobreEscribir(Material reg, int pos){
    FILE *p;
    p=fopen("materiales.dat", "rb+");///+ agrega al modo lo que le falta
    if(p==NULL){
        return false;
    }
    fseek(p,sizeof (reg)*pos,0);
    bool escribio=fwrite(&reg,sizeof reg,1,p);
    fclose(p);
    return escribio;
}


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




        for(int i=0;i<CantMateriales;i++){

                objMaterial=archMaterial.leerRegistro(i);

                if(objMaterial.getCodigoMaterial()==objCompra.getCodigoMaterial()){

                    if(objMaterial.getTipo()==1){
                acu+=objMaterial.getPU();
                    }
                }

        }


    }
    cout<<"La obra: "<<objObra.getCodigoObra()<<" gasto: "<<acu<<"  en obra gruesa"<<endl;
}





}

void puntoE(){
//a5) La/s provincia/s con más de 22 proveedores

ArchivoProveedor  archProv("proveedores.dat");
Proveedor objProv;
int contarProv=archProv.contarRegistros();
int provincias[24]={};

for(int y=0;y<24;y++){


for(int x=0;x<contarProv;x++){


    objProv=archProv.leerRegistro(x);
    if(y+1==objProv.getProvincia()){

        provincias[y]++;

    }

}


}

for(int i=0;i<24;i++){

   if(provincias[i]>22){
    cout<<"la provincia: "<<i+1<<"tiene mas de 22 proveedores "<<endl;
   }

}
}

void PuntoF(){

    //a6) Dar de baja lógica a todas las compras del año 2020.

ArchivoCompra archCompra("compras.dat");
Compra objCompra;

int contarCompras=archCompra.contarRegistros();

for(int x=0;x<contarCompras;x++){

    objCompra=archCompra.leerRegistro(x);
    if(objCompra.getFechaCompra().getAnio()==2020){

        objCompra.setActivo(false);

        sobreEscribirRegistro(objCompra,x);
    }
}




}

void puntoG(){
//a7) Modificar el precio de las aberturas en el archivo de materiales. Incrementar un 10% todos los materiales de ese tipo.
ArchivoMaterial archMaterial("materiales.dat");
Material objMaterial;
int contarMaterial=archMaterial.contarRegistros();

for(int x=0;x<contarMaterial;x++){

    objMaterial= archMaterial.leerRegistro(x);

    if(objMaterial.getTipo()==3){
       float nuevoPrecio=objMaterial.getPU()*1.10;
       objMaterial.setPU(nuevoPrecio);

    sobreEscribir(objMaterial,x);
    }
}


}




int main (){

PuntoA();
puntoB();
puntoC();
puntoD();
puntoE();
PuntoF();
puntoG();


//a7) Modificar el precio de las aberturas en el archivo de materiales. Incrementar un 10% todos los materiales de ese tipo.


return 0;}
