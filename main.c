#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>


#define FILE_NAME root.bin;

enum operation { MD, MF, RD, RF, COPY, CUT, PASTE, WRITE, READ, CD, CD_BAK, DIR, ERROR, SAVE, EXIT };
#pragma pack(push,1)
typedef struct File {
    char name[10];
    char data[10];
    int numberOfFiles;
    struct File *next;
    struct File *previous;
}File;
#pragma pack(pop)



#pragma pack(push,1)
typedef struct Directory {
    char name[10];
    int numberOfDirectories;
    struct Directory* directories[1000];
    int numberOfFiles;
    File* files[1000];
}Directory;
#pragma pack(pop)
void readDirectories(FILE*, Directory*);
void writeName(FILE*, char[10]);
char* toBin(char*);
void writeFileTail(FILE*, File*);
int getNumberOfFilesTail(File*);
//int getTypeOfFirstWord(char*);
//int changeStringToInt(char*);
int getNumberOfDirectories(Directory);
void readFileTail(FILE*, File*);
void writeNumberOfDirectories(FILE*, int);
void writeDirectories(FILE*, Directory);
int getNumberOfFiles(Directory);
void writeNumberOfFiles(FILE*, int);
void writeFiles(FILE*, Directory);

void makeDirectory();
void makeFile();
void removeDirectory();
void removeFile();
void copyFile();
void saveDamp();
void cutFile();
void pasteFile();
void writeFile();
void readFile();
void openDirectory();
void openDirectoryBack();
void showDirectoryList();
void showFileList();

char* readName(FILE*);
char* readData(FILE*);
int readNumberOfDirectories(FILE*);
int readNumberOfFiles(FILE*);
void readFiles(FILE*, Directory*);
bool isFileName(char*);
bool isBin(char* input);
bool isTxt(char* input);

char directoryName;
char fileName;
char* data;

int getNumberOfFiles(Directory root) {
    int numberOfFiles = 0;
    for (int i = 0; i < 1000; i++) {
        if (root.files[i] != NULL) {
            numberOfFiles += 1;
        }
        else break;
    }
    return numberOfFiles;
}

void writeNumberOfFiles(FILE *fileBin, int numberOfFiles) {
    int ifError =(int)fwrite(&numberOfFiles, sizeof(int), 1, fileBin);
    if (ifError == -1) {
        printf("Error with writing number of Files %i\n", numberOfFiles);
    }
}

int readNumberOfFiles(FILE *fileBin) {
    int numberOfFiles;
    int ifError = (int)fread(&numberOfFiles, sizeof(int), 1, fileBin);
    if (ifError == -1) {
        printf("Error with reading number of Files %i\n", numberOfFiles);
    }
    return numberOfFiles;
}



char* readName(FILE *fileBin) {
    char* name;

    if (!(name = (char *)calloc(1, sizeof(char) * 10))) {
        printf("Error memory1");
    }
    int ifError = (int)fread(name, sizeof(char) * 10, 1, fileBin);
    if (ifError == -1) {
        printf("Error with reading name %s\n", name);
    }
    //else {
    //   printf("Name %s\n", name);
    //  }
    return name;
}

Directory* readFromFile() {
    printf("-------------Start reading damp--------------------\n");
    Directory *root;
    if (!(root = (Directory *)calloc(1, sizeof(Directory)))) {
        printf("Error memory");
    }

    FILE *fileBin ;//= (FILE*)malloc(sizeof(FILE*));
    fileBin = fopen("root0.bin", "r");
    if (fileBin == NULL) {
        printf("Error opening fileBin");
    }
    strcpy(root->name, readName(fileBin));
    if (strcmp(root->name, "") == 0) {
        strcpy(root->name, "root");
        return root;
    }
    root->numberOfDirectories = readNumberOfDirectories(fileBin);
    readDirectories(fileBin, root);
    root->numberOfFiles = readNumberOfFiles(fileBin);
    readFiles(fileBin, root);

    fclose(fileBin);
    return root;
}

void writeName(FILE *fileBin, char name[10]) {
    int ifError = (int)fwrite(name, sizeof(char) * 10, 1, fileBin);

    if (ifError == -1) {
        printf("Error with writing name %s\n", name);
    }
}

int getNumberOfDirectories(Directory root) {
    int numberOfDirectory = 0;
    for (int i = 0; i < 1000; i++) {
        if (root.directories[i] != NULL) {
            numberOfDirectory += 1;
        }
        else break;
    }
    return numberOfDirectory;
}

void writeNumberOfDirectories(FILE *fileBin, int numberOfDirectories) {
    int ifError = (int)fwrite(&numberOfDirectories, sizeof(int), 1, fileBin);
    if (ifError == -1) {
        printf("Error with writing number of Directory %i\n", numberOfDirectories);
    }
}

int readNumberOfDirectories(FILE *fileBin) {
    int numberOfDirectories;
    int ifError = (int)fread(&numberOfDirectories, sizeof(int), 1, fileBin);
    if (ifError == -1) {
        printf("Error with writing number of Directory %i\n", numberOfDirectories);
    }
    return numberOfDirectories;
}

void readDirectories(FILE *fileBin, Directory* root) {
    for (int i = 0; i < root->numberOfDirectories; i++) {
        if (!(root->directories[i] = (Directory *)calloc(1, sizeof(Directory)))) {
            printf("Error memory");
        }
        strcpy(root->directories[i]->name, readName(fileBin));
        root->directories[i]->numberOfDirectories = readNumberOfDirectories(fileBin);
        readDirectories(fileBin, root->directories[i]);
        root->directories[i]->numberOfFiles = readNumberOfFiles(fileBin);
        readFiles(fileBin, root->directories[i]);
    }
}

void readFiles(FILE *fileBin, Directory* root) {
    for (int i = 0; i < root->numberOfFiles; i++) {
        if (!(root->files[i] = (File *)calloc(1, sizeof(File)))) {
            printf("Error memory");
        }
        strcpy(root->files[i]->name, readName(fileBin));
        strcpy(root->files[i]->data, readData(fileBin));
        root->files[i]->numberOfFiles = readNumberOfFiles(fileBin);
        readFileTail(fileBin, root->files[i]);
    }
}

void writeDirectories(FILE *fileBin, Directory root) {
    for (int i = 0; i < root.numberOfDirectories; i++) {
        writeName(fileBin, root.directories[i]->name);
        root.directories[i]->numberOfDirectories = getNumberOfDirectories(*root.directories[i]);
        writeNumberOfDirectories(fileBin,root.directories[i]->numberOfDirectories);
        writeDirectories(fileBin, *root.directories[i]);
        root.directories[i]->numberOfFiles = getNumberOfFiles(*root.directories[i]);//ATTENTION
        writeNumberOfFiles(fileBin, root.directories[i]->numberOfFiles);
        writeFiles(fileBin, *root.directories[i]);
    }
}

void readFileTail(FILE *fileBin, File* head) {
    int number = head->numberOfFiles;
    for (int i = 0; i < number; i++) {
        File *file;
        if (!(file = (File *)calloc(1, sizeof(File)))) {
            printf("Error memory");
        }
        strcpy(file->data, readData(fileBin));
        head->next = file;
        head = file;
    }
}

void writeData(FILE *fileBin, char data[10]) {
    int ifError = (int)fwrite(data, sizeof(char) * 10, 1, fileBin);
    if (ifError == -1) {
        printf("Error with writing data %s\n", data);
    }
}

char* readData(FILE *fileBin) {
    char* data;
    if (!(data = (char *)calloc(1, sizeof(char) * 10))) {
        printf("Error memory");
    }
    int ifError = (int)fread(data, sizeof(char) * 10, 1, fileBin);
    if (ifError == -1) {
        printf("Error with reading name %s\n", data);
    }
    return data;
}

void writeFiles(FILE *fileBin, Directory root) {
    for (int i = 0; i < root.numberOfFiles; i++) {
        writeName(fileBin, root.files[i]->name);
        writeData(fileBin, root.files[i]->data);
        root.files[i]->numberOfFiles = getNumberOfFilesTail(root.files[i]);
        writeNumberOfFiles(fileBin, root.files[i]->numberOfFiles);
        writeFileTail(fileBin, root.files[i]);
    }
}

void writeFileTail(FILE *fileBin, File* file) {
    int number = file->numberOfFiles;
    if (file->numberOfFiles != 0) {
        file = file->next;
        for (int i = 0; i < number; i++) {
            writeData(fileBin, file->data);
            file = file->next;
        }
    }
}

int getNumberOfFilesTail(File* file) {
    int numberOfFileTail = 0;
    while (file->next) {
        numberOfFileTail += 1;
        file = file->next;
    }
    return numberOfFileTail;
}

//const char *root = "root";
const char *to = ">";
const char *separator = "/";
char path[1024];

Directory* cutFromDirectory;
char nameOfCatedFile[1024];
Directory* activDirectory;
File* copiedFile;

typedef struct Path {
    Directory* dir;
    struct Path* next;
    struct Path* prev;
} Path;

//Path *end;
//Directory* root;


void writeFile() {
    bool isFileExist = false;
    int globalI = 0;
    for (int i = 0; i < 1000; i++) {
        if (activDirectory->files[i] != NULL) {
            if (strcmp(activDirectory->files[i]->name, &fileName) == 0) {
                isFileExist = true;
                File *activ = activDirectory->files[i];
                while (activ->next != NULL) {
                    activ = activ->next;
                }



                for (int k = 0; k < 1024; k++) {

                    if (k % 10 == 0) {
                        File *next;
                        if (!(next = (File *)calloc(1, sizeof(File)))) {
                            printf("Error with memory 1\n");
                        }
                        activ->next = next;
                        next->previous = activ;
                        activ = next;
                    }
                    activ->data[k % 10] = data[k];
                    if (data[k + 1] == NULL) {
                        for (int index = k; k < 0; k--) {
                            data[index] = NULL;
                        }
                        break;
                    }
                }
                break;
            }
        }
    }

    if (!isFileExist) {
        for (int i = 0; i < 1000; i++) {
            if (activDirectory->files[i] == NULL) {
                if (!(activDirectory->files[i] = (File *)calloc(1, sizeof(File)))) {
                    printf("Error with memory 2\n");
                }
                strcpy(activDirectory->files[i]->name, &fileName);
                activDirectory->files[globalI]->next = activDirectory->files[globalI]->previous = NULL;
// File *next;

                File* activ;
                activ = activDirectory->files[globalI];

                for (int j = 0; j < 10; j++) {
                    if (data[j] == NULL) {
                        for (int index = j; j < 0; j--) {
                            data[index] = NULL;
                        }
                        break;
                    }

                    activ->data[j] = data[j];
                }

                for (int k = 10; k < 1024; k++) {
                    if (k % 10 == 0) {
                        File* next;
                        if (!(next = (File *)calloc(1, sizeof(File)))) {
                            printf("Error with memory 3\n");
                        }
                        activ->next = next;
                        next->previous = activ;
                        activ = next;
                    }
                    activ->data[k % 10] = data[k];

                    if (data[k + 1] == NULL) {
                        for (int index = k; k < 0; k--) {
                            data[index] = NULL;
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
}

char* toBin(char* data) {
    char* result;
    int* bin;
    bin = (int*)malloc(sizeof(int));
// printf("bin %i\n",(int) sizeof (bin));
// printf("data %i\n",(int) sizeof (data));
    result = (char*)malloc(sizeof(char));
//printf("result %i\n",(int) sizeof (result));
    for (int i = 0; i < (((int) sizeof(data)) / 2); i++) {
        bin[i] = data[i];
    }
    int v;
    for (int j = 0; j < ((int) sizeof(bin)) / 2; j++) {
        v = 128;
        for (int i = 1; i <= 8; i++) {
            if (bin[j] >= v) {
                strcpy(&result[8 * j - 1 + i], "1");
                bin[j] -= v;
            }
            else {
                strcpy(&result[8 * j - 1 + i], "0");
            }
            v /= 2;
        }
    }
    return result;
}

void readFile() {
    bool isFileDoesntExist = true;
    for (int i = 0; i < 1000; i++) {
        if (activDirectory->files[i] != NULL) {
            if (strcmp(activDirectory->files[i]->name, &fileName) == 0) {
                isFileDoesntExist = false;
                File *activ;
                activ = activDirectory->files[i];
                while (activ != NULL) {
                    printf("%s", activ->data);
                    activ = activ->next;
                }
            }
        }
    }
    if (isFileDoesntExist) {
        printf("File doesn't exist");
    }
    printf("\n");
}

void showFileList() {
    bool check = true;
    for (int i = 0; i < 1000; i++) {
        if (activDirectory->files[i] != NULL) {
            printf(" %s\n", activDirectory->files[i]->name);
            check = false;
        }
    }
    if (check) {
        printf("File list is empty\n");
    }
}

void showDirectoryList() {
    bool check = true;
    for (int i = 0; i < 1000; i++) {
        if (activDirectory->directories[i] != NULL) {
            printf(" <DIR> %s\n", activDirectory->directories[i]->name);
            check = false;
        }
    }

    if (check) {
        printf("Directory list is empty\n");
    }

    showFileList();
}

void makeDirectory() {
// printf("%s", directoryName);
    for (int i = 0; i < 1000; i++) {
        if (activDirectory->directories[i] != NULL) {
            if (strcmp(activDirectory->directories[i]->name, &directoryName) == 0) {
                printf("Directory with this name is already exist\n");
                return;
            }
        }
    }
    for (int i = 0; i < 1000; i++) {
        if (activDirectory->directories[i] == NULL) {
            printf("%d\n", i);
            if (!(activDirectory->directories[i] = (Directory *)calloc(1, sizeof(Directory)))) {
                printf("Error with memory 4\n");
            }
            if (!(*(activDirectory->directories[i]->name) = (char)calloc(1, sizeof(char)))) {
                printf("Error with memory 5\n");
            }

            strcpy(activDirectory->directories[i]->name, &directoryName);
            printf("%s\n", &directoryName);
            return;
            break;

        }
    }
}

void makeFile() {
    for (int i = 0; i < 1000; i++) {
        if (activDirectory->files[i] != NULL) {
            if (strcmp(activDirectory->files[i]->name, &fileName) == 0) {
                printf("File with this name is already exist\n");
                return;

            }
        }
        else {
            if (!(activDirectory->files[i] = (File *)calloc(1, sizeof(File)))) {
                printf("Error with memory 6\n");
            }
            strcpy(activDirectory->files[i]->name, &fileName);
            return;
        }
    }
}

void removeDirectory() {
    bool check = false;
    for (int i = 0; i < 100; i++) {
        if (activDirectory->directories[i] != NULL) {
            if (strcmp(activDirectory->directories[i]->name, &directoryName) == 0) {
                free(activDirectory->directories[i]);
                activDirectory->directories[i] = NULL;
                check = false;

                break;
            }
            else {
                check = true;
            }
        }
    }
    if (check) { printf("Directory with this name is already exist\n"); }
}

void removeFile() {
    bool check = false;
    for (int i = 0; i < 100; i++) {
        if (activDirectory->files[i] != NULL) {
            if (strcmp(activDirectory->files[i]->name, &fileName) == 0) {
                free(activDirectory->files[i]);
                activDirectory->files[i] = NULL;
                check = false;
                break;
            }
            else {
                check = true;
            }
        }
    }
    if (check) { printf("File with this name is already exist\n"); }
}

void writeToFile() {
    FILE *fileBin = (FILE*)malloc(sizeof(FILE*));
    fileBin = fopen("root.bin", "w+b");
    if (fileBin == 0) {
        printf("Error opening fileBin");
    }

    writeName(fileBin,  activDirectory->name);
    activDirectory->numberOfDirectories = getNumberOfDirectories(* activDirectory);
    writeNumberOfDirectories(fileBin,  activDirectory->numberOfDirectories);
    writeDirectories(fileBin, * activDirectory);
    activDirectory->numberOfFiles = getNumberOfFiles(* activDirectory);
    writeNumberOfFiles(fileBin,  activDirectory->numberOfFiles);
    writeFiles(fileBin, * activDirectory);

    fclose(fileBin);
}

void saveDamp() {

    writeToFile();

}
void saveDampQuickPig(){
    FILE *fileBin = (FILE*)malloc(sizeof(FILE*));
    fileBin = fopen("root2.bin", "w+b");
    if (fileBin == 0) {
        printf("Error opening fileBin");
    }
    for (int i =0 ; i<1000; i++){
        if(activDirectory->directories[i] != 0){
            //  printf("Error with writing )))))) \n");
            int ifError =(int)fwrite((activDirectory->directories[i]), sizeof(Directory*), 1, fileBin);
            if (ifError == -1) {
                printf("Error with writing )))))) ");
            }
        }
    }

    fclose(fileBin);
}
int main(int argc, char* argv[]) {

    if (!(activDirectory = (Directory *)calloc(1, sizeof(Directory)))) {
        printf("Error memory root");
    }
    activDirectory = readFromFile();

    for (int i = 0; i < 1000; i++) {
        if (!(directoryName = (char) calloc(1, sizeof(char)*10))) {

            printf("Error memory1");
        }

        sprintf(&directoryName, "%d", i);

        makeDirectory();
        if ((fileName = (char)calloc(1, sizeof(char)*10))) {
            printf("Error memory2");
        }
        sprintf(&fileName, "%s%s", &directoryName, ".txt");

    }

    saveDamp();
    saveDampQuickPig();
    return 0;
}



