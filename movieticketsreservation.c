#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>



typedef struct CLIENT_DETAILS CLIENT_DETAILS;
typedef struct USER USER;

struct CLIENT_DETAILS{
        char* ID;
        char* PASSWORD;
};



USER* CREATE_CLIENT(void);
void GET_CLIENT_DETAILS(CLIENT_DETAILS*);
USER* VERIFY_CLIENT(CLIENT_DETAILS*);
int VERIFY_ID(char*);


USER* C;


typedef struct MOVIE{
        int Id;
        char* Screen;
        char* Movie_name;
        char* Date;
        char* time;
        int booked[121];
        int filled;
}Movie;

typedef struct SELECTION{
        int booking_id;
        Movie *SELECTED_MOVIE;
        int number_of_seats;
        int selected_seats[15];
        struct SELECTION *next;
}Selection;

struct USER{
       CLIENT_DETAILS* C_D;
       Selection *SELECT;
       USER* next;
};

Movie* Create_Movie(void);
void Get_Movies_Info(Movie**);
void Print_Movies(Movie**);//prints movie details

USER* userlogin();
void generateTickets();

void Select_Seats();
void seatsprint(int*,int*);//print seats and screen
void insertseatno(int*,int); //insert seat no selected by user to array
void clearscr(int);

int get_book_Id(void);
int verify_book_Id(int,USER*);
void Cancel_Booking(int,USER*);




void main(){
        Selection* S;
        Movie* M[8];
        USER* U;//current user after login.

        //creates the structure for each movie.

          for(int i=0;i<8;i++){
                  *(M+i)=Create_Movie();
          }

         Get_Movies_Info(M); //stores the movie details in the M array.

        int choice;
        clearscr(50);
        printf("\n\n\t\t1.CREATE A NEW ACCOUNT.");
        printf("\n\t\t2.LOGIN TO AN EXISTING ACCOUNT.");
        printf("\n\t\t3.EXIT");
        clearscr(20);
        printf("\nEnter your choice:");
        scanf("%d",&choice);
        getchar();
        while(choice!=3){
                switch(choice){
                        case 1:{
                                       USER* temp;
                                       temp=CREATE_CLIENT();
                                       GET_CLIENT_DETAILS(temp->C_D);
                                       if(VERIFY_ID(temp->C_D->ID)){
                                               printf("\033[0;31m");

                                               printf("\nOOPS!!! Entered ID already taken!\nTRY with some other ID");
                                               printf("\033[0m");
                                       }
                                       else{

                                          //inserting the CLIENT node in the correct position;
                                          if(C==NULL){
                                               C=temp;
                                          }
                                          else{
                                               USER* ptr;
                                               ptr=C;
                                               while(ptr->next!=NULL){
                                                       ptr=ptr->next;
                                               }
                                               ptr->next=temp;
                                          }
                                          clearscr(18);
                                          printf("\nACCOUNT CREATED SUCCESSFULLY!!!");
                                          clearscr(10);
                                       }
                                       break;


                               }
                        case 2:{
                                       USER* ptr;
                                       CLIENT_DETAILS* temp;
                                       temp=(CLIENT_DETAILS*)malloc(sizeof(CLIENT_DETAILS));
                                       GET_CLIENT_DETAILS(temp);
                                       ptr=VERIFY_CLIENT(temp);
                                       if(ptr==NULL){
                                               clearscr(18);
                                               printf("\nINVALID USERNAME or PASSWORD!!!");
                                               clearscr(10);
                                       }
                                       else{
                                               clearscr(18);
                                               printf("\nSUCCESSFULLY LOGGED IN!!!");
                                               clearscr(10);
                                               U=ptr;


                                       //creates the movie structure
                                       clearscr(50);
                                       int choice;
                                        printf("\n\t\t\t\t\t\tSARR CINEMAS");
                                        clearscr(10);
                                        printf("\n\t\t1.DISPLAY MOVIE SCHEDULES\n");
                                        printf("\n\t\t2.BOOK TICKETS!!!\n");
                                        printf("\n\t\t3.Cancel the booking\n");
                                        printf("\n\t\t4.LOGOUT.\n\n");
                                        printf("\nEnter your choice:");
                                        scanf("%d",&choice);
                                        clearscr(30);


                                       while(choice!=4){
                                                switch(choice){
                                                       case 1:{
                                                           Print_Movies(M);
                                                           break;
                                                       }

                                                      case 2:{
                                                            int M_ID,no_of_seats;
                                                            Print_Movies(M);
                                                            clearscr(26);
                                                            printf("\nENTER THE ID:");
                                                            scanf("%d",&M_ID);//getting the user choice

                                                            if(M[M_ID-1]->filled >= 120){
                                                                 printf("\n\n\tHOUSEFULL\n");
                                                                 printf("\n\n\tHOUSEFULL\n");
                                                                 printf("\n\n\tHOUSEFULL\n");
                                                                 break;
                                                            }



                                                           //U = (struct USER*)malloc(sizeof(struct USER));
                                                           Selection *ptr;
                                                           ptr = U->SELECT;


                                                           S = (struct SELECTION*)malloc(sizeof(struct SELECTION));
                                                           S->next = NULL;
                                                           if(ptr==NULL){
                                                               ptr=S;
                                                               U->SELECT=S;
                                                           }
                                                           else{
                                                                  while(ptr->next!=NULL){
                                                                         ptr=ptr->next;
                                                                  }
                                                                  ptr->next= S;//it stores the user selected movie details

                                                                  ptr=ptr->next;
                                                             }

                                                             ptr->SELECTED_MOVIE = M[M_ID-1];

                                                             printf("\nEnter the number of seats: ");
                                                             scanf("%d",&no_of_seats);
                                                             if(no_of_seats > 15){
                                                                     printf("You can only book a maximum of 15 tickets. For Bulk Tickets Contact Office\n");
                                                              break;
                                                              }
                                                             ptr->number_of_seats = no_of_seats;

                                                             Select_Seats(ptr);
                                                             //printf("%d ",ptr->selected_seats[0]);
                                                             static int val=10000;
                                                             val=val+1;
                                                             ptr->booking_id=val;

                                                             clearscr(20);
                                                             generateTickets(ptr,U);
                                                             break;
                                                   }

                                        case 3:{
                                                            int  book_id;
                                                            book_id=get_book_Id();

                                                            if(verify_book_Id(book_id,U))
                                                               Cancel_Booking(book_id,U);
                                                            else
                                                               printf("\nBOOKING ID NOT FOUND!!!");
                                                             break;

                                               }


                                        default:{
                                                          printf("\nINVALID CHOICE!!!");
                                         }

                               }
                                printf("\n\t\t\t\t\t\tSARR CINEMAS");
                                clearscr(10);
                                printf("\n\t\t1.DISPLAY MOVIE SCHEDULES\n");
                                printf("\n\t\t2.BOOK TICKETS!!!\n");
                                printf("\n\t\t3.Cancel the booking\n");
                                printf("\n\t\t4.LOGOUT.\n\n");
                                printf("\nEnter your choice:");
                                scanf("%d",&choice);
                                clearscr(30);

                              }
                  }
                  U=NULL;//logout.
                  break;

                   }
                case 3:{

                       Selection *ptr;
                       Selection *ptr2;
                       ptr = U->SELECT;
                        while(ptr != NULL){
                                free(ptr->SELECTED_MOVIE->booked);
                                free(ptr->SELECTED_MOVIE);
                                free(ptr->selected_seats);
                                ptr2 = ptr;
                                ptr = ptr->next;
                                free(ptr2);

                                 }
                                 clearscr(50);
                                 exit(1);
                       }

                default:{
                            printf("\nINVALID CHOICE!!!");
                            break;
                        }
                }

        printf("\n\n\t\t1.CREATE A NEW ACCOUNT.");
        printf("\n\t\t2.LOGIN TO AN EXISTING ACCOUNT.");
        printf("\n\t\t3.EXIT");
        clearscr(20);
        printf("\nEnter your choice:");
        scanf("%d",&choice);
        getchar();
        }

}

USER* CREATE_CLIENT(void){
        USER* c;
        c=(USER*)malloc(sizeof(USER));
        c->next=NULL;
        c->C_D=(CLIENT_DETAILS*)malloc(sizeof(CLIENT_DETAILS));
        return c;
}

void GET_CLIENT_DETAILS(CLIENT_DETAILS* temp){
        temp->ID=(char*)malloc(sizeof(char));
        temp->PASSWORD=(char*)malloc(sizeof(char));

        printf("\nENTER YOUR ID:");
        fgets(temp->ID,32,stdin);
        temp->PASSWORD=getpass("\nENTER THE PASSWORD:");//this function doesn't show the password while entering.
        return ;
}
int VERIFY_ID(char* Temp_ID){
        USER* ptr;
        ptr=C;
        while(ptr!=NULL){
                if(strcmp(ptr->C_D->ID,Temp_ID)==0)
                        return 1;
                ptr=ptr->next;
        }
        return 0;

}

USER* VERIFY_CLIENT(CLIENT_DETAILS* temp){
        USER* ptr,*result;
        ptr=C;
        while(ptr!=NULL){
                if(strcmp(ptr->C_D->ID,temp->ID)==0){//checks whether the given ID matches the stored ID
                                if(strcmp(ptr->C_D->PASSWORD,temp->PASSWORD)==0){//checks whether if the given ID matches then the corresponding password matches
                                        result=ptr;
                                        return result;
                                }
                }
                ptr=ptr->next;
        }
        return NULL;
}






int get_book_Id(void){
        int val;
        printf("\nEnter the booking id:");
        scanf("%d",&val);
        return val;
}


int verify_book_Id(int book_id,USER* U){
        Selection* ptr;
        ptr=U->SELECT;
        while(ptr!=NULL){
                if(ptr->booking_id==book_id)
                        return 1;
                ptr=ptr->next;
        }

        if(ptr==NULL)
                return 0;
}

void Cancel_Booking(int book_id,USER* U){
        Selection* ptr,*pre_ptr;
        ptr=U->SELECT;
        while(ptr != NULL){//if the first node is to delete
            if(book_id == ptr->booking_id){
                for(int i=0; i<ptr->number_of_seats; i++){
                        ptr->SELECTED_MOVIE->booked[ptr->selected_seats[i]-100] = 0;
                }
                printf("\nTHE BOOKING %d CANCELLED!!!",ptr->booking_id);
                ptr->booking_id = -1;
            }
            ptr = ptr->next;
        }
        return;
}




void Get_Movies_Info(Movie** M){
       M[0]->Id=1;
       M[0]->Screen="S1";
       M[0]->Movie_name="AVATAR";
       M[0]->Date="10-11-2020";
       M[0]->time="9.00 AM";
       M[0]->filled=0;


        M[1]->Id=2;
        M[1]->Screen="S2";
        M[1]->Movie_name="DEADPOOL";
        M[1]->Date="10-11-2020";
        M[1]->time="9.00 AM";
        M[1]->filled=0;

        M[2]->Id=3;
        M[2]->Screen="S1";
        M[2]->Movie_name="THE LION KING";
        M[2]->Date="10-11-2020";
        M[2]->time="3.00 PM";
        M[2]->filled=0;

        M[3]->Id=4;
        M[3]->Screen="S2";
        M[3]->Movie_name="THE AVENGERS";
        M[3]->Date="10-11-2020";
        M[3]->time="3.00 PM";
        M[3]->filled=0;

        M[4]->Id=5;
        M[4]->Screen="S1";
        M[4]->Movie_name="AVATAR";
        M[4]->Date="10-11-2020";
        M[4]->time="7.00 PM";
        M[4]->filled=0;

        M[5]->Id=6;
        M[5]->Screen="S2";
        M[5]->Movie_name="DEADPOOL";
        M[5]->Date="10-11-2020";
        M[5]->time="7.00 PM";
        M[5]->filled=0;

        M[6]->Id=7;
        M[6]->Screen="S1";
        M[6]->Movie_name="THE LION KING";
        M[6]->Date="10-11-2020";
        M[6]->time="6.00 PM";
        M[6]->filled=0;

       M[7]->Id=8;
       M[7]->Screen="S2";
       M[7]->Movie_name="THE AVENGERS";
       M[7]->Date="10-11-2020";
       M[7]->time="6.00 PM";
       M[7]->filled=0;

        return;

}

Movie* Create_Movie(void){
        Movie* M;
        M=(Movie*)malloc(sizeof(struct MOVIE));
        return M;
}

void Print_Movies(Movie** M){
       printf("\n*----------------------------------------------------------------------------------------------------------------------------------------*");
        printf("\nID\t\tMOVIE NAME\t\t\tSHOW DATE\t\t\tSHOW TIME\t\tSCREEN");
        printf("\n*----------------------------------------------------------------------------------------------------------------------------------------*");
        for(int i=0;i<8;i++){
                printf("\n%d\t\t%-30s %-30s %-30s%s",M[i]->Id,M[i]->Movie_name,M[i]->Date,M[i]->time,M[i]->Screen);
        }

        return;

}

void Select_Seats(Selection* S){
  int seatno,counter = 0;
  char seatchar;
  char seatstr[10]; // to avoid unwanted exception,so set to 10 though 4 is enough

  S->selected_seats[15] = 0;
 //U->SELECT->SELECTED_MOVIE->booked;// seats reserved till now

  clearscr(20); //jus prints 20 newline chars instead of clrscr i used this..this is better
  seatsprint(S->SELECTED_MOVIE->booked,S->selected_seats); // print seats,seatarr has seats selected by the current user

  S->SELECTED_MOVIE->filled += S->number_of_seats;
  while(counter < S->number_of_seats){
      printf("\n\n\nEnter Seat Number (example:- A03,B10) [%d/%d] : ",counter+1,S->number_of_seats);
      scanf("%s",seatstr);

      if(strlen(seatstr) == 3 && ( (seatstr[0] >= 65 &&
         seatstr[0] <= 70) || (seatstr[0] >= 97 &&
         seatstr[0] <= 102) ) && seatstr[1] >= 48 &&
         seatstr[1] <= 50 && seatstr[2] >= 48 &&
         seatstr[2] <= 57){ //i am checking for invalid seat no to avoid unwanted errors u
                            // i will explain in chat
          sscanf(seatstr,"%c%d",&seatchar,&seatno);
          if(seatchar >= 97 && seatchar <= 102){
                  seatchar -= 32;
          }
          if(seatno >= 1 && seatno <= 20 && S->SELECTED_MOVIE->booked[(seatchar-65)*20 + seatno] != 1){
              clearscr(20);
              insertseatno(S->selected_seats,100 + (seatchar-65)*20 + seatno);
              S->SELECTED_MOVIE->booked[(seatchar-65)*20 + seatno] = 1;
              seatsprint(S->SELECTED_MOVIE->booked,S->selected_seats);
              counter++;
          }else if(S->SELECTED_MOVIE->booked[(seatchar-65)*20 + seatno] == 1){
              clearscr(20);
              seatsprint(S->SELECTED_MOVIE->booked,S->selected_seats);
              printf("Sorry,the seat is already selected\nSelect some other seat\n");
          }
          else{
              clearscr(20);
              seatsprint(S->SELECTED_MOVIE->booked,S->selected_seats);
              printf("Enter a valid seat number\n");
          }

      }
      else if(strlen(seatstr) == 2 && ( (seatstr[0] >= 65 &&
         seatstr[0] <= 70) || (seatstr[0] >= 97 &&
         seatstr[0] <= 102) ) && seatstr[1] >= 48 &&
         seatstr[1] <= 57){

          sscanf(seatstr,"%c%d",&seatchar,&seatno);
          if(seatchar >= 97 && seatchar <= 102){
                  seatchar -= 32;
          }

          if(seatno >= 1 && seatno <= 20 && S->SELECTED_MOVIE->booked[(seatchar-65)*20 + seatno] != 1){
              clearscr(20);
              insertseatno(S->selected_seats,100 + (seatchar-65)*20 + seatno);
              S->SELECTED_MOVIE->booked[(seatchar-65)*20 + seatno] = 1;
              seatsprint(S->SELECTED_MOVIE->booked,S->selected_seats);
              counter++;
          }
          else if(S->SELECTED_MOVIE->booked[(seatchar-65)*20 + seatno] == 1){
              clearscr(20);
              seatsprint(S->SELECTED_MOVIE->booked,S->selected_seats);
              printf("Sorry,the seat is already selected\nSelect some other seat\n");
          }
          else{
              clearscr(20);
              seatsprint(S->SELECTED_MOVIE->booked,S->selected_seats);
              printf("Enter a valid seat number\n");
          }

      }
      else{
          clearscr(20);
          seatsprint(S->SELECTED_MOVIE->booked,S->selected_seats);
          printf("Enter a valid seat number\n");
      }
  }
}

void insertseatno(int *arr,int a){

    int i,j;

    for(i = 0;i < 15;i++){
        if(*(arr+i) == 0){
            *(arr+i) = a;
            break;
        }
        else if(*(arr+i) < a){
            continue;
        }
        else if(*(arr+i) > a){
            j = i;
            while(*(arr+j+1) != 0){
                j++;
            }
            while(j >= i){
                *(arr+j+1) = *(arr+j);
                j--;
            }
            *(arr+j+1) = a;
            break;
        }
        else{
            printf("Seatno insert error\n");
            break;
        }
    }
}

void seatsprint(int *arr,int *arr2){
    int seatpoint = 0,i,j,k;

    for(k = 0;k < 6;k++){

        printf("\n\t\t");
        j = 100 + k * 20;

        for(i = 1;i <= 20;i++){
            if(j+i == *(arr2+seatpoint)){
                printf("\033[1;32m");
            }
            else if(*(arr+(k*20)+i) == 1){
                printf("\033[1;31m");
            }
            printf("[");
            printf("%c",k+65);
            if(i > 9){
                printf("%d", i);
            }else{
                printf("0%d",i);
            }
            printf("] ");
            if(j+i == *(arr2+seatpoint)){
                seatpoint++;
                printf("\033[0m");
            }
            else if(*(arr+(k*20)+i) == 1){
                printf("\033[0m");
            }
        }
        printf("\n\n");
        if(k == 1){
            printf("PLATINUM\n");
            printf("\n\n\n");
        }
        if(k == 4){
            printf("ELITE\n");
            printf("\n\n\n\n");
        }
        if(k == 5){
            printf("BUDGET\n\n\n");
        }
    }
    printf("\t");
    for(k = 0;k < 140;k++){
        printf("-");
    }
    printf("\n\t\t\t\t\t\t\t YOUR DREAM SCREEN HERE \t\t\n");
    printf("\t");
    for(k = 0;k < 140;k++){
        printf("-");
    }
    printf("\n");
    printf("\033[1;32m");
    printf("\t\t\tSelected\t\t");
    printf("\033[0m");

    printf("\033[1;31m");
    printf("\t\t\tFilled\t\t");
    printf("\033[0m");

    printf("\t\t\tRemaining\t\t\n");

}

void clearscr(int n){
      for ( int i = 0; i < n; i++ ) // n is the no of lines to skip
        printf("\n");
}




void generateTickets(struct SELECTION *s , struct USER *u){
            int sum = 0,row,col;
            printf("\n\t\t\t\t\t\t---------------YOUR TICKET--------------------@@\n");
            printf("\t\t\t\t\t\t|\tSARR CINEMAS      bookingId:%d\n",s->booking_id);
            printf("\t\t\t\t\t\t|\tNAME : %s\n" , u->C_D->ID);
            printf("\t\t\t\t\t\t|\tSEAT : ");
            for(int i = 0;i < s->number_of_seats;i++){
                col = s->selected_seats[i]-100;
                row = ((s->selected_seats[i]-100)/20);
                if(row < 2){
                    sum += 150;
                }
                else if(row < 5){
                    sum += 120;
                }
                else{
                    sum += 30;
                }
                printf("%c%d",((s->selected_seats[i]-101)/20 + 65),(col-1)%20 + 1);
                if(i+1 != s->number_of_seats){
                    printf(",");
                }
            }
            printf("\n");
            printf("\t\t\t\t\t\t|\t______________________________\n");
            printf("\t\t\t\t\t\t|\t%s\n",s->SELECTED_MOVIE->Movie_name);
            printf("\t\t\t\t\t\t|\t______________________________\n");
            printf("\t\t\t\t\t\t|\tDATETIME : %s  %s\n",s->SELECTED_MOVIE->Date,s->SELECTED_MOVIE->time);
            printf("\t\t\t\t\t\t|\tNO OF SEATS SELECTED  : %d\n",s->number_of_seats);
            printf("\t\t\t\t\t\t|\t_______________________________\n");
            printf("\t\t\t\t\t\t|\tTOTAL                 :Rs.%d\n",sum);
            printf("\t\t\t\t\t\t|----------------------------------------------@@\n");
}
