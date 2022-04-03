// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char c) {
  switch (c) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
  }
  return -1;
}

bool isDigit(std::string pref) {
  for (size_t i = 0; i < pref.size(); ++i) {
    if (pref[i] < '0' || pref[i] > '9')
      return false;
  }
  return true;
}

std::string infx2pstfx(std::string inf) {
  TStack <char, 50> stack;
  std::string result;
  for (int i = 0; i < inf.size(); i++) {
    int p = priority(inf[i]);
    if (p == -1) {
      if (!result.empty() && priority(inf[i - 1]) != -1) {
        result.push_back(' ');
      }
      result.push_back(inf[i]);
    } else if (p == 0 || p > priority(stack.get()) || stack.isEmpty()) {
      stack.push(inf[i]);
    } else {
      if (p == 1) {
        while (stack.get() != '(') {
          result.push_back(' ');
          result.push_back(stack.get());
          stack.pop();
        }
        stack.pop();
      } else {
        while (priority(stack.get()) >= p) {
          result.push_back(' ');
          result.push_back(stack.get());
          stack.pop();
        }
        stack.push(inf[i]);
      }
    }
  }
  while (!stack.isEmpty()) {
    result.push_back(' ');
    result.push_back(stack.get());
    stack.pop();
  }
  return result;
}

int eval(std::string post) {
  TStack <int, 50> resStack;
  std::string temp;
  int a = 0, b = 0;
  size_t begin = 0, end = 0;
  for (size_t i = 0; i < post.size(); ++i) {
    if (post[i] == ' ' || i == post.size()-1) {
      end = i;
      if (i ==post.size() - 1)
        end++;
      temp = post.substr(begin, end - begin);
      begin = end + 1;
      if (isDigit(temp)) {
        resStack.push(std::stoi(temp));
      } else {
        b = resStack.get();
        resStack.pop();
        a = resStack.get();
        resStack.pop();
        if (temp == "+")
          resStack.push(a + b);
        else if (temp == "-")
          resStack.push(a - b);
        else if (temp == "*")
          resStack.push(a * b);
        else if (temp == "/")
          resStack.push(a / b);
      }
    }
  }
  return resStack.get();
}
