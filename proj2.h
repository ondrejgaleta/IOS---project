/**
 * @file proj2.h
 * @brief IOS - projekt 2 (synchronizace)
 * @author Ondrej Galeta
 * @date 2.5.2021
*/

#ifndef proj2_h
#define proj2_h

// Global variables
sem_t *elf;
sem_t *elf_end;
sem_t *sem_elf_nedd_help;
sem_t *hitched;
sem_t *xmas;
sem_t *startsem;
sem_t *sem_write;
sem_t *sem_santas_bed;
sem_t *endsem;

int *xgalet06prom = NULL;
int *xgalet06ElvesWait = NULL;
int *xgalet06ElvesHomeBOOL = NULL;
int *xgalet06EventNum = NULL;
int *xgalet06All = NULL;

/**
 * @brief Function is used to parse input from the command prompt and check if it is valid or not 
 * @param argc Number of arguments in command prompt
 * @param argv Pointer to array of a string containing arguments 
 * @param NE Number of elves
 * @param NR Number of reindeer
 * @param TE Time, in which elves work themselves in milliseconds 
 * @param TR Time which reindeer spent on holiday in milliseconds
 * @return Returns true when input is set correctly or false when it is not 
*/
bool parse_input(int argc, char *argv[], int *NE, int *NR, int *TE, int *TR) ;

/**
 * @brief Function is used to initialize shared memory and semaphores
 * @return Returns 0 if successful, 1 if failure
*/
bool init();

/**
 * @brief Function is used to deinitialize shared memory and semaphores
 * @return Returns nothing
*/
void deinit();

/**
 * @brief Function is used to print mes
 * @param str Pointer to string, which is dedicated to print 
 * @param num Special number in the string, 0 if not needed
 * @param fptr Pointer to file
 * @return Returns nothing
*/
void write_mes(char *str, int num, FILE *fptr);

/**
 * @brief Function represents jobs for Santa
 * @param fptr Pointer to file
 * @param NE Number of elves
 * @return Returns nothing
*/
void santa_job(FILE *fptr, int NE);

/**
 * @brief Function represents jobs for elves
 * @param fptr Pointer to file
 * @param id Id represents a count of ids
 * @param delay For how long it will wait
 * @return Returns nothing
*/
void elf_job(FILE *fptr, int id, double delay);

/**
 * @brief Function represents jobs for reindeer 
 * @param fptr Pointer to the file
 * @param id Id represents a count of ids 
 * @param delay For how long it will wait
 * @param NR Variable represents a count of reindeer 
 * @return Returns nothing
*/
void reinder_job(FILE *fptr, int id, double delay, int NR);

#define EXP_NUM_ARG 5

#endif