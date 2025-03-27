/**
 * @file proj2.c
 * @brief IOS - projekt 2 (synchronizace)
 * @author Ondrej Galeta
 * @date 2.5.2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
//waitpid
#include <sys/types.h>
#include <sys/wait.h>
#include "proj2.h"

#define MAXTR 1000
#define MAXTE 1000
#define MAXNR 20
#define MAXNE 1000

#define CREATE_CVAR(pointer) {(pointer) = mmap(NULL, sizeof(*(pointer)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);}
#define DESTROY_CVAR(pointer) {munmap((pointer), sizeof((pointer)));}


bool parse_input(int argc, char *argv[], int *NE, int *NR, int *TE, int *TR) {
    // function for parsing input
    // all magic constants comes from task description
    if(argc != EXP_NUM_ARG) {
        return false;
    }
    *NE = atoi(argv[1]);
    *NR = atoi(argv[2]);
    *TE = atoi(argv[3]);
    *TR = atoi(argv[4]);
    if((0 >= *NE) || (*NE >= MAXNE)) {
        printf("NE is not a number in valid range\n");
        return false;
    }
    if((0 >= *NR) || (*NR >= MAXTR)) {
        printf("NR is not a number in valid range\n");
        return false;
    }
     if((0 > *TE) || (*TE > MAXTE)) {
        if(strcmp(argv[3], "0")) {
        printf("TE is not a number in valid range %d\n", !strcmp(argv[3], "0"));
        return false;
        }
    }
    if((0 > *TR) || (*TR > MAXTR)) {
        if(strcmp(argv[4], "0")) {
        printf("TR is not a number in valid range\n");
        return false;
        }
    }
    return true;
}


bool init() {
    elf = sem_open("xgalet06", O_CREAT | O_EXCL, 0666, 0);
    elf_end= sem_open("xgalet061", O_CREAT | O_EXCL, 0666, 0);
    sem_elf_nedd_help = sem_open("xgalet062", O_CREAT | O_EXCL, 0666, 0);
    hitched = sem_open("xgalet063", O_CREAT | O_EXCL, 0666, 0);
    xmas = sem_open("xgalet064", O_CREAT | O_EXCL, 0666, 0);
    startsem = sem_open("xgalet066", O_CREAT | O_EXCL, 0666, 0);
    sem_write = sem_open("xgalet067", O_CREAT | O_EXCL, 0666, 1);
    sem_santas_bed = sem_open("xgalet068", O_CREAT | O_EXCL, 0666, 0);
    endsem = sem_open("xgalet069", O_CREAT | O_EXCL, 0666, 0);
    if((elf == SEM_FAILED) || (elf_end== SEM_FAILED) || (sem_elf_nedd_help == SEM_FAILED) || (hitched == SEM_FAILED) || (xmas == SEM_FAILED) || (startsem == SEM_FAILED) || (sem_write == SEM_FAILED) || (sem_santas_bed == SEM_FAILED) || (endsem == SEM_FAILED)) {
        printf("Sem initi failed\n");
        deinit();
        exit(1);
    }
    CREATE_CVAR(xgalet06prom)
    CREATE_CVAR(xgalet06ElvesWait)
    CREATE_CVAR(xgalet06ElvesHomeBOOL)
    CREATE_CVAR(xgalet06EventNum)
    CREATE_CVAR(xgalet06All)
    if((xgalet06prom == MAP_FAILED) || (xgalet06ElvesWait == MAP_FAILED) || (xgalet06ElvesHomeBOOL == MAP_FAILED) || (xgalet06EventNum == MAP_FAILED) || (xgalet06All == MAP_FAILED)) {
        printf("Variable failed\n");
        deinit();
        exit(1);
    }
    return 0;
}

void deinit() {
    // closing semaphores
    sem_close(elf);
    sem_close(elf_end);
    sem_close(sem_elf_nedd_help);
    sem_close(hitched);
    sem_close(xmas);
    sem_close(startsem);
    sem_close(sem_write);
    sem_close(sem_santas_bed);
    sem_close(endsem);
    // unlinking semaphores
    sem_unlink("xgalet069");
    sem_unlink("xgalet067");
    sem_unlink("xgalet066");
    sem_unlink("xgalet064");
    sem_unlink("xgalet063");
    sem_unlink("xgalet062");
    sem_unlink("xgalet06");
    sem_unlink("xgalet061");
    sem_unlink("xgalet068");

    // destroying shared memories
    DESTROY_CVAR(xgalet06prom)
    DESTROY_CVAR(xgalet06ElvesWait)
    DESTROY_CVAR(xgalet06ElvesHomeBOOL)
    DESTROY_CVAR(xgalet06EventNum)
    DESTROY_CVAR(xgalet06All)
}

void write_mes(char *str, int num, FILE *fptr) {
    sem_wait(sem_write);
    if(num == 0) {
        printf(str, ++(*xgalet06EventNum));
        fprintf(fptr, str, *xgalet06EventNum);
    } else { 
        printf(str, ++(*xgalet06EventNum), num);
        fprintf(fptr, str, *xgalet06EventNum, num);
    }
    fflush(fptr);
    sem_post(sem_write);
}

void santa_job(FILE *fptr, int NE) {
    // process Santa
    sem_wait(startsem);
    sem_post(startsem);
    write_mes("%d: Santa: going to sleep\n", 0, fptr);
    
    while(*xgalet06prom != 0) {
        sem_wait(sem_santas_bed);
        if(*xgalet06ElvesWait >= 3) {
            (*xgalet06ElvesWait) -= 3;
            write_mes("%d: Santa: helping elves\n", 0, fptr);
            sem_post(sem_elf_nedd_help);
            sem_post(sem_elf_nedd_help);
            sem_post(sem_elf_nedd_help);
            sem_wait(elf);
            sem_wait(elf);
            sem_wait(elf);
            write_mes("%d: Santa: going to sleep\n", 0, fptr);
        }
    }
    write_mes("%d: Santa: closing workshop\n", 0, fptr);
            
    //unlocking rest of elves
    *xgalet06ElvesHomeBOOL = 1; 
    for(int a = 0; a < NE; a++) {
        sem_post(sem_elf_nedd_help);
    }
    sem_post(elf_end);

    // hitch reindeers
    sem_post(hitched);

    // reindeer send message about hitch
    sem_wait(xmas);

    write_mes("%d: Santa: Christmas started\n", 0, fptr);
    (*xgalet06All)--;
    if((*xgalet06All) == 0) {
        sem_post(endsem);
    }
}

void elf_job(FILE *fptr, int id, double delay) {
    // process Elf
    id++;
    sem_wait(startsem);
    sem_post(startsem);
    write_mes("%d: Elf %d: started\n", id, fptr);
    if(delay != 0) {
        usleep(delay);
    }
    
    write_mes("%d: Elf %d: need help\n", id, fptr);
    (*xgalet06ElvesWait)++;
    sem_post(sem_santas_bed);
    

    sem_wait(sem_elf_nedd_help);
    if(*xgalet06ElvesHomeBOOL == 0) {
        write_mes("%d: Elf %d: get help\n", id, fptr);
        sem_post(elf);
    }
            
    sem_wait(elf_end);
    sem_post(elf_end);
    write_mes("%d: Elf %d: taking holidays\n", id, fptr);
    (*xgalet06All)--;
    if((*xgalet06All) == 0) {
        sem_post(endsem);
    }
}

void reinder_job(FILE *fptr, int id, double delay, int NR) {
    // process reindeer
    id++;
    sem_wait(startsem);
    sem_post(startsem);
    write_mes("%d: RD %d: rstarted\n", id, fptr);

    if(delay != 0) {
       usleep(delay);
    }

    write_mes("%d: RD %d: return home\n", id, fptr);
    (*xgalet06prom)--;
    sem_post(sem_santas_bed);
    
    sem_wait(hitched);
    sem_post(hitched);

    write_mes("%d: RD %d: get hitched\n", id, fptr);
    (*xgalet06prom)++;
    if(*xgalet06prom == NR) { 
        sem_post(xmas);
    }
    
    (*xgalet06All)--;
    if(*xgalet06All == 0) {
        sem_post(endsem);
    }
}

int main(int argc, char *argv[]) {
    int NE;
    int NR;
    int TE;
    int TR;

    if(!parse_input(argc, argv, &NE, &NR, &TE, &TR)) {
        printf("Ivalid input was set\n"); 
        exit(1);
    }

    init();
    *xgalet06All = NE + NR + 1;
    *xgalet06prom = NR;
    *xgalet06ElvesWait = 0;
    *xgalet06EventNum = 0;
    *xgalet06ElvesHomeBOOL = 0;

    FILE *fptr;
    if ((fptr = fopen("proj2.out","w")) == NULL){
        printf("Error with openig a file");
        deinit();
        exit(1);
    }

    srand(time(0));
    
    pid_t processPid = 1;

    processPid = fork();
    if(processPid == 0) {
        santa_job(fptr, NE);
        exit(0);
    }

    for(int i = 0; (i < NE) && (processPid > 0); i++) {
        processPid = fork();
        double delay = (double)(rand() % (TE + 1)) * 1000;
        if(processPid == 0) {
            elf_job(fptr, i, delay);
            exit(0);
        }
    }

    for(int i = 0; (i < NR) && (processPid > 0); i++) {
        processPid = fork();
        double delay = (double)((rand() % ((TR/2) + 1) - (TR/2)) + (TR/2))  * 1000;
        if(processPid == 0) {
            reinder_job(fptr, i, delay, NR);
            exit(0);
        }
    }

    // start all processes now
    sem_post(startsem);
    
    sem_wait(endsem);
    deinit();
    fclose(fptr);
    return 0;
}   