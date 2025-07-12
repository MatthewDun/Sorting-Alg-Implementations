#include <stdio.h>
#include <stdlib.h>
#include "proj3B_deque.h"


int main() 
{ 
    char* BUFFER = malloc(50 * sizeof(char));
    char* NEW_BUFFER = malloc(50 * sizeof(char));
    char** STR_ARRAY = malloc(50 * sizeof(char*));
    long* INT_ARRAY = malloc(50 * sizeof(long));

    int num = 0;
    int str = 0;
    //ADD NUMBERS OR WORDS THEIR RESPECTIVE DYNAMIC ARRAY
    printf("Please enter an integer or a string (empty to exit): \n");
    char *x = fgets(BUFFER, 50, stdin);


    while (x != NULL && BUFFER[0] != '\n') 
    {   
        int y = 0;
        while (BUFFER[y] != '\0' && y < 50)
        {
            if (BUFFER[y] != '\n')
            {
                NEW_BUFFER[y] = BUFFER[y];
            } else 
            {
                NEW_BUFFER[y] = '\0';
                break;
            }
            y++;
        }
        if (BUFFER[y] == '\0' && y < 50) {
        NEW_BUFFER[y] = '\0';  // Explicitly null-terminate if the buffer is not fully filled
        }




        printf("You entered the");
        if (NEW_BUFFER[0] < '0' || NEW_BUFFER[0] > '9')
        {
            printf(" string: \"");
        } else
        {
            printf(" number: ");
        }

        int q = 0;
        if (BUFFER[q] >= '0' && BUFFER[q] <= '9')
        {
            for (int i = 0; BUFFER[i] != '\0'; i++) 
            {
                if (BUFFER[i] == '\r') 
                {
                    BUFFER[i] = '\0';
                    break;
                }
            }
            while (BUFFER[q] == '0')
            {
                q++;
            }
            while (BUFFER[q] != '\n' && BUFFER[q] != '\0')
                {
                    printf("%c",NEW_BUFFER[q]);
                    q++;
                }
        }
        if (NEW_BUFFER[0] < '0' || NEW_BUFFER[0] > '9')
        {
            int j = 2;
            while (BUFFER[q + j] != '\0')
            {
                if ((BUFFER[q] >= '0' && BUFFER[q] <= '9') || BUFFER[q] == 'U')
                {
                    if (j == 1)
                    {
                    }
                    else
                    {
                        j--;
                    }
                }
                printf("%c",NEW_BUFFER[q]);
                q++;
            }   
        }

        if (NEW_BUFFER[0] < '0' || NEW_BUFFER[0] > '9')
        {
            printf("\"");
        }
        printf("\n");





        if (NEW_BUFFER[0] >= '0' && NEW_BUFFER[0] <= '9') 
        {
            int count = 0;
            int i = 0;
            if (BUFFER[i] == '0')
            {
                i++;
            }

            for (; NEW_BUFFER[i] >= '0' && NEW_BUFFER[i] <= '9'; i++) 
            {
                count = count * 10 + (NEW_BUFFER[i] - '0');
            }
            INT_ARRAY[num] = count;
            num++;
        }

        else 
        {
            STR_ARRAY[str] = malloc(MAX_STR_SIZE * sizeof(char));
            int i = 0;
            while (NEW_BUFFER[i] != '\0') 
            {
                STR_ARRAY[str][i] = NEW_BUFFER[i];
                //printf("%c\n",NEW_BUFFER[i]);
                i++;
                
            }
            STR_ARRAY[str][i] = '\0';
            str++;
        }

        printf("Please enter an integer or a string (empty to exit): \n");
        x = fgets(BUFFER, 50, stdin); 
    }


    //INITALIZE DEQUES
    Deque *long_deque = createDeque();
    Deque *char_deque = createDeque();


    //ADD TO FRONT OR BACK OF DEQUE DEPENDING ON ODD OR EVEN
    for (int i = 0; i < str; i++) 
    {
        int datasize = 0;
        int j = 0;
        while (STR_ARRAY[i][j] != '\0')
        {
            datasize++;
            j++;
        }
        datasize++;
        if (i % 2 == 0)
        {
            insertFront(char_deque, STR_ARRAY[i], datasize);
        } else
        {
            insertBack(char_deque, STR_ARRAY[i], datasize);
        }
        datasize = 0;
        j = 0;
    }

    for (int i = 0; i < num; i++) 
    {
        if (i % 2 == 0)
        {
            insertFront(long_deque, &INT_ARRAY[i], sizeof(long int));
        } else
        {
            insertBack(long_deque, &INT_ARRAY[i], sizeof(long int));
        }
    }
    printf("\n");
    printf("Printing string deque\n");
    printDeque(char_deque, printChar);
    printf("\n\n");
    printf("Printing long deque\n");
    printDeque(long_deque, printLong);
    printf("\n\n");


    
    printf("Removing string deque data using count\n");
    long int numHolder = 0;
	char stringHolder[MAX_STR_SIZE] = "";

    for (int i = 0; i < str; i++) 
    {
        int datasize = 0;
        int j = 0;
        while (STR_ARRAY[i][j] != '\0')
        {
            datasize++;
            j++;
        }
        datasize++;
        if (i % 2 == 0)
        {
            removeBack(char_deque, stringHolder, MAX_STR_SIZE);
            for (int i = 0; stringHolder[i] != '\0'; i++) 
            {
                if (stringHolder[i] == '\r') 
                {
                    stringHolder[i] = '\0';
                    break;
                }
            }
            printf("Removing %s\n",stringHolder);

        } else
        {
            removeFront(char_deque, stringHolder, MAX_STR_SIZE);
            for (int i = 0; stringHolder[i] != '\0'; i++) 
            {
                if (stringHolder[i] == '\r') 
                {
                    stringHolder[i] = '\0';
                    break;
                }
            }
            printf("Removing %s\n",stringHolder);
        }
        datasize = 0;
        j = 0;
    }
    printf("\n");
    printf("Removing long deque data using count\n");
    for (int i = 0; i < num; i++) 
    {
        if (i % 2 == 0)
        {
           removeBack(long_deque, &numHolder, sizeof(long int));
            printf("Removing %ld\n",numHolder);
        } else
        {
            removeFront(long_deque, &numHolder, sizeof(long int));
            printf("Removing %ld\n",numHolder);
        }
    }

    //FREE MEMORY
    freeDeque(long_deque);
    freeDeque(char_deque);
    free(BUFFER);
    free(NEW_BUFFER);
    for (int i = 0; i < str; i++) 
    {
        free(STR_ARRAY[i]);
    }
    free(STR_ARRAY);
    free(INT_ARRAY);

    return 0;
}
