#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int low = 32, high = 126;
const int range = high - low + 1;

enum opTypeEnum {
    ENCRYPTION = 1,
    DECRYPTION
};

bool checkInput(int,char**,opTypeEnum&);
void printMessage(char*);
void encryptFile(ifstream& in,ofstream& out,const string& key);
void decryptFile(ifstream& in,ofstream& out,const string& key);

int main(int argc,char** argv) {
    printf("\n");

    opTypeEnum operationType;
    if (checkInput(argc,argv,operationType) == false) {
        printMessage(argv[0]);
        return -1;
    }

    ifstream in(argv[2]);
    ofstream out(argv[3]);
    string key(argv[4]);

    for (int i=0;i < (int)key.size();++i) {
        key[i] %= range;
    }

    if (operationType == ENCRYPTION) {
        encryptFile(in,out,key);
        printf("Encryption successful!\n");
    }
    else {
        decryptFile(in,out,key);
        printf("Decryption successful!\n");
    }

    in.close();out.close();
    return 0;
}

bool checkInput(int argc,char** argv,opTypeEnum& operationType) {
    if (argc != 5) {
        printf("Invalid number of arguments!\n");
        return false;
    }

    if (argv[1][1] != '\0' || (argv[1][0] != '1' && argv[1][0] != '2')) {
        printf("Invalid operation!\n");
        return false;
    }

    int sz = strlen(argv[2]);
    if (strcmp(argv[2] + sz - 4,".txt") != 0) {
        printf("Invalid input file type!\n");
        return false;
    }

    sz = strlen(argv[3]);
    if (strcmp(argv[3] + sz - 4,".txt") != 0) {
        printf("Invalid output file type!\n");
        return false;
    }

    if (argv[1][0] == '1') {
        operationType = ENCRYPTION;

        FILE *f = fopen(argv[2],"r");

        if (f == NULL) {
            printf("Input file doesn't exist!\n");
            fclose(f);
            return false;
        }
        fclose(f);

        /*
        f = fopen(argv[3],"r");
        if (f != NULL) {
            printf("File already exists!\n");
            fclose(f);
            return false;
        }
        fclose(f);
        //*/
    }
    else {
        operationType = DECRYPTION;

        FILE *f = fopen(argv[2],"r");

        if (f == NULL) {
            printf("Input file doesn't exist!\n");
            fclose(f);
            return false;
        }

        /*
        f = fopen(argv[3],"r");
        if (f != NULL) {
            printf("File already exists!\n");
            fclose(f);
            return false;
        }
        fclose(f);
        //*/
    }

    return true;
}

void printMessage(char *name) {
    printf("Usage: %s <operation type> <if> <of> <key>\n\n",name);
    printf("- operation type = 1 if encryption is desired;\n");
    printf("<if> - full name of a local .txt file that is to be encrypted.\n");
    printf("<of> - full name of a local .txt file to store output.\n");
    printf("<key> - string that represents the key used for encryption.\n");
    printf("E.g.: %s 1 input.txt output.txt thisIsAKey\n\n",name);
    printf("- operation type = 2 if decryption is desired;\n");
    printf("<if> - full name of a local .txt file that is to be decrypted.\n");
    printf("<of> - full name of a local .txt file to store output.\n");
    printf("<key> - string that represents the key used for decryption.\n");
    printf("E.g.: %s 2 input.txt output.txt thisIsAKey\n\n",name);
}

void encryptFile(ifstream& in,ofstream& out,const string& key) {
    int idx = 0;

    char c = in.get();
    while (!in.fail()) {
        if (low <= c && c <= high) {

            c -= low;
            c = (c + key[idx]) % range;
            c += low;
        }
        ++idx;

        out<<(char)c;

        if (idx == key.length()) {
            idx = 0;
        }

        c = in.get();
    }
}

void decryptFile(ifstream& in,ofstream& out,const string& key) {
    int idx = 0;

    char c = in.get();
    while (!in.fail()) {
        if ((low <= c && c <= high)) {

            c -= low;
            c = (c - key[idx] + range) % range;
            c += low;
        }
        ++idx;

        out<<(char)c;

        if (idx == key.length()) {
            idx = 0;
        }

        c = in.get();
    }
}
