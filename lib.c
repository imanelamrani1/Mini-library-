#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>   // mkdir
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main() {
    char libraryName[256];

    printf("******************************************\n");
    printf("                                          \n");
    printf("Welcome To Mini Library Management System.\n");
    printf("                                          \n");
    printf("******************************************\n\n");

    // Demander le nom de la bibliothèque
    printf("Please enter the name of the library: ");
    if (fgets(libraryName, sizeof(libraryName), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    // Retirer le saut de ligne à la fin
    libraryName[strcspn(libraryName, "\n")] = 0;

    // Créer le dossier principal
    if (mkdir(libraryName, 0755) != 0) {
        if (errno == EEXIST) {
            printf("Directory '%s' already exists.\n", libraryName);
        } else {
            perror("Error creating main directory");
            return 1;
        }
    }

    // Construire les chemins des sous-dossiers
    char booksDir[300];
    char studentsDir[300];
    snprintf(booksDir, sizeof(booksDir), "%s/books", libraryName);
    snprintf(studentsDir, sizeof(studentsDir), "%s/students", libraryName);

    // Créer les sous-dossiers
    if (mkdir(booksDir, 0755) != 0 && errno != EEXIST) {
        perror("Error creating books directory");
        return 1;
    }
    if (mkdir(studentsDir, 0755) != 0 && errno != EEXIST) {
        perror("Error creating students directory");
        return 1;
    }

    // Créer les fichiers nécessaires
    char bookListFile[350];
    char studentListFile[350];
    snprintf(bookListFile, sizeof(bookListFile), "%s/bookList.txt", booksDir);
    snprintf(studentListFile, sizeof(studentListFile), "%s/studentList.txt", studentsDir);

    FILE *fp;

    fp = fopen(bookListFile, "w");
    if (fp == NULL) {
        perror("Error creating bookList.txt");
        return 1;
    }
    fclose(fp);

    fp = fopen(studentListFile, "w");
    if (fp == NULL) {
        perror("Error creating studentList.txt");
        return 1;
    }
    fclose(fp);

    printf("Your library %s has been created!\n", libraryName);

    return 0;
}

