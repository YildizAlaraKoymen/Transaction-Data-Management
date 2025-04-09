#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DO NOT CHANGE DATA STRUCTURE
struct Customer {
    char name[81];
    int transactions;
    int items_purchased;
    float amount_paid;
};

typedef struct Customer customer;

//DO NOT CHANGE FUNCTION PROTOTYPES
void menu();
void printCustomers(customer *, int);
int countCustomers(FILE*);
void readTransactions(FILE*, customer* ,int);
void heapify(customer*, int, int, int);
void heapSort(customer*, int,int);

//DO NOT CHANGE THE main FUNCTION
int main() {
    FILE *inFile;
    int no_of_customers = 0;
    customer *customers;

    inFile = fopen("transactions.txt", "r");
    if (inFile == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }
    no_of_customers = countCustomers(inFile);
    printf("There are %d unique customers\n", no_of_customers);

    customers = (customer*) malloc(no_of_customers * sizeof (customer));
    fclose(inFile);
    inFile = fopen("transactions.txt", "r");
    if (inFile == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }

    readTransactions(inFile, customers, no_of_customers);
    if (customers == NULL) {
        printf("\nCustomers have NOT been read successfully!\n");
        exit(1);
    }
    printCustomers(customers, no_of_customers);

    char command = 0;
    int exit = 0;
    while (exit != 1) {
        menu();
        printf("\nCommand: ");
        fflush(stdin);
        scanf("%c", &command);

        if (command == '1' || command == '2' || command == '3' || command == '4') {
            heapSort(customers, no_of_customers, command - '0');
            printCustomers(customers, no_of_customers);
        }
        else if (command == '5'){
            exit = 1;
            printf("Goodbye!\n");
        }
        else{
            printf("Please enter a valid command!\n");
        }
    }
    free(customers);
    return 0;
}

//DO NOT CHANGE THE menu FUNCTION
void menu () {
    printf("Please choose one of the following options:\n"
           "(1) Display customers sorted by number of transactions\n"
           "(2) Display customers sorted by number of items purchased\n"
           "(3) Display customers sorted by total amount paid\n"
           "(4) Display customers sorted by average amount paid per transaction\n"
           "(5) Exit\n");
}

//DO NOT CHANGE THE printCustomers FUNCTION

void printCustomers (customer* customers, int no_of_customers) {
    printf("List of customers:\n");
    int i;
    for (i = 0; i < no_of_customers; ++i) {
        printf("Name: %s, number of transactions = %d, number of items = %d, total amount paid = %.2f,"
               " average amount paid per transaction = %.2f\n",
               customers[i].name, customers[i].transactions, customers[i].items_purchased, customers[i].amount_paid,
               customers[i].amount_paid/customers[i].transactions);
    }
}

int countCustomers (FILE *inFile){

    rewind(inFile);
    char names[10][81];
    char firstline[200];

    char name[81];
    double transaction_ID;
    char transaction_time[81];
    char item_description[81];
    int items_purchased;
    float amount_paid;
    char country[81];

    int elements = 0;
    int i;

    fscanf(inFile, "%s\n", firstline);

    while(fscanf(inFile, "%[^;];%lf;%[^;];%[^;];%d;%f;%[^\n]\n", name, &transaction_ID, transaction_time,
                 item_description, &items_purchased, &amount_paid, country) != EOF)
    {
        for(i = 0; i < elements; i++)
        {
            if (strcmp(names[i], name) == 0) {
                break;
            }
        }
        if(elements == i)
        {
            strcpy(names[i], name);
            elements++;
        }
    }
    return elements;

}

void createCustomers(FILE *inFile, customer* customers)
{
    rewind(inFile);
    char names[10][81];
    char firstline[200];

    char name[81];
    double transaction_ID;
    char transaction_time[81];
    char item_description[81];
    int items_purchased;
    float amount_paid;
    char country[81];

    int elements = 0;
    int i;

    fscanf(inFile, "%s\n", firstline);

    while(fscanf(inFile, "%[^;];%lf;%[^;];%[^;];%d;%f;%[^\n]\n", name, &transaction_ID, transaction_time,
                 item_description, &items_purchased, &amount_paid, country) != EOF)
    {
        for(i = 0; i < elements; i++)
        {
            if (strcmp(customers[i].name, name) == 0) {
                break;
            }
        }
        if(elements == i)
        {
            strcpy(customers[i].name, name);
            customers[i].amount_paid = 0;
            customers[i].transactions = 0;
            customers[i].items_purchased = 0;
            elements++;
        }
    }

}

void fillCustomerInfo(FILE* inFile, customer* c)
{
    rewind(inFile);
    char firstline[200];

    char name[81];
    double transaction_ID;
    char transaction_time[81];
    char item_description[81];
    int items_purchased;
    float amount_paid;
    char country[81];

    fscanf(inFile, "%s\n", firstline);

    while(fscanf(inFile, "%[^;];%lf;%[^;];%[^;];%d;%f;%[^\n]\n", name, &transaction_ID, transaction_time,
                 item_description, &items_purchased, &amount_paid, country) != EOF)
    {
        if(strcmp(c->name, name) == 0)
        {
            c->transactions++;
            c->amount_paid = c->amount_paid + amount_paid * items_purchased;
            c->items_purchased = c->items_purchased + items_purchased;
        }
    }
}

void readTransactions (FILE* inFile, customer* customers, int no_of_customers) {

    createCustomers(inFile, customers);
    int i;
    for(i = 0; i < no_of_customers; i++)
    {
        fillCustomerInfo(inFile, &customers[i]);
    }
}

void Swap(customer* c1, customer* c2)
{
    customer temp;

    strcpy(temp.name, c1->name);
    temp.amount_paid = c1->amount_paid;
    temp.transactions = c1->transactions;
    temp.items_purchased = c1->items_purchased;

    strcpy(c1->name, c2->name);
    c1->amount_paid = c2->amount_paid;
    c1->transactions = c2->transactions;
    c1->items_purchased = c2->items_purchased;

    strcpy(c2->name, temp.name);
    c2->amount_paid = temp.amount_paid;
    c2->transactions = temp.transactions;
    c2->items_purchased = temp.items_purchased;

}


void heapify(customer* customers, int no_of_customers, int i, int criteria) {

    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    switch(criteria)
    {
        case 1: //TRANSACTIONS
        {
            if(l < no_of_customers && customers[l].transactions > customers[largest].transactions)
                largest = l;
            if(r < no_of_customers && customers[r].transactions > customers[largest].transactions)
                largest = r;
            break;
        }
        case 2: //ITEMS PURCHASED
        {
            if(l < no_of_customers && customers[l].items_purchased > customers[largest].items_purchased)
                largest = l;
            if(r < no_of_customers && customers[r].items_purchased > customers[largest].items_purchased)
                largest = r;
            break;
        }
        case 3: //TOTAL AMOUNT PAID
        {
            if(l < no_of_customers && customers[l].amount_paid > customers[largest].amount_paid)
                largest = l;
            if(r < no_of_customers && customers[r].amount_paid > customers[largest].amount_paid)
                largest = r;
            break;
        }
        case 4: //AVERAGE AMOUNT PAID
        {
            if(l < no_of_customers && (customers[l].amount_paid/customers[l].transactions) > (customers[largest].amount_paid/customers[largest].transactions))
                largest = l;
            if(r < no_of_customers && (customers[r].amount_paid/customers[r].transactions) > (customers[largest].amount_paid/customers[largest].transactions))
                largest = r;
            break;
        }
    }
    if(largest != i)
    {
        Swap(&customers[i], &customers[largest]);
        heapify(customers, no_of_customers, largest, criteria);
    }
}

void heapSort(customer* customers, int no_of_customers, int criteria) {

    int i;

    for(i = no_of_customers/2 - 1; i >= 0; i--)
        heapify(customers, no_of_customers, i, criteria);

    for(i = no_of_customers - 1; i > 0; i--)
    {
        Swap(&customers[0], &customers[i]);
        heapify(customers, i, 0, criteria);
    }

}