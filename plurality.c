#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9
#define MAXBUFFERSIZE     80
char buffer[MAXBUFFERSIZE];


void getAnInput();
void getAnInput() {
    buffer[0] = '\0';
    char c;
    int char_count;
    int valid_choice = 0;
    do  {
        c = getchar();
        char_count = 0;
        while (c != '\n' && char_count < MAXBUFFERSIZE)   {
            buffer[char_count++] = c;
            c = getchar();
        }
        buffer[char_count] = 0x00;
        valid_choice = 1;
    } while (valid_choice == 0);
}
// Candidates have name and vote count
typedef struct  {
   // string name;
   char name[MAXBUFFERSIZE];
    int votes;
}  candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes

bool vote(char name[]);
void print_winner(void);

int main(int argc, char *argv[]) {
    // Check for invalid usage
    if (argc < 2)  {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)  {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)  {
        // candidates[i].name = argv[i + 1];
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;  
    }
    printf("Number of voters: ");
    int voter_count;
    getAnInput();
    voter_count = atoi(buffer);

    // Loop over all voters
    for (int i = 0; i < voter_count; i++) {
        printf("Vote: ");
        getAnInput();

        // Check for invalid vote
       
        if (!vote(buffer)) {
          printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(char name1[])   {
    for (size_t i = 0; i < candidate_count; i++)  {
        if (strcmp(name1, candidates[i].name ) == 0)  {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void) {
    int idWinner = 0;
    int max = 0;
    int fr[candidate_count];
    for (size_t i = 0; i < candidate_count; i++) {  
        if (candidates[i].votes >= max)  {
            max = candidates[i].votes;
            idWinner = i;
            fr[i] = max;
        } else {
            fr[i] = 0;
        }
    }
    for (size_t i = 0; i < candidate_count; i++)  {
        if (fr[i] == max)  {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
