/**
 * Main driver program for the MLB team
 * sorting and searching demo code.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <search.h>

#include "team.h"

extern int NUM_TEAMS;

int main(int argc, char **argv) {

  //default file path
  char *filePath = "../data/mlb_nl_2011.csv";
  if(argc == 2) {
    filePath = argv[1];
  }

  Team *teams = readCsvFile(filePath);

  if(teams == NULL) {
    fprintf(stderr, "Unable to process CSV file.\n");
    exit(1);
  }

  printf("Teams, original order: \n");
  printAllTeams(teams, NUM_TEAMS);

  printf("(Bubble) Sorted by win percentage: \n");
  bubbleSortTeams(teams, NUM_TEAMS, teamComparisonByWinPercentage);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Selection) Sorted by payroll: \n");
  selectionSortTeamsByPayroll(teams, NUM_TEAMS);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Selection with comparator) Sorted by payroll: \n");
  // TODO: change this line to use your comparator for payroll in decreasing
  // order
  selectionSortTeams(teams, NUM_TEAMS, NULL);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Quick) Sorted by name: \n");
  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByName);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Quick) Sorted by win percentage: \n");
  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByWinPercentage);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Quick) Sorted by state (then city): \n");
  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByStateCity);
  printAllTeams(teams, NUM_TEAMS);

  printf("(Quick) Sorted by payroll (increasing order): \n");
  // TODO: call qsort using your comparator function here
  printAllTeams(teams, NUM_TEAMS);

  /* search, find */
  Team caKey;
  initTeam(&caKey, "", 0, 0, "", "CA", 0, 0);
  Team *caTeam = NULL;

  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByWinPercentage);
  caTeam = bsearch(&caKey, teams, NUM_TEAMS, sizeof(Team), teamComparisonByState);
  printf("Search #1 result for CA team (via state): \n");
  printTeam(caTeam);

  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByState);
  caTeam = bsearch(&caKey, teams, NUM_TEAMS, sizeof(Team), teamComparisonByState);
  printf("Search #2 result for CA team (via state): \n");
  printTeam(caTeam);

  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByStateCity);
  caTeam = bsearch(&caKey, teams, NUM_TEAMS, sizeof(Team), teamComparisonByState);
  printf("Search #3 result for CA team (via state): \n");
  printTeam(caTeam);

  qsort(teams, NUM_TEAMS, sizeof(Team), teamComparisonByWinPercentage);
  size_t elems = NUM_TEAMS;
  caTeam = lfind(&caKey, teams, &elems, sizeof(Team), teamComparisonByState);
  printf("Search #4 result for CA team (via state): \n");
  printTeam(caTeam);

  // TODO: Search for the Cubs and print it out:
  printf("Search result for Cubs (via name): \n");

  return 0;
}
