#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

void displayOptions(void);
void enterRecord(void);
void displayRecord(void);
void searchRecord(void);
void editRecord(void);
void ascending(void);
void descending(void);
void deleteRecord(void);
void store(void);

struct Student
{
  char full_name[55];
  int roll;
  int eng;
  int nep;
  int math;
} student[100];
int n;

int main(void)
{
  while (1)
  {
    system("cls");

    displayOptions();

    int c;
    c = getch();
    printf("%c", c);

    switch (c)
    {
    case '1':
      enterRecord();
      break;
    case '2':
      displayRecord();
      printf("\n\nPress any key to exit view.");
      getch();
      break;
    case '3':
      searchRecord();
      break;
    case '4':
      editRecord();
      break;
    case '5':
      ascending();
      break;
    case '6':
      descending();
      break;
    case '7':
      deleteRecord();
      break;
    case '8':
      return 0;
      break;
    default:
      printf("\nWrong Input. Try again!");
      getch();
      break;
    }
  }
}

void displayOptions(void)
{
  system("cls");
  printf("\n\n");
  printf("          # STUDENT RECORD MANAGEMENT SYSTEM #\n");
  printf("\n +-------------------------------------------------------+\n");
  printf(" |                        MENU                           |\n");
  printf(" +-------------------------------------------------------+\n");
  printf(" | 1. Enter Record.                                      |\n");
  printf(" | 2. Display Record.                                    |\n");
  printf(" | 3. Search Record                                      |\n");
  printf(" | 4. Edit Record.                                       |\n");
  printf(" | 5. Ascending Order. (marks)                           |\n");
  printf(" | 6. Descending Order. (marks)                          |\n");
  printf(" | 7. Delete Record.                                     |\n");
  printf(" | 8. Exit.                                              |\n");
  printf(" +-------------------------------------------------------+\n");
  printf("\nEnter Choice : ");
}

void enterRecord(void)
{
  system("cls");
  printf("\n\n");
  printf("         # STUDENT RECORD MANAGEMENT SYSTEM #\n");
  printf("+-------------------------------------------------------+\n");
  printf("|                  Enter Record Menu                    |\n");
  printf("+-------------------------------------------------------+\n");
  printf("|Enter no. of entries: ");
  scanf("%d", &n);

  // Check if the number of entries is within the array bounds
  if (n > 100)
  {
    printf("Error: Number of entries exceeds maximum capacity.\n");
    return;
  }

  for (int i = 0; i < n; i++)
  {
    printf("\n| Student %d:", i + 1);
    printf("\n|    Name: ");
    fflush(stdin);
    gets(student[i].full_name);

    printf("|    Roll number: ");
    scanf("%d", &student[i].roll);

    printf("|    English: ");
    scanf("%d", &student[i].eng);

    printf("|    Nepali: ");
    scanf("%d", &student[i].nep);

    printf("|    Math: ");
    scanf("%d", &student[i].math);

    printf("+-------------------------------------------------------+\n");
  }

  if (n > 0)
  {
    store();
  }
}

void displayRecord(void)
{
  system("cls");
  printf("\n\n");
  printf("                          # STUDENT RECORD MANAGEMENT SYSTEM #\n");
  printf("+-----------------------------------------------------------------------------------------+\n");
  printf("|                                    Display Record Menu                                  |\n");
  printf("+-----------------------------------------------------------------------------------------+\n");
  printf("| S.N | Name                 | Roll Number | English | Nepali | Math | Total | Percentage |\n");
  printf("+-----+----------------------+-------------+---------+--------+------+-------+------------+\n");

  FILE *fp = fopen("store.txt", "r");
  if (fp != NULL)
  {
    char fn[55];
    int r, e, n, m, t;
    float p;
    int counter = 1;
    rewind(fp);
    while (fscanf(fp, "%[^,],%d,%d,%d,%d\n", fn, &r, &e, &n, &m) == 5)
    {
      t = e + n + m;
      p = (float)t / 300 * 100;
      printf("| %-3d | %-20s | %-11d | %-7d | %-6d | %-4d | %-5d | %-10.2f |\n", counter, fn, r, e, n, m, t, p);
      counter++;
    }
    fclose(fp);
  }
  else
  {
    printf("Error: Unable to open file for reading.\n");
  }

  printf("+-----+----------------------+-------------+---------+--------+------+-------+------------+\n");
}

void searchRecord(void)
{
  system("cls");
  printf("\n\n");
  printf("                              # STUDENT RECORD MANAGEMENT SYSTEM #\n");
  printf("+-----------------------------------------------------------------------------------------+\n");
  printf("|                            Search Record Menu (Name or Roll Number)                     |\n");
  printf("+-----------------------------------------------------------------------------------------+\n");

  FILE *fp = fopen("store.txt", "r");
  if (fp != NULL)
  {
    char fn[55];
    int r, e, n, m, t;
    float p;
    int counter = 1;
    char searchQuery[100];
    int searchCriteria;
    printf("Search by:\n");
    printf("    1. Name\n");
    printf("    2. Roll Number\n");
    printf("Enter your choice: ");
    scanf("%d", &searchCriteria);

    printf("Enter search query: ");
    fflush(stdin);
    gets(searchQuery);

    // Convert search query to lowercase for case insensitivity
    for (int i = 0; searchQuery[i] != '\0'; i++)
    {
      searchQuery[i] = tolower(searchQuery[i]);
    }

    rewind(fp);

    printf("+-----------------------------------------------------------------------------------------+\n");
    printf("| S.N | Name                 | Roll Number | English | Nepali | Math | Total | Percentage |\n");
    printf("+-----+----------------------+-------------+---------+--------+------+-------+------------+\n");
    while (fscanf(fp, "%[^,],%d,%d,%d,%d\n", fn, &r, &e, &n, &m) == 5)
    {
      // Convert name to lowercase for case insensitivity
      char lowercaseName[55];
      int i;
      for (i = 0; fn[i] != '\0'; i++)
      {
        lowercaseName[i] = tolower(fn[i]);
      }
      lowercaseName[i] = '\0';

      if ((searchCriteria == 1 && strstr(lowercaseName, searchQuery) != NULL) || (searchCriteria == 2 && r == atoi(searchQuery)))
      {
        t = e + n + m;
        p = (float)t / 300 * 100;
        printf("| %-3d | %-20s | %-11d | %-7d | %-6d | %-4d | %-5d | %-10.2f |\n", counter, fn, r, e, n, m, t, p);
        counter++;
      }
    }
    fclose(fp);

    if (counter == 1)
    {
      printf("No records found matching the search criteria.\n");
    }
  }
  else
  {
    printf("Error: Unable to open file for reading.\n");
  }

  printf("+-----+----------------------+-------------+---------+--------+------+-------+------------+\n");
  printf("\n\nPress any key to exit view.");
  getch();
}

void editRecord(void)
{
  system("cls");
  printf("\n\n");
  printf("                          # STUDENT RECORD MANAGEMENT SYSTEM #\n");
  printf("+-----------------------------------------------------------------------------------------+\n");
  printf("|                                    Edit Record Menu                                     |\n");
  printf("+-----------------------------------------------------------------------------------------+\n");
  printf("| S.N | Name                 | Roll Number | English | Nepali | Math | Total | Percentage |\n");
  printf("+-----+----------------------+-------------+---------+--------+------+-------+------------+\n");

  FILE *fp = fopen("store.txt", "r");
  if (fp != NULL)
  {
    char fn[55];
    int r, e, n, m, t;
    float p;
    int counter = 1;
    rewind(fp);
    while (fscanf(fp, "%[^,],%d,%d,%d,%d\n", fn, &r, &e, &n, &m) == 5)
    {
      t = e + n + m;
      p = (float)t / 300 * 100;
      printf("| %-3d | %-20s | %-11d | %-7d | %-6d | %-4d | %-5d | %-10.2f |\n", counter, fn, r, e, n, m, t, p);
      counter++;
    }
    fclose(fp);
    printf("+-----+----------------------+-------------+---------+--------+------+-------+------------+\n");
  }
  else
  {
    printf("Error: Unable to open file for reading.\n");
    return;
  }

  int editIndex;
  printf("Enter the serial number of the record you want to edit: ");
  scanf("%d", &editIndex);
  editIndex--; // Adjust index to match array indexing (0-based)

  if (editIndex >= 0)
  {
    // Open the file for reading and writing
    FILE *fp = fopen("store.txt", "r");
    if (fp != NULL)
    {
      // Open a temporary file for writing
      FILE *temp_fp = fopen("temp.txt", "w");
      if (temp_fp != NULL)
      {
        char fn[55];
        int roll, eng, nep, math;
        int counter = 1;
        rewind(fp);
        while (fscanf(fp, "%[^,],%d,%d,%d,%d\n", fn, &roll, &eng, &nep, &math) == 5)
        {
          if (counter == editIndex + 1)
          {
            printf("Current Record: %s, %d, %d, %d, %d\n", fn, roll, eng, nep, math);

            // Prompt for new values
            printf("Enter new Name: ");
            fflush(stdin);
            gets(fn);
            printf("Enter new roll: ");
            scanf("%d", &roll);
            printf("Enter new Marks - English: ");
            scanf("%d", &eng);
            printf("                  Nepali: ");
            scanf("%d", &nep);
            printf("                  Maths: ");
            scanf("%d", &math);
          }
          fprintf(temp_fp, "%s,%d,%d,%d,%d\n", fn, roll, eng, nep, math);
          counter++;
        }
        fclose(temp_fp);
        fclose(fp);

        // Replace the original file with the temporary file
        remove("store.txt");
        rename("temp.txt", "store.txt");

        printf("Record edited successfully!\n");
      }
      else
      {
        printf("Error: Unable to open temporary file for writing.\n");
      }
    }
    else
    {
      printf("Error: Unable to open file for reading.\n");
    }
  }
  else
  {
    printf("Invalid serial number. Please try again.\n");
  }

  printf("\n\nPress any key to exit view.");
  getch();
}

void ascending()
{
  FILE *fp = fopen("store.txt", "r");
  if (fp == NULL)
  {
    printf("Error: Unable to open file for reading.\n");
    return;
  }

  // Allocate memory for one record initially
  int capacity = 1;
  struct Student *students = (struct Student *)malloc(capacity * sizeof(struct Student));
  if (students == NULL)
  {
    printf("Error: Memory allocation failed.\n");
    fclose(fp);
    return;
  }

  int num_records = 0;
  char line[256]; // Assuming maximum line length is 255 characters

  // Read each line of the file and parse it into the structure
  while (fgets(line, sizeof(line), fp) != NULL)
  {
    if (num_records >= capacity)
    {
      // If the number of records exceeds the current capacity, double the capacity
      capacity *= 2;
      struct Student *temp = (struct Student *)realloc(students, capacity * sizeof(struct Student));
      if (temp == NULL)
      {
        printf("Error: Memory allocation failed.\n");
        fclose(fp);
        free(students);
        return;
      }
      students = temp;
    }

    // Parse the line into the structure
    if (sscanf(line, "%[^,],%d,%d,%d,%d\n", students[num_records].full_name, &students[num_records].roll, &students[num_records].eng, &students[num_records].nep, &students[num_records].math) != 5)
    {
      printf("Error reading record %d from file.\n", num_records + 1);
      fclose(fp);
      free(students);
      return;
    }

    // Print the record (for debugging)
    printf("Read record: %s, %d, %d, %d, %d\n", students[num_records].full_name, students[num_records].roll, students[num_records].eng, students[num_records].nep, students[num_records].math);

    num_records++;
  }

  fclose(fp);

  // Sort the array of students based on total marks
  for (int i = 0; i < num_records - 1; i++)
  {
    for (int j = 0; j < num_records - i - 1; j++)
    {
      int total_j = students[j].eng + students[j].nep + students[j].math;
      int total_j_plus_1 = students[j + 1].eng + students[j + 1].nep + students[j + 1].math;
      if (total_j > total_j_plus_1)
      {
        // Swap students[j] and students[j + 1]
        struct Student temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }

  // Display the sorted records
  system("cls");
  printf("\n\n");
  printf("                          # STUDENT RECORD MANAGEMENT SYSTEM #\n");
  printf("+-----------------------------------------------------------------------------------------+\n");
  printf("|                        Records in Ascending Order (total marks)                         |\n");
  printf("+-----------------------------------------------------------------------------------------+\n");
  printf("| S.N | Name                 | Roll Number | English | Nepali | Math | Total | Percentage |\n");
  printf("+-----+----------------------+-------------+---------+--------+------+-------+------------+\n");

  for (int i = 0; i < num_records; i++)
  {
    int total = students[i].eng + students[i].nep + students[i].math;
    float percentage = (float)total / 300 * 100;
    printf("| %-3d | %-20s | %-11d | %-7d | %-6d | %-4d | %-5d | %-10.2f |\n", i + 1, students[i].full_name, students[i].roll, students[i].eng, students[i].nep, students[i].math, total, percentage);
  }

  printf("+-----------------------------------------------------------------------------------------+\n");

  free(students);

  printf("Enter any key to exit. ");
  getch();
}

void descending(void)
{
  FILE *fp = fopen("store.txt", "r");
  if (fp == NULL)
  {
    printf("Error: Unable to open file for reading.\n");
    return;
  }

  // Allocate memory for one record initially
  int capacity = 1;
  struct Student *students = (struct Student *)malloc(capacity * sizeof(struct Student));
  if (students == NULL)
  {
    printf("Error: Memory allocation failed.\n");
    fclose(fp);
    return;
  }

  int num_records = 0;
  char line[256]; // Assuming maximum line length is 255 characters

  // Read each line of the file and parse it into the structure
  while (fgets(line, sizeof(line), fp) != NULL)
  {
    if (num_records >= capacity)
    {
      // If the number of records exceeds the current capacity, double the capacity
      capacity *= 2;
      struct Student *temp = (struct Student *)realloc(students, capacity * sizeof(struct Student));
      if (temp == NULL)
      {
        printf("Error: Memory allocation failed.\n");
        fclose(fp);
        free(students);
        return;
      }
      students = temp;
    }

    // Parse the line into the structure
    if (sscanf(line, "%[^,],%d,%d,%d,%d\n", students[num_records].full_name, &students[num_records].roll, &students[num_records].eng, &students[num_records].nep, &students[num_records].math) != 5)
    {
      printf("Error reading record %d from file.\n", num_records + 1);
      fclose(fp);
      free(students);
      return;
    }

    // Print the record (for debugging)
    printf("Read record: %s, %d, %d, %d, %d\n", students[num_records].full_name, students[num_records].roll, students[num_records].eng, students[num_records].nep, students[num_records].math);

    num_records++;
  }

  fclose(fp);

  // Sort the array of students based on total marks
  for (int i = 0; i < num_records - 1; i++)
  {
    for (int j = 0; j < num_records - i - 1; j++)
    {
      int total_j = students[j].eng + students[j].nep + students[j].math;
      int total_j_plus_1 = students[j + 1].eng + students[j + 1].nep + students[j + 1].math;
      if (total_j < total_j_plus_1)
      {
        // Swap students[j] and students[j + 1]
        struct Student temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }

  // Display the sorted records
  system("cls");
  printf("\n\n");
  printf("                            # STUDENT RECORD MANAGEMENT SYSTEM #\n");
  printf("+-----------------------------------------------------------------------------------------+\n");
  printf("|                        Records in Descending Order (total marks)                        |\n");
  printf("+-----------------------------------------------------------------------------------------+\n");
  printf("| S.N | Name                 | Roll Number | English | Nepali | Math | Total | Percentage |\n");
  printf("+-----+----------------------+-------------+---------+--------+------+-------+------------+\n");

  for (int i = 0; i < num_records; i++)
  {
    int total = students[i].eng + students[i].nep + students[i].math;
    float percentage = (float)total / 300 * 100;
    printf("| %-3d | %-20s | %-11d | %-7d | %-6d | %-4d | %-5d | %-10.2f |\n", i + 1, students[i].full_name, students[i].roll, students[i].eng, students[i].nep, students[i].math, total, percentage);
  }

  printf("+-----------------------------------------------------------------------------------------+\n");

  free(students);

  printf("Enter any key to exit. ");
  getch();
}

void deleteRecord(void)
{
  int serial = 0;
  struct Student student;
  system("cls");
  printf("\n\n");
  printf("                            # STUDENT RECORD MANAGEMENT SYSTEM #\n");
  printf("+-----------------------------------------------------------------------------------------+\n");
  printf("|                           Delete Record Menu (by Serial Number)                         |\n");
  printf("+-----------------------------------------------------------------------------------------+\n");
  printf("| S.N | Name                 | Roll Number | English | Nepali | Math | Total | Percentage |\n");
  printf("+-----+----------------------+-------------+---------+--------+------+-------+------------+\n");

  FILE *fp = fopen("store.txt", "r");
  if (fp != NULL)
  {
    char fn[55];
    int r, e, n, m, t;
    float p;
    int counter = 1;
    rewind(fp);
    while (fscanf(fp, "%[^,],%d,%d,%d,%d\n", fn, &r, &e, &n, &m) == 5)
    {
      t = e + n + m;
      p = (float)t / 300 * 100;
      printf("| %-3d | %-20s | %-11d | %-7d | %-6d | %-4d | %-5d | %-10.2f |\n", counter, fn, r, e, n, m, t, p);
      counter++;
    }
    fclose(fp);
    printf("+-----+----------------------+-------------+---------+--------+------+-------+------------+\n");
    // Prompt the user to enter the serial number of the record to delete
    int deleteSerial;
    printf("Enter the serial number of the record you want to delete: ");
    scanf("%d", &deleteSerial);

    // Open the file again for reading and a temporary file for writing
    fp = fopen("store.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (fp == NULL || tempFile == NULL)
    {
      printf("Error: Unable to open files for reading and writing.\n");
      return;
    }

    // Write the records back to the temporary file, excluding the record with the specified serial number
    serial = 0;
    while (fscanf(fp, "%[^,],%d,%d,%d,%d\n", student.full_name, &student.roll, &student.eng, &student.nep, &student.math) == 5)
    {
      serial++;
      if (serial != deleteSerial)
      {
        fprintf(tempFile, "%s,%d,%d,%d,%d\n", student.full_name, student.roll, student.eng, student.nep, student.math);
      }
    }
    fclose(fp);
    fclose(tempFile);

    // Remove the original file
    if (remove("store.txt") != 0)
    {
      printf("Error: Unable to delete the original file.\n");
      return;
    }

    // Rename the temporary file to the original file name
    if (rename("temp.txt", "store.txt") != 0)
    {
      printf("Error: Unable to rename the temporary file.\n");
      return;
    }

    printf("Record deleted successfully.\n");
    printf("Press any key to exit view.");
    getch();
  }
  else
  {
    printf("\nError opening file for deleting record.");
  }
}

void store(void)
{
  FILE *fp = fopen("store.txt", "a");
  if (fp != NULL)
  {
    // fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++)
    {
      fprintf(fp, "%s,%d,%d,%d,%d\n", student[i].full_name, student[i].roll, student[i].eng, student[i].nep, student[i].math);
    }
    fclose(fp);
  }
  else
  {
    printf("Error: Unable to open file for writing.\n");
  }
}
