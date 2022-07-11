#include <iostream>
#include <stack>
#include <sstream>
#include <cmath>
using namespace std;

const double Pi = acos(-1);


struct Struct //Определение типа чисел
{
    char type;
    double value;
};


double Sin(double x) {
    return (round(sin(x) * 10000000) / 10000000);
}
double Cos(double x) {
    return (round(cos(x) * 10000000) / 10000000);
}
double Ctg(double x) {
    double a = cos(x);
    double b = Sin(x);
    return (a / b);
}

bool Math(stack <Struct>& Stack_ch, stack <Struct>& Stack_opp, Struct& item) {
    if (Stack_ch.size() == 0) {
        return false;
    }

    double a, b, c;
    a = Stack_ch.top().value;
    Stack_ch.pop();
    switch (Stack_opp.top().type)
    {
    case '+':
        b = Stack_ch.top().value;
        Stack_ch.pop();
        c = a + b;
        item.type = '0';
        item.value = c;
        Stack_ch.push(item);
        Stack_opp.pop();
        break;
    case '-':
        b = Stack_ch.top().value;
        Stack_ch.pop();
        c = b - a;
        item.type = '0';
        item.value = c;
        Stack_ch.push(item);
        Stack_opp.pop();
        break;
    case '^':
        b = Stack_ch.top().value;
        Stack_ch.pop();
        c = pow(b, a);
        item.type = '0';
        item.value = c;
        Stack_ch.push(item);
        Stack_opp.pop();
        break;
    case '*':
        b = Stack_ch.top().value;
        Stack_ch.pop();
        c = a * b;
        item.type = '0';
        item.value = c;
        Stack_ch.push(item);
        Stack_opp.pop();
        break;
    case '/':
        b = Stack_ch.top().value;
        if (a == 0) {
            cerr << "\nНа 0 делить нельзя!\n";
            return false;
        }
        Stack_ch.pop();
        c = (b / a);
        item.type = '0';
        item.value = c;
        Stack_ch.push(item);
        Stack_opp.pop();
        break;
    case 's':
        c = Sin(a);
        item.type = '0';
        item.value = c;
        Stack_ch.push(item);
        Stack_opp.pop();
        break;
    case 'c':
        c = Cos(a);
        item.type = '0';
        item.value = c;
        Stack_ch.push(item);
        Stack_opp.pop();
        break;
    case 't':
        if (Cos(a) == 0) {
            cerr << "\nНеверный аргумент для тангенса!\n";
            return false;
        }
        else {
            c = tan(a);
            item.type = '0';
            item.value = c;
            Stack_ch.push(item);
            Stack_opp.pop();
            break;
        }

    case 'g':
        if (Sin(a) == 0) {
            cerr << "\nНеверный аргумент для котангенса!\n";
            return false;
        }
        else {
            c = Ctg(a);
            item.type = '0';
            item.value = c;
            Stack_ch.push(item);
            Stack_opp.pop();
            break;
        }
    case 'e':
        c = exp(a);
        item.type = '0';
        item.value = c;
        Stack_ch.push(item);
        Stack_opp.pop();
        break;
    default:
        cerr << "\nОшибка!\n";
        return false;
        break;
    }
    return true;
}

int Rang(char ch) {//Приоритет 
    if (ch == 's' || ch == 'c' || ch == 't' || ch == 'g' || ch == 'e') return 4;
    if (ch == '^') return 3;
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    else return 0;
}

void Error_(stack <Struct>& Stack_ch, stack <Struct>& Stack_op) {
    while (Stack_ch.size() != 0) {
        Stack_ch.pop();
    }
    while (Stack_op.size() != 0) {
        Stack_op.pop();
    }
    cout << "\nОшибка\n" << endl;
    string str;
    getline(cin, str);
}

int main()
{
    setlocale(LC_ALL, "rus");

    while (true) {
        bool Error = false;
        cout << "   Введите выражение: ";


        char ch;
        double value;
        bool flag = true;
        stack<Struct> Stack_ch;
        stack<Struct> Stack_op;
        Struct item;
        while (true) {
            ch = cin.peek();
            if (ch == '\n') break;
            if (ch == ' ') {
                cin.ignore();
                continue;
            }

            if (ch == 's' || ch == 'c' || ch == 't' || ch == 'e') {
                char foo[3];
                for (int i = 0; i < 3; i++) {
                    ch = cin.peek();
                    foo[i] = ch;
                    cin.ignore();
                }
                if (foo[0] == 's' && foo[1] == 'i' && foo[2] == 'n') {
                    item.type = 's';
                    item.value = 0;
                    Stack_op.push(item);
                    continue;
                }
                if (foo[0] == 'c' && foo[1] == 'o' && foo[2] == 's') {
                    item.type = 'c';
                    item.value = 0;
                    Stack_op.push(item);
                    continue;
                }
                if (foo[0] == 't' && foo[1] == 'a' && foo[2] == 'n') {
                    item.type = 't';
                    item.value = 0;
                    Stack_op.push(item);
                    continue;
                }
                if (foo[0] == 'c' && foo[1] == 't' && foo[2] == 'g') {
                    item.type = 'g';
                    item.value = 0;
                    Stack_op.push(item);
                    continue;
                }
                if (foo[0] == 'e' && foo[1] == 'x' && foo[2] == 'p') {
                    item.type = 'e';
                    item.value = 0;
                    Stack_op.push(item);
                    continue;
                }
            }
            if (ch == 'p') {
                item.type = '0';
                item.value = Pi;
                Stack_ch.push(item);
                flag = 0;
                cin.ignore();
                continue;
            }

            if (ch >= '0' && ch <= '9' || ch == '-' && flag == 1) {
                if (ch == '-' && flag == 1) {
                    cin.ignore();
                    int check = cin.peek();
                    if (check == '0') {
                        item.value = 0;
                        Stack_ch.push(item);
                        item.value = -1;
                        Stack_ch.push(item);
                        item.type = '*';
                        Stack_op.push(item);

                        flag = 0;
                        cin.ignore();
                        continue;
                    }else {
                        cin >> value;
                        if (value == 0)
                        {
                            cin.clear();
                            ch = cin.peek();
                            if (ch == '(') {
                                item.value = -1;
                                Stack_ch.push(item);
                                item.type = '*';
                                Stack_op.push(item);
                                flag = 1;
                            }
                            else {
                                Error = true;
                                cin.clear();
                                break;
                            }
                            
                            
                        } else {
                            item.type = '0';
                            item.value = -value;
                            Stack_ch.push(item);
                            flag = 0;
                            continue;
                        }

                    }
                }
                else {
                    cin >> value;
                    item.type = '0';
                    item.value = value;
                    Stack_ch.push(item);
                    flag = 0;
                    continue;
                }
            

            }

            if (ch == '+' || ch == '-' && flag == 0 || ch == '*' || ch == '/' || ch == '^') {
                if (Stack_op.size() == 0) {
                    item.type = ch;
                    item.value = 0;
                    Stack_op.push(item);
                    cin.ignore();
                    continue;
                }
                if (Stack_op.size() != 0 && Rang(ch) >
                    Rang(Stack_op.top().type)) {
                    item.type = ch;
                    item.value = 0;
                    Stack_op.push(item);
                    cin.ignore();
                    continue;
                }
                if (Stack_op.size() != 0 && Rang(ch) <= Rang(Stack_op.top().type)) {
                    if (Math(Stack_ch, Stack_op, item) == false) {
                       
                        return 0;
                    }
                    continue;
                }
            }
            if (ch == '(') {
                item.type = ch;
                item.value = 0;
                Stack_op.push(item);
                cin.ignore();
                flag = 1;

            }else if  (ch == ')') {
                if (Stack_op.size() == 0) {
                    Error = true;
                    break;
                }
                while (Stack_op.top().type != '(') {
                    if (Math(Stack_ch, Stack_op, item) == false) {
                        return 0;
                    }
                    else continue;
                }
                Stack_op.pop();
                cin.ignore();
                continue;
            }
            else {
                cout << "\nНеверно введено выражение!\n";
                return 0;
            }
        }

        if (Stack_ch.size() == 0 and Stack_op.size() == 1) {
            Error = true;
        }
        if ( Stack_ch.size() + 1 > Stack_ch.size() or !Stack_op.size() and !Stack_ch.top().value) {
            Error = true;
        }

        if (Stack_ch.size() == 0 and Stack_op.size() != 0) {
            Error = true;
        }
        if (!Error) {
            int flag = 0;
            while (Stack_op.size() !=
                0) {
                if (Math(Stack_ch, Stack_op, item) == false) {
                    cout << endl;
                    string str;
                    getline(cin, str);
                    flag = 1;
                    break;
                }

            }
            if (Stack_ch.size() == 1 and !flag) {
                cout << Stack_ch.top().value << " " << endl;
                Stack_ch.pop();
                cin.ignore();
            }
            else if (Stack_ch.size() != 1 and !flag) {
               Error_(Stack_ch, Stack_op);
            }
            
        }
        else {
            Error_(Stack_ch, Stack_op);
        }
       }
       
}