#include "interfaz.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;


void Ventana::LlenarMatriz(){
    this->M;
    string linea;
    int i=0;
    ifstream archivo("Laberinto 14x20.txt");//, ios::in);
    while (getline(archivo,linea)){
        for (int j=0;j<linea.length();j++){
            M[i][j]= linea.at(j);
            }
            i++;
        }
    archivo.close();
    
}
void Ventana::LlenarMatriz2(int laberinto){
    this->M;
    string linea;
    int i=0;
    if(laberinto==1){
        ifstream archivo("Laberinto 10x10.txt");//, ios::in);
        while (getline(archivo,linea)){
            for (int j=0;j<linea.length();j++){
                M[i][j]= linea.at(j);
                }
                i++;
            }
        archivo.close();
        this->largo=500;
        this->ancho=500;
    }
    else if(laberinto==2){
        ifstream archivo("Laberinto 12x15.txt");//, ios::in);
        while (getline(archivo,linea)){
            for (int j=0;j<linea.length();j++){
                M[i][j]= linea.at(j);
                }
                i++;
            }
        archivo.close();
        this->largo=750;
        this->ancho=600;
        
    }
    else{
        ifstream archivo("Laberinto 14x20.txt");//, ios::in);
        while (getline(archivo,linea)){
            for (int j=0;j<linea.length();j++){
                M[i][j]= linea.at(j);
                }
                i++;
            }
        archivo.close();
        this->largo=1000;
        this->ancho=700;
    }
    
    
    
}

  
 

Ventana::Ventana()
{
    this->window=nullptr; // colocamos nuestro puneteros a null;
    this->windowSurface=nullptr; // colocamos // nuestro canas a null
    
    SDL_Init(SDL_INIT_VIDEO); // inciamos la interfaz grafica
    
}


void Ventana::IniciarVentana()
{
    this->largo;
    this->ancho;
    int antx=0, anty=0,f=1; 
    SDL_Surface *image1=nullptr, *image2=nullptr , *image3=nullptr, *image4=nullptr;
   
    
    bool isRunning =true; // con esta bandera indicaremos que el programa esta correindo
    SDL_Event ev; //variable que tendra los eventos
    /*Creando la ventana*/
    this->window=SDL_CreateWindow("Garden Of Avalon",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,largo,ancho,SDL_WINDOW_SHOWN);
    this->windowSurface = SDL_GetWindowSurface(this->window);
    /*Cragando las imagenes*/
    
    image1=SDL_LoadBMP("pared.bmp");
    image2=SDL_LoadBMP("pasillo.bmp");
    image3=SDL_LoadBMP("salida.bmp");
    image4=SDL_LoadBMP("raton.bmp");

   
    while(isRunning) // si esta en true continuara el juego
    {
      
        while(SDL_PollEvent(&ev) != 0) //escuchamos los diferentes eventos que se producen
        {
            if(ev.type == SDL_QUIT) // si el usuario da clic en boton salir de la venana
            {
                isRunning=false; // colocamos false para salir del while y terminar el juego
            }
            
            else if(ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if(ev.button.button == SDL_BUTTON_LEFT)
                {
                 //posicionar el raton
                    //cout << "x: " << ev.button.x << endl;
                    //cout << "y: " << ev.button.y << endl;
                   
                    if( (ev.button.x >= 0 && ev.button.x <= largo) && (ev.button.y >= 0 && ev.button.y <= ancho))
                    {
                        if(M[ev.button.y/50][ev.button.x/50] == '0')
                        {
                            //cout << "Pasillo " <<M[ev.button.y/50][ev.button.x/50]<< endl;
                            Ventana::ColocarImagen((ev.button.y/50)*50,(ev.button.x/50)*50,image4);
                            const clock_t begin_time=clock();
                            double ini;
                            double fin;
                            ini=float(clock()-begin_time)/ CLOCKS_PER_SEC;
                            Ventana::llenarLaberinto2(ev.button.y,ev.button.x);
                            fin=float(clock()-begin_time)/ CLOCKS_PER_SEC;
                            cout<<endl;
                            this->tiempo=(fin-ini);
                            cout<<"El tiempo que se tardo fue: "<<(fin-ini)<<" segundos"<<endl;
                            
                        }
                    }
                    
                    
                }
            }
            
            if(f==1)
            {
                    // recorremos la matriz para llenarla
                for(int i=0;i<14;i++)
                {
                     for(int j=0;j<20;j++)
                     {
                         if(M[i][j] == 'P')
                         {
                             Ventana::ColocarImagen(i*50,j*50,image1);
                         }
                         else if(M[i][j] == '0')
                         {
                             Ventana::ColocarImagen(i*50,j*50,image2);
                         }
                         else
                         {
                              Ventana::ColocarImagen(i*50,j*50,image3);
                         }
                     }
                }
                f=0;
            }
            
             
        }
        
        //SDL_BlitSurface(currentImage,NULL,windowSurface,NULL);
        SDL_UpdateWindowSurface(this->window); // refresacmos la ventana
    }
    
   SDL_FreeSurface(image1);
    SDL_FreeSurface(image2); 
    
    SDL_DestroyWindow(this->window); // destruimos la ventana
   image1 = image2 = nullptr;
    this->window=nullptr;
    SDL_Quit(); // salimos de sdl
}

void Ventana::ColocarImagen(int x, int y, SDL_Surface *image)
{
    SDL_Rect destination;
    destination.x=y;
    destination.y=x;
    SDL_BlitSurface(image,NULL,this->windowSurface,&destination);
    //SDL_Flip(this->windowSurface);
    //SDL_UpdateWindowSurface(this->window);
}

int Ventana::ObtenerPuntaje(){
    this->puntaje;
    this->M;
    for(int i=0;i<14;i++){
        for(int j=0;j<20;j++){
            if(M[i][j]=='R'){
                puntaje=puntaje+100;
            }
        }
    }
    return puntaje;
}

float Ventana::ObtenerTiempo(){
    return this->tiempo;
}

// funcion para llenar el laberinto
void Ventana::llenarLaberinto(int a, int b){

    int y,x;
    y=a/50;
    x=b/50;
    
    SDL_Surface *pared=nullptr,*raton=nullptr, *pasillo=nullptr;
    pasillo=SDL_LoadBMP("pasillo.bmp");
    pared=SDL_LoadBMP("pared.bmp");
    raton=SDL_LoadBMP("raton.bmp");
    
    if(M[y][x+1]=='S' || M[y+1][x]=='S' || M[y-1][x]=='S' || M[y][x-1]=='S' ){
        cout<<endl;
        cout<<"FELICIDADES, HAS LLEGADO A LA SALIDA!"<<endl;
        cout<<"Merlin: GARADEWANAINDAKEDONE!"<<endl;
        M[y][x]='R';
    }
    
    else if(M[y][x+1]=='0'){
        //cout<<"DERECHA"<<endl; 
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen(y*50,(x+1)*50,raton);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='R';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto(y*50,(x+1)*50);

    }
    else if(M[y+1][x]=='0'){
        //cout<<"ABAJO"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y+1)*50,(x)*50,raton);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='R';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
    else if(M[y][x-1]=='0'){
        //cout<<"IZQUIERDA"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x-1)*50,raton);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='R';
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

        
    }
    else if(M[y-1][x]=='0'){
        //cout<<"ARRIBA"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y-1)*50,(x)*50,raton);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='R';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='P' && M[y+1][x]=='R' && M[y-1][x]=='P' && M[y][x-1]=='P' ){
        //cout<<"Regresa"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
    else if(M[y][x+1]=='P' && M[y+1][x]=='R' && M[y-1][x]=='X' && M[y][x-1]=='P' ){
        //cout<<"Regresa 2"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='R' && M[y+1][x]=='P' && M[y-1][x]=='X' && M[y][x-1]=='P' ){
        //cout<<"Regresa 3"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x+1)*50);

    }
    else if(M[y][x+1]=='P' && M[y+1][x]=='R' && M[y-1][x]=='P' && M[y][x-1]=='X' ){
        //cout<<"Regresa 4"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='P' && M[y+1][x]=='P' && M[y-1][x]=='X' && M[y][x-1]=='R' ){
        //cout<<"Regresa 5"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

    }
    else if(M[y][x+1]=='X' && M[y+1][x]=='P' && M[y-1][x]=='P' && M[y][x-1]=='R' ){
        //cout<<"Regresa 6"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='X' && M[y+1][x]=='P' && M[y-1][x]=='R' && M[y][x-1]=='P' ){
        //cout<<"Regresa 7"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    else if(M[y][x+1]=='P' && M[y+1][x]=='X' && M[y-1][x]=='R' && M[y][x-1]=='P' ){
        //cout<<"Regresa 8"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='R' && M[y+1][x]=='P' && M[y-1][x]=='P' && M[y][x-1]=='P'){
        //cout<<"Regresa 9"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x+1)*50);

    }
    else if(M[y][x+1]=='R' && M[y+1][x]=='R' && M[y-1][x]=='X' && M[y][x-1]=='P' ){
        //cout<<"Regresa 10"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x+1)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='R' && M[y+1][x]=='P' && M[y-1][x]=='P' && M[y][x-1]=='X' ){
        //cout<<"Regresa 11"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x+1)*50);

    }
    else if(M[y][x+1]=='X' && M[y+1][x]=='X' && M[y-1][x]=='P' && M[y][x-1]=='R' ){
        //cout<<"Regresa 12"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='X' && M[y+1][x]=='R' && M[y-1][x]=='X' && M[y][x-1]=='P' ){
        //cout<<"Regresa 13"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
    //regresa 14 is down here
    else if(M[y][x+1]=='P' && M[y+1][x]=='R' && M[y+2][x]=='0' && M[y-1][x]=='R' && M[y][x-1]=='P' ){
        //cout<<"Regresa 14"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='P' && M[y+1][x]=='R' && M[y-1][x]=='X' && M[y][x-1]=='P' ){
        //cout<<"Regresa 15"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
    else if(M[y][x+1]=='R' && M[y+1][x]=='X' && M[y-1][x]=='X' && M[y][x-1]=='P' ){
        //cout<<"Regresa 16"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x+1)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='X' && M[y+1][x]=='0' && M[y-1][x]=='R' && M[y][x-1]=='P' ){
        //cout<<"Regresa 17"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    else if(M[y][x+1]=='R' && M[y+1][x]=='P' && M[y-1][x]=='P' && M[y][x-1]=='R' ){
        //cout<<"Regresa 18"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='R' && M[y+1][x]=='X' && M[y-1][x]=='P' && M[y][x-1]=='R' ){
        //cout<<"Regresa 19"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

    }
    else if(M[y][x+1]=='P' && M[y+1][x]=='P' && M[y-1][x]=='R' && M[y][x-1]=='X' ){
        //cout<<"Regresa 20"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='R' && M[y+1][x]=='X' && M[y-1][x]=='P' && M[y][x-1]=='P' ){
        //cout<<"Regresa 21"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x+1)*50);

    }
    else if(M[y][x+1]=='R' && M[y+1][x]=='P' && M[y-1][x]=='P' && M[y][x-1]=='X' ){
        //cout<<"Regresa 22"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x+1)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='P' && M[y+1][x]=='X' && M[y-1][x]=='P' && M[y][x-1]=='R' ){
        //cout<<"Regresa 23"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

    }
    else if(M[y][x+1]=='P' && M[y+1][x]=='P' && M[y-1][x]=='R' && M[y][x-1]=='P' ){
        //cout<<"Regresa 24"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='R' && M[y+1][x]=='X' && M[y-1][x]=='P' && M[y][x-1]=='X' ){
        //cout<<"Regresa 25"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x+1)*50);

    }
    else if(M[y][x+1]=='R' && M[y+1][x]=='R' && M[y-1][x]=='P' && M[y][x-1]=='X' ){
        //cout<<"Regresa 26"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x+1)*50);

    }
     //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='P' && M[y+1][x]=='P' && M[y-1][x]=='P' && M[y][x-1]=='R' ){
        //cout<<"Regresa 27"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

    }
    //RIP ARRIBA
    else if(M[y][x+1]=='P' && M[y+1][x]=='R' && M[y+2][x]!='R' && M[y][x-1]=='P' && M[y-1][x]!='R' ){
        //cout<<"Regresa 28"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
     //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='X' && M[y+1][x]=='P' && M[y-1][x]=='X' && M[y][x-1]=='R' ){
        //cout<<"Regresa 29"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

    }
    else if(M[y][x+1]=='X' && M[y+1][x]=='R' && M[y-1][x]=='P' && M[y][x-1]=='P' ){
        //cout<<"Regresa 30"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='P' && M[y+1][x]=='R' && M[y-1][x]=='X' && M[y][x-1]=='X' ){
        //cout<<"Regresa 31"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
    else if(M[y][x+1]=='R' && M[y+1][x]=='P' && M[y-1][x]=='X' && M[y][x-1]=='X' ){
        //cout<<"Regresa 33"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x+1)*50);

    }
     //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='P' && M[y+1][x]=='X' && M[y-1][x]=='X' && M[y][x-1]=='R' ){
        //cout<<"Regresa 34"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

    }
    else if(M[y][x+1]=='P' && M[y+1][x]=='X' && M[y-1][x]=='R' && M[y][x-1]=='X' ){
        //cout<<"Regresa 35"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
     //DERECHA ABAJO ABAJO+1 ABAJO+2 ARRIBA IZQUIERDA
    else if(M[y][x+1]=='P' && M[y+1][x]=='R' && M[y+2][x]=='R' && M[y+3][x]=='R' && M[y-1][x]=='R' && M[y][x-1]=='P' ){
        //cout<<"Regresa 36"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
     //DERECHA ABAJO ARRIBA ARRIBA+1 ARRIBA+2 IZQUIERDA
    else if(M[y][x+1]=='P' && M[y+1][x]=='R' && M[y-1][x]=='R' && M[y-2][x]=='R' && M[y-3][x]=='R' && M[y][x-1]=='P' ){
        //cout<<"Regresa 37"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='X' && M[y+1][x]=='X' && M[y-1][x]=='R' && M[y][x-1]=='P' ){
        //cout<<"Regresa 38"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    else if(M[y][x+1]=='P' && M[y+1][x]=='X' && M[y-1][x]=='X' && M[y][x-1]=='R' ){
        //cout<<"Regresa 38"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='P' && M[y+1][x]=='R' && M[y+2][x]=='P' && M[y-1][x]=='R' && M[y][x-1]=='P' ){
        //cout<<"Regresa 39"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    else if(M[y][x+1]=='P' && M[y+1][x]=='X' && M[y-1][x]=='0' && M[y][x-1]=='R' ){
        //cout<<"Regresa 40"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    //DERECHA ABAJO ARRIBA IZQUIERDA
    else if(M[y][x+1]=='X' && M[y+1][x]=='P' && M[y-1][x]=='X' && M[y][x-1]=='R' ){
        //cout<<"Regresa 41"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x-1)*50);

    }
    else if(M[y][x+1]=='R' && M[y+1][x]=='R' && M[y+2][x]=='R' && M[y-1][x]=='P' && M[y][x-1]=='P' ){
        //cout<<"Regresa 42"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y)*50,(x+1)*50);

    }
    
}

void Ventana::llenarLaberinto2(int a, int b){ 
    int y,x;
    y=a/50;
    x=b/50;
    
    SDL_Surface *pared=nullptr,*raton=nullptr, *pasillo=nullptr;
    pasillo=SDL_LoadBMP("pasillo.bmp");
    raton=SDL_LoadBMP("raton.bmp");
  
    
    if(M[y][x+1]=='S' || M[y+1][x]=='S' || M[y-1][x]=='S' || M[y][x-1]=='S' ){
        cout<<"Merlin: GARADEWANAINDAKEDONE!"<<endl;
        M[y][x]='R';
    }   
   
    
    //BASE NORMAL (???)
    else if(M[y][x+1]=='0'){
        //cout<<"DERECHA"<<endl; 
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen(y*50,(x+1)*50,raton);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='R';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto(y*50,(x+1)*50);

    }
    else if(M[y+1][x]=='0'){
        //cout<<"ABAJO"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y+1)*50,(x)*50,raton);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='R';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
    else if(M[y][x-1]=='0'){
        //cout<<"IZQUIERDA"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x-1)*50,raton);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='R';
        Ventana::llenarLaberinto((y)*50,(x-1)*50);
        

    }
    else if(M[y-1][x]=='0'){
        //cout<<"ARRIBA"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y-1)*50,(x)*50,raton);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='R';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    
    //RIP
    else if(M[y+1][x]!='0' && M[y-1][x]!='0' && M[y][x-1]=='R' && M[y][x+1]!='0'){
        //cout<<"IZQUIERDA"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y)*50,(x-1)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        Ventana::llenarLaberinto((y)*50,(x-1)*50);
        

    }
    else if(M[y+1][x]!='0' && M[y-1][x]=='R' && M[y][x-1]!='0' && M[y][x+1]!='0'){
        //cout<<"ARRIBA"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y-1)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y-1)*50,(x)*50);

    }
    else if(M[y+1][x]!='0' && M[y-1][x]!='0' && M[y][x-1]!='0' && M[y][x+1]=='R'){
        //cout<<"DERECHA"<<endl; 
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen(y*50,(x+1)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto(y*50,(x+1)*50);

    }
    else if(M[y+1][x]=='R' && M[y-1][x]!='0' && M[y][x-1]!='0' && M[y][x+1]!='0'){
        //cout<<"ABAJO"<<endl;
        //cout<<(((a/50)+1)/50)*50<<","<<((b+50)/50)*50<<endl;
        Ventana::ColocarImagen((y+1)*50,(x)*50,pasillo);
        //cout<<"Se colocó la imagen"<<endl;
        M[y][x]='X';
        //cout<<"La posicion ahora es:"<<M[y][x]<<endl;
        Ventana::llenarLaberinto((y+1)*50,(x)*50);

    }
    
    
}     
        
    
 