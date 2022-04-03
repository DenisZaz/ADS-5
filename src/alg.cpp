// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char op) {
  switch (op) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    default: return 4;
  }
}

int calc(char op, int x, int y) {
  switch (op) {
    case '+': return x + y;
    case '-': return x - y;
    case '*': return x * y;
    case '/': return x / y;
  }
  return 0;
}

std::string str1 = "";
std::string infx2pstfx(std::string inf) {
TStack <char, 100> charstack;
for (int i = 0; i < inf.length(); i++) {
  if (priority(inf[i]) == 4) {
    str1 += inf[i];
  } else if (priority(inf[i]) > 1 && priority(inf[i]) < 4) {
      if (charstack.isEmpty() || priority(charstack.get()) == 0) {
        charstack.push(inf[i]);
          str1 += " ";
         } else if (priority(inf[i]) > priority(charstack.get())) {
             charstack.push(inf[i]);
             str1 += " ";
         } else if (priority(inf[i]) <= priority(charstack.get())) {
             str1 += " ";
             str1 += charstack.get();
             charstack.pop();
             str1 += " ";
             while ((priority(inf[i]) <= priority(charstack.get())
             || priority(charstack.get()) != 0) && !charstack.isEmpty()) {
               str1 += " ";
               str1 += charstack.get();
               charstack.pop();
               str1 += " ";
             }
             charstack.push(inf[i]);
          }
        } else if (priority(inf[i]) == 0) {
            charstack.push(inf[i]);
        } else if (priority(inf[i]) == 1) {
            while (priority(charstack.get()) != 0) {
              str1 += " ";
              str1 += charstack.get();
              charstack.pop();
            }
            charstack.pop();
        }
    }
    while (!charstack.isEmpty()) {
      str1 += " ";
      str1 += charstack.get();
      charstack.pop();
    }
  return str1;
}

int eval(std::string postf) {
TStack <int, 100> numstack;
int sum = 0, x = 0, y = 0;
for (int i = 0; i < postf.size(); i+=2) {
  if (priority(postf[i]) == 4) {
    numstack.push(atoi(&postf[i]));
  } else {
      y = numstack.get();
      numstack.pop();
      x = numstack.get();
      numstack.pop();
      sum = calc(postf[i], x, y);
      numstack.push(sum);
    }
}
return sum;
}
