#include <stdio.h>
#include <ctype.h>

#define SIZE 100

char stack[SIZE];
int top = -1;

void Convert(char *infix,char* postfix); //infix-ic postfix convertacia
int CalcPofx(char* postfix); 
void RemoveSpace(char * expr);
void push(char e);
char pop();
int pre(char el); //operatri priariteti voroshum

void Convert(char* infix,char* postfix)
{
    char el, ch;
    int i = 0, j = 0;
    
    RemoveSpace(infix);
    push('@');//stacki verjy
    
    while((ch = infix[i++]) != '\n')
    {
        if(ch == '(')
        push(ch);
        else if(isalnum(ch)) //ete tiv(kam tar) e 
        {
            postfix[j] = ch;
            ++j;
        }
        else if(ch == ')')
        {
            while(stack[top] != '(')
            postfix[j] = pop();
            ++j;
            el = pop(); 
        }
        else //operator e
        {
            while(pre(stack[top]) >= pre(ch)) //priaritety hamematenq
            {
                postfix[j] = pop();
                ++j;
            }
            push(ch);
        }
    }
    
    while(stack[top] != '@') //datarkenq stacky
    {
        postfix[j] = pop();
        ++j;
    }
    postfix[j] = 0;
}



int CalcPofx(char* postfix)
{
    char ch;
    int i = 0, op1 = 0, op2 = 0;
    
    while((ch = postfix[i++]) != 0)
    {
        if(isdigit(ch))
        push(ch-'0');//push anenq simvoli tvayin arzheqy
        else
        {
            op2 = pop();
            op1 = pop();
            switch(ch)
            {
                case '+' :
                    push(op1+op2);
                    break;
                case '-' : 
                    push(op1-op2); 
                    break;
                case '*' : 
                    push(op1*op2);
                    break;
                case '/' :
                    push(op1/op2);
                    break;    
                default :
                    printf("\n invalid op");
            }
        }
    }
    return stack[top];
}

void RemoveSpace(char* expr) 
{
    int count = 0; 

    for (int i = 0; expr[i]; ++i) 
        if (expr[i] != ' ') 
            expr[count++] = expr[i]; 

    expr[count] = '\0';
}

int pre(char el) 
{ 
 switch (el) 
 {
    case '@':
        return 0;
    case '(':
        return 1;
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
 }
}

void push(char e)
{
    stack[++top] = e;
}

char pop()
{
    return (stack[top--]);
}

int main()
{
    char infix[100], postfix[100];
    printf("Mutqagreq artahaytutyun: ");
    fgets(infix, 100, stdin);
    
    Convert(infix, postfix);
    
    printf("\nArdyunqy: %d\n", CalcPofx(postfix));
    return 0;
}
