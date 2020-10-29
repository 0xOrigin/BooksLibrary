#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct booksData {
    int id;
    char name[60];
    int quantity;
};
int countlines, maxNumBooks=500;
void Insert_Book(struct booksData books[maxNumBooks], struct booksData booksCopy[maxNumBooks]);
int Delete_Book_byID(int id, struct booksData books[maxNumBooks], struct booksData booksCopy[maxNumBooks]);
int Search_Book_byID(int id,int lines,struct booksData books[maxNumBooks]);
void Search_Book_byNAME(char name[60],struct booksData booksCopy[maxNumBooks]);
void Display_Sorted_byNAME(struct booksData booksCopy[maxNumBooks]);
void Display_Unsorted(struct booksData books[maxNumBooks]);

int main(void){
    struct booksData books[maxNumBooks];
    struct booksData booksCopy[maxNumBooks];
    char current_char, check;
    FILE *fptr;
    if((fptr = fopen("books.txt", "r")) == NULL){
        system("cls||clear");
        printf("\t\t\tWelcome on Books Library\n");
        printf("[-]File Not found\n");
        printf("[-]The program has been terminated successfully.\n");
        return 0;
    }
    /********************************** To get the number of lines ******************************/
    while(!feof(fptr)){
        current_char = fgetc(fptr);
        if(current_char == '\n')
            ++countlines;
    }
    rewind(fptr);
    /*********************************** Reading data from file *****************************************/
    int cntname;
    for(int i=0;i<countlines;i++){
        fscanf(fptr, "%d ", &books[i].id);
        booksCopy[i].id = books[i].id;
        cntname = 0;
        check = fgetc(fptr);
        while(check != ';' && !feof(fptr)){
            books[i].name[cntname] = check;
            booksCopy[i].name[cntname] = check;
            ++cntname;
            check = fgetc(fptr);
        }
        fscanf(fptr, " %d\n", &books[i].quantity);
        booksCopy[i].quantity = books[i].quantity;
    }
    fclose(fptr);
    /*************************************   User menu   *********************************/
    char Qcontinue;
    do{
        int id;
        char choice,bookname[60];
        system("cls||clear");
        printf("\t\t\tWelcome on Books Library\n");
        printf("[-]Menu:\n");
        printf("\t[1] - Insert a book.\n");
        printf("\t[2] - Delete a book by ID.\n");
        printf("\t[3] - Search a book by ID.\n");
        printf("\t[4] - Search a book by name.\n");
        printf("\t[5] - Display all books sorted by name.\n");
        printf("\t[6] - Display all books unsorted.\n");
        do{
            printf("[+]Choose a number(0 to terminate the program): ");
            scanf(" %c", &choice);
            switch(choice){
                case '1':
                    Insert_Book(books, booksCopy);
                    break;
                case '2':
                    printf("\n[+]Enter book id to delete: ");
                    scanf("%d", &id);
                    Delete_Book_byID(id, books, booksCopy);
                    break;
                case '3':
                    printf("\n[+]Enter book id to search: ");
                    scanf("%d", &id);
                    Search_Book_byID(id, countlines-1, books);
                    break;
                case '4':
                    printf("\n[+]Enter book name to search: ");
                    getchar();
                    gets(bookname);
                    Search_Book_byNAME(bookname, booksCopy);
                    break;
                case '5':
                    if(countlines == 0){
                        printf("\n[-]There are no books to Display.\n");
                        break;
                    }
                    Display_Sorted_byNAME(booksCopy);
                    break;
                case '6':
                    if(countlines == 0){
                        printf("\n[-]There are no books to Display.\n");
                        break;
                    }
                    Display_Unsorted(books);
                    break;
                case '0':
                    printf("[-]The program has been terminated successfully.\n");
                    return 0;
                default:
                    printf("[-]Enter a valid choice.\n");
                    break;
            }
        }while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6');
        printf("\n[+]Do you want to perform any additional operation? (y/n): ");
        scanf(" %c", &Qcontinue);
    }while(Qcontinue == 'Y' || Qcontinue == 'y');
    printf("[-]The program has been terminated successfully.\n");
    return 0;
}

void Insert_Book(struct booksData books[maxNumBooks], struct booksData booksCopy[maxNumBooks]){
    int id, quantity;
    char name[60];
    printf("\n[+]Enter id: ");
    scanf("%d", &id);
    books[countlines].id = id;
    booksCopy[countlines].id = id;
    printf("[+]Enter book name: ");
    getchar();
    gets(name);
    strcpy(books[countlines].name, name);
    strcpy(booksCopy[countlines].name, name); 
    printf("[+]Enter quantity: ");
    scanf("%d", &quantity);
    books[countlines].quantity = quantity;
    booksCopy[countlines].quantity = quantity;
    FILE *fptr;
    fptr = fopen("books.txt", "a");
    fprintf(fptr, "%d ", books[countlines].id);
    fprintf(fptr, "%s;", books[countlines].name);
    fprintf(fptr, " %d\n", books[countlines].quantity);
    fclose(fptr);
    ++countlines;
    printf("\n[-]The book has been inserted successfully.\n");
}

int Delete_Book_byID(int id, struct booksData books[maxNumBooks], struct booksData booksCopy[maxNumBooks]){
    int foundPos=0, foundFlag=1, changeStructValue=0;
    for(int i=0;i<countlines;i++)
        if(books[i].id == id){
            foundPos = i;
            foundFlag = 0;
        }
    if(foundFlag){
        printf("\n[-]The book not found.\n");
        return 0;
    }
    /**************** Changing the data after deletion  ***************/
    FILE *fptr;
    fptr = fopen("books.txt", "w");
    for(int i=0;i<countlines;i++){
        if(i == foundPos)
            changeStructValue = 1;
        if(changeStructValue){
            books[i].id = books[i+1].id;
            strcpy(books[i].name, books[i+1].name);
            books[i].quantity = books[i+1].quantity; 
        }
        if(i != countlines-1){
            fprintf(fptr, "%d ", books[i].id);
            fprintf(fptr, "%s;", books[i].name);
            fprintf(fptr, " %d\n", books[i].quantity);
        }
    }
    fclose(fptr);
    --countlines;
    for(int i=0;i<countlines;i++){
        booksCopy[i].id = books[i].id;
        strcpy(booksCopy[i].name, books[i].name);
        booksCopy[i].quantity = books[i].quantity;
    }
    printf("\n[-]The book has been deleted successfully.\n");
    return 0;
}

int Search_Book_byID(int id,int lines,struct booksData books[maxNumBooks]){
    if(lines == -1){
        printf("\n[-]Not found.\n");
        return 0;
    }
    if(books[lines].id == id){
        printf("\n[-]Found!");
        printf("\n\tID\t\tBook name\t\t\t\t\t\t\tQuantity\n");
        printf("\t%-10d\t%-60s\t%d\n", books[lines].id, books[lines].name, books[lines].quantity);
        return 0;
    }
    return Search_Book_byID(id,--lines,books);
}

void Search_Book_byNAME(char name[60],struct booksData booksCopy[maxNumBooks]){
    for(int i=0;i<countlines;i++)
        for(int j=i+1;j<countlines;j++){
            char tempSort[60];
            int tempforInt;
            if(strcmp(booksCopy[i].name, booksCopy[j].name) > 0){
                strcpy(tempSort, booksCopy[i].name);
                strcpy(booksCopy[i].name, booksCopy[j].name);
                strcpy(booksCopy[j].name, tempSort);
                tempforInt = booksCopy[i].id;
                booksCopy[i].id = booksCopy[j].id;
                booksCopy[j].id = tempforInt;
                tempforInt = booksCopy[i].quantity;
                booksCopy[i].quantity = booksCopy[i+1].quantity;
                booksCopy[j].quantity = tempforInt;
            }
        }
    /********* Binary Search *************/
    int middle, low=0, high=countlines-1, foundFlag=0;
    while(low <= high){
        middle = (low + high) / 2;
        if(strcmp(name, booksCopy[middle].name) == 0){
            foundFlag = 1;
            break;
        }
        else if(strcmp(name, booksCopy[middle].name) > 0)
            high = middle - 1;
        else
            low = middle + 1;
    }
    if(foundFlag){
        printf("\n[-]Found!");
        printf("\n\tID\t\tBook name\t\t\t\t\t\t\tQuantity\n");
        printf("\t%-10d\t%-60s\t%d\n", booksCopy[middle].id, booksCopy[middle].name, booksCopy[middle].quantity);
    }
    else
        printf("\n[-]Not found.\n");
}

void Display_Sorted_byNAME(struct booksData booksCopy[maxNumBooks]){
    for(int i=0;i<countlines;i++)
        for(int j=i+1;j<countlines;j++){
            char tempSort[60];
            int tempforInt;
            if(strcmp(booksCopy[i].name, booksCopy[j].name) > 0){
                strcpy(tempSort, booksCopy[i].name);
                strcpy(booksCopy[i].name, booksCopy[j].name);
                strcpy(booksCopy[j].name, tempSort);
                tempforInt = booksCopy[i].id;
                booksCopy[i].id = booksCopy[j].id;
                booksCopy[j].id = tempforInt;
                tempforInt = booksCopy[i].quantity;
                booksCopy[i].quantity = booksCopy[i+1].quantity;
                booksCopy[j].quantity = tempforInt;
            }
        }
    printf("\n\tNo.\tID\t\tBook name\t\t\t\t\t\t\tQuantity\n");
    for(int i=0;i<countlines;i++)
        printf("\t%03d\t%-10d\t%-60s\t%d\n", i+1, booksCopy[i].id, booksCopy[i].name, booksCopy[i].quantity);
}

void Display_Unsorted(struct booksData books[maxNumBooks]){
    printf("\n\tNo.\tID\t\tBook name\t\t\t\t\t\t\tQuantity\n");
    for(int i=0;i<countlines;i++)
        printf("\t%03d\t%-10d\t%-60s\t%d\n", i+1, books[i].id, books[i].name, books[i].quantity);
}