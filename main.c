#include <stdio.h>
#include <stdlib.h>
#include <conio.c>
#include <time.h>
#include <windows.h>
#define maxcombi 4
#define maxcouleurs 6
#define maxessais 10
typedef char mm_combi[maxcombi];
typedef int mm_score[2];
FILE *secret;
FILE *historique;
mm_combi sec;
void affichedate(char *texte,char *texte1){ /* cette fonction affiche la date et l'ecrit aussi dans el fichier historique */
                                            FILE *auj,*tim;
                                            char date[20]="",time[20]="";
                                            system("echo %date% > date.txt ");
                                            system("echo %time% > time.txt ");
                                            auj=fopen("date.txt","r+");
                                            fscanf(auj,"%s",date);fclose(auj);
                                            system("DEL date.txt");
                                            tim=fopen("time.txt","r+");
                                            fscanf(tim,"%s",time);fclose(tim); time[5]='\0'; system("DEL time.txt");
                                            printf("%s %s %s %s\n",texte,date,texte1,time);
                                            historique=fopen("historique.txt","a+");
                                            fprintf(historique,"%s %s %s %s\n",texte,date,texte1,time);
                                            fclose(historique);
                                         }
char couleur(int X){ /* retour du caractere de la couleur */
                    switch(X){
                    case BLUE:return 'B';
                    case GREEN:return 'V';
                    case CYAN:return 'C';
                    case RED:return 'R';
                    case MAGENTA:return 'M';
                    case BROWN:return 'A';
                    case LIGHTGRAY:return 'D';
                    case DARKGRAY:return 'E';
                    case LIGHTBLUE:return 'F';
                    case LIGHTGREEN:return 'J';
                    default:break;
                    } return 0;
                  }
void menucouleur(){
    int i,j,ii; gotoxy(wherex()+47,wherey()); for (ii=1;ii<maxcouleurs+1;ii++){
i=wherex();
j=wherey();
gotoxy(i,j); textbackground(ii);
    printf("%c",couleur(ii));
      textbackground(0);
    printf(" ");}}
int couleur1(char X){ /* retour de l'indice de la couleur */
                    switch(X){
                case 'B' : return 1;
					case 'V' : return 2;
					case 'C' : return 3;
					case 'R' : return 4;
					case 'M' : return 5;
					case 'A' : return 6;
					case 'D' : return 7;
					case 'E' : return 8;
					case 'F' : return 9;
					case 'J' : return 10;
                    default:break;
                    } return 0;}
void init_combi_remise(int m,int p,mm_combi la_combi){ /* combinaision par hasard */
                int i;
                secret=fopen("secret.txt","w");
                srand(time(NULL));
                fprintf(secret,"La combinaison secrete est : ");
                for(i=0;i<m;i++){
                sec[i]=couleur(rand()%(p)+1);
                fprintf(secret,"%c ",la_combi[i]);
                }
                fclose(secret);
            }
int existe(char x,mm_combi TT){ /* recherche sequentielle */
                                int i=maxcombi-1;
                                while(x!=TT[i] && i!=-1) { i--;}
                                return i;
}
void essai(mm_score t){ mm_combi test; /* essai numero i avec le test et le retour de score */
    historique=fopen("historique.txt","a+");
    int i,ii,j;
    mm_combi aux;
    for (ii=0;ii<maxcombi;ii++){ /* lecture des coueleurs */
                                test[ii]=getch();
                                i=wherex();
                                j=wherey();
                                gotoxy(i,j);
                                textbackground(couleur1(test[ii]));
                                fprintf(historique,"%c",test[ii]);
                                printf(" ");
                                textbackground(0);
                                fprintf(historique," ");
                                printf(" ");
                                }
                                fclose(historique);
for(ii=0;ii<maxcombi;ii++){
        aux[ii]=sec[ii];}
for(ii=0;ii<maxcombi;ii++){
    if(test[ii]==aux[ii]) {(t[1])++; aux[ii]=couleur(maxcouleurs+1);  test[ii]=couleur(maxcouleurs+2);}}
    for(ii=0;ii<maxcombi;ii++){ if(existe(test[ii],aux)!=-1){t[0]++; aux[existe(test[ii],aux)]=couleur(maxcouleurs+3);}}

} /* fin essai */
void affiche(){ /* afficher la combi secrete */
    int i,ii,j ;

for(ii=0;ii<=maxcombi;ii++) { i=wherex();
j=wherey();
gotoxy(i,j); textbackground(couleur1(sec[ii]));
    printf(" ");
      textbackground(0);
    printf(" ");}}
void jeux(){ /* le jeu */

            int XX=0,i=1,ii;
            mm_score score;
            score[0]=0; score[1]=0;
            while ( (XX!=maxcombi) && (i<=maxessais)){
              historique=fopen("historique.txt","a+"); printf("[%2d] : ",maxessais-i+1);fprintf(historique,"[%2d] : ",maxessais-i+1); fclose(historique); essai(score); historique=fopen("historique.txt","a+");   printf("   mal place: %d reussi: %d  \n\n",score[0],score[1]); fprintf(historique,"   mal place: %d reussi: %d  \n\n",score[0],score[1]); fclose(historique); i++; score[0]=0; XX=score[1]; score[1]=0;
            }  historique=fopen("historique.txt","a+");
            if (XX==maxcombi){ printf("vous avez gagner"); fprintf(historique,"vous avez gagner");} else{ printf("vous avez perdu la combinaison est : \n       "); fprintf(historique,"vous avez perdu la combinaison est : \n       ");
            for (ii=0;ii<maxcombi;ii++){ fprintf(historique,"%c ",sec[ii]);}  fclose(historique);
            affiche();}
            }
void titre(){ /* affichage du titre en couleur */
    printf("                    ");textbackground(5);printf("MasterMind\n\n\n\n"); textbackground(0);textbackground(0);}
void menujeux(){
    char c;
 titre(); affichedate("Le jeux a commance le ","a ");menucouleur(); printf("\n");
init_combi_remise(maxcombi,maxcouleurs,sec);
jeux(); affichedate("\nLe jeux est termine le ","a "); printf("\nappuyer sur une touche pour retourner au menu : "); c=getch();  clrscr();
}
void clrhst(){ /* supprimer l'historique du jeux */
    char c;
    titre();
    historique=fopen("historique.txt","w");
    fclose(historique);
    printf("L'historique a ete supprime avec succes");
    printf("\nappuyer sur une touche pour retourner au menu : "); c=getch();  clrscr();
}
void regles(){ char c;
    titre();
printf("hello\n world"); menucouleur();
printf("\nappuyer sur une touche pour retourner au menu : ");
c=getch(); clrscr();

}
int main(){
    int i=0;
    textcolor(9);
     do{ system("cls");
titre();
    printf("                      Menu : \n       [1] afficher les regles du jeu [1] \n             [2] commancer le jeu [2] \n         [3] supprimer l'historique [3] \n                 [4] quittez [4]\n              Tapez votre choix : ");
    scanf("%d",&i);
    clrscr();
    switch(i){
    case 1 : regles(); break;
    case 2 : menujeux();  break;
    case 3 : clrhst(); break;
    case 4 : i=4; break;
    default : i=0;
    }
  } while(i!=4);
return 0;
}
