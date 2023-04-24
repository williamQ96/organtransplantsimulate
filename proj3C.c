/* CS 212 Project: Donations (2022)
   ~Always appreciated, never expected, non-refundable~

   Author: S. Isaac Geronimo Anderson (Fall 2022)
   */

#include <stdio.h>   /* printf */
#include <stdlib.h>  /* malloc */
#include <string.h>  /* strcmp */

/* Do not change these values for your submission. */
#define QUEUE_SIZE 12  /* Note: Works with 12 on 3C-input.txt */
#define BLOOD_TYPES 4
#define LINE_LENGTH 80

/* Your code goes below this line. */

struct queue
{
  /* Add your struct members here. */
	int front;
	int back;
	char* strings[QUEUE_SIZE];
	int population;

};
typedef struct queue Queue;

void initializeQueue(Queue *q)
{
	q->front=0;
	q->back=0;
	q->population=0;	
}

void enqueue(char* name, Queue *q)
{
	q->strings[q->back]=name;
	q->back++;
	q->back%=QUEUE_SIZE;
	q->population++;
//	printf("enqueue:   %s\n",name);
}

char* dequeue(Queue *q)
{
	char* temp =q->strings[q->front];
//	printf("dequeue: %s %d\n",temp,q->front);
	q->front++;
	q->front%=QUEUE_SIZE;
	q->population--;
//	printf("front=%d,population=%d\n",q->front,q->population);
	return temp;
}








/* Your code goes above this line.  printf(
      "MATCH: %s donates to %s via Dr. %s\n",
      donor,
      recipient,
      surgeon);
*/









/* Here is a suggested helper function for checking blood type
   compatibility. */
int isDonorToRecipient(char *donor, char *recipient)
{
  if (strcmp(donor, "O") == 0 || strcmp(donor, recipient) == 0)
    return 1;
  if (strcmp(donor, "A") == 0 && strcmp(recipient, "AB") == 0)
    return 1;
  if (strcmp(donor, "B") == 0 && strcmp(recipient, "AB") == 0)
    return 1;
  return 0;
}


/* Uncomment printQueue and prettyPrintQueue when your queue struct
   and functions are implemented. */

void printQueue(struct queue *q)
{
  printf("Printing queue %p\n", q);
  printf("\tThe index for the front of the queue is %d\n", q->front);
  printf("\tThe index for the back of the queue is %d\n", q->back);
  if (q->population == 0)
  {
    printf("\tThe queue is empty.\n");
  }
  else
  {
    for (int i = 0; i < q->population; i++)
    {
      int index = (q->front + i) % QUEUE_SIZE;
      printf("\t\tEntry[%d]: \"%s\"\n", index, q->strings[index]);
    }
  }
}


void prettyPrintQueue(struct queue *q, char *label, char *type)
{
  if (q->population == 0)
  {
    printf("No unmatched entries for %s (%s)\n", label, type);
  }
  else
  {
    printf("Unmatched %s (%s):\n", label, type);
    for (int i = 0; i < q->population; i++)
    {
      int index = (q->front + i) % QUEUE_SIZE;
      printf("%s\n", q->strings[index]);
    }
  }
}



int main(int argc, char **argv)
{
  /***  STEP #1: Implement your queue code and test it.  ***/

  /* This test code: */
 /*
  struct queue *q = malloc(sizeof (struct queue));
  initializeQueue(q);
  printQueue(q);
  enqueue("hello", q);
  printQueue(q);
  enqueue("world", q);
  printQueue(q);
  printf("Dequeue: %s\n", dequeue(q));
  printQueue(q);
  free(q);
  */

  /* Gives this output (with different pointers):

Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 0
	The queue is empty.
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 1
		Entry[0] = "hello"
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 2
		Entry[0] = "hello"
		Entry[1] = "world"
Dequeue: hello
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 1
	The index for the back of the queue is 2
		Entry[1] = "world"
  */
  /***
    STEP #2: Open the input file (argc/argv stuff).
             You should read the file line-by-line in the next step
             using fgets (or fscanf or getline).
             Note: You must not hard-code the input file name.
             You must not use fread.
             You should exit with an error if file opening fails.
  ***/
	FILE* f=fopen(argv[1],"r");
	char buffer[LINE_LENGTH];
	if(f==NULL){printf("ERROR:file doesn't exist");exit(EXIT_FAILURE);}

	






  /***
    STEP #3: After your queue code works and after you can read the
             file, implement the prompt.
             Note: Here is the print statement to use for a match:
*/

  char *types[BLOOD_TYPES] = {"AB", "B", "A", "O"};

  struct queue *donors[BLOOD_TYPES];
  struct queue *recipients[BLOOD_TYPES];
  struct queue *surgeons = malloc(sizeof (struct queue));

  donors[0]=malloc(sizeof(struct queue));
  donors[1]=malloc(sizeof(struct queue));
  donors[2]=malloc(sizeof(struct queue));
  donors[3]=malloc(sizeof(struct queue));
  recipients[0]=malloc(sizeof(struct queue));
  recipients[1]=malloc(sizeof(struct queue));
  recipients[2]=malloc(sizeof(struct queue));
  recipients[3]=malloc(sizeof(struct queue));
 
  initializeQueue(donors[0]); 
  initializeQueue(donors[1]); 
  initializeQueue(donors[2]); 
  initializeQueue(donors[3]); 
  initializeQueue(recipients[0]); 
  initializeQueue(recipients[1]); 
  initializeQueue(recipients[2]); 
  initializeQueue(recipients[3]); 
  initializeQueue(surgeons); 


	while(fgets(buffer,LINE_LENGTH,f))
	{
		if(buffer[0]=='R')
		{	char blood[5];
			char str[30];
			sscanf(buffer,"R:%[^:]:%[^\n]",blood,str);
			char*name = strdup(str);	

			if(surgeons->population==0&&strcmp("AB",blood)==0){enqueue(name,recipients[0]);continue;}
			if(surgeons->population==0&&strcmp("B",blood)==0) {enqueue(name,recipients[1]);continue;}
			if(surgeons->population==0&&strcmp("A",blood)==0) {enqueue(name,recipients[2]);continue;}
			if(surgeons->population==0&&strcmp("O",blood)==0) {enqueue(name,recipients[3]);continue;}
	
			int flag=0;
			for(int i=0;i<4;i++)
			{
				if(donors[i]->population==0) continue;
				if(isDonorToRecipient(types[i],blood)==1)
				{
					flag=1;
					printf("MATCH: %s donates to %s via Dr. %s\n", dequeue(donors[i]),name,dequeue(surgeons));

					break;
				}
				
			}
			if(flag==1) continue;
			else
			{
			if(strcmp("AB",blood)==0){enqueue(name,recipients[0]);}
			if(strcmp("B",blood)==0){enqueue(name,recipients[1]);}
			if(strcmp("A",blood)==0){enqueue(name,recipients[2]);}
			if(strcmp("O",blood)==0){enqueue(name,recipients[3]);}
			}
		}
		else if(buffer[0]=='D')
		{	char blood[5];
			char str[30];
			sscanf(buffer,"D:%[^:]:%[^\n]",blood,str);
char*name = strdup(str);	
			if(surgeons->population==0&&strcmp("AB",blood)==0){enqueue(name,donors[0]);continue;}
			if(surgeons->population==0&&strcmp("B",blood)==0) {enqueue(name,donors[1]);continue;}
			if(surgeons->population==0&&strcmp("A",blood)==0) {enqueue(name,donors[2]);continue;}
			if(surgeons->population==0&&strcmp("O",blood)==0) {enqueue(name,donors[3]);continue;}
	
			int flag=0;
			for(int i=0;i<4;i++)
			{
				if(recipients[i]->population==0) continue;
				if(isDonorToRecipient(blood,types[i])==1)
				{
					flag=1;
					printf("MATCH: %s donates to %s via Dr. %s\n", name,dequeue(recipients[i]),dequeue(surgeons));

					break;
				}
				
			}
			if(flag==1) continue;
			else
			{
			if(strcmp("AB",blood)==0){enqueue(name,donors[0]);}
			if(strcmp("B",blood)==0){enqueue(name,donors[1]);}
			if(strcmp("A",blood)==0){enqueue(name,donors[2]);}
			if(strcmp("O",blood)==0){enqueue(name,donors[3]);}
			}

		}

		else if(buffer[0]=='S')
		{       char str[30];
			sscanf(buffer,"S:%[^\n]",str);
char*name = strdup(str);	
			int flag=0;
			for(int i=0;i<4;i++)
			{	for(int j=0;j<4;j++)
				{
					if(recipients[i]->population !=0&& donors[j]->population !=0)
					{
						if(isDonorToRecipient(types[j],types[i])==1)
						{
							printf("MATCH: %s donates to %s via Dr. %s\n", dequeue(donors[j]),dequeue(recipients[i]),name);
						//	printf("donor=%s,recipient=%s\n",types[j],types[i]);
							flag=1;
							break;
						}
					}
					
				}
				if(flag==1) break;

			}
		

			if(flag==1) continue;
	
			else
			{
				enqueue(name,surgeons);
			}
		}
	}		

  /***
    STEP #4: After your matching code is done, add prettyPrintQueue
             calls for each of your recipient queues, your donor
             queues, and your surgeon queue. If you used the
             suggested "recipients" and "donors" arrays, and the
             "types" array, then you can use these print statements*/

  for (int r = 0; r < BLOOD_TYPES; r++)
    prettyPrintQueue(recipients[r], "recipients", types[r]);
  for (int d = 0; d < BLOOD_TYPES; d++)
    prettyPrintQueue(donors[d], "donors", types[d]);
  prettyPrintQueue(surgeons, "surgeons", "type-agnostic");

            /* If you did not use arrays for your recipient and donor
             queues, then you should print your recipient queues in
             this order, for example:

  prettyPrintQueue(recipients_AB, "recipients", "AB");
  prettyPrintQueue(recipients_A, "recipients", "B");
  prettyPrintQueue(recipients_B, "recipients", "A");
  prettyPrintQueue(recipients_O, "recipients", "O");

             Then, print your donor queues in the same order, then
             print your surgeon queue.
  ***/

  /* If you have time, be sure to free any memory you allocated. */
  free(surgeons);
  for(int i=0;i<4;i++)
  {
	free(donors[i]);
	free(recipients[i]);
  }
  

  return EXIT_SUCCESS;
}


/* End. */
