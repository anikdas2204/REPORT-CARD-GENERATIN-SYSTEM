/*NAME : RC_GEN v3.2
  DEVELOPERS : DIPAK GHOSH, ANIK DAS*/

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<windows.h>
#include<stdlib.h>

char gvar;  //VARIABLE TO CHANGE DISPLAY SETTINGS
int r,c;    //VARIABLES TO STORE THE TERMINAL SIZE
HWND hWnd;  //HANDLE FOR MESSAGE BOX

//INFORMATION TAKEN FROM STUDENT USING STRUCTRE
struct student
{
    char rollno[20];
    char name[50];

    float att;

    float p_marks,e_marks,eng_marks,cs_marks,m_marks,chem_marks;

    int p_gp,chem_gp,cs_gp,e_gp,eng_gp,m_gp;           
    int p_cp,chem_cp,cs_cp,e_cp,eng_cp,m_cp;   
    int att_cu;

    char grade[2];
    float cgpa;
} st;

//STRUCTURE TO STORE CREDIT POINTS
struct credit_units
{
    int p_cu,chem_cu,cs_cu,e_cu,m_cu,eng_cu;
}cu;

//FILE POINTERS IN GLOBAL DECLALRATION
FILE *fptr;
FILE *fptr10;
FILE *fptr6;

//CREATING GOTOXY FUNCTION
COORD coord={0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//FUNCTION TO TAKE MULTI WORD STRIMG FROM USER
void getline(char *p, int max_size)
{
	char c='a';
	int count=0;
	while (((c=getche())!='\r') && (count<=max_size))
	{
		*p=c;
		p++;
		count++;
	}
	*p='\0';
    printf("\n");
}

//FUNCTION TO MAKE BOX
void box()
{
	int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < c; i++){ //TOP
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(c-1,0);
    printf("%c",187); //extreme right
    for(i = 1; i < r; i++){
        gotoxy(c-1, i);
        printf("%c",186);
    }
    gotoxy(c-1,r-1);
    printf("%c",188);
    for(i = c-2; i > 0; i--){ //bottom
        gotoxy(i,r-1);
        printf("%c",205);
    }
    gotoxy(0,r-1);
    printf("%c",200); //extreme left
    for(i = r-2; i > 0; i--){
        gotoxy(0,i);
        printf("%c",186);
    }
}

//DOCUMENTATION PAGE FOR MAIN MENU
void help_mainmenu()
{
    FILE *fptr7;
    char str1[5000];
    system("cls");
    if(gvar=='1')
	    system("COLOR 71");
	else
		system("COLOR 1");        
    fptr7 = fopen("mainmenu.txt","r");
    if (fptr7==NULL)
    {
        printf("FILE IS NOT AVAILABLE");
    }
    else
    {
        while(fgets(str1,5000,fptr7)!=NULL)
        {
            printf("%s",str1);
        }
    }
    fclose(fptr7);
    getch();
}

void help_creditmenu()
{
    FILE *fptr5;
    char str1[5000];
    system("cls");
    if(gvar=='1')
	    system("COLOR 76");
	else
		system("COLOR 6");        
    fptr5 = fopen("creditmenu.txt","r");
    if (fptr5==NULL)
    {
        printf("FILE IS NOT AVAILABLE");
    }
    else
    {
        while(fgets(str1,5000,fptr5)!=NULL)
        {
            printf("%s",str1);
        }
    }
    fclose(fptr5);
    getch();
}

//DOCUMENTATION PAGE FOR RESULT MENU
void help_resultmenu()
{
    FILE *fptr8;
    char str2[5000];
    system("cls");
    fptr8 = fopen("resultmenu.txt","r");
    if (fptr8==NULL)
    {
        printf("FILE IS NOT AVAILABLE");
    }
    else
    {
        while(fgets(str2,5000,fptr8)!=NULL)
        {
            printf("%s",str2);
        }
    }
    fclose(fptr8);
    getch();
}

//DOCUMENTATION PAGE FOR ENTRY/EDIT MENU
void help_entryeditmenu()
{
    FILE *fptr9;
    char str3[5000];
    system("cls");
    fptr9 = fopen("entryeditmenu.txt","r");
    if (fptr9==NULL)
    {
        printf("FILE IS NOT AVAILABLE");
    }
    else
    {
        while(fgets(str3,5000,fptr9)!=NULL)
        {
            printf("%s",str3);
        }
    }
    fclose(fptr9);
    getch();
}

//FUNCTION TO CHECK THE RANGE OF VALUES ENTERED BY THE USER
float fnCheckRange(float fVal)
{
    float fNewVal=0;

    if (fVal <= 100 && fVal >= 0)
    {
        return fVal;
    }
    else
    {
        MessageBox(hWnd,
                   TEXT("VALUE SHOULD BE BETWEEN 0 & 100"),
                   TEXT("INVALID ENTRY"),
                   MB_OK | MB_ICONERROR);
        do
        {
            printf("\tENTER A NEW VALUE : ");
            scanf("%f",&fVal);
        }while (fVal <=0 && fVal>=100);
        return fVal;
    }
}

//FUNCTION TO PREVENT ROLL NUMBER DUPLICACY
int check_roll(char x[20])
{
    fptr = fopen("student.dat","rb");
    while ((fread(&st,sizeof(st),1,fptr))>=0)
    {
        if (strcmp(st.rollno,x)==0)
            return 1;
        else
            return 0;
    }
    fclose(fptr);
}
//ENTRY  FOR CREDIT UNIT POINTS
void take_cu()
{
    fptr10 = fopen("cu.dat","wb");
    printf("Enter the Credit Units for each subject : ");
    printf("\n for Physics  : ");
    scanf("%d",&cu.p_cu);
    printf("\n for Chemistry  : ");
    scanf("%d",&cu.chem_cu);
    printf("\n for Electrical  : ");
    scanf("%d",&cu.e_cu);
    printf("\n for English  : ");
    scanf("%d",&cu.eng_cu);
    printf("\n for Mathematics  : ");
    scanf("%d",&cu.m_cu);
    printf("\n for Computer Science  : ");
    scanf("%d",&cu.cs_cu);
    fwrite(&cu,sizeof(cu),1,fptr10);
    printf("THE CREDIT UNITS HAVE BEEN TAKEN SUCCESSFULLY!");
    fclose(fptr10);
    getch();
}

//DISPLAY THE CURRENT CREDIT POINTS
void display_cu()
{
    fptr10 = fopen("cu.dat","rb");
    printf("CURRENT CREDIT UNITS FOR EACH SUBJECT ARE AS FOLLOWS :-");
    while((fread(&cu,sizeof(cu),1,fptr10)) > 0)
    {
        printf("\n\nfor Physics : %d",cu.p_cu);
        printf("\nfor Chemistry : %d",cu.chem_cu);
        printf("\nfor Electrical : %d",cu.e_cu);
        printf("\nfor English : %d",cu.eng_cu);
        printf("\nfor Mathematics : %d",cu.m_cu);
        printf("\nfor Computer Science  : %d",cu.cs_cu);
    }
    fclose(fptr10);
    getch();
}

//FUNCTION TO CALCULATE GRADE POINTS FOR EACH SUBJECT
 float cal_cgpa(float marks)
{
    if (marks>90)
        return 10;
    else if (marks>80 && marks<=90)
        return 9;
    else if (marks>70 && marks<=80)
        return 8;
    else if (marks>60 && marks<=70)
        return 7;
    else if (marks>50 && marks<=60)
        return 6;
    else if (marks>40 && marks<=50)
        return 5;
    else if (marks>30 && marks<=40)
        return 4;
    else if (marks>20 && marks<=30)
        return 3;
    else if (marks>10 && marks<=20)
        return 2;
    else if(marks>0 && marks<=10)
        return 1;
    else
        return 0;
}

//FUNCTION TO CALCULATE GRADE FOR EACH STUDENT
void grade_cal(float cg)
{
    if (cg>9.0)
        strcpy(st.grade,"A1");
    else if (cg>8.0 && cg<=9.0)
        strcpy(st.grade,"A2");
    else if (cg>7.0 && cg<=8.0)
        strcpy(st.grade,"B1");
    else if (cg>6.0 && cg<=7.0)
        strcpy(st.grade,"B2");
    else if (cg>5.0 && cg<=6.0)
        strcpy(st.grade,"C1");
    else if (cg>4.0 && cg<=5.0)
        strcpy(st.grade,"C2");
    else if (cg>3.0 && cg<=4.0)
        strcpy(st.grade,"D");
    else if (cg>2.0 && cg<=3.0)
        strcpy(st.grade,"E");
    else
        strcpy(st.grade,"F"); 
}

//Function for taking records of students
void write_student()
{
    char r[20];
    int flag;
    float a;
    float p1,chem1,cs1,e1,eng1,m1;
    int p=0,chem=0,cs=0,e=0,eng=0,m=0;                  //COPIES OF THE INDIVIDUAL CREDIT UNITS
    int tot_cu = 0;                            //TO CALCULATE THE TOTAL CREDIT UNITS  & CREDIT POINTS ATTAINED FOR THE CALCULATION PURPOSE
    printf("\n\t\t\t\t\tPLEASE ENTER THE DETAILS OF THE STUDENT\n");
    printf("\n\tEnter the Roll Number of the student :");
    scanf("%s",&r);
    flag=check_roll(r);
    if (flag == 1)
    {
        printf("\tSTUDENT WITH THIS ROLL NUMBER ALREADY EXISTS! TRY AGAIN WITH OTHER ROLL NUMBER");
        exit(0);
    }
    else
    {
        fptr=fopen("student.dat","ab");
        strcpy(st.rollno,r);
    }
    printf("\tEnter the Name of the student :");
    getline(st.name,50);
    fflush(stdin);
    printf("\tEnter the Aggregate Attendance in percentage of the student : ");
    scanf("%f",&a);

    st.att = fnCheckRange(a);

    if (st.att >= 75)
    {
        printf("\tEnter the Marks in Physics out of 100 :");
        scanf("%f",&p1);

        st.p_marks = fnCheckRange(p1);

        printf("\tEnter the Marks in Electrical out of 100 :");
        scanf("%f",&e1);

        st.e_marks = fnCheckRange(e1);

        printf("\tEnter the Marks in English out of 100 :");
        scanf("%f",&eng1);

        st.eng_marks = fnCheckRange(eng1);

        printf("\tEnter the Marks in Computer Science out of 100 :");
        scanf("%f",&cs1);

        st.cs_marks = fnCheckRange(cs1);

        printf("\tEnter the Marks in Mathematics out of 100 :");
        scanf("%f",&m1);

        st.m_marks = fnCheckRange(m1);

        printf("\tEnter the Marks in Chemistry out of 100 :");
        scanf("%f",&chem1);

        st.chem_marks = fnCheckRange(chem1);

        fptr10 = fopen("cu.dat","rb");
        while((fread(&cu,sizeof(cu),1,fptr10))>0)
        {
            p=cu.p_cu;
            chem=cu.chem_cu;
            e=cu.e_cu;
            eng=cu.eng_cu;
            cs=cu.cs_cu;
            m=cu.m_cu;
        }
        tot_cu = p+chem+cs+e+m+eng;
        st.p_gp=cal_cgpa(st.p_marks);
        st.p_cp=st.p_gp*p;
        st.e_gp=cal_cgpa(st.e_marks);
        st.e_cp=st.e_gp*e;
        st.cs_gp=cal_cgpa(st.cs_marks);
        st.cs_cp=st.cs_gp*cs;
        st.chem_gp=cal_cgpa(st.chem_marks);
        st.chem_cp=st.chem_gp*chem;
        st.eng_gp=cal_cgpa(st.eng_marks);
        st.eng_cp=st.eng_gp*eng;
        st.m_gp=cal_cgpa(st.m_marks);
        st.m_cp=st.m_gp*m;
        st.att_cu=st.p_cp+st.cs_cp+st.chem_cp+st.e_cp+st.eng_cp+st.m_cp;
        st.cgpa=st.att_cu/tot_cu;
        grade_cal(st.cgpa);
        fclose(fptr10);
        fwrite(&st,sizeof(st),1,fptr);
        fclose(fptr);
        
        MessageBox(hWnd,
                   TEXT("STUDENT'S RECORD SAVED SUCCESSFULLY"),
                   TEXT("TASK CONFIRMATION MESSAGE"),
                   MB_ICONINFORMATION | MB_OK);
    }
    else
    {
        MessageBox(hWnd,
                   TEXT("STUDENT IS DETAINED DUE TO LOWER ATTENDANCE AND IS ADVISED TO REPEAT THE CURRENT ACADEMIC SESSION!"),
                   TEXT("INFORMATION"),
                   MB_ICONINFORMATION | MB_OK);

        st.p_marks = 0;
        st.e_marks = 0;
        st.eng_marks = 0;
        st.cs_marks = 0;
        st.m_marks =0;
        st.chem_marks = 0;
        fptr10 = fopen("cu.dat","rb");
        while((fread(&cu,sizeof(cu),1,fptr10))>0)
        {
            p=cu.p_cu;
            chem=cu.chem_cu;
            e=cu.e_cu;
            eng=cu.eng_cu;
            cs=cu.cs_cu;
            m=cu.m_cu;
        }
        tot_cu = p+chem+cs+e+m+eng;
        st.p_gp=cal_cgpa(st.p_marks);
        st.p_cp=st.p_gp*p;
        st.e_gp=cal_cgpa(st.e_marks);
        st.e_cp=st.e_gp*e;
        st.cs_gp=cal_cgpa(st.cs_marks);
        st.cs_cp=st.cs_gp*cs;
        st.chem_gp=cal_cgpa(st.chem_marks);
        st.chem_cp=st.chem_gp*chem;
        st.eng_gp=cal_cgpa(st.eng_marks);
        st.eng_cp=st.eng_gp*eng;
        st.m_gp=cal_cgpa(st.m_marks);
        st.m_cp=st.m_gp*m;
        st.att_cu=st.p_cp+st.cs_cp+st.chem_cp+st.e_cp+st.eng_cp+st.m_cp;
        st.cgpa=st.att_cu/tot_cu;
        grade_cal(st.cgpa);
        fclose(fptr10);
        fwrite(&st,sizeof(st),1,fptr);
        fclose(fptr);
    }
}

//FUNCTION TO DISPLAY ALL RECORDS
void display_all()
{
    system("cls");
    printf("\n\n                     AVAILABLE RECORDS\n\n");
    fptr=fopen("student.dat","rb");
    while(1)
    {
        if (fread(&st,sizeof(st),1,fptr)>0)
        {
            printf("\n\tRoll number of Student : %s",st.rollno);
            printf("\n\tName of Student : %s",st.name);
            printf("\n\tAttendance in percentage : %f",st.att);
            printf("\n\tMarks of Student in Physics: %f",st.p_marks);
            printf("\n\tMarks of Student in Electrical: %f",st.e_marks);
            printf("\n\tMarks of Student in English: %f",st.eng_marks);
            printf("\n\tMarks of Student in Computer Science: %f",st.cs_marks);
            printf("\n\tMarks of Student in Mathematics: %f",st.m_marks);
            printf("\n\tMarks of Student in Chemistry: %f",st.chem_marks);
            printf("\n\tCumulative Grade Points : %d",st.att_cu);
            printf("\n\tGrade : %s",st.grade);
            printf("\n\tCGPA : %f",st.cgpa);
            printf("\n\n=======================================================================================================================\n");
        }
        else
        {
            MessageBox(hWnd,
                       TEXT("THERE ARE NO MORE RECORDS TO SHOW"),
                       TEXT("INFORMATION"),
                       MB_OK | MB_ICONERROR);
            break;
        }   
    }
    fclose(fptr);
    getch();
}

//FUNCTION TO DISPALY A SPECIFIC RECORD
void display_sp(char n[20])
{
    int flag=0;
    int p=0,e=0,chem=0,eng=0,m=0,cs=0;
    fptr=fopen("student.dat","rb");
    fptr10 = fopen("cu.dat","rb");
    while((fread(&cu,sizeof(cu),1,fptr10))>0)
    {
        p=cu.p_cu;
        chem=cu.chem_cu;
        e=cu.e_cu;
        eng=cu.eng_cu;
        cs=cu.cs_cu;
        m=cu.m_cu;
    }
    fclose(fptr10);
    while((fread(&st,sizeof(st),1,fptr))>0 && flag==0)
    {
        if (strcmp(st.rollno,n)==0)
        {
            system("cls");
            printf("\n\n======================================================================================================================\n\n");
            printf("    ROLL NUMBER :    %s",st.rollno);
            printf("\n    NAME        :    %-44s",st.name);
            printf("\n    ATTENDANCE  :    %-24f",st.att);
            printf("\n\n    ===============================================================\n");
            printf("        SUBJECT       CREDIT UNIT  MARKS  GRADE POINT  CREDIT POINT  ");
            printf("\n    ===============================================================\n");
            printf("    PHYSICS           %-13d%-5.2f%+6d%+12d",p,st.p_marks,st.p_gp,st.p_cp);
            printf("\n    MATHEMATICS       %-13d%-5.2f%+6d%+12d",m,st.m_marks,st.m_gp,st.m_cp);
            printf("\n    CHEMISTRY         %-13d%-5.2f%+6d%+12d",chem,st.chem_marks,st.chem_gp,st.chem_cp); 
            printf("\n    ELECTRICAL        %-13d%-5.2f%+6d%+12d",e,st.e_marks,st.e_gp,st.e_cp);
            printf("\n    COMPUTER SCIENCE  %-13d%-5.2f%+6d%+12d",cs,st.cs_marks,st.cs_gp,st.cs_cp);
            printf("\n    ENGLISH           %-13d%-5.2f%+6d%+12d",eng,st.eng_marks,st.eng_gp,st.eng_cp);
            printf("\n    ===============================================================\n\n");
            printf("    CUMULATIVE CREDIT POINT: %d",st.att_cu);
            printf("\n    GRADE: %s",st.grade);
            printf("                CGPA: %f",st.cgpa);
            printf("\n\n======================================================================================================================\n");
            flag=1;
        }
    }
    if(flag==0)
    {
        MessageBox(hWnd,
                   TEXT("RECORD DOES NOT EXIST IN THE STUDENT DATABASE"),
                   TEXT("INFORMATION"),
                   MB_OK | MB_ICONERROR);
    }
    fclose(fptr);
    getch();
}

//FUNCTION TO DELETE A RECORD
void delete_student(char rnum[20])
{
    FILE *fptr2;
    system("cls");
    fptr=fopen("student.dat","rb");
    fptr2=fopen("Tempstu.dat","wb");
    rewind(fptr);
    while((fread(&st,sizeof(st),1,fptr))>0)
    {
        if(strcmp(st.rollno,rnum)!=0)
        {
            fwrite(&st,sizeof(st),1,fptr2);
        }
    }
    fclose(fptr2);
    fclose(fptr);
    remove("student.dat");
    rename("Tempstu.dat","student.dat");
    MessageBox(hWnd,
                   TEXT("RECORD DELETD FROM THE STUDENT DATABASE"),
                   TEXT("INFORMATION"),
                   MB_OK | MB_ICONERROR);
    getch();
}

//FUNCTION TO DELETE ALL RECORDS
void delete_all()
{
    char cho;
    system("cls");
	if(gvar=='1')
		system("COLOR 75");
	else
		system("COLOR 5");
	box();
    printf("\n\tARE YOU SURE YOU WANT TO DELETE ALL EXISTING RECORDS?");
    printf("\n\t1. YES");
    printf("\n\t2. NO");
    printf("\n\n\t ENTER YOUR CHOICE (1/2) : ");
    cho=getche();
    switch(cho)
    {
        case '1': 
        {
            remove("student.dat");
            MessageBox(hWnd,
                       TEXT("ALL EXISTING RECORDS HAVE BEEN REMOVED FROM THE STUDENT DATABASE"),
                       TEXT("TASK CONFIRMEATION MESSAGE"),
                       MB_OK | MB_ICONINFORMATION);
        }
        break;
        case '2': break;
        default : printf("\a");
                  delete_all();
    }  
}

//FUNCTION TO MODIFY STUDENT'S DETAILS
void modify_student()
{
    char rnum[20];
    int flag=0;
    int p=0,m=0,e=0,chem=0,cs=0;
    float a;
    float p1,e1,chem1,m1,cs1,eng1;
    int eng=0;
    int tot_cu;
    FILE *fptr3;
    system("cls");
    printf("\n\n\t\t\t\t\t\t\tTO MODIFY");
    printf("\n\n\tPlease Enter the Roll number of the Student : ");
    scanf("%s",&rnum);
    fptr=fopen("student.dat","rb+");
    while((fread(&st,sizeof(st),1,fptr))>0)
    {
        if (strcmp(st.rollno,rnum)==0)
        {
            printf("\n\t\tDETAILS AVAILABLE!");
            printf("\n\n\tRoll number of Student : %s",st.rollno);
            printf("\n\tName of Student : %s",st.name);
            printf("\n\tAttendance : %f",st.att);
            printf("\n\tMarks of Student in Physics: %f",st.p_marks);
            printf("\n\tMarks of Student in Electrical: %f",st.e_marks);
            printf("\n\tMarks of Student in English: %f",st.eng_marks);
            printf("\n\tMarks of Student in Computer Science: %f",st.cs_marks);
            printf("\n\tMarks of Student in Mathematics: %f",st.m_marks);
            printf("\n\tMarks of Student in Chemistry: %f",st.chem_marks);
            printf("\n\tCumulative Grade Points : %d",st.att_cu);
            printf("\n\tGrade : %s",st.grade);
            printf("\n\tCGPA : %f",st.cgpa);
            printf("\n\n=======================================================================================================================\n");
            printf("\nENTER THE MODIFIED DETAILS FOR ROLL NUMBER : %s",rnum);
            strcpy(st.rollno,rnum);
            flag=1;
            printf("\nEnter the Name of the student :");
            getline(st.name,50);
            fflush(stdin);
            printf("Enter the Aggregate Attendance in percentage of the student : ");
            scanf("%f",&a);

            st.att = fnCheckRange(a);

            if (st.att >= 75)
            {
                printf("\tEnter the Marks in Physics out of 100 :");
                scanf("%f",&p1);

                st.p_marks = fnCheckRange(p1);

                printf("\tEnter the Marks in Electrical out of 100 :");
                scanf("%f",&e1);

                st.e_marks = fnCheckRange(e1);

                printf("\tEnter the Marks in English out of 100 :");
                scanf("%f",&eng1);

                st.eng_marks = fnCheckRange(eng1);

                printf("\tEnter the Marks in Computer Science out of 100 :");
                scanf("%f",&cs1);

                st.cs_marks = fnCheckRange(cs1);

                printf("\tEnter the Marks in Mathematics out of 100 :");
                scanf("%f",&m1);

                st.m_marks = fnCheckRange(m1);

                printf("\tEnter the Marks in Chemistry out of 100 :");
                scanf("%f",&chem1);

                st.chem_marks = fnCheckRange(chem1);

                fptr10 = fopen("cu.dat","rb");
                while((fread(&cu,sizeof(cu),1,fptr10))>0)
                {
                    p=cu.p_cu;
                    chem=cu.chem_cu;
                    e=cu.e_cu;
                    eng=cu.eng_cu;
                    cs=cu.cs_cu;
                    m=cu.m_cu;
                }
                tot_cu = p+chem+cs+e+m+eng;
                st.p_gp=cal_cgpa(st.p_marks);
                st.p_cp=st.p_gp*p;
                st.e_gp=cal_cgpa(st.e_marks);
                st.e_cp=st.e_gp*e;
                st.cs_gp=cal_cgpa(st.cs_marks);
                st.cs_cp=st.cs_gp*cs;
                st.chem_gp=cal_cgpa(st.chem_marks);
                st.chem_cp=st.chem_gp*chem;
                st.eng_gp=cal_cgpa(st.eng_marks);
                st.eng_cp=st.eng_gp*eng;
                st.m_gp=cal_cgpa(st.m_marks);
                st.m_cp=st.m_gp*m;
                st.att_cu=st.p_cp+st.cs_cp+st.chem_cp+st.e_cp+st.eng_cp+st.m_cp;
                st.cgpa=st.att_cu/tot_cu;
                grade_cal(st.cgpa);
                fclose(fptr10);
                MessageBox(hWnd,
                           TEXT("STUDENT'S RECORD SAVED SUCCESSFULLY"),
                           TEXT("TASK CONFIRMATION MESSAGE"),
                           MB_ICONINFORMATION |MB_OK);
            }
            else
            {
                MessageBox(hWnd,
                           TEXT("STUDENT IS DETAINED DUE TO LOWER ATTENDANCE AND IS ADVISED TO REPEAT THE CURRENT ACADEMIC SESSION!"),
                           TEXT("INFORMATION"),
                           MB_ICONINFORMATION |MB_OK);

                st.p_marks = 0;
                st.e_marks = 0;
                st.eng_marks = 0;
                st.cs_marks = 0;
                st.m_marks =0;
                st.chem_marks = 0;
                fptr10 = fopen("cu.dat","rb");
                while((fread(&cu,sizeof(cu),1,fptr10))>0)
                {
                    p=cu.p_cu;
                    chem=cu.chem_cu;
                    e=cu.e_cu;
                    eng=cu.eng_cu;
                    cs=cu.cs_cu;
                    m=cu.m_cu;
                }
                tot_cu = p+chem+cs+e+m+eng;
                st.p_gp=cal_cgpa(st.p_marks);
                st.p_cp=st.p_gp*p;
                st.e_gp=cal_cgpa(st.e_marks);
                st.e_cp=st.e_gp*e;
                st.cs_gp=cal_cgpa(st.cs_marks);
                st.cs_cp=st.cs_gp*cs;
                st.chem_gp=cal_cgpa(st.chem_marks);
                st.chem_cp=st.chem_gp*chem;
                st.eng_gp=cal_cgpa(st.eng_marks);
                st.eng_cp=st.eng_gp*eng;
                st.m_gp=cal_cgpa(st.m_marks);
                st.m_cp=st.m_gp*m;
                st.att_cu=st.p_cp+st.cs_cp+st.chem_cp+st.e_cp+st.eng_cp+st.m_cp;
                st.cgpa=st.att_cu/tot_cu;
                grade_cal(st.cgpa);
                fclose(fptr10);
                getch();
            }
            fseek(fptr,-(long)sizeof(st),SEEK_CUR);
            fwrite(&st,sizeof(st),1,fptr);
            break;
        }
	}
    if (flag==0)
    {
        MessageBox(hWnd,
                   TEXT("RECORD DOES NOT EXIST IN THE STUDENT DATABASE"),
                   TEXT("INFORMATION"),
                   MB_OK | MB_ICONERROR);
	}
    fclose(fptr);
}

//FUNCTION FOR RESULT MENU
void result()
{
    int ans;
    char choice, rno[20];
    system("cls");
    if(gvar=='1')
	    system("COLOR 72");
	else
		system("COLOR 2");
    box();
    gotoxy(52,5);
    printf("RESULT MENU");
    printf("\n\t1.DISPLAY ALL RECORDS");
    printf("\n\t2.DISPLAY A STUDENT'S RECORD");
    printf("\n\t3.HELP");
    printf("\n\t4.BACK TO MAIN MENU");
    printf("\n\n\t  ENTER YOUR CHOICE(1/2/3/4) : ");
    ans=getche();
    switch(ans)
    {
        case '1': if(gvar=='1')
	    			system("COLOR 73");
				else
					system("COLOR 3");
    			display_all();
                break;

        case '2': if(gvar=='1')
                    system("COLOR 73");
                else
                    system("COLOR 3");
                system("cls");
                box();
                printf("ENTER THE ROLL NUMBER OF THE STUDENT : ");
                scanf("%s",&rno);
                display_sp(rno);
                break;

        case '3': if(gvar=='1')
	    			system("COLOR 73");
				else
					system("COLOR 3");
                help_resultmenu();
                break;

        case '4': break;

        default :printf("\a");
    }
}

//INTRO FUNCTION
void intro()
{
    system("cls");
	system("COLOR 6");
	box();
    gotoxy(((c/2)-1),((r/2)-9));
    printf("STUDENT");
    gotoxy(((c/2)-3),((r/2)-6));
    printf("REPORT CARD");
    gotoxy(((c/2)-6),((r/2)-3));
    printf("GENERATION SYSTEM");
    gotoxy(((c/2)-6),((r/2)+1));
    printf("BROUGHT TO YOU BY:");
	gotoxy(((c/2)-8),((r/2)+2));
	printf("ANIK DAS-A91005219124");
	gotoxy(((c/2)-9),((r/2)+3));
	printf("DIPAK GHOSH-A91005219125");
	gotoxy(((c/2)-12),((r/2)+4));
	printf("SHRIJA CHATTERJEE-A91005219126");
	gotoxy(((c/2)-11),((r/2)+5));
	printf("ANUSHMITA DUTTA-A91005219128");
	gotoxy(((c/2)-9),((r/2)+6));
	printf("ANWESHA RAY-A91005219130");
    gotoxy(((c/2)-43),((r/2)+9));
    printf("COLLEGE: AMITY SCHOOL OF ENGINEERING AND TECHNOLOGY (ASET), AMITY UNIVERSITY KOLKATA (AUK)");
    getch();
}

//FUNCTION TO CHANGE DISPLAY SETTINGS
void change_disp()
{
	system("cls");
	if(gvar=='1')
	    system("COLOR 78");
	else
		system("COLOR 8");
	box();
	gotoxy(52,5);
	printf("DISPLAY MENU");
	printf("\n\n\t1. LIGHT MODE");
	printf("\n\t2. DARK MODE (Restore Default)");
	printf("\n\t3. BACK TO MAIN MENU");
	printf("\n\n\t PLEASE ENTER YOUR CHOICE(1/2/3) : ");
    gvar=getche();
    switch(gvar)
    {
    	case '1': system("cls");
    			  system("COLOR 78");
    			  box();
    	     	  printf("SETTINGS CHANGED TO LIGHT MODE.");
    	     	  break;
		case '2': system("cls");
    			  system("COLOR 8");
    			  box();
    			  printf("SETTINGS RESTORED TO DARK MODE.");
    			  break;
    	case '3': break;
    	default: printf("\a");
    }
	getch();    
}

//MAIN MENU FUNCTION FOR INSERTING RECORDS
void entry_menu()
{
    char ch2,rno[20];
    system("cls");
    if(gvar=='1')
	    system("COLOR 74");
	else
		system("COLOR 4");
	box();
    gotoxy(52,5);
    printf("ENTRY MENU");
    printf("\n\n\t1. ENTER STUDENT RECORDS");
    printf("\n\t2. MODIFY STUDENT'S RECORD");
    printf("\n\t3. DELETE A RECORD");
    printf("\n\t4. DELETE ALL RECORDS");
    printf("\n\t5. HELP");
    printf("\n\t6. BACK TO MAIN MENU");
    printf("\n\n\t PLEASE ENTER YOUR CHOICE(1/2/3/4/5/6) : ");
    ch2=getche();
    switch(ch2)
    {
        case '1': system("cls");
        		  if(gvar=='1')
	    			system("COLOR 75");
				  else
					system("COLOR 5");
				  box();
    			  write_student();
                  break;
        case '2': if(gvar=='1')
	    			system("COLOR 75");
				  else
					system("COLOR 5");
				  modify_student();
                  break;
        case '3': system("cls");
				  if(gvar=='1')
	    			system("COLOR 75");
				  else
					system("COLOR 5");
				  box();
    			  printf("\n\n\t\\t\t\t\t\t TO DELETE RECORD");
                  printf("\n\n\t Please Enter the Roll Number of the Student : ");
                  scanf("%s",&rno);
                  delete_student(rno);
                  break;
        case '4':
            {
                delete_all();
                getch();
            }
            break;
        case '5': if(gvar=='1')
					system("COLOR 75");
				  else
					system("COLOR 5");
                  help_entryeditmenu();
                  break;
        case '6': break;
        default: printf("\a");
                 entry_menu();
    }
}

//FUNCTION TO DISPLAY CREDIT MENU
void credit_menu()
{
    char ch10;
    system("cls");
    if(gvar=='1')
	    system("COLOR 76");
	else
		system("COLOR 6");
	box();
    gotoxy(52,5);
    printf("CREDIT UNITS MENU");
    printf("\n\n\t1. ENTRY / EDIT CREDIT UNITS");
    printf("\n\t2. DISPLAY CURRENT CREDIT UNITS");
    printf("\n\t3. HELP");
    printf("\n\t4. BACK TO MAIN MENU");
    printf("\n\n\tENTER YOUR CHOICE (1/2/3): ");
    ch10=getche();
    switch(ch10)
    {
        case '1' : system("cls");
                   if(gvar=='1')
                    system("COLOR 75");
				   else
					system("COLOR 5");
				   box();        
                   take_cu();
                   break;   
        case '2' : system("cls");
                   if(gvar=='1')
	    			system("COLOR 75");
				   else
					system("COLOR 5");
				   box();
                   display_cu();
                   break;
        case '3' : help_creditmenu();
                   break;
        case '4' : break;
        default: printf("\a");
                 credit_menu();
    }
}

//MAIN FUNCTION OF THE PROGRAM
int main(int argc,char *argv[])
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    hWnd = GetConsoleWindow();
    SetWindowLong(hWnd,GWL_STYLE,GetWindowLong(hWnd,GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX); 

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);         //GETTING THE TERMINAL SIZE OF THE USER SYSTEM
    c = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    r = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    char ch;
    intro();
    MessageBox(hWnd,
               "IT IS ADVISED TO GO TO THE HELP SECTION FOR EACH OF THE MENUS SO THAT YOU CAN USE THIS APPLICATION FLAWLESSLY!",
               "ADVICE",
               MB_ICONINFORMATION |MB_OK);
    do
    {
        system("cls");
        if(gvar=='1')
	    system("COLOR 71");
		else
		system("COLOR 1");
        box();
		gotoxy(52,5);
        printf("MAIN MENU");
        printf("\n\n\t1. RESULT MENU");
        printf("\n\t2. ENTRY/EDIT MENU");
        printf("\n\t3. CREDIT UNITS MENU");
        printf("\n\t4. CHANGE DISPLAY SETTINGS");
        printf("\n\t5. HELP");
        printf("\n\t6. EXIT");
        printf("\n\n\t   ENTER YOUR CHOICE (1/2/3/4/5/6) : ");
        ch=getche();
        switch(ch)
        {
            case '1':system("cls");
                     result();
                     break;
            case '2':entry_menu();
                     break;
            case '3':credit_menu();
                     break;
            case '4':change_disp();
            		 break;
            case '5':help_mainmenu();
                     break;
            case '6':exit(0);
            default:printf("\a");
        }
    }while(ch!='6');
    getch();
    return 0;
}

//PROGRAM ENDS