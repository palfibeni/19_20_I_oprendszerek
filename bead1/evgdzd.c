#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
Első beadandó
A "Szakács Tamás" utazási iroda csődbe ment. Sok üdülőhelyen maradtak utasok. A csőd "hullámai" elmosták a pontos nyilvántartást is, 
így mikor az utasok hazaszállítását szervezik nem is tudják pontosan, hogy hol, kik maradtak.

Készítsen C nyelven programot(aminek egy GNU C/C++ fordítóval Linux rendszeren, ilyen például az opsys.inf.elte.hu is, fordulnia és futnia kell) 
aminek segítségével a különböző helyeken rekedt utasok fel tudnak iratkozni a mentésre várók listájára. 
Erre a listára fel kell venni az utas nevét, a helyszínt (csak az utazási iroda rögzített helyszínei adottak, Bali, Mali, Cook szigetek, Bahamák, Izland), 
az utas telefonszámát és az ott rekedt csoport utazási módját (repülő, hajó, autóbusz). 

Az adatokat fájlban tároljuk, az adatfelvételen túl legyen lehetőségünk az adatokon módosítani, törölni és helyszínenként listáztatni.

A forrásállományokat a gyakorlathoz tartozó Canvas oldalon töltsék fel.

Beadási határidő: 2019 november 4. 
*/

bool quit = false;
char* name;
int menuItem = 0;
int subMenuItem = 0;

char* dataFile = "./data.txt";
char* locations[5] = {"Bali", "Mali", "Cook szigetek", "Bahamák", "Izland"};
char* travelingMethods[3] = {"repülő", "hajó", "autóbusz"};

int count;
struct Traveler *travelers;

struct Traveler {
    char* name;
    int location;
    int travelingMethod;
};

/**
* Get the number of lines in the file.
*/
int getFileLineCount();

/**
* Read all travelers from file to the global variable travelers.
*/
struct Traveler* readData(int count);

/**
* Format database friendly the given traveler.
*/
char* toDataString(struct Traveler traveler);

/**
* Format user friendly the given traveler.
*/
char* toStringFormatted(struct Traveler traveler);

/**
* Read a string from user, without lineend.
*/
char* readStr();

/**
* Read a single char from user.
*/
char readChar();

/**
* Read a single char from user, and converts it to int.
*/
int readInt();

/**
* Greet user to subMenu, with given message then navigate to subMenuItem 1.
*/
void greetingsToSubMenu(char *message);

/**
* Get a string from user, with message given.
*/
char* chooseName(char* message);

/**
* Get location from user, with message given, if valid, navigate user to given newSubMenuItem.
*/
int chooseLocation(char *message, int newSubMenuItem);

/**
* Get traveling methond from user, with message given, if valid, navigate user to given newSubMenuItem.
*/
int chooseTravelingMethod(char *message, int newSubMenuItem);

/**
* Save current travelers array to file, without closing the file.
*/
void saveDataWithoutClose(FILE *fPtr);

/**
* Get traveler index by name, if found, navigate user to subMenuItem 2.
*/
int getIndexByName();

/**
* Save travelers to file, and navigate user vack to main menu.
*/
void saveModifiedData();

void greetings() {
    printf("Kedves utazó!\n");
    printf("Üdvözlöm Szakács Tamás utazási iroda, utasok hazaszállítását segítő programban.\n");
    printf("Felvesszük adataid, és segítünk a hazajutásban!\n");
    printf("Amennyiben ki szeretne lépni az alkalmazásból bármelyik fázisban egy \'q\' betű leütésével megteheti.\n");
    name = chooseName("Hogy hívnak? ");
}

void mainMenu() {
    printf("Mit szeretnél tenni? A kiválasztott menüpont sorszámát írd be, vagy \'q\' ha kilépnél!\n");
    printf("1. Új személy felvétele az utasmentési listára\n");
    printf("2. Meglévő adat módosítása\n");
    printf("3. Meglévő adat törlése\n");
    printf("4. Meglévő adatok listázása helyszínenként\n");
    printf("Választott menü sorszáma: ");
    int newMenuItem = readInt();
    if (newMenuItem > 0 && newMenuItem < 5) {
        menuItem = newMenuItem;
        count = getFileLineCount();
        travelers = readData(count);
    }
}

// 1. ADD NEW DATA

void saveNewData(struct Traveler newTraveler) {
    FILE *fPtr = fopen(dataFile, "w");
    if (!fPtr) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    saveDataWithoutClose(fPtr);
    fputs(toDataString(newTraveler), fPtr);
    
    fclose(fPtr);
}

void confirmNewData(struct Traveler newTraveler) {
    printf("A megadott adatok: \n%s", toStringFormatted(newTraveler));
    printf("Helyes? (i/n) \n");
    char c = readChar();
    if (c == 'i') {
        saveNewData(newTraveler);
        subMenuItem = -1;
        menuItem = 0;
    } else {
        subMenuItem = 0;
    }
}

void addNewData() {
    struct Traveler newTraveler;
    
    subMenuItem = 0;
    while (!quit) {
        switch (subMenuItem) {
            case -1:
                return;
            case 0:
                greetingsToSubMenu("Új személyt adnál hozzá az mentési listához, ehhez meg kell adnod az adatait.\n");
                break;
            case 1:
                newTraveler.name = chooseName("Mi a személy neve? ");
                subMenuItem = 2;
                break;
            case 2:
                newTraveler.location = chooseLocation("Hol nyaral? Kérem adja meg a helyszín sorszámát.\n", 3);
                break;
            case 3:
                newTraveler.travelingMethod = chooseTravelingMethod("Mivel utazott? Kérem adja meg az utazási forma sorszámát.\n", 4);
                break;
            case 4:
                confirmNewData(newTraveler);
                break;
            default:
                printf("Hiba, ha inkább kilépnél írj egy \'q\'-t?\n");
        }
    }
}

// 2. MODIFY DATA

void editName(int index) {
    char message[50];
    sprintf(message, "Mi az új név? (korábban: %s) ", travelers[index].name);
    travelers[index].name = chooseName(message);
    subMenuItem = 3;
}

void editLocation(int index) {
    char message[50];
    sprintf(message, "Mi az új helszín? (korábban: %s)\n", locations[travelers[index].location - 1]);
    travelers[index].location = chooseLocation(message, 4);
}

void editTravelingMethod(int index) {
    char message[50];
    sprintf(message, "Mi az új utazási forma? (korábban: %s)\n", travelingMethods[travelers[index].travelingMethod - 1]);
    travelers[index].travelingMethod = chooseTravelingMethod(message, 5);
}

void confirmEditData(int index) {
    printf("A megadott adatok: \n%s", toStringFormatted(travelers[index]));
    printf("Helyes? (i/n) \n");
    char c = readChar();
    if (c == 'i') {
        saveModifiedData();
        subMenuItem = -1;
        menuItem = 0;
    } else {
        subMenuItem = 0;
    }
}

void modifyData() {
    int index;
    
    subMenuItem = 0;
    while (!quit) {
        switch (subMenuItem) {
            case -1:
                return;
            case 0:
                greetingsToSubMenu("Korábbi adat módosítása.\n");
                break;
            case 1:
                index = getIndexByName();
                break;
            case 2:
                editName(index);
                break;
            case 3:
                editLocation(index);
                break;
            case 4:
                editTravelingMethod(index);
                break;
            case 5:
                confirmEditData(index);
                break;
            default:
                printf("Hiba, ha inkább kilépnél írj egy \'q\'-t?\n");
        }
    }
}

// 3. DELETE DATA

void deleteDataByIndex(int index) {
    for (int c = index; c < count - 1; c++) {
        travelers[c] = travelers[c+1];
    }
    count--;
}

void confirmDeleteData(int index) {
    printf("A törlendő elem adatai: \n%s", toStringFormatted(travelers[index]));
    printf("Helyes? (i/n) \n");
    char c = readChar();
    if (c == 'i') {
        deleteDataByIndex(index);
        saveModifiedData();
        subMenuItem = -1;
        menuItem = 0;
    } else {
        subMenuItem = 0;
    }
}

void deleteData() {
    int index;
    
    subMenuItem = 0;
    while (!quit) {
        switch (subMenuItem) {
            case -1:
                return;
            case 0:
                greetingsToSubMenu("Adat törlése.\n");
                break;
            case 1:
                index = getIndexByName();
                break;
            case 2:
                confirmDeleteData(index);
                break;
            default:
                printf("Hiba, ha inkább kilépnél írj egy \'q\'-t?\n");
        }
    }
}

// 4. LIST BY LOCATION

void printDataByLocations(int location) {
    for (int i = 0; i < count; i++) {
        if(travelers[i].location == location) {
            printf("%s\n", toStringFormatted(travelers[i]));
        }
    }
    subMenuItem = -1;
    menuItem = 0;
}

void listDataByLocations() {
    int location;
    
    subMenuItem = 0;
    while (!quit) {
        switch (subMenuItem) {
            case -1:
                return;
            case 0:
                greetingsToSubMenu("Az adatok listázása helyszín alapján történik.\n");
                break;
            case 1:
                location = chooseLocation("Melyik helyszín bajbajutottjait szeretné listázni?.\n", 2);
                break;
            case 2:
                printf("print\n");
                printDataByLocations(location);
                break;
            default:
                printf("Hiba, ha inkább kilépnél írj egy \'q\'-t?\n");
        }
    }
}

// MAIN MENU

int main( ) {
    greetings();
    while (!quit) {
        switch (menuItem) {
            case 0:
                mainMenu();
                break;
            case 1:
                //1. Új személy felvétele az utasmentési listára
                addNewData();
                break;
            case 2:
                //2. Meglévő adat módosítássa
                modifyData();
                break;
            case 3:
                //3. Meglévő adat törlése
                deleteData();
                break;
            case 4:
                //4. Meglévő adatok listázása helyszínenként
                listDataByLocations();
                break;
            default:
                printf("Hiba, biztos ezt akartad írni? (%c) Ha inkább kilépnél írj egy \'q\'-t?\n", menuItem + '0');
                menuItem = 0;
        }
    }
    free(travelers);
    printf("Köszönjük, hogy programunkat használtad, %s\n", name);
    return 0;
}

void removeNewLine(char* string) {
    size_t length = strlen(string);
    if ((length > 0) && (string[length-1] == '\n')) {
        string[length-1] ='\0';
    }
}

char* readStr() {
    char line[256];
    if (fgets(line, sizeof line, stdin) == NULL) {
        printf("Input error.\n");
        exit(1);
    }
    removeNewLine(line);
    if (strcmp(line, "q") == 0) {
        quit = true;
    }
    return strdup(line);
}

char readChar() {
    return readStr()[0];
}

int readInt() {
    return readChar() - '0';
}

int getFileLineCount() {
    FILE *fPtr = fopen(dataFile, "r");
    if (fPtr == NULL) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    char line[255];
    while (fgets(line, 255, (FILE*) fPtr)) {
        count = count + 1;
    }
    fclose(fPtr);
    return count;
}

struct Traveler* readData(int count) {
    FILE *fPtr = fopen(dataFile, "r");
    if (fPtr == NULL) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    struct Traveler *travelers = malloc(sizeof(struct Traveler) * count);
    char line[255];
    int i = 0;
    while (fgets(line, 255, (FILE*) fPtr)) {
        char *p = strtok (line, ";");
        travelers[i].name=(char*)malloc(sizeof(char*));
        strcpy(travelers[i].name, p);
        p = strtok (NULL, ";");
        travelers[i].location = atoi(p);
        p = strtok (NULL, ";");
        travelers[i].travelingMethod = atoi(p);
        i++;
    }
    fclose(fPtr);
    
    return travelers;
}

char* toDataString(struct Traveler traveler) {
    char formatted[256];
    sprintf(formatted,  "%s;%i;%i\n",
        traveler.name,
        traveler.location,
        traveler.travelingMethod);
    return strdup(formatted);
}

char* toStringFormatted(struct Traveler traveler) {
    char formatted[256];
    sprintf(formatted,  "név:           %s\n"
                        "helyszín:      %s\n"
                        "utazási forma: %s\n", 
        traveler.name, 
        locations[traveler.location - 1], 
        travelingMethods[traveler.travelingMethod - 1]);
    return strdup(formatted);
}

void greetingsToSubMenu(char *message) {
    printf(message);
    subMenuItem = 1;
}

char* chooseName(char* message) {
    char* name = "";
    while (strlen(name) < 2) {
        printf(message);
        name = readStr();
    }
    return name;
}

int chooseLocation(char *message, int newSubMenuItem) {
    printf(message);
    for (int i = 0; i < 5; i++) {
        printf("%i. %s\n", i + 1, locations[i]);
    }
    printf("Választott helyszín sorszáma: ");
    int newLocation = readInt();
    if (newLocation < 6 && newLocation > 0) {
        subMenuItem = newSubMenuItem;
    } else {
        printf("Hiba, biztos akartad írni, ha inkább kilépnél írj egy \'q\'-t? %c\n", newLocation);
    }
    return newLocation;
}

int chooseTravelingMethod(char *message, int newSubMenuItem) {
    printf(message);
    for(int i = 0; i < 3; i++) {
        printf("%i. %s\n", i + 1, travelingMethods[i]);
    }
    printf("Választott utazási forma sorszáma: ");
    int travelingMethod = readInt();
    if (travelingMethod < 4 && travelingMethod > 0) {
        subMenuItem = newSubMenuItem;
    } else {
        printf("Hiba, biztos ezt akartad írni? (%c) Ha inkább kilépnél írj egy \'q\'-t?\n", travelingMethod);
    }
    return travelingMethod;
}

void saveDataWithoutClose(FILE *fPtr) {
    for (int i = 0; i < count; i++) {
        fputs(toDataString(travelers[i]), fPtr);
    }
}

int getIndexByName() {
    char *editName = chooseName("Mi a személy neve? ");
    for (int i = 0; i < count; i++) {
        if (strcmp(travelers[i].name,  editName) == 0) {
            subMenuItem = 2;
            return i;
        }
    }
    printf("Hiba, ilyen személy nincs az adatbázisban, ha inkább kilépnél írj egy \'q\'-t?\n");
}

void saveModifiedData() {
    FILE *fPtr = fopen(dataFile, "w");
    if(!fPtr) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    saveDataWithoutClose(fPtr);
    fclose(fPtr);
    subMenuItem = -1;
    menuItem = 0;
}