#include <stdio.h>
#include <string.h>
#include<stdlib.h>
FILE *fptr;


typedef struct donarInfo
{
    char name[40];
    char birthDay[15];
    char add[40];
    char bg[40];
    int age;
    long long int con;
    float hemo;


} PERSON ;

PERSON people;

void inputInfoOfDonar();///inser
void viewAllDonar();///view
void searchForDonar();///search
void deleteDonar();
void updateInfoOfDonar();
void shortAgeBasis();
int main()
{
    int choice;

    while (1){


        printf("\t\t\t\"\"Welcome UIU Blood Bank\"\"\n\n");
        printf("\t_________\"\"Press 1 for Donate Blood.\"\"_________\n\n");///insert
        printf("\t_________\"\"Press 2 for Request Blood.\"\"_________\n\n");///search
        printf("\t_________\"\"Press 3 for see Donar list.\"\"_________\n\n");///view
        printf("\t_________\"\"Press 4 for delete your info.\"\"_________\n\n");
        printf("\t_________\"\"Press 5 for update your information( opps sorry this side is under work try later) .\"\"_________\n\n");///update
        printf("\t_________\"\"Press 6 for short Donar list(age basis).\"\"_________\n\n");
        printf("\t_________\"\"Press 0 for Exit.\"\"_________\n\n");
        scanf("%d",&choice);
        getchar();
        if (choice==1){
            inputInfoOfDonar();
        } else if (choice==2){
            searchForDonar();
        } else if (choice==3){
            viewAllDonar();
        } else if (choice==4){
            deleteDonar();
        } else if (choice==5){
            updateInfoOfDonar();
        } else if (choice==6){
            shortAgeBasis();
        }
        else if (choice==0){
            break;
        }

        printf("\t\tEnter any key to continue\n");
        getchar();
    }


    return 0;
}
void inputInfoOfDonar(){
    fptr= fopen("data.txt","a");
    char address[50];

    if (fptr==NULL){
        printf("\n\tERROR CAN'T OPEN FILE");
        return;
    } else{
        printf("Name:");
        gets(people.name);


        printf("Birthday (dd/mm/yyyy):");
        gets(people.birthDay);


        printf("Present address:");
        gets(address);
        strupr(address);
        strcpy(people.add,address);



        printf("Blood Group:");
        gets(people.bg);


        printf("Age:");
        scanf("%d", &people.age);


        printf("Contact Number:+880");
        scanf("%lld", &people.con);


        printf("Hemoglobin:");
        scanf("%f", &people.hemo);

        fwrite(&people, sizeof(people),1,fptr);
        fclose(fptr);
    }
    printf("\t_________\"\"Information stored in database successfully_________\"\"\n");

}

void viewAllDonar(){
    fptr= fopen("data.txt","r");

    if (fptr==NULL){
        printf("\n\tERROR CAN'T OPEN FILE");
        return;
    } else{
        printf("\n\t\t\t\tDonar list\n");
        ////printf("\nName\tDate of Birth\t   Address\tBlood Group\tAge\tContact Number\tHemoglobin\n");
        while (fread(&people,sizeof(people),1,fptr)==1){

            printf("Name\t   : %s\nDate of Birth : %s\nAddress       : %s\nBlood Group   : %s\nAge\t      : %d\nContact Number : 0%lld\nHemoglobin    : %.3f\n",people.name,people.birthDay,people.add,people.bg,people.age,people.con,people.hemo);

        }
        fclose(fptr);

    }


}

void searchForDonar(){
    char bloodGroup[5];
    char address[50];
    int flag=0;
    FILE *fptr;
    fptr= fopen("data.txt","r");
    if (fptr==NULL){
        printf("\n\tERROR CAN'T OPEN FILE");
        return;
    } else{
        printf("Enter blood  group which you want:");
        fgets(bloodGroup, sizeof(bloodGroup),stdin);
        bloodGroup[strcspn(bloodGroup,"\n")]='\0';
        printf("Enter your desire location:");
        fgets(address, sizeof(address),stdin);
        address[strcspn(address,"\n")]='\0';
        strupr(address);

        while (fread(&people,sizeof(people),1,fptr)>0){
            if (strcmp(people.bg,bloodGroup)==0 && strcmp(people.add,address)==0){
                printf("Name\t   : %s\nDate of Birth : %s\nAddress       : %s\nBlood Group   : %s\nAge\t      : %d\nContact Number : %lld\nHemoglobin    : %.3f\n",people.name,people.birthDay,people.add,people.bg,people.age,people.con,people.hemo);
                flag=1;
            }
        }
        if (flag==0){
            printf("Not found");
        }
    }
    fclose(fptr);

}
void deleteDonar(){
    char na[40];
    int flag=0;
    FILE *fptr,*tempfptr;
    fptr= fopen("data.txt","r");
    if (fptr==NULL){
        printf("\n\tERROR CAN'T OPEN FILE");
        return;
    }else{
        printf("Enter your name for delete: ");
        fgets(na,sizeof (na),stdin);
        na[strcspn(na,"\n")]='\0';
        tempfptr= fopen("temp.txt","a");
        while (fread(&people, sizeof(people),1,fptr)==1){
            if (strcmp(na, people.name) != 0) {
                /// printf("Your info deleted successful\n");
                fwrite(&people, sizeof(people), 1, tempfptr);

            }
            else
                flag++;

        }
        /// printf("%d",flag);
        if (flag==0){
            printf("\t\t\tYour name isn't found\n");
        }
        if (flag!=0){
            printf("\t\t\tInformation delete successful\n");
        }
        fclose(fptr);
        fclose(tempfptr);

        remove("data.txt");
        rename("temp.txt","data.txt");


    }

}

void updateInfoOfDonar(){
    char namme[40];
    int flag=0;
    float newhemo;
    FILE *fptr= fopen("data.txt","r+");
    if (fptr==NULL){
        printf("\n\tERROR CAN'T OPEN FILE");
        return;
    } else{
        printf("Enter your name for update hemoglobin: ");
        fgets(namme,sizeof(namme),stdin );
        namme[strcspn(namme,"\n")]='\0';
        while (fread(&people,sizeof (people),1,fptr)>0 && flag==0){
            if (strcmp(namme,people.name)==0){
                flag=1;
                printf("Enter the new hemoglobin level: ");
                scanf("%f",&people.hemo);
                fflush(stdin);
                fseek(fptr,-(long )sizeof(people.name),1 );
                fwrite(&people.hemo,sizeof (people.hemo),1,fptr);
                printf("\n\t\t\tNew hemoglobin level updated\n");
            }
        }
        if (flag==0){
            printf("Error");
        }
    }
    fclose(fptr);


}
void shortAgeBasis(){
    PERSON temp;
    PERSON arr[50];

    int i=0,j,k=0;
    FILE *fptr= fopen("data.txt","r");
    if (fptr==NULL){
        printf("\n\t\tError!!!! Can't open file");
        return;
    }
    while (fread(&arr[i], sizeof(arr[i]),1,fptr)==1){
        i++; k++;
    }
    for ( i = 0; i<k ; ++i) {
        for ( j = 0; j <k-i-1 ; ++j) {
            if (arr[j].age>arr[j+1].age){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    fclose(fptr);
}



