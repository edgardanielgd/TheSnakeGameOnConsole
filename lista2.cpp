#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<list>
#include<time.h>
#include<fstream>
#include<string>
#include<dirent.h>
using namespace std;
struct dato{
	string nombre;
	int puntuacion;
}puntuaciones[10];
struct mapa{
	int id;
	string nombre;
	mapa *siguiente;
};
int c=157,co=207,ca=189,limInfX=2,limMaX=50,limInfY=2,limMaY=20;
char salir='u';
void gotoxy(int x,int y){
HANDLE k;
k=GetStdHandle(STD_OUTPUT_HANDLE);
COORD co;
co.X=x;
co.Y=y;
SetConsoleCursorPosition(k,co);
}
void oc(bool valor){
HANDLE l;
l=GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO d;
d.bVisible=valor;
d.dwSize=12;
SetConsoleCursorInfo(l,&d);
}
void leerStats(){
	string contenido;
	fstream archivo("Scores.txt");
	if(archivo.fail())return;
	int contador=0;
	while(getline(archivo,contenido)){
		if(contador>9)break;
		if(contenido.size()>15){
			puntuaciones[contador].nombre=contenido.substr(0,15);
		}else puntuaciones[contador].nombre=contenido;
		if(getline(archivo,contenido)){
			if(contenido.size()>10){
				puntuaciones[contador].puntuacion=atoi(contenido.substr(0,10).c_str());	
			}else puntuaciones[contador].puntuacion=atoi(contenido.c_str());
		}else puntuaciones[contador].puntuacion=0;
		contador++;
	}
	archivo.close();
}

void ordenar(){
for(int i=1;i<10;i++){
int nRetroceso=1;
while((puntuaciones+(i-nRetroceso))->puntuacion < (puntuaciones+(i-nRetroceso+1))->puntuacion ){
int tmp_cod=(puntuaciones+(i-nRetroceso))->puntuacion;
string tmp_char=(puntuaciones+(i-nRetroceso))->nombre;
(puntuaciones+(i-nRetroceso))->puntuacion=(puntuaciones+(i-nRetroceso+1))->puntuacion;
(puntuaciones+(i-nRetroceso))->nombre=(puntuaciones+(i-nRetroceso+1))->nombre;
(puntuaciones+(i-nRetroceso+1))->puntuacion=tmp_cod;
(puntuaciones+(i-nRetroceso+1))->nombre=tmp_char;
nRetroceso++;
if(i-nRetroceso<0)break;
}
}
}
void imprimirStats(){
	ofstream archivo("Scores.txt");
	string cadena;
	for(int i=0;i<10;i++){
		if(puntuaciones[i].nombre=="" && puntuaciones[i].puntuacion==0)continue;
		cadena.append(puntuaciones[i].nombre);
		cadena.append("\n");
		cadena.append(to_string(puntuaciones[i].puntuacion).c_str());
		cadena.append("\n");
	}
	archivo.write(cadena.c_str(),cadena.size());
	archivo.close();
}
void imprimirStatsConsola(){
	system("cls");
	printf("Nombre\t\tPuntuacion\n");
	for(int i=0;i<10;i++){
		gotoxy(0,i+1);
		printf("%d. %s",i+1,puntuaciones[i].nombre.c_str());
		gotoxy(16,i+1);
		printf("%d\n",puntuaciones[i].puntuacion);
	}
	getch();
	
}
class punto{
private:
int x,y,xan,yan;
public:
char dir;
punto(){}
punto(int _x,int _y,char _dir,bool visible=true):x(_x),y(_y),dir(_dir){
if (visible){
gotoxy(x,y);
printf("%c",c);
act();
}
}
void act(){
xan=x;
yan=y;
}
void mov(){
switch(dir){
case 'w':
gotoxy(xan,yan);
printf(" ");
y--;
gotoxy(x,y);
printf("%c",c);
act();
break;
case 's':
gotoxy(xan,yan);
printf(" ");
y++;
gotoxy(x,y);
printf("%c",c);
act();
break;
case 'd':
gotoxy(xan,yan);
printf(" ");
x++;
gotoxy(x,y);
printf("%c",c);
act();
break;
case 'a':
gotoxy(xan,yan);
printf(" ");
x--;
gotoxy(x,y);
printf("%c",c);
act();
break;
}
}
int GetX(){
return x;
}
int GetY(){
return y;
}
void SetX(int _x_){
act();
x=_x_;
}
void SetY(int _y_){
act();
y=_y_;
}
};
class comida{
int x,y;
bool comido;
public:
comida(bool __comido=false):comido(__comido){}
comida(int _x,int _y,bool _comido=false):x(_x),y(_y),comido(_comido){
gotoxy(x,y);
printf("%c",ca);
}
void Imp(){
gotoxy(x,y);
if(comido){
printf("%c",ca);
}else
printf("%c",co);
}
void comer(){
comido=true;
}
int GetX(){
return x;
}
int GetY(){
return y;
}
void SetX(int _x_){
x=_x_;
}
void SetY(int _y_){
y=_y_;
}
bool devorado(){
return comido;
}
};
class muro{
int x,y,xa,ya;
public:
muro(){}
muro(int _x,int _y):x(_x),y(_y){
gotoxy(x,y);
printf("%c",219);
actu();
}
void actu(){
xa=x;
ya=y;
}
void movi(int v,int q){
gotoxy(xa,ya);
printf(" ");
x=v;
y=q;
gotoxy(x,y);
printf("%c",219);
actu();
}
int GetX(){
return x;
}
int GetY(){
return y;
}
void SetX(int _x_){
x=_x_;
}
void SetY(int _y_){
y=_y_;
}
};
class cursorDesign{
int x,y;
public:
cursorDesign(){}
cursorDesign(int _x,int _y):x(_x),y(_y){
oc(true);
gotoxy(x,y);
}
void mover(char direccion){
	switch(direccion){
		case 'w':{
			y--;
			gotoxy(x,y);
			break;
		}
		case 's':{
			y++;
			gotoxy(x,y);
			break;
		}
		case 'a':{
			x--;
			gotoxy(x,y);
			break;
		}
		case 'd':{
			x++;
			gotoxy(x,y);
			break;
		}
	}
}
void pintar(bool pared){
	gotoxy(x,y);
	(pared)?printf("%c",178):printf(" ");
	gotoxy(x,y);
}
int GetX(){
	return x;
}
int GetY(){
	return y;
}
};
void crearM(int x,int y,list<muro *> &laberinto){
muro *nuevoM=new muro(x,y);
laberinto.push_back(nuevoM);
nuevoM=NULL;
delete nuevoM;
}
void cuadro1(int,list<muro *> &);
int random(int min,int max){
return (rand()%(max-min-1))+min+1;
}
void inicio(list<comida *> &comidita,list<punto *> &culebra,punto *&cabeza,punto *&cola,int size=5,int x=10,int y=10, char dire='d'){
if(!comidita.empty()){
for(list<comida *>::iterator ky=comidita.begin();ky!=comidita.end();++ky){
delete (*ky);
}
for(int kk=comidita.size();kk>0;kk--){
comidita.pop_back();
}
}
if(!culebra.empty()){
for(list<comida *>::iterator kx=comidita.begin();kx!=comidita.end();++kx){
delete (*kx);
}
for(int kk=culebra.size();kk>0;kk--){
culebra.pop_back();
}
}
comida *nuevo2=new comida(random(limInfX,limMaX),random(limInfY,limMaY));
comidita.push_back(nuevo2);
for (int i=0;i<size;i++){
punto *nuevo=new punto(x-i,y,dire);
culebra.push_back(nuevo);
}
cabeza=culebra.front();
cola=culebra.back();
}
void actualizar(list<punto *>culebra,punto *cabeza){
char aux,aux2;
aux=cabeza->dir;
punto *aux3=new punto();
for (list<punto *>::iterator rec=culebra.begin();rec!=culebra.end();++rec){
aux2=(*rec)->dir;
(*rec)->dir=aux;
aux=aux2;
}
}
void recibir(punto *&cabeza,bool &fin){
if (kbhit()){
char m=getch();
if ((m=='a' or m== 's' or m=='d' or m=='w') && !(m=='a' && cabeza->dir=='d') && !(m=='d' && cabeza->dir=='a') && !(m=='s' && cabeza->dir=='w') && !(m=='w' && cabeza->dir=='s'))cabeza->dir=m;
if(m==salir)fin=true;
}
}
void mover(list<punto *>culebra,bool &gameover,int nivel,list<muro *>laberinto){
for(list <muro *>::iterator mu=laberinto.begin();mu!=laberinto.end();++mu){
if((culebra.front()->GetX()==(*mu)->GetX()-1 && culebra.front()->GetY()==(*mu)->GetY() && culebra.front()->dir=='d') or (culebra.front()->GetX()==(*mu)->GetX()+1 && culebra.front()->GetY()==(*mu)->GetY() && culebra.front()->dir=='a') or (culebra.front()->GetY()==(*mu)->GetY()-1 && culebra.front()->GetX()==(*mu)->GetX() && culebra.front()->dir=='s') or (culebra.front()->GetY()==(*mu)->GetY()+1 && culebra.front()->GetX()==(*mu)->GetX() && culebra.front()->dir=='w')) {
gameover=true;
return;
}
}
for (list<punto *>::iterator r=culebra.begin();r!=culebra.end();++r){
if((culebra.front()->GetX()==(*r)->GetX()-1 && culebra.front()->GetY()==(*r)->GetY() && culebra.front()->dir=='d') or (culebra.front()->GetX()==(*r)->GetX()+1 && culebra.front()->GetY()==(*r)->GetY() && culebra.front()->dir=='a') or (culebra.front()->GetY()==(*r)->GetY()-1 && culebra.front()->GetX()==(*r)->GetX() && culebra.front()->dir=='s') or (culebra.front()->GetY()==(*r)->GetY()+1 && culebra.front()->GetX()==(*r)->GetX() && culebra.front()->dir=='w')) {
gameover=true;
return;
}
}
for (list<punto *>::iterator rel=culebra.begin();rel!=culebra.end();++rel){
if ((*rel)->GetY()==limMaY-1 && (*rel)->dir=='s'){
(*rel)->SetY(limInfY);
}
if ((*rel)->GetY()==limInfY+1 && (*rel)->dir=='w'){
(*rel)->SetY(limMaY);
}
if ((*rel)->GetX()==limInfX+1 && (*rel)->dir=='a'){
(*rel)->SetX(limMaX);
}
if ((*rel)->GetX()==limMaX-1 && (*rel)->dir=='d'){
(*rel)->SetX(limInfY);
}
}
for (list<punto *>::iterator re=culebra.begin();re!=culebra.end();++re){
(*re)->mov();
}
}
void comer(punto *cabeza,punto *cola,list<comida *> &comidita,list<muro *> laberinto,bool &crecer,int &tempx,int &tempy,int &puntos,int nivel){
comida *aux5=new comida();
comida *aux6=new comida();
aux5=comidita.back();
aux6=comidita.front();
if (aux5->GetX()==cabeza->GetX() && aux5->GetY()==cabeza->GetY()){
aux5->comer();
bool error=true;
comida *nuevo3=new comida();
do{
error=false;
nuevo3->SetX(random(limInfX,limMaX));
nuevo3->SetY(random(limInfY,limMaY));
for(list<muro *>::iterator hg=laberinto.begin();hg!=laberinto.end();++hg){
if(nuevo3->GetX()==(*hg)->GetX() && nuevo3->GetY()==(*hg)->GetY()){
error=true;
}
}
}while(error);
nuevo3->Imp();
comidita.push_back(nuevo3);
nuevo3=NULL;
delete nuevo3;
}
if (comidita.front()->GetX()==cola->GetX() && comidita.front()->GetY()==cola->GetY()){
crecer=true;
delete comidita.front();
comidita.pop_front();
tempx=cola->GetX();
tempy=cola->GetY();
puntos+=200*(nivel*0.25)+100;
}else{
crecer=false;
}
for (list<comida *>::iterator aq=comidita.begin();aq!=comidita.end();++aq){
(*aq)->Imp();
}
aux5=NULL;
delete aux5;
}
void crecimiento(list<punto *> &culebra,punto *&cola,bool crec,int x1,int y1 ){
if (crec){
punto *nuevo4=new punto(x1,y1,'x');
culebra.push_back(nuevo4);
cola=nuevo4;
}
}
void ImprPuntos(int puntos,list<punto *>culebra){
gotoxy(30,0);
printf("Largo: %d",culebra.size());
gotoxy(30,1);
printf("puntos: %010d",puntos);
}
void normal(){
gotoxy(limInfX,limInfY);
printf("%c",201);
gotoxy(limMaX,limInfY);
printf("%c",187);
gotoxy(limMaX,limMaY);
printf("%c",188);
gotoxy(limInfX,limMaY);
printf("%c",200);
for (int i=limInfX+1;i<=limMaX-1;i++){
gotoxy(i,limInfY);
printf("%c",205);
gotoxy(i,limMaY);
printf("%c",205);
}
for (int j=limInfY+1;j<=limMaY-1;j++){
gotoxy(limInfX,j);
printf("%c",186);
gotoxy(limMaX,j);
printf("%c",186);
}
}
void cuadro1(int nivel,list<muro *> &laberinto){
for(list<muro *>::iterator t1=laberinto.begin();t1!=laberinto.end();++t1){
delete (*t1);
}
gotoxy(0,0);
printf("%d",laberinto.size());
for(int i=laberinto.size();i>0;i--){
laberinto.pop_back();
}
if(nivel==0){
normal();
}else if(nivel==1){
normal();
for (int i=limInfX;i<=limMaX;i++){
crearM(i,limInfY,laberinto);
crearM(i,limMaY,laberinto);
}
for (int j=limInfY;j<=limMaY;j++){
crearM(limInfX,j,laberinto);
crearM(limMaX,j,laberinto);
}
}else if(nivel==2){
normal();
for (int k=limInfY+1;k<=limMaY-1;k++){
crearM(limInfX+((limMaX-limInfX)/2),k,laberinto);
}
for (int l=limInfX+1;l<=limMaX-1;l++){
crearM(l,limInfY+((limMaY-limInfY)/2),laberinto);

}
}else if(nivel==3){
normal();
int a=limInfY+7,b=limMaY-7,c=limInfY+9;
for (int m=limInfY+5;m<=limMaY-5;m++){
if(m==a or m==b or m==c)continue;
crearM(limInfX+5,m,laberinto);
crearM(limMaX-5,m,laberinto);
}
a=(limInfX+(limMaX-limInfX))/3;
b=2*a;
c=3*a;
for (int n=limInfX+5;n<=limMaX-5;n++){
if(n==a or n==b or n==c)continue;
crearM(n,limInfY+5,laberinto);
crearM(n,limMaY-5,laberinto);
}
}else if(nivel==4){
normal();
int d=limInfY+(limMaY-limInfY)/2;
for (int o=limInfY+1;o<=limMaY-1;o++){
if(o==d)continue;
crearM(limInfX,o,laberinto);
crearM(limInfX+12,o,laberinto);
crearM(limInfX+24,o,laberinto);
crearM(limInfX+36,o,laberinto);
crearM(limInfX+48,o,laberinto);
}
}else if(nivel==5){
normal();
int e=limInfY+(limMaY-limInfY)/2;
int f=limInfX+(limMaX-limInfX)/2;
for (int o=limInfY+10;o<=limMaY;o++){
if(o==e)continue;
crearM(limInfX+48,o,laberinto);
}
for (int p=limInfY;p<=limMaY-10;p++){
crearM(limInfX,p,laberinto);
}
for (int p=limInfX;p<=limMaX-f;p++){
crearM(p,limInfY,laberinto);
}
for (int p=limInfX+f;p<=limMaX;p++){
crearM(p,limMaY,laberinto);
}
for(int po=limInfX+2;po<=limMaX-2;po+=6){
for (int pi=limInfY+2;pi<limMaY-2;pi+=3){
crearM(po,pi,laberinto);
}
}
}
}
int menu(int tipo){
system("cls");
char **elementos;
int filas;
int seleccion=1;
if (tipo==0)filas=5;
if(tipo==2)filas=5;
if(tipo==1)filas=8;
elementos=new char*[filas];
for (int w=0;w<filas;w++){
elementos[w]=new char[30];
}
if(tipo==0){
*elementos=(char*)"Jugar";
*(elementos+1)=(char*)"Mejores Puntajes";
*(elementos+2)=(char*)"Crear Nivel";
*(elementos+3)=(char*)"Tienda";
*(elementos+4)=(char*)"Salir";
}else if(tipo==2){
*elementos=(char*)"Facil";
*(elementos+1)=(char*)"Corriente";
*(elementos+2)=(char*)"Complicado :O";
*(elementos+3)=(char*)"Maniaco (Ni siquiera Bots)";
*(elementos+4)=(char*)"Volver";
}else if(tipo==1){
*elementos=(char *)"Todos los niveles";
*(elementos+1)=(char*)"Nivel 1";
*(elementos+2)=(char*)"Nivel 2";
*(elementos+3)=(char*)"Nivel 3";
*(elementos+4)=(char*)"Nivel 4";
*(elementos+5)=(char*)"Nivel 5";
*(elementos+6)=(char*)"Nivel 6";
*(elementos+7)=(char*)"Volver";
}
for(int i=0;i<filas;i++){
gotoxy(5,5+i);
if (seleccion-1==i){
printf(">>>%s",*(elementos+i));
}else
printf("   %s",*(elementos+i));
}
while(1){
if (kbhit()){
int sel=getch();
if(sel==224){
sel=getch();
}
if (sel==80)seleccion++;
if(sel==72)seleccion--;
//
if(sel==13 && seleccion==1 && tipo==0){
int opt=menu(1);
if(opt!=0){
system("cls");
return opt;
}
}
if(sel==13 && seleccion==5 && tipo==0){
return 0;
}
if(sel==13 && seleccion==2 && tipo==0){
return 29;
}
if(sel==13 && seleccion==3 && tipo==0){
return 30;
}
if(sel==13 && seleccion==8 && tipo==1){
system("cls");
return 0;
}else if(sel==13 && tipo==1){
int opt2=menu(2);
if(opt2!=0){
system("cls");
return (((seleccion-1)*4)+opt2);
}
}

if(sel==13 && seleccion==5 && tipo==2){
system("cls");
return 0;
}else if(sel==13 && tipo==2){
return seleccion;
}
//
if(seleccion<1)seleccion=filas;
if(seleccion>filas)seleccion=1;
for(int i=0;i<filas;i++){
gotoxy(5,5+i);
if (seleccion-1==i){
printf(">>>%s",*(elementos+i));
}else
printf("   %s",*(elementos+i));
}
}

}
}
void jugarCampana(int nivel,int velocidad,int &puntos,bool constante=false){
bool fin=false;
bool crecer=false;
int tempx,tempy;
punto *cabeza=NULL;
punto *cola=NULL;
list<punto *> culebra;
list<comida *> comidita;
list<muro *> laberinto;
time_t reloj1=time(0);
system("cls");
gotoxy(1,0);
printf("Muevase con w,a,s,d");
gotoxy(1,1);
printf("U para salir");
inicio(comidita,culebra,cabeza,cola,5,7,8);
gotoxy(20,1);
printf("Nivel: %d",nivel);
gotoxy(0,0);
cuadro1(nivel,laberinto);
Sleep(2000);
while(!fin or nivel>5){
recibir(cabeza,fin);
mover(culebra,fin,nivel,laberinto);
crecimiento(culebra,cola,crecer,tempx,tempy);
actualizar(culebra,cabeza);
comer(cabeza,cola,comidita,laberinto,crecer,tempx,tempy,puntos,nivel);
ImprPuntos(puntos,culebra);
if(culebra.size()==nivel+(nivel*3)+10 && !constante){
system("cls");
gotoxy(1,0);
printf("Muevase con w,a,s,d");
gotoxy(1,1);
printf("U para salir");
int xin,yin;
if (nivel==0)xin=10,yin=11;
if (nivel==1)xin=10,yin=9;
if (nivel==2)xin=10,yin=11;
if (nivel==3)xin=10,yin=11;
inicio(comidita,culebra,cabeza,cola,5,xin,yin);
nivel++;
gotoxy(20,1);
printf("Nivel: %d",nivel+1);
cuadro1(nivel,laberinto);
Sleep(2000);
}
Sleep(velocidad);
}
//puntos=nivel*5/(tiempo)
int reloj=difftime(time(0),reloj1);
system("cls");
gotoxy(5,5);
int retor=(reloj>0)?0:(nivel*50000)/(reloj*velocidad);
if (nivel>5){
printf("Ha gamado\nPuntos Obtenidos: %d\nPuntos de bonificacion: %d\nTotal: %d",puntos,retor,puntos+retor);
}else
printf("Ha perdido\nPuntos Obtenidos: %d\nPuntos de bonificacion: %d\nTotal: %d",puntos,retor,puntos+retor);
puntos+=retor;
Sleep(1000);
if(puntos>puntuaciones[9].puntuacion){
system("cls");
gotoxy(0,0);
printf("Digita tu nombre:\n");
char *input=(char*)malloc(10);
fgets(input,10,stdin);
strtok(input,"\n");
puntuaciones[9].nombre=(char*)input;
puntuaciones[9].puntuacion=puntos;
ordenar();
imprimirStats();
}

}
void crearNivel(){
system("cls");
printf("Digite el nombre del mapa\n");
char cadena[24];
fgets(cadena,20,stdin);
strtok(cadena,"\n");
system("cls");
gotoxy(0,0);
printf("Muevase con W,A,S,D. Presione 't' para crear o quitar un muro. Cuando finalice presione U");
cursorDesign *cursor1=new cursorDesign(10,10);
int arreglo[limMaY-1][limMaX];
for(int z=0;z<limMaY-1;z++){
	for(int y=0;y<limMaX;y++){
		arreglo[z][y]=0;
	}
}
normal();
while(1){
	
	if(kbhit()){
		char a=getch();
		if(a=='u')break;
		if(a=='w' && cursor1->GetY()-1<2)continue;
		if(a=='a' && cursor1->GetX()-1<2)continue;
		if(a=='s' && cursor1->GetY()+1>limMaY)continue;
		if(a=='d' && cursor1->GetX()+1>limMaX)continue;
		cursor1->mover(a);
		if(a=='t'){
			int x=cursor1->GetX();
			int y=cursor1->GetY();
			if(arreglo[y-limInfY][x-limInfX]!=0){
				arreglo[y-limInfY][x-limInfX]=0;
				cursor1->pintar(false);
				if(x==limInfX && y==limInfY){
					printf("%c",201);	
				}else if(x==limInfX && y==limMaY){
					printf("%c",200);
				}else if(x==limMaX && y==limInfY){
					printf("%c",187);
				}else if(x==limMaX && y==limMaY){
					printf("%c",188);
				}else if(y==limMaY or y==limInfY){
					printf("%c",205);
				}else if(x==limMaX or x==limInfX){
					printf("%c",186);
				}
			}else{
			arreglo[y-limInfY][x-limInfX]=1;
			cursor1->pintar(true);
		}
		}
	}
}
system("cls");
gotoxy(0,0);
char *write=(char*)malloc((limMaX+1)*(limMaY));
for(int i=0;i<limMaY-1;i++){
	for(int j=0;j<limMaX;j++){
		*(write+(i*limMaX+j))=*(to_string(arreglo[i][j]).c_str());
	}
	*(write+(i*limMaX+limMaX-1))='\n';
}
strcat(cadena,".txt");
char path[50]="customLevels\\";
strcat(path,cadena);
ofstream archivo;
archivo.open(path);
archivo.write(write,(limMaX*(limMaY-1)));
archivo.close();
oc(false);
}
void LeerCarpeta(mapa *&primero){
   mapa *aux=primero;
   while(aux!=NULL){
   		mapa *aux2=aux;
   		aux=aux->siguiente;
   		free(aux2);
   		delete aux2;
   }
   DIR *dr;
   struct dirent *en;
   dr = opendir("customLevels"); //open all directory
   if (dr) {
   		int contador=1;
   		mapa *ultimo=NULL;
        while ((en = readdir(dr)) != NULL) {
    	if(en->d_namlen>4){ //*.txt
    	if(contador==1){
    		primero=new mapa;
    		primero->id=contador;
    		contador++;
    		primero->nombre=en->d_name;
    		primero->siguiente=new mapa;
    		ultimo=primero;
    		aux=primero->siguiente;
		}else{
        aux->id=contador;
        contador++;
        aux->nombre=en->d_name;
        aux->siguiente=new mapa;
        ultimo=aux;
        aux=aux->siguiente;
    	}
    }
      }
       delete ultimo->siguiente;
       ultimo->siguiente=NULL;
       mapa *aux2=primero;
       closedir(dr); //close all directory
   }else{
   printf("No hay mapas aun...");
   system("pause");
   return;
}
}
void crearMapaCustom(mapa *primero,list<muro*> &laberinto){
	int x=0,len=0;
	mapa *aux=primero;
	string sElegido;
	while(aux!=NULL){
		gotoxy(5,5+len);
		if(aux->id==x+1){
			sElegido=aux->nombre;
			printf(">>>%s",aux->nombre.c_str());
		}else printf("   %s",aux->nombre.c_str());
		
		len++;
		aux=aux->siguiente;
	}
	gotoxy(5,5+len);
	printf("   Volver");
	int seleccion;
	while(seleccion!=13){
		seleccion=getch();
		if(seleccion==224){
			seleccion=getch();
		}
		if(seleccion==80){
			x++;
			if(x==len+1)x=0;
		}
		if(seleccion==72){
			x--;
			if(x==-1)x=len;
		}
		if(seleccion==80 or seleccion==72){
		aux=primero;
		int pos=0;
		while(aux!=NULL){
		gotoxy(5,5+pos++);
		if(aux->id==x+1){
			sElegido=aux->nombre;
			printf(">>>");
		}else printf("   ");
		aux=aux->siguiente;
		}
		if(x==len){
		gotoxy(5,5+pos);
		printf(">>>");
		}else {
		gotoxy(5,5+pos);
		printf("   ");
		}
	}
	}
	system("cls");
	gotoxy(0,0);
	for(list<muro*>::iterator it=laberinto.begin();it!=laberinto.end();++it){
		delete *(it);
	}
	for(int i=0;i<laberinto.size();i++){
		laberinto.pop_back();
	}
	if(x!=len){
		string linea;
		char path[50]="customLevels\\";
		strcat(path,sElegido.c_str());
		ifstream archivo(path);
		while(getline(archivo,linea)){
			//
		}
		printf(path);
	}
}
void Funcion_principal(){
leerStats();
ordenar();
oc(false);
int opc=0;
int nivel;
while(1){
opc=menu(0);
int puntos=0;
int niv,vel;
niv=((opc-1)/4)-1;
vel=100-((opc-1)%4)*25;
if(opc==0){
return;
}else if(opc>4 && opc<=28){
jugarCampana(niv,vel,puntos,1);
}else if(opc<=4){
jugarCampana(0,vel,puntos,0);
}else if(opc==29){
imprimirStatsConsola();
}else if(opc==30){
crearNivel();
}
}
}
main(){
oc(false);
mapa *primero=NULL;
LeerCarpeta(primero);
list<muro*> laberinto;
crearMapaCustom(primero,laberinto);
}

