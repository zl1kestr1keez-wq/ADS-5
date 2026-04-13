// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

using std::string;

int getPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int doOperation(int left, int right, char op) {
  if (op == '+') return left + right;
  if (op == '-') return left - right;
  if (op == '*') return left * right;
  if (op == '/') return left / right;
  return 0;
}

string infx2pstfx(const string& inf) {
  TStack<char, 100> stack;
  string result;
  for (int i = 0; i < inf.length(); i++) {
    char c = inf[i];
    if (isdigit(c)) {
      while (i < inf.length() && isdigit(inf[i])) {
        result += inf[i];
        i++;
      }
      result += ' ';
      i--;
    } else if (c == '(') {
      stack.addToStack(c);
    } else if (c == ')') {
      while (!stack.stackIsEmpty() && stack.lookAtTop() != '(') {
        result += stack.takeFromStack();
        result += ' ';
      }
      if (!stack.stackIsEmpty() && stack.lookAtTop() == '(') {
        stack.takeFromStack();
      }
    } else if (isOperator(c)) {
      while (!stack.stackIsEmpty() &&
        getPriority(stack.lookAtTop()) >= getPriority(c)) {
        result += stack.takeFromStack();
        result += ' ';
      }
      stack.addToStack(c);
    }
  }
  while (!stack.stackIsEmpty()) {
    result += stack.takeFromStack();
    result += ' ';
  }
  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
  return result;
}
int eval(const string& post) {
  TStack<int, 100> stack;
  for (int i = 0; i < post.length(); i++) {
    char c = post[i];
    if (c == ' ') continue;
    if (isdigit(c)) {
      int number = 0;
      while (i < post.length() && isdigit(post[i])) {
        number = number * 10 + (post[i] - '0');
        i++;
      }
      stack.addToStack(number);
      i--;
    } else if (isOperator(c)) {
      int right = stack.takeFromStack();
      int left = stack.takeFromStack();
      int result = doOperation(left, right, c);
      stack.addToStack(result);
    }
  }
  return stack.takeFromStack();
}
