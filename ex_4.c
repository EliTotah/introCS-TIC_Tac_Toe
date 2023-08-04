#include <stdio.h>
#include <string.h>

#define SIZEARR 10
#define SIZESTR 20
#define SIZESQR 5

/***********************************************************************************
 * Eli Totah
 * 209186014
 * ass04
***********************************************************************************/

void progressOfGame(int row,int column);
int scanNames (char str[SIZESTR],char arrStr[][SIZESTR]);
void arrangeLexographic(int index, char arrStr[][SIZESTR]);
void printNames(int numOfNames, char arrStr[][SIZESTR]);
void printSqrNum (int row,int column);
void printSqr (int row, int column,char arrSqr[][SIZESQR]);
void initializeArr (int row,int column,char arrSqr[][SIZESQR]);
int playX (int row,int column,char name[SIZESTR], char arrSqr[][SIZESQR]);
int playO (int row,int column,char name[SIZESTR], char arrSqr[SIZESQR][SIZESQR]);
int isRow(char arrSqr[][SIZESQR],int row, int column, int iIndex, int jIndex);
int isCol(char arrSqr[][SIZESQR],int row,int column, int iIndex, int jIndex);
int isDig1(char arrSqr[][SIZESQR],int row, int column, int iIndex, int jIndex);
int isDig2(char arrSqr[][SIZESQR],int row, int column, int iIndex, int jIndex);
int isTie(char arrSqr[][SIZESQR],int row, int column);
int endGame(int row, int column,char arr[][SIZESQR]);

int main()
{
    int row,column;
    printf("Enter size of the game and the participants names:\n");
    scanf("%dX%d,", &row , &column);
    progressOfGame(row,column);
    return 0;
}

/***********************************************************************************
* Function name: progressOfGame
* Input: int row,int column
* Output: none
* Function Operation: The function performs the entire functions and advances the game process
***********************************************************************************/

void progressOfGame(int row,int column)
{
    int choose1=0,choose2=0;
    char str[SIZESTR];
    char arrStr[SIZEARR][SIZESTR];
    char arrSqr[SIZESQR][SIZESQR];
    scanf(" %[^\r\n]s", str);
    int numOfNames=scanNames(str,arrStr);
    printf("Your board size is %dx%d!\n"
           "Choose 2 participants:\n",row,column);
    arrangeLexographic(numOfNames,arrStr);
    printNames(numOfNames,arrStr);
    scanf("%d,%d",&choose1,&choose2);
    printf("Hi %s and %s,\n",arrStr[choose1-1],arrStr[choose2-1]);
    printSqrNum(row,column);
    printf("let start the game!\n"
                   "-\t-\t-\t-\n");
    initializeArr(row,column,arrSqr);
    printSqr(row,column,arrSqr);
    // if player 1 didn't win or there is not tie situation so let player2 to play
    while (playX(row,column,arrStr[choose1-1],arrSqr)==0)
    {
        int p=playO(row,column,arrStr[choose2-1],arrSqr);
        // if player 2 win or there is tie situation
        if (p==2 || p==3)
            break;
        else continue;
    }
}

/***********************************************************************************
* Function name: scanNames
* Input: char str[],char arrStr[][]
* Output: int j
2* Function Operation: The function separates the names of the players,
                      puts them into a two-dimensional array and returns the number of names entered.
***********************************************************************************/

int scanNames (char str[SIZESTR],char arrStr[][SIZESTR])
{
    int j=0;
    char * token = strtok(str,",");
    while (token!=NULL)
    {
        // to get rid of the spaces before the name
        while (token[0]==' ')
            token++;
        strcpy(arrStr[j], token);
        token = strtok(NULL, ",");
        j++;
    }
    // return the num of names we have in the array
    return j;
}

/***********************************************************************************
* Function name: arrangeLexographic
* Input: int index, char arrStr[][]
* Output: none
* Function Operation: The function sorts the names of the players by lexicographically order
***********************************************************************************/

void arrangeLexographic(int index, char arrStr[][SIZESTR])
{
    char temp[SIZESTR];
    for (int i = 0; i < index; ++i)
        for(int j=i+1;j<index;++j)
            /* If the ASCI value of the difference between the two strings
               is greater than 0 then the second string should be before the first,
               if not so we are good and both string exits in their right positions */
            if (strcmp(arrStr[i],arrStr[j])>0)
            {
                // swap the string
                strcpy(temp, arrStr[i]);
                strcpy(arrStr[i], arrStr[j]);
                strcpy(arrStr[j], temp);
            }
}

/***********************************************************************************
* Function name: printNames
* Input: int numOfNames, char arrStr[][]
* Output: none
* Function Operation: The function prints the names of the players
***********************************************************************************/

void printNames(int numOfNames, char arrStr[][SIZESTR])
{
    for (int i = 0; i < numOfNames; ++i)
        printf("%d.\t%s\n",i+1,arrStr[i]);
}

/***********************************************************************************
* Function name: printSqrNum
* Input: int row,int column
* Output: none
* Function Operation: The function prints the game board and the digits of the places on the board
***********************************************************************************/

void printSqrNum (int row,int column)
{
    printf("This cell numbered:\n");
    int count = 1;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            // if we have board of 1X1
            if (j==column-1 && column==1)
                printf("   %d   |",count);
            else
            {   // To avoid printing unnecessary profit in the last digit
                if (j == column - 1)
                    printf("   %d", count);
                else printf("   %d   |", count);
            }
            count++;
        }
        printf("\n");
        if (i!=row-1)
        {
            for (int j = 0; j < column; ++j)
            {
                // To avoid printing unnecessary plus in the last row
                if (j == column - 1)
                    printf("-----");
                else printf("-----+");

            }
        }
        // if we have board of 1X1
        if (row==1)
            printf("-----+");
        printf("\n");
    }
}

/***********************************************************************************
* Function name: printSqr
* Input: int row, int column, char arrSqr[][]
* Output: none
* Function Operation: The function prints the game board
***********************************************************************************/

void printSqr (int row, int column, char arrSqr[][SIZESQR])
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            // if we have board of 1X1
            if (j==column-1 && column==1)
                printf("   %c   |",arrSqr[i][j]);
            else
            {   // To avoid printing unnecessary profit in the last digit
                if (j == column - 1)
                    printf("   %c", arrSqr[i][j]);
                else printf("   %c   |", arrSqr[i][j]);
            }
        }
        printf("\n");
        if (i!=row-1)
        {
            for (int j = 0; j < column; ++j)
            {
                // To avoid printing unnecessary plus in the last row
                if (j == column - 1)
                    printf("-----");
                else printf("-----+");
            }
        }
        // if we have board of 1X1
        if (row==1)
            printf("-----+");
        printf("\n");
    }
}

/***********************************************************************************
* Function name: initializeArr
* Input: int row, int column, char arrSqr[][]
* Output: none
* Function Operation: The function initializes the array so that each member of the array has "-"
***********************************************************************************/

void initializeArr (int row,int column,char arrSqr[][SIZESQR])
{
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            arrSqr[i][j]='_';
}

/***********************************************************************************
* Function name: playX
* Input: int row,int column,char name[], char arrSqr[][]
* Output: int
* Function Operation: The function insert 'X' to the place that the user chose
***********************************************************************************/

int playX (int row,int column,char name[SIZESTR], char arrSqr[][SIZESQR])
{
    int count=0,play=0,i,temp=0;
    printf("It %s turn, you X:\n",name);
    scanf(" %d",&play);
    // while the input number is wrong (place not exist)
    while (temp!=1)
    {
        if (play < 1 || play > (row * column))
        {
            printf("This place not exist!\n"
                   "It %s turn, you X:\n", name);
            scanf(" %d", &play);
            // if the input num is right change temp and go out from the loop
            if (play >= 1 && play <= (row * column))
                temp=1;
        }
        else temp=1;
    }
    for (i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            /* the loop runs on the elements of the array and each time the counter increased by 1.
               when count equals to the number that the user inserted so it means we got to the place he wanted,
               we verify that he is empty and insert X.  */
            count++;
            if ((play == count) && (arrSqr[i][j] == '_'))
            {
                arrSqr[i][j] = 'X';
                break;
            }
            // if the user chose unempty place we will print message and let him another try
            else if (play == count && ((arrSqr[i][j] == 'O') || (arrSqr[i][j] == 'X')))
            {
                printf("This place not empty!\n");
                printf("It %s turn, you X:\n", name);
                scanf(" %d", &play);
                count = 0,i=-1;
                break;
            }
        }
    }
    printSqr(row,column,arrSqr);
    // if our first user won print win message and return 1
    if(endGame(row,column,arrSqr)==1)
    {
        printf("%s has win! You played well!", name);
        return 1;
    }
    // if there is tie print tie message and return 3
    if(endGame(row,column,arrSqr)==3)
    {
        printf("The game end, No one wins. You played well!");
        return 3;
    }
    // if we still have empty places in the board return 0
    return 0;
}

/***********************************************************************************
* Function name: playO
* Input: int row,int column,char name[], char arrSqr[][]
* Output: int
* Function Operation: The function insert 'O' to the place that the user chose
***********************************************************************************/

int playO (int row,int column,char name[SIZESTR], char arrSqr[][SIZESQR]) {
    int count = 0, play=0,temp=0;
    printf("It %s turn, you O:\n", name);
    scanf(" %d", &play);
    // while the input number is wrong (place not exist)
    while (temp!=1)
    {
        if (play < 1 || play > (row * column))
        {
            printf("This place not exist!\n"
                   "It %s turn, you O:\n", name);
            scanf(" %d", &play);
            // if the input num is right change temp and go out from the loop
            if (play >= 1 && play <= (row * column))
                temp=1;
        }
        else temp=1;
    }
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            /* the loop runs on the elements of the array and each time the counter increased by 1.
               when count equals to the number that the user inserted so it means we got to the place he wanted,
               we verify that he is empty and insert O.  */
            count++;
            if ((play == count) && (arrSqr[i][j] == '_'))
            {
                arrSqr[i][j] = 'O';
                break;
            }
            // if the user chose unempty place we will print message and let him another try
            else if (play == count && ((arrSqr[i][j] == 'O') || (arrSqr[i][j] == 'X')))
            {
                printf("This place not empty!\n");
                printf("It %s turn, you O:\n", name);
                scanf(" %d", &play);
                count = 0, i = -1;
                break;
            }
        }
    }
    printSqr(row, column, arrSqr);
    // if our first user won print win message and return 1
    if (endGame(row, column, arrSqr) == 2)
    {
        printf("%s has win! You played well!", name);
        return 2;
    }
    // if there is tie print tie message and return 3
    if (endGame(row, column, arrSqr) == 3)
    {
        printf("The game end, No one wins. You played well!");
        return 3;
    }
    // if we still have empty places in the board return 0
    return 0;
}

/***********************************************************************************
* Function name: isRow
* Input: char arrSqr[][],int row, int column, int iIndex, int jIndex
* Output: int
* Function Operation: The function check if there is win situation in the row (3 'X' or 'O' in the row)
***********************************************************************************/

int isRow(char arrSqr[][SIZESQR],int row, int column, int iIndex, int jIndex)
{
    int count=0;
    for(int i=0;i<column;++i)
    {
        if (arrSqr[iIndex][i] == 'X')
            count++;
    }
    // if all the row is 'X' so play 1 win, return 1
    if (count==row)
        return 1;
    count=0;
    for(int i=0;i<column;++i)
    {
        if (arrSqr[iIndex][i] =='O')
            count++;
    }
    // if all the row is 'O' so play 2 win, return 2
    if(count==row)
        return 2;
    return 0;
}

/***********************************************************************************
* Function name: isCol
* Input: char arrSqr[][],int row, int column, int iIndex, int jIndex
* Output: int
* Function Operation: The function check if there is win situation in the column (3 'X' or 'O' in the column)
***********************************************************************************/

int isCol(char arrSqr[][SIZESQR],int row,int column, int iIndex, int jIndex)
{
    int count=0;
    for(int i=0;i<row;++i)
    {
        if (arrSqr[i][jIndex] == 'X')
            count++;
    }
    // if all the column is 'X' so play 1 win, return 1
    if (count==column)
        return 1;
    count=0;
    for(int i=0;i<row;++i)
    {
        if (arrSqr[i][jIndex] =='O')
            count++;
    }
    // if all the column is 'X' so play 2 win, return 2
    if(count==column)
        return 2;
    return 0;
}
/***********************************************************************************
* Function name: isDig
* Input: char arrSqr[][],int row, int column, int iIndex, int jIndex
* Output: int
* Function Operation: The function check if there is win situation in the main diagonal
                      (3 'X' or 'O' in the diagonal)
***********************************************************************************/

int isDig1(char arrSqr[][SIZESQR],int row, int column, int iIndex, int jIndex)
{
    int i,j,count=0;
    for(i=0,j=0;i<row && j<column;++i,++j)
    {
        if (arrSqr[i][j] == 'X')
            count++;
    }
    // if all the main diagonal is 'X' so play 1 win, return 1
    if(count==row)
        return 1;
    count=0;
    for(i=0,j=0;i<=row && j<=column;++i,++j)
    {
        if (arrSqr[i][j] =='O')
            count++;
    }
    // if all the main diagonal is 'O' so play 2 win, return 2
    if(count==row)
        return 2;
    return 0;
}

/***********************************************************************************
* Function name: isDig2
* Input: char arrSqr[][],int row, int column, int iIndex, int jIndex
* Output: int
* Function Operation: The function check if there is win situation in the second diagonal
                      (3 'X' or 'O' in the diagonal)
***********************************************************************************/

int isDig2(char arrSqr[][SIZESQR],int row, int column, int iIndex, int jIndex)
{
    int i, j,count=0;
    for (i = row-1, j = 0; i >= 0 && j<column; --i, ++j)
    {
        if (arrSqr[i][j] == 'X')
            count++;
    }
    // if all the second diagonal is 'X' so play 1 win, return 1
    if(count==row)
        return 1;
    count=0;
    for (i = row-1, j = 0; i >= 0 && j<column; --i, ++j)
    {
        if (arrSqr[i][j] =='O')
            count++;
    }
    // if all the second diagonal is 'O' so play 2 win, return 2
    if(count==row)
        return 2;
    return 0;
}

/***********************************************************************************
* Function name: isTie
* Input: char arrSqr[][],int row, int column
* Output: int
* Function Operation: The function check if there is tie situation in the board
                      (all the board is unempty without win of any side)
***********************************************************************************/

int isTie(char arrSqr[][SIZESQR],int row, int column)
{
    int count=0;
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            // we runs on all the array, if all of them are unempty so count increase by 1.
            if (arrSqr[i][j] == 'X' || arrSqr[i][j] == 'O')
                count++;
    /* if counter equals to numbers of elements of the array so it mean
       we did not reach a state of victory and it is impossible to continue the game,
       i.e a draw. return 3 */
    if (count==(row*column))
        return 3;
    return 0;
}

/***********************************************************************************
* Function name: endGame
* Input: int row, int column,char arrSqr[][]
* Output: int
* Function Operation: The function check if there is win situation or tie situation in the board
***********************************************************************************/

int endGame (int row, int column,char arrSqr[][SIZESQR])
{
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
        {
            if (arrSqr[i][j] == 'X')
            {
                // if there is win situation of player 1
                if (isRow(arrSqr, row, column, i, j) == 1 ||
                    isCol(arrSqr, row, column, i, j) == 1 ||
                    isDig1(arrSqr, row, column, i, j) == 1 ||
                    isDig2(arrSqr, row, column, i, j) == 1)
                    return 1;
            }
            else if (arrSqr[i][j] == 'O')
            {
                // if there is win situation of player 2
                if (isRow(arrSqr, row, column, i, j) == 2 ||
                    isCol(arrSqr, row, column, i, j) == 2 ||
                    isDig1(arrSqr, row, column, i, j) == 2 ||
                    isDig2(arrSqr, row, column, i, j) == 2)
                    return 2;
            }
            // if there is tie situation
            if(isTie(arrSqr,row,column)==3)
                return 3;
        }
    return 0;
}