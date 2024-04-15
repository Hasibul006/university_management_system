#include<stdio.h>
#include<math.h>
#include<string.h>

//container of admin's information
typedef struct
{
    char id[20],pass[20];

} admin;

//container of teacher's information
typedef struct
{
    char id[20],pass[20],firstname[20],lastname[20];
    int course[9999];

} teacher;

//container of student's information
typedef struct
{
    char id[20],pass[20],firstname[20],lastname[20];
    int marks[9999];

} student;

//gloval variables used in many cases in the middle of the code
int nostudent=0;//to check if the desired student is found
int noteacher=0;//to check if the desired teacher is found
int sstruc_size=sizeof(student);//size of an element of student structure
int tstruc_size=sizeof(teacher);//size of an element of teacher structure
teacher teach;
student stu;


//adding teacher with the information(ID,Password,Firstname,Lastname) given by admin
void add_teacher()
{
    teacher t;
    printf("Set new teacher's id : ");
    scanf("%s",t.id);
    printf("Set new teacher's password : ");
    scanf("%s",t.pass);
    printf("Enter teacher's firstname and lastname using a space in middle : ");
    //Animesh Kumar
    scanf("%s %s",t.firstname,t.lastname);
    memset(t.course,0,sizeof(t.course));
    FILE *f=fopen("teacherinfo.txt","a");
    //file dedicated only for teacher's info
    fwrite(&t,sizeof(teacher),1,f);
    fclose(f);
    printf("\nBack to admin panel\n");
}


//adding student with the information(ID,Password,Firstname,Lastname) given by admin
void add_student()
{
    student st;
    printf("Enter new student's id : ");
    scanf("%s",st.id);
    printf("Enter new student's password : ");
    scanf("%s",st.pass);
    printf("Enter firstname and lastname using a space in middle :");
    //Hasibul Islam
    scanf("%s %s",st.firstname,st.lastname);
    memset(st.marks,-1,sizeof(st.marks));
    FILE *f=fopen("studentinfo.txt","a");
    //file dedicated only for student's info
    fwrite(&st,sizeof(student),1,f);
    fclose(f);
    printf("\nBack to admin panel\n");
}




/*
removing a teacher's all information from file

1. Enter the teacher's id and password
2. Create a backup file to store the teacher's information except for the teacher's
   info which has to be removed
3. then copy the backup file's information to the main teacher file where there is no information of the given teacher

*/

teacher remove_teacher(teacher t1)
{
    teacher t2;
    if(!strcmp(t1.id,teach.id))
    {
        //Enter the ID and password of the teacher's to be removed
        printf("Enter teacher's id : ");

        scanf("%s",t1.id);
        printf("Enter teacher's password : ");
        scanf("%s",t1.pass);
    }
    memset(t1.course,0,sizeof(t1.course));
    FILE *f1=fopen("backup.txt","w");//creating a baackup file to store the information that shouldn't be removed
    FILE *f2=fopen("teacherinfo.txt","r");

    //the removed information must be preserved in t1 struct
    //because we need this info when we do the updating work of the teacher's information
    while(fread(&t2,sizeof(teacher),1,f2))
    {
        if(!strcmp(t1.id,t2.id) && !strcmp(t1.pass,t2.pass))
        {
            noteacher++;
            t1=t2;
            continue;
        }
        fwrite(&t2,sizeof(teacher),1,f1);//writing in backup file
    }
    fclose(f1);
    fclose(f2);
    f1=fopen("backup.txt","r");
    f2=fopen("teacherinfo.txt","w");

    while(fread(&t2,sizeof(teacher),1,f1))
    {
        fwrite(&t2,sizeof(teacher),1,f2);
        //getting back the informations from the backup file
    }
    fclose(f1);
    fclose(f2);
    return t1;
}


/*
updating teacher's ID, password, Firstname, Lastname

1. Remove the information of the teacher's which to be updated from the file keeping the information
   preserved in another struct t1
2. after doing the updating information it is appended in the teacher file
   so the updated teacher will be in the last position of the file

*/
void update_teacher()
{
    teacher t=remove_teacher(teach);//calling removing function
    if(noteacher==0)
    {
        printf("\nNo Teacher containing this id and password is found\ntry again\n");
        //if desired teacher isn't found in the file
        noteacher=0;
        return;
    }
    //keep updating entering your choice
    for(; ;)
    {
        printf("\nWhat do you want to update?\n1. ID\n2.Password\n3.Firstname\n4.Lastname\nEnter your choice(enter 0 to stop updating) : ");
        int n;
        scanf("%d",&n);
        if(n==0)break;
        else if(n==1)
        {
            printf("Enter new ID : ");
            scanf("%s",t.id);
        }
        else if(n==2)
        {
            printf("Enter new password: ");
            scanf("%s",t.pass);
        }
        else if(n==3)
        {
            printf("Enter new Firstname :\n");
            scanf("%s",t.firstname);
        }
        else if(n==4)
        {
            printf("Enter new Lastname: ");
            scanf("%s",t.lastname);
        }
    }
    FILE* f;
    f=fopen("teacherinfo.txt","a");
    fwrite(&t,sizeof(teacher),1,f);
    fclose(f);
    printf("\nBack to admin panel\n");
}



/*
removing a student's all information from file

1. Enter the student's id and password
2. Create a backup file to store the student's information except for the teacher's
   info which has to be removed
3. then copy the backup file's information to the main student file where there is no information of the given student

*/

student remove_student(student st1)
{
    student st2;
    if(!strcmp(st1.id,stu.id))
    {
        printf("\nEnter student's id : ");

        scanf("%s",st1.id);
        printf("\nEnter student's password : ");
        scanf("%s",st1.pass);
    }
    FILE *f1=fopen("backup.txt","w");
    FILE *f2=fopen("studentinfo.txt","r");

    while(fread(&st2,sizeof(student),1,f2))
    {
        if(!strcmp(st2.id,st1.id) && !strcmp(st2.pass,st1.pass))
        {
            st1=st2;
            //the removed information must be preserved in st1 struct
            //because we need this info when we do the updating work of the student's information
            nostudent++;
            continue;
        }
        fwrite(&st2,sizeof(student),1,f1);
    }
    fclose(f1);
    fclose(f2);
    f1=fopen("backup.txt","r");
    f2=fopen("studentinfo.txt","w");
    while(fread(&st2,sizeof(student),1,f1))
    {
        fwrite(&st2,sizeof(student),1,f2);
    }
    fclose(f1);
    fclose(f2);
    return st1;
}

/*
updating student's ID, password, Firstname, Lastname

1. Remove the information of the student's which to be updated from the file keeping the information
   preserved in another struct t1
2. after doing the updating information it is appended in the student file
   so the updated student will be in the last position of the file

*/

void update_student()
{
    student st=remove_student(stu);
    if(nostudent==0)
    {
        printf("No student containing this id and password is found\npress 6 to exit or 4 to try again : ");
        nostudent=0;
        return;
    }
    for(; ;)
    {
        printf("What do you want to update?\n1. ID\n2.Password\n3.Firstname\n4.Lastname\nEnter your choice(enter 0 to stop updating) : ");
        int n;
        scanf("%d",&n);
        if(n==0)break;
        else if(n==1)
        {
            printf("Enter new ID :\n");
            scanf("%s",st.id);
        }
        else if(n==2)
        {
            printf("Enter new password:\n");
            scanf("%s",st.pass);
        }
        else if(n==3)
        {
            printf("Enter new Firstname :\n");
            scanf("%s",st.firstname);
        }
        else if(n==4)
        {
            printf("Enter new Lastname:\n");
            scanf("%s",st.lastname);
        }
    }
    FILE *f=fopen("studentinfo.txt","a");
    fwrite(&st,sizeof(student),1,f);
    fclose(f);
    fflush(f);
    printf("\nBack to admin panel\n");
}


/*

  assigning courses
  1. remove the teacher calling the removing function which return the removed teacher info
  2. the enter the courses information in the returned info
  3. append the teacher's info in the teacher file

*/
void course_assign()
{
    teacher t=remove_teacher(teach);
    if(noteacher==0)
    {
        printf("No Teacher containing this id and password is found\npress 8 to exit or 5 to try again: ");
        noteacher=0;
        return;
    }
    int x;
    printf("Enter course numbers[1201(CSE), 1203(DLD), 1217(EEE), 1207(MATH), 1208(CHEM)] (enter 0 to stop assigning) :\n");
    fflush(stdout);
    for(; ;)
    {
        scanf("%d",&x);
        if(x==0)break;
        //the element of the array's of index equal to the course number is 1 if the course is assigned
        // or the value is 0 if not assigned
        t.course[x]=1;
    }
    FILE *f=fopen("teacherinfo.txt","a");
    fwrite(&t,sizeof(teacher),1,f);
    fclose(f);
    printf("\nBack to admin panel\n");
}


int admin_check()
{
    //if it is being compiled for the first time then 1st it will set the admin's id and password
    //after 2nd time compilinig it will check admin's id and password
    FILE *f;
    admin a2;
    f=fopen("admininfo.txt","r+");
    if(f==NULL)
    {
        fclose(f);
        printf("First set admin's Id :");
        fflush(stdout);
        admin a1;
        scanf("%s",a1.id);
        printf("Set admin's password :");
        scanf("%s",a1.pass);
        f=fopen("admininfo.txt","w");
        fwrite(&a1,sizeof(admin),1,f);
        fclose(f);
        printf("\nNow log in again\n");
    }

    printf("Please Enter id : ");
    fflush(stdout);
    admin a1;
    scanf("%s",a1.id);
    printf("Please Enter password : ");
    scanf("%s",a1.pass);
    f=fopen("admininfo.txt","r");
    int x=0;
//	checking user id, password does exist in the file or not
    while(fread(&a2,sizeof(admin),1,f))
    {
        if(!strcmp(a2.id,a1.id) && !strcmp(a2.pass,a1.pass)) x=1;
    }
    fclose(f);
    return x;
}


/*
   This function control which work has to be done according to the input given by admin
   admin can add,remove to update the information using this function after the succesfull log in
*/
void admin_panel()
{
    if(!admin_check())
    {
        printf("Invalid user id or password\nTry again or enter 0 to exit database\n");
        return;
    }
    printf("\n\t________ Admin Panel ________\n\n");
    while(1)
    {
        printf("1. add teacher\n2. add student\n3. update teacher\n4. update student\n5. Assign course to teacher\n6. Remove Teacher\n7. Remove Student\n8. Exit\n\nEnter your choice  :");
        fflush(stdout);
        int a;
        scanf("%d",&a);

        //calling user defined functions according to the input
        if(a==1) add_teacher();
        else if(a==2) add_student();
        else if(a==3) update_teacher();
        else if(a==4) update_student();
        else if(a==5)course_assign();
        else if(a==6)
        {
            remove_teacher(teach);
            if(noteacher==0)
            {
                printf("There is no Teacher with this ID and password\n\n");
                noteacher=0;
                continue;
            }
            printf("Desired teacher's information is removed\n\n");
        }
        else if(a==7)
        {
            remove_student(stu);
            if(nostudent==0)
            {
                printf("There is no student with this ID and password\n\n");
                nostudent=0;
                continue;
            }
            printf("Desired student's information is removed\n\n");
        }
        else if(a==8)
        {
            printf("\nGoodbye admin!\n\n");
            return;
        }


    }
    printf("\nGoodbye admin!\n\n");
    return;
}



/*

   This function will find a element in the student file using student's firstname
   1. take input the firstname of the student
   2. open the file and start a loop to compare all the student's firstname with the given one
   3. if failed to find give a massage
   4. if found output all the information of the student

*/
void find_student()
{
    student st;
    printf("Enter student firstname: ");
    fflush(stdout);
    scanf("%s",st.firstname);
    int check=0;
    FILE *f=fopen("studentinfo.txt","r");
    while(fread(&stu,sizeof(student),1,f))
    {
        if(!strcmp(st.firstname,stu.firstname))
        {
            check++;
            printf("\nThe information of the student: \n\tID : %s\n\tPassword : %s\n\tName : %s %s\n\n",stu.id,stu.pass,stu.firstname,stu.lastname);
        }
    }
    fclose(f);
    if(check==0)
    {
        printf("There is no student with this firstname!\n");
        return;
    }
    printf("\nBack to teacher's panel\n");
    return;
}



/*

  count all the student in the file
  1. open the file
  2. start a loop to count how many element of student structure if included in this file

*/
void student_counting()
{
    int count=0;
    student st;
    FILE *f=fopen("studentinfo.txt","r");
    while(fread(&st,sizeof(student),1,f))
    {
        count++;
    }
    fclose(f);
    printf("There are %d students in KUET CSE\n",count);
    printf("\nBack to teacher's panel\n");
    fflush(stdout);
}



/*

   The teacher will assign the marks of exams of his courses
1. enter the course number of which marks is to be assigned
2. if the teacher is not assigned to this course then give a massage and return
3. open the student file the assign the marks using a loop

*/
void assigning_marks(teacher t)
{
    printf("Enter the course number of which the marks you want to assign : ");
    fflush(stdout);
    int cours,x=0;
    scanf("%d",&cours);
    if(t.course[cours]==0)
    {
        printf("\nYou are not assigned to this course\nenter 4 to exit or 1 to try again : ");
        return;
    }
    FILE *f=fopen("studentinfo.txt","r+");
    student st;
    while(fread(&st,sizeof(student),1,f))
    {

        fseek(f,-sstruc_size,SEEK_CUR);
        //fseek is used to bring the pointer back to the appropriate student
        printf("Enter the marks of %s : ",st.id);
        int mark;
        scanf("%d",&mark);
        st.marks[cours]=mark;
        //the value of the element of the array equal to the course number is the marks which the student got in exam
        fwrite(&st,sizeof(student),1,f);
        fflush(f);
    }
    fclose(f);
    printf("\nBack to teacher's panel\n");
    return;
}


/*

this function will check if the given id and password is matched with the information in the file
1. Enter the teacher's id and password
2. open the file and start a loop to compare the given info and the info in the file
3. if match return 1 else 0

*/

int teacher_check()
{
    printf("\nEnter Your ID : ");
    fflush(stdout);
    scanf("%s",teach.id);
    printf("Enter your password : ");
    scanf("%s",teach.pass);

    FILE *f;
    teacher t;
    f=fopen("teacherinfo.txt","r");
    int x=0;
    int tsize=sizeof(teacher);
    while(fread(&t,sizeof(teacher),1,f))
    {
        if(!strcmp(teach.id,t.id) && !strcmp(teach.pass,t.pass))
        {
            x=1;
            fseek(f,-tsize,SEEK_CUR);
            fread(&teach,sizeof(teacher),1,f);
            //teach is a element of teacher structure declared globally
            //this fseek and fread function is used to save all the information of the teacher logged in
            //because this information will be needed during marks assigning
            break;
        }
    }
    fclose(f);
    return x;
}

void teacher_panel()
{
    if(!teacher_check())
    {
        printf("Invalid ID or Password\n");
        return;
    }


    while(1)
    {
        int x;
        printf("\n________ Teacher's Panel ________\n\n\n1. provide class test marks\n2. find a student\n3. count student\n4. Exit\nEnter your choice : ");
        fflush(stdout);
        scanf("%d",&x);

        if(x==1)assigning_marks(teach);
        else if(x==2)find_student();
        else if(x==3) student_counting();
        else if(x==4)
        {
            printf("\n\nGood bye teacher.\n");
            return;
        }
    }
    printf("\n\nGood bye teacher\n\n");

}


/*
  1. First find the student form the file
  2. Enter the course number of which the marks to give
*/

void check_mark(student st1)
{
    student st2;
    FILE *f=fopen("studentinfo.txt","r");
    int target=0;
    while(fread(&st2,sizeof(student),1,f))
    {
        if(!strcmp(st1.id,st2.id) && !strcmp(st1.pass,st2.pass)) break;
        //comparing the logged in student's info and the info of stored in the file
    }
    fclose(f);
    for(; ;)
    {
        printf("\nEnter the course number of Which marks you want to see(or enter 0 to exit) : ");
        int cours;
        scanf("%d",&cours);

        //the value of the index equal to the course number given in input of the marks array is the desired marks
        if(cours==0)break;
        if(st2.marks[cours]==-1)
        {
            printf("Result is not published yet or you don't study this ocurse!\n");
            continue;
        }
        printf("The obtained marks of in this course is %d\n\n",st2.marks[cours]);
    }
    printf("\nBack to student's panel\n");
    return;
}

//checking if the given student's id and password are matched with the information in the file
int check_student()
{
    printf("Enter id : ");
    fflush(stdout);
    student st1;
    scanf("%s",st1.id);
    printf("Enter Password : ");
    scanf("%s",st1.pass);
    FILE *f;
    student st2;
    f=fopen("studentinfo.txt","r");
    int check=0;
    while(fread(&st2,sizeof(student),1,f)==1)
    {
        if(!strcmp(st1.id,st2.id) && !strcmp(st1.pass,st2.pass))
        {
            check=1;
            fseek(f,-sstruc_size,SEEK_CUR);
            stu=st2;
            //stu is a element of student structure declared globally
            //preserving the logged in student's information as it'll required to check the marks

            break;
        }
    }
    fclose(f);
    return check;

}

//it will control the student's functions
void student_panel()
{
    int s=check_student();
    if(!s)
    {
        printf("Invalid id or password\ntry again letter\n");
        return;
    }

    printf("  \nWelcome %s %s\n",stu.firstname,stu.lastname);
    fflush(stdout);
    while(1)
    {
        printf("\n________Student's Panel________\n1. View Marks\n2. Exit\nEnter your Choice : ");
        int choice;
        scanf("%d",&choice);
        if(choice==2)
        {
            printf("\nGood bye %s %s\n\n",stu.firstname,stu.lastname);
            break;
        }
        else check_mark(stu);
    }
    printf("Enter 0 to exit or log in again!\n");
}



/*
  this is the main file in which the user input if he is admin or teacher of student
  then the individual functions are called

*/
int main()
{
    printf("\t\t KHULNA UNIVERSITY OF ENGINEERING & TECHNOLOGY\n\t\t DEPARTMENT OF COMPUTER SCIENCE & ENGINEERING\n\t\t----------------------------------------------\n\n");
    printf("Welcome to student-teacher database of KUET\n");
    for(; ;)
    {
        printf("\nLog in as:\n 1. Admin\n 2. Teacher\n 3. Student\n 0. Exit\nEnter your choice :");
        int a;
        scanf("%d",&a);
        if(a==0)break;
        if(a==1) admin_panel();
        else if(a==2) teacher_panel();
        else student_panel();
    }

    return 0;
}


