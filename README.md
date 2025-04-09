# Transaction-Data-Management
This C program processes transaction data from a file and organizes it by customer. It demonstrates core concepts such as file operations, dynamic memory allocation, data structuring, sorting via Heap Sort, and menu-based user interaction.

Features
File Input: Reads transaction data from a file named transactions.txt.

Customer Data Management:
Automatically identifies and tracks unique customers.

Calculates and stores:
Total number of transactions per customer.
Total number of items purchased.
Total amount of money spent.
Average amount spent per transaction.

Sorting: Uses the Heap Sort algorithm to sort customer records by:
Total number of transactions.
Total number of items purchased.
Total money spent.
Average amount spent per transaction.

User Interface: Menu-based CLI that allows users to choose a sorting option and view results.

Input Format
The program expects a file named transactions.txt to be present in the same directory. Each line in the file represents a transaction in the following format:
Name;TransactionId;TransactionTime;ItemDescription;NumberOfItemsPurchased;CostPerItem;Country
Alice;6355745;02/02/2019;LONDON BUS COFFEE MUG;6;11.73;United Kingdom
Bob;6283376;12/26/2018;SET 12 COLOUR PENCILS DOLLY GIRL;3;3.52;France
Charlie;6385599;02/15/2019;PACK OF 12 SUKI TISSUES;72;0.9;Germany

Only the following columns are processed:
Name
Number of Items Purchased
Cost Per Item

Key Functions
countCustomers(FILE *fp): Counts the number of unique customers in the transaction file.
readTransactions(FILE *fp, Customer *customers, int customerCount): Populates and updates the customer array with transaction data.
heapSort(Customer *customers, int size, int sortOption): Sorts customer data according to the chosen metric.
heapify(Customer *customers, int size, int rootIndex, int sortOption): Helper function used by heapSort.

How to Use
Place your transactions.txt file in the same directory as the program binary.
Compile the program using a C compiler (e.g., gcc).
Run the program.
