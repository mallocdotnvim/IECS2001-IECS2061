
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef enum {op, val} mytype;

struct data
{
  mytype type;
  int value;
  char oper;
};

struct mystack
{
  data a[MAX];
  int top;

  bool IsEmpty();
  bool IsFull();
  void Push(data da);
  data Pop();
  data Top();

  mystack()
  {
    top = -1;
  }
};

bool mystack::IsEmpty()
{
  return top == -1;
}

bool mystack::IsFull()
{
  return top == MAX - 1;
}

void mystack::Push(data da)
{
  if (IsFull())
    printf("The STACK is full\n");
  else
    a[++top] = da;
}

data mystack::Pop()
{
  if (IsEmpty())
  {
    printf("The STACK is empty\n");
    data temp = {};
    return temp;
  }

  return a[top--];
}

data mystack::Top()
{
  if (IsEmpty())
  {
    printf("The STACK is empty\n");
    data temp = {};
    return temp;
  }

  return a[top];
}

int Priority(char oper)
{
  switch (oper)
  {
    case '+':
    case '-':
      return 1;

    case '*':
    case '/':
      return 2;

    default:
      return 0;
  }
}

bool InfixToPostfix(const char* expression, data postfix[], int& count)
{
  mystack stack;
  count = 0;

  for (int i = 0; expression[i] != '\0';)
  {
    if (isspace((unsigned char)expression[i]))
    {
      i++;
      continue;
    }

    if (isdigit((unsigned char)expression[i]))
    {
      data temp = {};
      temp.type = val;
      temp.value = 0;

      while (isdigit((unsigned char)expression[i]))
      {
        temp.value = temp.value * 10 + expression[i] - '0';
        i++;
      }

      if (count >= MAX)
        return false;

      postfix[count++] = temp;
    }
    else if (expression[i] == '(')
    {
      data temp = {};
      temp.type = op;
      temp.oper = expression[i];

      stack.Push(temp);
      i++;
    }
    else if (expression[i] == ')')
    {
      while (!stack.IsEmpty() && stack.Top().oper != '(')
      {
        if (count >= MAX)
          return false;

        postfix[count++] = stack.Pop();
      }

      if (stack.IsEmpty())
        return false;

      stack.Pop();
      i++;
    }
    else if (strchr("+-*/", expression[i]) != NULL)
    {
      data temp = {};
      temp.type = op;
      temp.oper = expression[i];

      while (!stack.IsEmpty() &&
             stack.Top().oper != '(' &&
             Priority(stack.Top().oper) >= Priority(temp.oper))
      {
        if (count >= MAX)
          return false;

        postfix[count++] = stack.Pop();
      }

      stack.Push(temp);
      i++;
    }
    else
    {
      return false;
    }
  }

  while (!stack.IsEmpty())
  {
    if (stack.Top().oper == '(')
      return false;

    if (count >= MAX)
      return false;

    postfix[count++] = stack.Pop();
  }

  return count > 0;
}

void ShowPostfix(data postfix[], int count)
{
  for (int i = 0; i < count; i++)
  {
    if (postfix[i].type == val)
      printf("%d", postfix[i].value);
    else
      printf("%c", postfix[i].oper);
  }

  printf("\n");
}

bool EvaluatePostfix(data postfix[], int count, int& result)
{
  mystack stack;

  for (int i = 0; i < count; i++)
  {
    if (postfix[i].type == val)
    {
      stack.Push(postfix[i]);
    }
    else
    {
      if (stack.top < 1)
        return false;

      int b = stack.Pop().value;
      int a = stack.Pop().value;

      data temp = {};
      temp.type = val;

      switch (postfix[i].oper)
      {
        case '+':
          temp.value = a + b;
          break;

        case '-':
          temp.value = a - b;
          break;

        case '*':
          temp.value = a * b;
          break;

        case '/':
          if (b == 0)
            return false;

          temp.value = a / b;
          break;

        default:
          return false;
      }

      stack.Push(temp);
    }
  }

  if (stack.top != 0)
    return false;

  result = stack.Pop().value;
  return true;
}

int main()
{
  FILE* fp = fopen("1117hw.txt", "r");

  if (fp == NULL)
  {
    printf("Cannot open file\n");
    return 1;
  }

  char expression[MAX];
  data postfix[MAX];
  int count;
  int result;

  while (fgets(expression, MAX, fp) != NULL)
  {
    if (strspn(expression, " \t\r\n") == strlen(expression))
      continue;

    if (!InfixToPostfix(expression, postfix, count))
    {
      printf("Invalid expression\n");
      continue;
    }

    ShowPostfix(postfix, count);

    if (EvaluatePostfix(postfix, count, result))
      printf("result : %d\n", result);
    else
      printf("Invalid expression\n");
  }

  fclose(fp);

  return 0;
}
