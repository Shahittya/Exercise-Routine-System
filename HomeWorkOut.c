#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Userauth {
    char username[20];
    char password[10];
};

struct Exercise {
    int day;
    char name[50];
    char type[20];
    int duration;
    struct Exercise *next;
};

struct Cardio {
    int distance;
    int speed;
};

struct Strength {
    int sets;
    int reps;
    float weight;
};

struct Notes {
    char data[100];
    struct Notes *next;
};

struct User {
    char name[30];
    int age;
    float height;
    float weight;
    struct User *ptrnext;
    struct Userauth uauth;
    struct Exercise *exercise;
    struct Cardio *cardio;
    struct Strength *strength;
   struct Notes *notesHead;
    struct Notes *notesTail;
};

struct User *headptr = NULL, *newptr, *currentptr, *delnode;
//user count will increase
int usercount = 0;

void signIn();
int login(char username[20], char password[10]);
void UserDetails(char username[20], char password[20]);
void edit(char username[20], char password[20]);
void routine(char username_1[20], char password_1[10]);
void see_routine(char username_1[20], char password_1[10]);
void push_exercise(struct User *user, struct Exercise *new_exercise);
void pop_exercise(struct User *user);
void searchUser();
void ShowUsers();
void Usernotes(char username_1[20], char password_1[10]);
void displayNotes(struct User *user);
void dequeue(struct User *user);
void clearConsole()
{
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

int main() {
    while (1) {

        int choice;
        printf("\n------------------WELCOME USER------------------\n");
        printf("1. Sign Up\n");
        printf("2. Login\n");
        scanf("%d", &choice);
        if (choice == 1) {
            signIn();

        } else if (choice == 2) {
            char username_1[20];
            char password_1[10];
            printf("Enter username: \n");
            scanf("%s", username_1);
            printf("Enter password: \n");
            scanf("%s", password_1);
            int auth = 0;
            if (login(username_1, password_1) == 1) {
                printf("Login Successful\n\n");
                auth = 1;
                printf("\n--------------Welcome %s--------------\n", username_1);
                while (auth == 1) {
                    int decision;
                    printf("\nChoose Any Option\n1.Show Recommended Exercise\n2.Create an exercise routine\n3.Show Routine\n4.See User Details\n5.Edit User Details\n6.Search User\n7.See All Active Users\n8.Notes\n9.Logout\n");
                    scanf("%d", &decision);
                    if (decision == 1) {

                        printf("\n-------------Recommendation-------------\n");
                        currentptr = headptr;
                        while (currentptr != NULL) {
                            if (strcmp(username_1, currentptr->uauth.username) == 0) {
                                float bmi = currentptr->weight / (currentptr->height * currentptr->height);
                                printf("Your BMI (Body Mass Index) is %f\n", bmi);
                                if (bmi <= 18.5) {
                                    printf("Resistance exercises like weightlifting, bodyweight exercises (push-ups, squats, lunges), and resistance band workouts.\n");
                                    printf("Focus on strength training to build muscle mass.\n");
                                    printf("\n");
                                } else if (bmi >= 18.5 && bmi <= 24.9) {
                                    printf("Aim for a balanced exercise routine that includes cardiovascular exercises, strength training, and flexibility exercises.\n");
                                    printf("Cardiovascular exercises such as running, cycling, swimming, brisk walking, or dancing to maintain cardiovascular health.\n");
                                    printf("\n");
                                } else if (bmi >= 25 && bmi <= 29.9) {
                                    printf("Focus on both cardiovascular exercises to burn calories and strength training to build muscle and boost metabolism.\n");
                                    printf("High-intensity interval training (HIIT) to burn calories and improve cardiovascular fitness.\n");
                                    printf("\n");
                                } else if (bmi >= 30.0) {
                                    printf("Emphasize low-impact cardiovascular exercises to reduce stress on joints while still burning calories, such as swimming, cycling, or using an elliptical machine.\n");
                                    printf("Strength training exercises focusing on large muscle groups to increase calorie burn and improve muscle mass.\n");
                                    printf("\n");
                                } else {
                                    printf("Something Went Wrong!!\n");
                                }
                                break;
                            }
                            currentptr = currentptr->ptrnext;
                        }
                    } else if (decision == 2) {
                        routine(username_1, password_1);

                    } else if (decision == 3) {
                        see_routine(username_1, password_1);
                    } else if (decision == 4) {
                        UserDetails(username_1, password_1);

                    } else if (decision == 5) {
                        edit(username_1, password_1);
                    } else if (decision == 6) {
                        searchUser();
                    } else if (decision == 7) {
                        ShowUsers();
                    } else if (decision == 8) {
                        Usernotes(username_1, password_1);
                    } else if (decision == 9) {
                        printf("\n");
                        printf("Logged Out Successfully\n");
                        auth = 0;
                    } else {
                        printf("Input Error\n");
                    }
                }
            } else {
                printf("\nLogin Error!!\n");
            }
        } else {
            printf("Input Error\n");
        }
    }

}

void signIn() {
    newptr = (struct User *)malloc(sizeof(struct User));
    printf("Enter your full name:\n");
    getchar();
    fgets(newptr->name, sizeof(newptr->name), stdin);
    newptr->name[strcspn(newptr->name, "\n")] = '\0';
    printf("Enter your age:\n");
    scanf("%d", &newptr->age);
    printf("Enter your height:(in meter)\n");
    scanf("%f", &newptr->height);
    printf("Enter your weight(in kilograms)\n");
    scanf("%f", &newptr->weight);
    printf("Set a username:\n");
    scanf("%s", newptr->uauth.username);
    printf("Set a password:\n");
    scanf("%s", newptr->uauth.password);
    printf("\n\nUser Added Successfully!!\n");
    usercount++;

    newptr->exercise = NULL;
    newptr->cardio = NULL;
    newptr->strength = NULL;
    newptr->notesHead = NULL;
    newptr->notesTail = NULL;

    if (headptr == NULL) {
        headptr = newptr;
        newptr->ptrnext = NULL;
    } else {
        currentptr = headptr;
        while (currentptr->ptrnext != NULL) {
            currentptr = currentptr->ptrnext;
        }
        currentptr->ptrnext = newptr;
        newptr->ptrnext = NULL;
    }

}

int login(char username[20], char password[10]) {
    currentptr = headptr;
    while (currentptr != NULL) {
        if (strcmp(currentptr->uauth.username, username) == 0 && strcmp(currentptr->uauth.password, password) == 0) {
            return 1;
        }
        currentptr = currentptr->ptrnext;
    }
    return 0;
}

void UserDetails(char username[20], char password[20]) {
    clearConsole();
    currentptr = headptr;
    while (currentptr != NULL) {
        if (strcmp(username, currentptr->uauth.username) == 0 && strcmp(password, currentptr->uauth.password) == 0) {
            printf("\n");
            printf("--------------- User Details ---------------\n");
            printf("Full Name: %s\n", currentptr->name);
            printf("Age: %d\n", currentptr->age);
            printf("Height: %.2f meters\n", currentptr->height);
            printf("Weight: %.2f kgs\n", currentptr->weight);
            break;
        }
        currentptr = currentptr->ptrnext;
    }
}


void edit(char username[20], char password[20]) {
    struct User *currentptr = headptr; // implementing a passing structure in a function
    clearConsole();
    while (currentptr != NULL) {
            if (strcmp(username, currentptr->uauth.username) == 0 && strcmp(password, currentptr->uauth.password) == 0) {
                int choice;
    printf("\n-------------------Edit Section-------------------\n");
    printf("Do you want to edit your name?\n1.Yes\n2.No\n");
    scanf("%d", &choice);
    if (choice == 1) {
            printf("Edit Name:\n");
    getchar(); // To consume the newline left by previous scanf
    fgets(currentptr->name, sizeof(currentptr->name), stdin);
    currentptr->name[strcspn(currentptr->name, "\n")] = '\0';
}



        printf("Do you want to edit your age?\n1.Yes\n2.No\n");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Edit Age:\n");
            scanf("%d", &currentptr->age);
        }

        printf("Do you want to edit your weight?\n1.Yes\n2.No\n");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Edit Weight\n");
            scanf("%f", &currentptr->weight);
        }

        printf("Do you want to edit your height?\n1.Yes\n2.No\n");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Edit Height:\n");
            scanf("%f", &currentptr->height);
        }

        printf("\nChanges Applied Successfully!!\n");
    }
    currentptr = currentptr->ptrnext;
}

}

void pop_exercise(struct User *user) {
if (user->exercise == NULL) {
printf("\n");
printf("No exercises to pop.\n");
return;
}
struct Exercise *delnode = user->exercise; // implementing a passing structure in a function
user->exercise = user->exercise->next;
free(delnode);
printf("\n");
printf("Exercise popped successfully.\n");
}

void routine(char username_1[20], char password_1[10]) {
    clearConsole();
    currentptr = headptr;
    while (currentptr != NULL) {
        if (strcmp(username_1, currentptr->uauth.username) == 0 && strcmp(password_1, currentptr->uauth.password) == 0) {
            int choice;
            printf("Choose exercise type:\n1. Cardio\n2. Strength\n");
            scanf("%d", &choice);

            struct Exercise *new_exercise = (struct Exercise *)malloc(sizeof(struct Exercise));
            new_exercise->next = NULL;
            printf("\n");
            printf("Enter exercise name:\n");
            getchar();
            fgets(new_exercise->name, sizeof(new_exercise->name), stdin);
            new_exercise->name[strcspn(new_exercise->name, "\n")] = '\0';
            printf("Enter day of exercise (1-7):\n");
            scanf("%d", &new_exercise->day);
            printf("Enter duration (in minutes):\n");
            scanf("%d", &new_exercise->duration);

            if (choice == 1) {
                strcpy(new_exercise->type, "Cardio");
                struct Cardio *new_cardio = (struct Cardio *)malloc(sizeof(struct Cardio));
                printf("Enter distance (in km):\n");
                scanf("%d", &new_cardio->distance);
                printf("Enter speed (in km/h):\n");
                scanf("%d", &new_cardio->speed);
                new_exercise->next = currentptr->exercise;
                currentptr->exercise = new_exercise;
                currentptr->cardio = new_cardio;
            } else if (choice == 2) {
                strcpy(new_exercise->type, "Strength");
                struct Strength *new_strength = (struct Strength *)malloc(sizeof(struct Strength));
                printf("Enter sets:\n");
                scanf("%d", &new_strength->sets);
                printf("Enter reps per set:\n");
                scanf("%d", &new_strength->reps);
                printf("Enter weight (in kg):\n");
                scanf("%f", &new_strength->weight);
                new_exercise->next = currentptr->exercise;
                currentptr->exercise = new_exercise;
                currentptr->strength = new_strength;
            } else {
                printf("Invalid choice.\n");
                free(new_exercise);
            }

        }
        currentptr = currentptr->ptrnext;
    }
}

void see_routine(char username_1[20], char password_1[10]) {
    clearConsole();
    currentptr = headptr;
    while (currentptr != NULL) {
        if (strcmp(username_1, currentptr->uauth.username) == 0 && strcmp(password_1, currentptr->uauth.password) == 0) {
            struct Exercise *exercise = currentptr->exercise;
            if (exercise == NULL) {
                printf("No exercise routine found.\n");
                return;
            }
            printf("----------Exercise Routine:----------\n");
            printf("\n");
            while (exercise != NULL) {
                printf("Day: %d\nName: %s\nType: %s\nDuration: %d minutes\n", exercise->day, exercise->name, exercise->type, exercise->duration);

                if (strcmp(exercise->type, "Cardio") == 0) {
                    printf("Cardio Details:\nDistance: %d km\nSpeed: %d km/h\n", currentptr->cardio->distance, currentptr->cardio->speed);
                    printf("\n");
                } else if (strcmp(exercise->type, "Strength") == 0) {
                    printf("Strength Details: Sets: %d\nReps per set: %d\nWeight: %.2f kg\n", currentptr->strength->sets, currentptr->strength->reps, currentptr->strength->weight);
                    printf("\n");
                }


                exercise = exercise->next;
            }
                        printf("Do you want to POP the last added exercise\n1.Yes\n2.No\n");
        int choice1;
        scanf("%d",&choice1);
        if(choice1==1)
        {
            pop_exercise(currentptr);
        }

            break;
        }
        currentptr = currentptr->ptrnext;
    }
}
//linear squential search
void searchUser() {

    char username[20];
    printf("Enter username to search:\n");
    scanf("%s", username);
    currentptr = headptr;
    while (currentptr != NULL) {
        if (strcmp(username, currentptr->uauth.username) == 0) {
            printf("\n");
            printf("User found:\n");
            printf("Full Name: %s\n", currentptr->name);
            printf("Age: %d\n", currentptr->age);
            printf("Height: %.2f meters\n", currentptr->height);
            printf("Weight: %.2f kgs\n", currentptr->weight);
            return;
        }
        currentptr = currentptr->ptrnext;
    }
    printf("User not found.\n");
}

//selection sort-see all users
void ShowUsers()
{
    int smallest;
    struct User *currentptr=headptr;
    struct User *users[usercount];
    for(int i=0;i<usercount;i++)
        {
            users[i]=currentptr;
    currentptr=currentptr->ptrnext;
}
for(int i=0;i<usercount;i++)
{
    smallest=i;
    for(int j=i+1;j<usercount;j++)
{
    if(users[j]->age<users[smallest]->age)
{
    smallest=j;
}
}
   struct User *temp=users[i];
   users[i]=users[smallest];
   users[smallest]=temp;
}
   printf("\nTotal Users: %d\n", usercount);
   printf("\n");
 for(int i=0;i<usercount;i++)
{
    printf("\n");
    printf("User Full Name: %s\n",users[i]->name);
    printf("User Age: %d\n",users[i]->age);
    printf("User Name %s\n",users[i]->uauth.username);
    printf("User Height %.2f meters\n",users[i]->height);
    printf("User Weight %.2f kilograms\n",users[i]->weight);
    printf("\n");
    printf("\n");
}
searchUser();
}
//this part is notes
void displayNotes(struct User *user) {
    clearConsole();
    struct Notes *currentNote = user->notesHead;
    if (currentNote == NULL) {
        printf("No notes available.\n");
        return;
    }
    printf("Notes:\n");
    while (currentNote != NULL) {
            printf("\n");
        printf("- %s\n", currentNote->data);
        currentNote = currentNote->next;
    }
}

void enqueue(struct User *user, char *noteData) {
    struct Notes *newNote = (struct Notes *)malloc(sizeof(struct Notes));
    strcpy(newNote->data, noteData);
    newNote->next = NULL;

    if (user->notesTail == NULL) {
        user->notesHead = user->notesTail = newNote;
    } else {
        user->notesTail->next = newNote;
        user->notesTail = newNote;
    }
}

void dequeue(struct User *user) {
    if (user->notesHead == NULL) {
        printf("No notes to dequeue.\n");
        return;
    }

    struct Notes *delNote = user->notesHead;
    user->notesHead = user->notesHead->next;

    if (user->notesHead == NULL) {
        user->notesTail = NULL;
    }

    free(delNote);
    printf("Note dequeued successfully.\n");
}

void Usernotes(char username_1[20], char password_1[10]) {
    clearConsole();
    struct User *currentptr = headptr;
    while (currentptr != NULL) {
        if (strcmp(username_1, currentptr->uauth.username) == 0 && strcmp(password_1, currentptr->uauth.password) == 0) {
            int choice;
            printf("\n--------------NOTES--------------\n");
            printf("1. Add a note\n");
            printf("2. Dequeue a note\n");
            scanf("%d", &choice);
            getchar(); // To consume the newline left by previous scanf

            if (choice == 1) {
                char noteData[100];
                printf("Enter your note:\n");
                fgets(noteData, sizeof(noteData), stdin);
                noteData[strcspn(noteData, "\n")] = '\0';
                enqueue(currentptr, noteData);
                printf("Note added successfully.\n");
                displayNotes(currentptr);
            } else if (choice == 2) {
                dequeue(currentptr);
                displayNotes(currentptr);
            } else {
                printf("Invalid choice.\n");
            }
            return;
        }
        currentptr = currentptr->ptrnext;
    }
    printf("User not found or incorrect password.\n");
}


