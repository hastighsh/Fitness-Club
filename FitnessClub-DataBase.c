#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 48
#define fieldLength 258

struct db_type
{
   char name[fieldLength];
   
   int age;

   int height;   // cm
   float bmi;
   char status[fieldLength] ;
};

 
char prompt_menu(void);
void enterNew(struct db_type * pArr[]);  
void init_list(struct db_type * pArr[]); 
void displayDB(struct db_type * pArr[]);   
void sortDB(struct db_type * pArr[]);
void updateRecord(struct db_type * pArr[]); 
void removeRecord(struct db_type * pArr[]);
void clearDB(struct db_type * pArr[]);


int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    char choice;
    for(; ;){
      choice = prompt_menu();
      //different prompts from the user
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
        
         case 's': sortDB(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
        
         case 'u': updateRecord(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }
     return 0;
}

/*Making prompt menu*/
char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("(U)pdate record\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay database\t|\n");
  
    printf("|    %-20s","(Q)uit");
    printf("*Case Insensitive*\t\t\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
    //scanf("%s", s);  
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
	 
 }
}


void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

/* delete all the records in the database */
void clearDB(struct db_type * pArr[]){
   char yn[3];
   printf("are you sure to clear database? (y) or (n)? ");
    
   fgets(yn,3,stdin);
   
   // complete the function by calling init_list();
   if( strcmp(yn, "Y") != 0 || strcmp(yn, "y") != 0){
      init_list(pArr);
   } else if(strcmp(yn, "N") != 0 || strcmp(yn, "n") != 0){
      return;
   }
   
}


/* input items into the database */
void enterNew(struct db_type * pArr[SIZE])
{  
   char name[fieldLength];
   char ageS[fieldLength];
   char heightS[fieldLength];
   char weightS[fieldLength];
   int age;
   int height;
   float weight;
   
   struct db_type * newEntry = malloc(sizeof(struct db_type));
   printf("name: "); 
   fgets(name, fieldLength, stdin);
   printf("age: ");
   fgets(ageS, fieldLength, stdin);
   age = atof(ageS);

   printf("height (cm): ");
   fgets(heightS, fieldLength, stdin);
   height = atoi(heightS);

   printf("weight (kg): ");
   fgets(weightS, fieldLength, stdin);
   weight = atof(weightS);

   
   

   float bmi = weight / (height*height/10000);


   char status[fieldLength] = {'\0'};
   if(bmi < 18.5){
      strcat(status, "Underweight");
   } else if (18.5 < bmi && bmi < 24.999){
      strcat(status, "Normal weight");
   } else if (25.0 < bmi && bmi < 29.999){
      strcat(status, "Overweight");
   } else if (30.0 < bmi && bmi < 34.999){
      strcat(status, "Obese class I");
   } else if (35.0 < bmi && bmi < 39.999){
      strcat(status, "Obese class II");
   } else {
      strcat(status, "Obese class III");
   }

   newEntry->age = age;
   strcat(newEntry->name, name);
   newEntry->height = height;
   newEntry->bmi = bmi;
   strcat(newEntry->status, status);

   int i;
   for(i = 0; pArr[i] != NULL; i++);
      pArr[i] = newEntry;

}


/* remove an existing item from the database */
void removeRecord (struct db_type * pArr[])	
{
   char name[fieldLength];
   int i, j;

   printf("enter full name to remove: ");
   fgets(name, fieldLength, stdin);

   for(i = 0; pArr[i] != NULL; i++){
      
      if(strcmp(pArr[i]->name, name) == 0){
         
         for(j = i; pArr[j] != NULL; j++){
            pArr[j] = pArr[j+1];
         }
      }
   }

   
}

/* display all the records in the database. Generate output with the same formaing as the sample output 
*/
void displayDB(struct db_type * pArr[]){
  
  int t;
  printf("===============================\n");
  for (t=0; t <SIZE ; t++)
  {
     if( pArr[t] != NULL)
     {
        printf("\nname:\t%s",   pArr[t]->name );  
        printf("age:\t%d",   pArr[t]->age );
        printf("\nheight:\t%d",   pArr[t]->height );
        printf("\nBMI:\t%.1f",   pArr[t]->bmi );
        printf("\nstatus:\t%s",   pArr[t]->status );

     } else {
      break;
     }
     printf("\n");
  }

  printf("========== %d records ==========\n", t);
  
 
}


 /* modify (update weight of) an existing member */
void updateRecord (struct db_type * pArr[])	{
  
  char weightS[5];
  float weight;
  int i = 0;
  char name[fieldLength];

  printf("enter full name to search: ");
  fgets(name, fieldLength, stdin);

  while(pArr[i] != NULL){
   if(strcmp(pArr[i]->name, name) == 0){
      printf("record found, enter new weight (kg): ");
      fgets(weightS, 5, stdin);
      weight = atof(weightS);
      
      float newBMI = weight / (pArr[i]->height*pArr[i]->height/10000);
      pArr[i]->bmi = newBMI;

      char status1[fieldLength] = {'\0'};
      if(newBMI < 18.5){
         strcat(status1, "Underweight");
      } else if (18.5 < newBMI && newBMI < 24.999){
         strcat(status1, "Normal weight");
      } else if (25.0 < newBMI && newBMI < 29.999){
         strcat(status1, "Overweight");
      } else if (30.0 < newBMI && newBMI < 34.999){
         strcat(status1, "Obese class I");
      } else if (35.0 < newBMI && newBMI < 39.999){
         strcat(status1, "Obese class II");
      } else {
         strcat(status1, "Obese class III");
      }

         strcat(pArr[i]->status," -> ");
         strcat(pArr[i]->status, status1);
      
      int len = strlen(name);
      name[len - 1] = '\0';
      printf("record [%s] updated successfully.", name);
      
      
   }
      i++;
  }
  
}

 
// sort the records, either by name or BMI. Prompt user for choice
void sortDB(struct db_type * pArr[])
{

   char nb[fieldLength];
   int i, j;

  printf("sort by name (n) or BMI (b)? ");
  fgets(nb, fieldLength, stdin);

  int smallest = 0;

  if(strcmp(nb, "n\n") == 0 ){

   for(i = 0; pArr[i] != NULL; i++){
      smallest = i;
      for(j = i; pArr[j] != NULL; j++){

         if(strcmp(pArr[j]->name, pArr[smallest]->name) < 0){
            smallest = j;
         }
      }
      struct db_type *temp = pArr[smallest];
      pArr[smallest] = pArr[i];
      pArr[i] = temp;
   }
  } else if (strcmp(nb, "b\n") == 0){

      for(i = 0; pArr[i] != NULL; i++){
      smallest = i;
      for(j = i; pArr[j] != NULL; j++){

         if(pArr[j]->bmi < pArr[smallest]->bmi){
            smallest = j;
         }
      }
      struct db_type *temp = pArr[smallest];
      pArr[smallest] = pArr[i];
      pArr[i] = temp;
   }
  }
}

