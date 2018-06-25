#include <SDL2/SDL.h>
#include <string.h>

class Ventana
{
private:
    char M[14][20];
    //_int y,x;
    int ancho,largo;
    int puntaje=0;
    float tiempo=0;
    
    /*Variable donde se alamcenara nuestra ventana*/
    SDL_Window *window; 
    /*Variable donde guardara el canvas*/
    SDL_Surface *windowSurface;
public:
    Ventana(); // constructor para incializar las variables para la interfaz
    void IniciarVentana(); // aca iniciarmeos nuestra ventana
    void LlenarMatriz();
    void LlenarMatriz2(int);
    void llenarLaberinto(int,int);
    void llenarLaberinto2(int,int);
    void ColocarImagen(int , int , SDL_Surface *); // fucnion que nos servira para colocar una imagen
    char ObtenerMatriz(double);
    int ObtenerPuntaje();
    float ObtenerTiempo();
};
