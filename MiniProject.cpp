#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isWhitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

bool isOperator(char c) {
    return (c == '>' || c == '<' || c == '=' || c == '!' || c == '&' || c == '|');
}

bool analyzeIfElseSyntax(string code) {
    stack<char> brackets;
    bool inCondition = false;
    bool hasCondition = false;
    
    for (int i = 0; i < code.length(); i++) {
        char c = code[i];
        
        if (isWhitespace(c)) continue;
        
        if (i < code.length() - 1 && code.substr(i, 2) == "if") {
            i += 1;
            while (i + 1 < code.length() && isWhitespace(code[i + 1])) i++;
            if (i + 1 < code.length() && code[i + 1] == '(') {
                brackets.push('(');
                inCondition = true;
                i++;
            } else {
                cout << "Error: Missing '(' after 'if'\n";
                return false;
            }
        }
        else if (c == '(') {
            brackets.push(c);
            inCondition = true;
        }
        else if (c == ')') {
            if (brackets.empty()) {
                cout << "Error: Unmatched ')'\n";
                return false;
            }
            brackets.pop();
            inCondition = false;
            hasCondition = true;
        }
        else if (c == '{') {
            if (!hasCondition) {
                cout << "Error: Missing condition before '{'\n";
                return false;
            }
            brackets.push(c);
        }
        else if (c == '}') {
            if (brackets.empty()) {
                cout << "Error: Unmatched '}'\n";
                return false;
            }
            brackets.pop();
        }
        else if (i < code.length() - 3 && code.substr(i, 4) == "else") {
            if (!hasCondition) {
                cout << "Error: 'else' without preceding 'if'\n";
                return false;
            }
            i += 3;
        }
        else if (inCondition && isOperator(c)) {
            continue;
        }
    }
    
    if (!brackets.empty()) {
        cout << "Error: Unmatched brackets\n";
        return false;
    }
    
    return true;
}

int main() {
    cout << "If-Else Syntax Analyzer\n";
    cout << "Enter your if-else code (press Enter twice to analyze):\n";
    
    string code, line;
    while (getline(cin, line) && !line.empty()) {
        code += line + "\n";
    }
    
    if (code.empty()) {
        cout << "No code entered!\n";
        return 1;
    }
    
    if (analyzeIfElseSyntax(code)) {
        cout << "Syntax is valid!\n";
    } else {
        cout << "Syntax is invalid!\n";
    }
    
    return 0;
}