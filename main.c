#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_SIZE    128

typedef struct operator{
    unsigned char op : 6; //6bits enough for 64 numbers, if you use symbol that have bigger number in ASCII, just remove ": 6", and ": 2"
    char pr : 2; //priority of the operator. 2bits enough for numbers in range [-2; 1], enough for what we need.
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

double solver(TOK *tokens, int *numAm)
{
    TOK temp;
    int i, j;
    double res;

    for(int i=0; i<(*numAm-1); ++i){
        if(tokens->ops[i].pr==1){
            j = i;
            res = tokens->nums[i];
            while(tokens->ops[i].pr==1){
                switch (tokens->ops[i].op)
                {
                case '*': res *= tokens->nums[++i];     break;
                case '/': res /= tokens->nums[++i];     break;
                }
            }
            temp.nums[j]=res;
            temp.ops[j].op='+';
            temp.ops[j].pr=0;
        } else{
            temp.ops[i] = tokens->ops[i];
            temp.nums[i] = tokens->nums[i];
        }
        }

    for(int u=0; u<j; ++u){
        switch(temp.ops[u].op)
        {
            case '+': res += temp.nums[u];    break;
            case '-': res -= temp.nums[u];    break;
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
                do{
                    weight=0.1;
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

    printf("Answer: %.2f", solver(&tokens, &numIndx));

//    printf("%d\n%d\n%c", tokens.numbers[0], tokens.numbers[1], tokens.operators[0]);

    return 0;
}

int main(void)
{
    parser();

    return 0;
}