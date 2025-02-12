//saja nazih asfour
//1210737
//sec4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//set a new name to use it
typedef struct BST_Node * BST;
//function defintion
BST InsertStudent(BST T,int Student_ID,const char*Student_Name,const char *Student_City,const char *Student_datain,int Class_ID);
BST InsertStudentByName(BST Tnew,int Student_ID,const char*Student_Name,const char *Student_City,const char *Student_datain,int Class_ID);
BST FindStudent(BST T  , int Student_ID);
void UpdateStudentInformation(BST T,int Student_ID,const char*Student_Name,const char *Student_City,const char *Student_datain,int Class_ID);
BST FindMin(BST T);
BST DeleteStudent(BST T,int Student_ID);
void SaveStudentInFile(BST T, FILE *in);
void ListSudentByName(BST T);
void SearchForCity(BST T, const char* Student_City);
void SearchForClass(BST T, int Class_ID);
BST DeleteStudentFromName(BST T,const char* Student_Name);
BST FindStudentByName(BST T , const char* Student_Name);
//structure for binary search tree
struct BST_Node{
    //the information of each student
    int  Student_ID;
    char Student_Name [1000];
    char Student_City [1000];
    char Student_datain [1000];
    int  Class_ID;
    //left and right for each node
    BST left;
    BST right;
};
int main()
{
    BST T=NULL;
    BST Tname=NULL;
    int Student_ID, Class_ID;
    char Student_Name[1000], Student_City[1000], Date[1000] ,CityToSearch [1000];
    //read from the file
    FILE *in=fopen("students.data","r");
         while(fscanf(in,"%d %s %s %s %d",&Student_ID,Student_Name,Student_City,Date,&Class_ID)!=EOF) {
             T = InsertStudent(T, Student_ID, Student_Name, Student_City, Date, Class_ID);
             Tname = InsertStudentByName(Tname, Student_ID, Student_Name, Student_City, Date, Class_ID);
         }
    fclose(in);
    int op;
    do{
        printf("Enter your choice:\n");
        printf("1. Insert a student info\n");
        printf("2. Find a student by the ID\n");
        printf("3. List all students in lexicographic order of their names\n");
        printf("4. Search for a city and list all students from that city\n");
        printf("5. List all students by their class in lexicographic order of their names\n");
        printf("6. Delete a student info\n");
        printf("7. Save all students in file\n");
        printf("8. Exit\n");
        scanf("%d", &op);
        switch(op){
            //this case for insert new student
            case 1:{
                printf("Enter Student ID:\n");
                scanf("%d", &Student_ID);
                printf("Enter Student Name:\n");
                scanf("%s", Student_Name);
                printf("Enter Student City:\n");
                scanf("%s", Student_City);
                printf("Enter class ID:\n");
                scanf("%d", &Class_ID);
                printf("Enter enrollment date:\n");
                scanf("%s", Date);
                T = InsertStudent(T, Student_ID, Student_Name, Student_City, Date, Class_ID);
                Tname = InsertStudentByName(Tname, Student_ID, Student_Name, Student_City, Date, Class_ID);
                printf("Student Inserted successfully\n");
                break;
            }
                //this case for find student by ID
            case 2:{
                printf("Enter student ID:\n");
                scanf("%d", &Student_ID);
                BST stu = FindStudent(T,Student_ID);
                if (stu != NULL) {
                    printf("Student found!\n");
                    printf("Student ID is %d\n", stu->Student_ID);
                    printf("Student Name is %s\n", stu->Student_Name);
                    printf("Student City is %s\n", stu->Student_City);
                    printf("Class ID is  %d\n", stu->Class_ID);
                    printf("Enrollment Date is %s\n", stu->Student_datain);
                    printf("Do You Want To Update Student Information?\nif yes enter 1:\n");
                    BST stu1= FindStudentByName(Tname,stu->Student_Name);
                    int choice;
                    scanf("%d", &choice);
                    //if user want to update the information of student
                    if (choice == 1) {
                        printf("Update Student ID:\n");
                        scanf("%d",&Student_ID);
                        printf("Update student name:\n");
                        scanf("%s", Student_Name);
                        printf("Update student City:\n");
                        scanf("%s", Student_City);
                        printf("Update class ID:\n");
                        scanf("%d", &Class_ID);
                        printf("Update enrollment date:\n");
                        scanf("%s", Date);
                        UpdateStudentInformation(T, Student_ID, Student_Name,Student_City, Date, Class_ID);
                        UpdateStudentInformation(stu1, Student_ID, Student_Name,Student_City, Date, Class_ID);
                        printf("Student information updated!\n");
                    }
                }
                else
                    printf("Student not found!\n");
                break;
            }
                //this case to list all student in order of their names
            case 3:{
                if (T == NULL)
                    printf("No students found!\n");
                else {
                    printf(" List of Students \n");
                    ListSudentByName(Tname);
                }
                break;
            }
                //this case to list all student in the city user want it
            case 4:{
                printf("Enter city To search:\n");
                scanf("%s", CityToSearch);
                printf("List of Students from %s :\n", CityToSearch);
                SearchForCity(Tname, CityToSearch);
                break;
            }
                //this case to list all student from class user want it
            case 5:{
                printf("Enter class ID you want to search:\n");
                scanf("%d", &Class_ID);
                printf("List of Students in Class %d :\n", Class_ID);
                SearchForClass(Tname, Class_ID);
                break;
            }
                //this case for delete any student
            case 6:{
                printf("Enter student name and  ID you want to delete(name first):\n");
                scanf("%s",Student_Name);
                scanf("%d", &Student_ID);
                T = DeleteStudent(T, Student_ID);
                Tname= DeleteStudentFromName(Tname,Student_Name);
                printf("Student deleted successfully!\n");
                break;
            }
                //this case to save to file
            case 7:{
                in = fopen("students.data", "w");
                if (in != NULL) {
                    SaveStudentInFile(T, in);
                    fclose(in);
                    printf("Students saved to file successfully!\n");
                }
                else
                    printf("Error opening file!\n");
                break;
            }
            case 8:{
                printf("Thank you for using my program!\n");
                break;
            }
            default :
                printf("Invalid choice! Please try again.\n");
        }
    }while(op!=8);
    return 0;
}
//function to insert student into a binary search tree
BST InsertStudent(BST T,int Student_ID,const char*Student_Name,const char *Student_City,const char *Student_datain,int Class_ID){
    //if the tree is empty , insert at first node
    if ( T == NULL ) {
        T = (BST) malloc (sizeof(struct BST_Node));
        //check for malloc if work correct and find place in memory
        if ( T == NULL )
            printf ("ERROR,Out of space!\n");
        else{
            T->Student_ID= Student_ID;
            strcpy(T->Student_Name,Student_Name);
            strcpy(T->Student_City,Student_City);
            strcpy(T->Student_datain,Student_datain);
            T->Class_ID=Class_ID;
            T->left = T->right = NULL;
        }
    }
        //if tree not empty, so check where we must insert
    else if ( Student_ID < T->Student_ID)
        T->left = InsertStudent( T->left ,Student_ID,Student_Name,Student_City,Student_datain,Class_ID);
    else if ( Student_ID > T->Student_ID)
        T->right = InsertStudent(T->right,Student_ID,Student_Name,Student_City,Student_datain,Class_ID);
    return T;
}
//function to find student by his/her ID
BST FindStudent(BST T , int Student_ID){
    //if the tree is NULL(empty)
    if ( T == NULL)
        return NULL;
    //greater than ID move to right
    if ( Student_ID < T->Student_ID)
        return ( FindStudent (T->left,Student_ID));
        //Less than ID move to left
    else if ( Student_ID > T->Student_ID )
        return ( FindStudent ( T->right, Student_ID));
        //if equal
    else
        return T;
}
//function to find student by his/her ID
BST FindStudentByName(BST T , const char* Student_Name){
    //if the tree is NULL(empty)
    if ( T == NULL)
        return NULL;
    //greater than ID move to right
    if ( strcmp(Student_Name,T->Student_Name)<0)
        return ( FindStudentByName(T->left,Student_Name));
        //Less than ID move to left
    else if (strcmp(Student_Name,T->Student_Name)>0)
        return ( FindStudentByName( T->right, Student_Name));
        //if equal
    else
        return T;
}
//function to find the smallest ID int the binary search tree
BST FindMin(BST T){
    //if the tree not empty
    if(T!=NULL)
        while(T->left != NULL)
            T=T->left;
    return T;
}
//function to delete student by the Id of student
BST DeleteStudent(BST T,int Student_ID){
    BST temp, child;
    //if the tree is empty
    if ( T == NULL )
        printf("Element not found");
        //if ID smallest than the one in the tree
    else if ( Student_ID < T->Student_ID)
        //go left
        T->left = DeleteStudent(T->left, Student_ID);
        //if ID larger than the one in the tree
    else if ( Student_ID > T->Student_ID)
        //go right
        T->right = DeleteStudent(T->right, Student_ID);
        //found element and has (right ,left) elements
    else if ( T->left && T->right ) {
        temp = FindMin(T->right);
        T->Student_ID = temp->Student_ID;
        strcpy(T->Student_Name,temp->Student_Name);
        strcpy(T->Student_City,temp->Student_City);
        strcpy(T->Student_datain,temp->Student_datain);
        T->Class_ID=temp->Class_ID;
        T->right = DeleteStudent(T->right, T->Student_ID);
    }
        //if we have one or zero children
    else{
        temp = T;
        if ( T->left == NULL)
            child = T->right;
        if (T->right == NULL)
            child = T->left;
        free ( temp);
        return child;
    }
    return T;
}
//function to delete student by name
BST DeleteStudentFromName(BST T,const char* Student_Name){
    BST temp, child;
    //if the tree is empty
    if ( T == NULL )
        printf("Element not found\n");
        //if name smallest than the one in the tree
    else if ( strcmp(Student_Name,T->Student_Name)<0)
        //go left
        T->left = DeleteStudentFromName(T->left, Student_Name);
        //if ID larger than the one in the tree
    else if (strcmp(Student_Name,T->Student_Name)>0)
        //go right
        T->right = DeleteStudentFromName(T->right, Student_Name);
        //found element and has (right ,left) elements
    else if ( T->left && T->right ) {
        temp = FindMin(T->right);
        T->Student_ID = temp->Student_ID;
        strcpy(T->Student_Name,temp->Student_Name);
        strcpy(T->Student_City,temp->Student_City);
        strcpy(T->Student_datain,temp->Student_datain);
        T->Class_ID=temp->Class_ID;
        T->right = DeleteStudentFromName(T->right, T->Student_Name);
    }
        //if we have one or zero children
    else{
        temp = T;
        if ( T->left == NULL)
            child = T->right;
        if (T->right == NULL)
            child = T->left;
        free ( temp);
        return child;
    }
    return T;
}
//function to Save all	students in	file
void SaveStudentInFile(BST T, FILE *in){
    if ( T != NULL){
        SaveStudentInFile(T->left,in);
        fprintf(in,"%d\n%s\n%s\n%s\n%d\n",T->Student_ID,T->Student_Name,T->Student_City,T->Student_datain,T->Class_ID );
        SaveStudentInFile(T->right,in);
    }
}
//function to list student in order of their name
void ListSudentByName(BST T){
    if ( T == NULL)
        return ;
    ListSudentByName(T->left);
    printf("student ID is %d\nstudent name is %s\nstudent city is %s\ndate in is %s\nclass id is %d\n",T->Student_ID
            ,T->Student_Name,T->Student_City,T->Student_datain,T->Class_ID );
    ListSudentByName(T->right);
}
//function to update student information
void UpdateStudentInformation(BST T,int Student_ID,const char*Student_Name,const char *Student_City,const char *Student_datain,int Class_ID){
    strcpy(T->Student_Name,Student_Name);
    T->Student_ID=Student_ID;
    strcpy(T->Student_City,Student_City);
    strcpy(T->Student_datain,Student_datain);
    T->Class_ID=Class_ID;
}
//function to insert student in order of their name
BST InsertStudentByName(BST Tnew,int Student_ID,const char*Student_Name,const char *Student_City,const char *Student_datain,int Class_ID){
    //if the tree is empty , insert the data from temp to it
    if ( Tnew == NULL ) {
        Tnew = (BST) malloc (sizeof(struct BST_Node));
        //check for malloc if work correct and find place in memory
        if ( Tnew == NULL )
            printf ("ERROR,Out of space!\n");
        else{
            Tnew->Student_ID= Student_ID;
            strcpy(Tnew->Student_Name,Student_Name);
            strcpy(Tnew->Student_City,Student_City);
            strcpy(Tnew->Student_datain,Student_datain);
            Tnew->Class_ID=Class_ID;
            Tnew->left = Tnew->right = NULL;
        }
    }
        //if tree not empty,so check where we must insert
    else if(strcmp(Student_Name,Tnew->Student_Name)<0)
        Tnew->left = InsertStudentByName( Tnew->left ,Student_ID,Student_Name,Student_City,Student_datain,Class_ID);
    else if (strcmp(Student_Name,Tnew->Student_Name)>0)
        Tnew->right = InsertStudentByName(Tnew->right,Student_ID,Student_Name,Student_City,Student_datain,Class_ID);
    return Tnew;
}
//Search for a city	and	list all students from	that city
void SearchForCity(BST T, const char* Student_City){
    if(T!=NULL){
        SearchForCity(T->left,Student_City);
        if(strcmp(T->Student_City,Student_City)==0){
            printf("Student ID is %d\n",T->Student_ID);
            printf("Student Name is %s\n",T->Student_Name);
            printf("Student Date enrollment is %s\n",T->Student_datain);
            printf("Student Class ID is %d\n",T->Class_ID);
        }
        SearchForCity(T->right,Student_City);
    }
}
//List all students	by their class
void SearchForClass(BST T, int Class_ID){
    if(T!=NULL){
        SearchForClass(T->left,Class_ID);
        if(T->Class_ID==Class_ID){
            printf("Student ID is %d\n",T->Student_ID);
            printf("Student Name is %s\n",T->Student_Name);
            printf("Student Date enrollment is %s\n",T->Student_datain);
            printf("Student is in %s city\n",T->Student_City);
        }
        SearchForClass(T->right,Class_ID);
    }
}