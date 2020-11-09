#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <monetary.h>

#include "mlb.h"

const int NUM_TEAMS = 16;

Team *createTeam(char *name, int wins, int loss, char *city, char *state,
                 double payroll, double aveSalary) {
  Team *t = (Team *)malloc(sizeof(Team) * 1);
  t->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(t->name, name);
  t->wins = wins;
  t->loss = loss;
  t->city = (char *)malloc(sizeof(char) * (strlen(city) + 1));
  strcpy(t->city, city);
  t->state = (char *)malloc(sizeof(char) * (strlen(state) + 1));
  strcpy(t->state, state);
  t->payroll = payroll;
  t->averageSalary = aveSalary;
  return t;
}

void printTeam(const Team *t) {
  if (t == NULL) {
    printf("null\n");
    return;
  }
  double winPerc = t->wins / (double)(t->wins + t->loss);
  printf("%-10s %3d  %3d (%4.3f) %-15s %2s $%12.2f $%9.2f\n", t->name, t->wins,
         t->loss, winPerc, t->city, t->state, t->payroll, t->averageSalary);
}

void printAllTeams(Team *teams, int size) {
  int i;
  printf("%-9s %-4s %-4s (%-4s) %-12s %-2s %-13s %-11s\n", "Name", "Wins",
           "Loss", "Win %", "City", "State", "Payroll", "Avg Salary");
  for (i = 0; i < size; i++) {
    printTeam(&teams[i]);
  }
}

Team *readFile(const char *fileName) {
  Team *teams = (Team *)malloc(sizeof(Team) * NUM_TEAMS);

  FILE *instream = fopen(fileName, "r");
  if (instream == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", fileName);
    exit(1);
  }

  // read the file, line by line
  int i = 0;
  int size = 1000;
  char *tempBuffer = (char *)malloc(sizeof(char) * size);

  // discard first line
  fgets(tempBuffer, size, instream);
  while (fgets(tempBuffer, size, instream) != NULL && i < NUM_TEAMS) {
    char name[100];
    int wins, loss;
    char *city, *state;
    double payroll, averageSalary;
    // remove the endline character from the line
    tempBuffer[strlen(tempBuffer) - 1] = '\0';
    char *teamToken = strtok(tempBuffer, " ");
    strcpy(name, teamToken);
    wins = atoi(strtok(NULL, " "));
    loss = atoi(strtok(NULL, " "));
    city = strtok(NULL, " ");
    state = strtok(NULL, " ");
    payroll = atof(strtok(NULL, " "));
    averageSalary = atof(strtok(NULL, " "));
    Team *t = createTeam(name, wins, loss, city, state, payroll, averageSalary);
    teams[i] = *t;
    i++;
  }
  fclose(instream);

  free(tempBuffer);

  return teams;
}

void bubbleSortTeams(Team *teams, int size,
                     int (*compar)(const void *, const void *)) {
  int i, j;
  Team temp;
  for (i = 0; i < size - 1; i++) {
    for (j = 0; j < size - 1; j++) {
      // compare adjacent teams by asking the compar function passed in:
      if (compar(&teams[j], &teams[j + 1]) > 0) {
        // swap them...
        temp = teams[j];
        teams[j] = teams[j + 1];
        teams[j + 1] = temp;
      }
    }
  }
}

void selectionSortTeamsByPayroll(Team *teams, int size) {
  // TODO: implement this function
}

void selectionSortTeams(Team *teams, int size,
                        int (*compar)(const void *, const void *)) {
  // TODO: implement this function
}

int teamComparisonByName(const void *s1, const void *s2) {
  const Team *t1 = (const Team *)s1;
  const Team *t2 = (const Team *)s2;
  int result = strcmp(t1->name, t2->name);
  return result;
}

int teamComparisonByState(const void *s1, const void *s2) {
  const Team *t1 = (const Team *)s1;
  const Team *t2 = (const Team *)s2;
  return strcmp(t1->state, t2->state);
}

int teamComparisonByStateCity(const void *s1, const void *s2) {
  const Team *t1 = (const Team *)s1;
  const Team *t2 = (const Team *)s2;
  if (strcmp(t1->state, t2->state) == 0) {
    return strcmp(t1->city, t2->city);
  } else {
    return strcmp(t1->state, t2->state);
  }
}

int teamComparisonByWinPercentage(const void *s1, const void *s2) {
  const Team *t1 = (const Team *)s1;
  const Team *t2 = (const Team *)s2;
  double t1_winPer = t1->wins / (double)(t1->wins + t1->loss);
  double t2_winPer = t2->wins / (double)(t2->wins + t2->loss);

  if (t1_winPer < t2_winPer) {
    return 1;
  } else if (t1_winPer == t2_winPer) {
    return 0;
  } else {
    return -1;
  }
}

// TODO: implement your own comprator function to order
//      Teams by payroll in descending order; be sure to
//      add your function prototype to the mlb.h header file!
