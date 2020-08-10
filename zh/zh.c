#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <fcntl.h>
#include <errno.h>
#include <unistd.h> 
#include <wait.h> 

/*
Operációs rendszerek gyakorlati zárthelyi dolgozat, 2019 december 12. 16 óra

Ha készen van a megoldással jelezze egy oktatónak, 
aki ellenőrzi az elkészült programot, amire az oktató jegyet ad.

Itt a szakdolgozati témák bejelentési ideje. A hallgató (gyerek) beadja, 
feltölti a választott témát a Neptunba(szülő), amit a választott témavezető (gyerek) vagy elfogad vagy nem.

 

A Neptun készen áll, létrehoz egy hallgató folyamatot, 
aki bejelenti csövön a szakdolgozati témát, 
a bejelentő az alábbi adatokat tartalmazza: 
Hallgató neve, Dolgozat címe, Beadás éve, Témavezető neve. 
A beérkezést követően a Neptun kiküldi a témavezetői kérést 
a témavezetőnek szintén csövön keresztül, aki kiírja a képernyőre 
az adatokat, majd befejeződik a program, szülő vár a gyerekek befejezésére.

Miután a témavezető megkapja a Neptunból a felkérést, azt 60% eséllyel elutasítja, 
amiről SIG_NOT_ACCEPTED jelzést küld elutasítás, SIG_ACCEPTED jelzést küld elfogadás 
esetén a Neptunnak. Ezt az értesítést Neptun továbbküldi a hallgatónak, aki miután 
fogadja a jelzést kiírja, hogy a témát elfogadta a témavezető vagy nem. Ezután befejeződik a program.
Ha a témavezető nem fogadta el a témát, akkor hallgató választhat kijelölt 
témavezetőt. Egy kijelölt témavezető nevet Neptun az osztott memóriába ír, 
ahonnan a hallgató kiveheti vagy új témavezetőt nevez meg. Ezt az eredményt 
hallgató írja ki, és a program fejeződjön be.
Az osztott memóriába helyezett témavezetőt több hallgató is igénybe veheti, 
így azt védje szemaforral.
*/


typedef struct {
    char* nev;
    char* cim;
    int ev;
    char* temavezeto;
} Dolgozat;


int main( ) {
    
    Dolgozat dolgozat;
    
    int pipefdHallgato[2]; // unnamed pipe file descriptor array
    if (pipe(pipefdHallgato) == -1) {
        perror("Hiba a pipe nyitaskor!");
        exit(EXIT_FAILURE);
    }
    int pipefdTemavezeto[2]; // unnamed pipe file descriptor array
    if (pipe(pipefdTemavezeto) == -1) {
        perror("Hiba a pipe nyitaskor!");
        exit(EXIT_FAILURE);
    }
    
    int hallgatoPid = fork();
    if( hallgatoPid > 0) {
        // neptun
        int temavezetoPid = fork();
        if( temavezetoPid > 0) {
            printf("neptun: kesz\n");
            Dolgozat beerkezett;
            close(pipefdTemavezeto[0]);
            close(pipefdHallgato[1]);  //Usually we close the unused write end
            read(pipefdHallgato[0], &beerkezett.nev, sizeof(char*));
            printf("neptun: megerkezett %s\n", beerkezett.nev);
            read(pipefdHallgato[0], &beerkezett.cim, sizeof(char*));
            printf("neptun: megerkezett %s\n", beerkezett.cim);
            read(pipefdHallgato[0], &beerkezett.ev, sizeof(int));
            printf("neptun: megerkezett %i\n", beerkezett.ev);
            read(pipefdHallgato[0], &beerkezett.temavezeto, sizeof(char*));
            printf("neptun: megerkezett %s\n", beerkezett.temavezeto);
            // neptun
            printf("neptun: tovabbkuld \n");
            write(pipefdTemavezeto[1], &beerkezett.nev, sizeof(beerkezett.nev));
            write(pipefdTemavezeto[1], &beerkezett.cim, sizeof(beerkezett.cim));
            write(pipefdTemavezeto[1], &beerkezett.ev, sizeof(beerkezett.ev));
            write(pipefdTemavezeto[1], &beerkezett.temavezeto, sizeof(beerkezett.temavezeto));
            close(pipefdTemavezeto[1]);
            // gyerek terminálása.
            wait(NULL); 
            wait(NULL); 
            
        } else if(temavezetoPid == 0) {
            // temavezeto
            printf("temavezeto: kesz\n");
            close(pipefdTemavezeto[1]);  //Usually we close the unused write end
            Dolgozat ertekelendo;
            read(pipefdTemavezeto[0], &ertekelendo.nev, sizeof(char*));
            printf("temavezeto: megerkezett %s\n", ertekelendo.nev);
            read(pipefdTemavezeto[0], &ertekelendo.cim, sizeof(char*));
            printf("temavezeto: megerkezett %s\n", ertekelendo.cim);
            read(pipefdTemavezeto[0], &ertekelendo.ev, sizeof(int));
            printf("temavezeto: megerkezett %i\n", ertekelendo.ev);
            read(pipefdTemavezeto[0], &ertekelendo.temavezeto, sizeof(char*));
            printf("temavezeto: megerkezett %s\n", ertekelendo.temavezeto);
        
            exit(0);
        } else {
            printf("fork: Error\n");
            printf("Test FAILED\n");
            exit(-1);
        }
       
    } else if(hallgatoPid == 0) {
        // hallgato
        close(pipefdTemavezeto[0]);
        close(pipefdTemavezeto[1]);
        printf("hallgato: kesz\n");
        char* nev = "Hallgato Bela";
        char* cim = "Nagyon szep dolgozat";
        int ev = 2019;
        char* temavezeto = "Temavezeto Bela";
        write(pipefdHallgato[1], &nev, sizeof(nev));
        write(pipefdHallgato[1], &cim, sizeof(cim));
        write(pipefdHallgato[1], &ev, sizeof(ev));
        write(pipefdHallgato[1], &temavezeto, sizeof(temavezeto));
        printf("hallgato: elkuldve \n");
        close(pipefdHallgato[1]);
        
        exit(0);
    } else {
        printf("fork: Error\n");
        printf("Test FAILED\n");
        exit(-1);
    }
    
    
    return 0;
}

































