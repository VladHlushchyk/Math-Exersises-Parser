#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_SIZE    128

typedef struct operator{
    unsigned char op : 6; //6bits enough for 64 numbers, if you use symbol that have bigger number in ASCII, just remove ": 6", and ": 2"
    unsigned char pr : 2; //priority of the operator. 2bits enough for numbers in range [0; 3], enough for what we need.
} OP;

typedef struct tokens{
    double nums[NUM_SIZE];
    OP ops[NUM_SIZE -1];
} TOK;

// gets char that isn't space(' ') and returns it
char getC(void)
{
    char c;
    do{c=getchar();}while(c==' ');
    return c;
}

double solver(TOK *tokens, int *numAm) //solving the math example, and return result
{
    TOK temp;
    double res, res_mul;
    int i=0, j=0;

    for(i; i<*numAm; ++i, ++j){
        if(tokens->ops[i].pr==1){
            res_mul=tokens->nums[i];
            while(tokens->ops[i].pr==1){
                switch (tokens->ops[i].op)
                {
                case '*': res_mul *= tokens->nums[++i];     break;
                case '/': res_mul /= tokens->nums[++i];     break;
                }
            }
            temp.nums[j]=res_mul;
            if (i < *numAm - 1) temp.ops[j] = tokens->ops[i];
            else temp.ops[j].op = 0;
        } else{
            temp.ops[j] = tokens->ops[i];
            temp.nums[j] = tokens->nums[i];
        }
    }

    res = temp.nums[0];
    for(int u=0; u<=j; ++u){
        switch(temp.ops[u].op)
        {
            case '+': res += temp.nums[u+1];    break;
            case '-': res -= temp.nums[u+1];    break;
        }
    }

    return res;
}

// the function that parses elements, and gives it to solver func
int parser(void)
{
    int numIndx=0, opIndx=0;// numIndx - index that needed to add numbers into numbers array, opIndx is the same as numIndx, but for operators
    double num, weight;
    char c;
    TOK tokens; 

    printf("Enter math example below:\n");

    do{
        c=getC();
        if(isdigit(c)){
            num=0;
            do{
                num = num*10+(c-'0');
                c=getC();                
            }while(isdigit(c));

            if(c=='.'||c==','){// for real numbers
                c=getC();
                weight=0.1;
                do{
                    num = num+(c-'0')*weight;
                    weight*=0.1;
                    c=getC();
                }while(isdigit(c));
            }
            
            tokens.nums[numIndx] = num;
            ++numIndx;
            ungetc(c, stdin);
        } else if(c=='+'||c=='-'){
            tokens.ops[opIndx].op = c;
            tokens.ops[opIndx].pr = 0;
            ++opIndx;
        } else if(c=='*'||c=='/'||c=='%'){
            tokens.ops[opIndx].op = c;
            tokens.ops[opIndx].pr = 1;
            ++opIndx;
        } else printf("\nError: there is no symbol '%c';\n", c);
    }while(c!='='&&c!='\n');

    printf("Your answer is %.2f", solver(&tokens, &numIndx));

//    printf("%d\n%d\n%c", tokens.numbers[0], tokens.numbers[1], tokens.operators[0]);

    return 0;
}

int main(void)
{
    parser();

    printf("\n\nPress any button to close the window.");
    int c;      while ((c = getchar()) != '\n' && c != EOF) { }     // to clear input buffer stdin
    getchar();      // to wait till the button is pressed
    return 0;
}