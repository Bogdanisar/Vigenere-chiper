#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>

#if 1
#define pv(x) cout<<#x<<" = "<<x<<"; ";cout.flush()
#define pn cout<<endl
#else
#define pv(x)
#define pn
#endif

using namespace std;
ifstream in("input.in");
ofstream out("output.out");

#define pb push_back
#define ui unsigned int
const int NMax = 1e6 + 5;
const int low = 32, high = 126;
const int range = high - low + 1;

void doEncrypt();
void doDecrypt();
void encryptFile(ifstream& in,ofstream& out,const string& key);
void decryptFile(ifstream& in,ofstream& out,const string& key);

int main() {
    bool quit = false;

    while (!quit) {
        printf("Vigenere Encryption / Decryption Program:\n");
        printf("What option would you like to choose?\n1: Encrypt;\n2: Decrypt;\n3: Quit;\n");
        printf("Please enter your choice (1,2,3): ");

        char option;
        cin>>option;
        switch (option) {
            case '1': {
                doEncrypt();
                break;
            }
            case '2': {
                doDecrypt();
                break;
            }
            case '3': {
                quit = true;
                break;
            }
            default: {
                system("CLS");
                printf("\nThat is not a valid option!\n\n");
            }
        }
    }

    in.close();out.close();
    return 0;
}

void doEncrypt() {
    system("CLS");
    printf("You have chosen to do an encryption.\n");

    string inputPath;
    ifstream in;
        while (true) {
        printf("\nChoose 1 to select an input file for encryption or 2 to cancel the process: ");
        char option;
        cin>>option;
        if (option == '2') {
            system("CLS");
            printf("\nEncryption was stopped.\n\n");
            return;
        }
        if (option != '1') {
            printf("\nPlease enter a valid option!\n");
            continue;
        }

        printf("\nPlease enter the full path of the file you wish to encrypt:\n");
        getline(cin,inputPath);
        getline(cin,inputPath);
        in.open(inputPath);

        if (!in.fail()) {
            printf("Path is correct!\n");
            break;
        }

        printf("Can't find file at the given path\n");
    }

    string outputName;
    while (true) {
        printf("\nChoose 1 to select an output file for encryption or 2 to cancel the process: ");
        char option;
        cin>>option;
        if (option == '2') {
            system("CLS");
            printf("\nEncryption was stopped.\n\n");
            return;
        }
        if (option != '1') {
            printf("\nPlease enter a valid option!\n");
            continue;
        }

        printf("\nPlease enter a valid file name:\n");
        getline(cin,outputName);
        getline(cin,outputName);
        out.open(outputName);

        bool allLetters = true;
        for (char character : outputName) {
            if (!('a' <= character && character <= 'z')) {
                allLetters = false;
                break;
            }
        }

        if (allLetters) {
            printf("\nThe name is valid!\n");
            break;
        }

        printf("The given name is invalid\n\n");
    }
    outputName += ".out";
    cout<<"Output file is: "<<outputName<<"\n\n";
    ofstream out(outputName);

    string key;
    printf("Please enter an encryption key containing english letters:\n");
    getline(cin,key);

    for (char& character : key) {
        character %= range;
    }

    encryptFile(in,out,key);
    in.close();
    out.close();

    system("CLS");
    printf("\nEncryption was successful!\n\n");
}

void doDecrypt() {
    system("CLS");
    printf("You have chosen to do a decryption.\n");

    string inputPath;
    ifstream in;
        while (true) {
        printf("\nChoose 1 to select an input file for decryption or 2 to cancel the process: ");
        char option;
        cin>>option;
        if (option == '2') {
            system("CLS");
            printf("\nDecryption was stopped.\n\n");
            return;
        }
        if (option != '1') {
            printf("\nPlease enter a valid option!\n");
            continue;
        }

        printf("\nPlease enter the full path of the file you wish to decrypt:\n");
        getline(cin,inputPath);
        getline(cin,inputPath);
        in.open(inputPath);

        if (!in.fail()) {
            printf("Path is correct!\n");
            break;
        }

        printf("Can't find file at the given path\n");
    }

    string outputName;
    while (true) {
        printf("\nChoose 1 to select an output file for decryption or 2 to cancel the process: ");
        char option;
        cin>>option;
        if (option == '2') {
            system("CLS");
            printf("\nDecryption was stopped.\n\n");
            return;
        }
        if (option != '1') {
            printf("\nPlease enter a valid option!\n");
            continue;
        }

        printf("\nPlease enter a valid file name:\n");
        getline(cin,outputName);
        getline(cin,outputName);
        out.open(outputName);

        bool allLetters = true;
        for (char character : outputName) {
            if (!('a' <= character && character <= 'z')) {
                allLetters = false;
                break;
            }
        }

        if (allLetters) {
            printf("\nThe name is valid!\n");
            break;
        }

        printf("The given name is invalid\n\n");
    }
    outputName += ".out";
    cout<<"Output file is: "<<outputName<<"\n\n";
    ofstream out(outputName);

    string key;
    printf("Please enter a decryption key containing english letters:\n");
    getline(cin,key);

    for (char& character : key) {
        character %= range;
    }

    decryptFile(in,out,key);
    in.close();
    out.close();

    system("CLS");
    printf("\nDecryption was successful!\n\n");
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
