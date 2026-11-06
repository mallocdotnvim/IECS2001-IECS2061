
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

struct Stack
{
  char *arr;
  int top;
  int capacity;

  Stack(int n)
  {
    capacity = n;
    arr = new char[n];
    top = -1;
  }

  ~Stack()
  {
    delete[] arr;
  }

  bool is_empty()
  {
    return top == -1;
  }

  void push(char c)
  {
    if (top < capacity - 1) {
      arr[++top] = c;
    }
  }

  char pop()
  {
    if (is_empty()) {
      return '\0';
    }

    return arr[top--];
  }

  char peek()
  {
    if (is_empty()) {
      return '\0';
    }

    return arr[top];
  }

  string result()
  {
    string s;

    for (int i = 0; i <= top; i++) {
      s += arr[i];
    }

    return s;
  }
};

string removeES(string str)
{
  Stack st(str.size());
  int lastE = -1;

  for (int i = 0; i < str.size(); i++) {
    char c = str[i];
    char lower = tolower((char)(c));

    if (lower == 'e') {
      st.push(c);
      lastE = st.top;
    }
    else if (lower == 's') {
      if (lastE != -1) {
        st.top = lastE - 1;
        lastE = -1;

        for (int j = st.top; j >= 0; j--) {
          char ch = tolower(
            (char)(st.arr[j])
          );

          if (ch == 'e') {
            lastE = j;
            break;
          }

          if (ch == 's') {
            break;
          }
        }
      }
      else {
        st.push(c);
      }
    }
    else {
      st.push(c);
    }
  }

  return st.result();
}

int main()
{
  ifstream file("input.txt");
  ofstream output("output.txt");

  if (!file.is_open() || !output.is_open()) {
    cout << "Cannot open file\n";
    return 1;
  }

  string line;

  while (getline(file, line)) {
    output << removeES(line) << '\n';
  }

  file.close();
  output.close();

  return 0;
}
