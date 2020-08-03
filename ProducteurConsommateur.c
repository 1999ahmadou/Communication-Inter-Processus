#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<wait.h>
#include<string.h>
#define N 10 /* Nombre d'espace vide dans le tampon */
int tampon;  /* depotoire (permet de stocker ou de retirer les objets) */
void produire_objet(int objet)
{
    objet=1;
}
void deposer_objet(int objet)
{
    tampon=objet;
    printf("\t\t\t\t\t Phase de Production\n\n\n");//Depot d'un Objet
}
void retirer_objet(int objet)
{
    objet=tampon;
}
void consommer_objet(int objet)
{
    int consommation=objet;
    printf("\t\t\t\t\t Phase de Consommation\n\n\n");//Apres retrait
}
int main ()
{
    int f;

    /* Declaration des descripteur */
	int desc[2];
	int desc1[2];
	int desc2[2];

    /* Tableau de caractéres permettant de stocker le message à transmettre */
    char message1[100];
    char message2[100];
    char message3[100];

    strcpy(message1,"Est ce que le Tampon est vide?");//Demande s'il peux consommer
    strcpy(message2,"Non je viens de deposer un objet");
    strcpy(message3,"J'ai retiré l'objet");

    int objet;

    /* Creation des Tube anonymes */
	pipe(desc);
	pipe(desc1);
	pipe(desc2);

    f=fork();
    switch(f){
        case -1: printf("Erreur dans fork()\n");
             return -1;
        case 0: /*Consommateur */

             /* Fermeture des descripteurs qui ne sont pas utiles au processus(consommateur) */
 		     close(desc[0]);
 		     close(desc1[1]);
		     close(desc2[0]);
             for (int i = 0; i < N; i++){
                
                printf("\t\t\t\tFils---> %s\n\n",message1);
                 write(desc[1],message1,sizeof(message1)); /* Envoie d'un message(Send) */
                 
	            }
                 while(1){

     
                 read(desc1[0],message2,sizeof(message2)); /* Reception d'un message (Receive) */

                 retirer_objet(objet);
			
                 consommer_objet(objet);
                 printf("\t\t\t\tFils---> %s\n\n",message3);
		         write(desc2[1],message3,sizeof(message3)); /* Envoie d'un message(Send) */
                 }
             break;
        default: /*Producteur*/

             /* Fermeture des descripteurs qui ne sont pas utiles au processus(consommateur) */
	         close(desc[1]);
	         close(desc1[0]);
	         close(desc2[1]);
             while(1){
                 produire_objet(objet);
		
                 read(desc[0],message1,sizeof(message1)); /* Reception d'un message (Receive) */

                 deposer_objet(objet);

                 printf("\t\t\t\tPere---> %s\n\n",message2);
                 write(desc1[1],message2,sizeof(message2)); /* Envoie d'un message(Send) */
                 
		         read(desc2[0],message3,sizeof(message3)); /* Reception d'un message (Receive) */
                 
             }
             break;
    }
    return 0;
}
