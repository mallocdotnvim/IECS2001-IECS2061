#include <iostream>
#include <stack>
using namespace std;

bool parentheses(stack<char>&st, string str)
{
  for (int i = 0; i < str.size(); i++) {
    char c = str[i];
    if (c == '(' || c == '{' || c == '[') {
      st.push(c);
    } else {
      if (st.empty() ||
        (c == ')' && st.top() != '(') ||
        (c == '{' && st.top() != '{') ||
        (c == '[' && st.top() != '[') 
      ) {
        return false;
      }
      st.pop();
    }
  }
  return st.empty();
}

int main(void)
{
  cin.tie(0)->ios::sync_with_stdio(0);
  stack<char> st;
  string str; cin >> str;
  bool flag = parentheses(st, str);
  cout << ((flag == true) ? "Yes" : "No") << '\n';
  
}
