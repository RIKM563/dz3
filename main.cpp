#include <math.h>
#include <string>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

void mspace(string &stroka)
{
    int a = 0;
    int b = 0;
    while (stroka[b] != '\0') {
        stroka[a] = stroka[b];
        b++;
        if (stroka[a] != ' ') a++;
    }
    stroka = stroka.substr(0, a);
    return;
}

vector<int> hey(string str) {
    int length = size(str);
    int pos1, pos2, b;
    b = 0;
    pos1 = -1;
    for (int i = 0; i < length; i++) {
        if ((str[i] == '(')) {
            b++;
            if (pos1 == -1) {
                pos1 = i;
            }
        }
        if (str[i] == ')') {
            b--;
            if (b == 0) {
                pos2 = i;
                return {pos1, pos2};
            }
        }
    }
    if (b == 0) {
        return {0, 0};
    }
}

bool check_correct(string calc, bool &x) {
    set<char> elements;
    for (int i = 40; i < 58; i++)
        elements.insert((char) i);
    elements.erase(',');
    elements.insert('s');
    elements.insert('c');
    elements.insert('t');
    elements.insert('e');
    elements.insert('x');
    int ckobka = 0;
    bool m = true;
    for (int i = 0; i < size(calc); i++) {
        char pos = calc[i];
        if (pos == '(') {
            ckobka += 1;
            if (calc[i + 1] == ')') {
                m = false;
                cout << "Skobki ne nyzhny: " << i + 1 << endl;
            }
        } else if (pos == ')') {
            ckobka -= 1;
            if (ckobka < 0) {
                m = false;
                cout << "Lishnya ): " << i + 1 << endl;
            }
        }
        if (pos == 'c') {
            if ((calc.substr(i, 4) == "ctg(") || (calc.substr(i, 4) == "cos("))
                i += 2;
            else {
                m = false;
                cout << "cos or ctg neverno ispolzyetsya: " << i + 1 <<
                     endl;
            }
        }
        if (pos == 's') {
            if (calc.substr(i, 4) == "sin(") i += 2;
            else {
                m = false;
                cout << "sin neverno ispolzyetsya: " << i + 1 << endl;
            }
        }
        if (pos == 't') {
            if (calc.substr(i, 3) == "tg(") i += 1;
            else {
                m = false;
                cout << "tg neverno ispolzyetsya: " << i + 1 << endl;
            }
        }
        if (pos == 'e') {
            if (calc.substr(i, 4) == "exp(") i += 2;
            else {
                m = false;
                cout << "exp neverno ispolzyetsya: " << i + 1 << endl;
            }
        }
        if (pos == 'x') {
            x = true;
        }
        if (elements.find(pos) == elements.end()) {
            m = false;
            cout << "Ne ponyatnyi element: " << i + 1 << endl;
        }
        if (pos == '.') {
            if (i == 0 || isdigit(calc[i - 1]) == false || isdigit(calc[i + 1]) == false) {
                m = false;
                cout << "Problema s tockoi: " << i + 1 << endl;
            }
            int k = 0;
            while (calc[i] == '.' || isdigit(calc[i])) {
                i++;
                if (calc[i] == '.') {
                    m = false;
                    cout << "Problema s tockoi: " << i + 1 << endl;
                }
            }
            i--;
        }
        if ((pos == '/' || pos == '*' || pos == '+') && (i == 0 || calc[i - 1] == '(' || calc[i + 1] ==
                                                                                          ')')) {
            m = false;
            cout << "Neponyatnyi symvol: " << i + 1 << endl;
        }
        if ((pos == '/' || pos == '*' || pos == '+' || pos == '-') && (calc[i + 1] == '/' || calc[i + 1]
                                                                                              == '*' ||
                                                                        calc[i + 1] == '+' || calc[i + 1] == '-')) {
            m = false;
            cout << "Neponyatnyi symvol: " << i + 2 << endl;
        }
    }
    if (ckobka > 0) {
        m = false;
        cout << "Lishnie skobki" << endl;
    }
    if (m != 1) {
        cout << "Chto-to ne tak";
        return 0;
    } else return 1;
}

double calc(string a) {
    int Size = size(a);
    string s;
    string p;
    string v;
    int trg = 1;
    double znach;
    while (trg != 0) {
        if ((trg = a.find("sin")) != -1) {
            vector<int> sk = hey(v.assign(a, trg, Size - trg));
            sk[0] += trg;
            sk[1] += trg;
            p.assign(a, 0, trg);
            s.assign(a, sk[0] + 1, sk[1] - sk[0] - 1);
            v.assign(a, sk[1] + 1, Size - sk[1]);
            znach = sin(calc(s));
            a = p + to_string(znach) + v;
            Size = size(a);
        } else if ((trg = a.find("cos")) != -1) {
            vector<int> sko = hey(v.assign(a, trg, Size - trg));
            sko[0] += trg;
            sko[1] += trg;
            p.assign(a, 0, trg);
            s.assign(a, sko[0] + 1, sko[1] - sko[0] - 1);
            v.assign(a, sko[1] + 1, Size - sko[1]);
            znach = cos(calc(s));
            a = p + to_string(znach) + v;
            Size = size(a);
        } else if ((trg = a.find("ctg")) != -1) {
            vector<int> sk = hey(v.assign(a, trg, Size - trg));
            sk[0] += trg;
            sk[1] += trg;
            p.assign(a, 0, trg);
            s.assign(a, sk[0] + 1, sk[1] - sk[0] - 1);
            v.assign(a, sk[1] + 1, Size - sk[1]);
            znach = 1 / tan(calc(s));
            a = p + to_string(znach) + v;
            Size = size(a);
        } else if ((trg = a.find("tg")) != -1) {
            vector<int> sk = hey(v.assign(a, trg, Size - trg));
            sk[0] += trg;
            sk[1] += trg;
            p.assign(a, 0, trg);
            s.assign(a, sk[0] + 1, sk[1] - sk[0] - 1);
            v.assign(a, sk[1] + 1, Size - sk[1]);
            znach = tan(calc(s));
            a = p + to_string(znach) + v;
            Size = size(a);
        } else if ((trg = a.find("exp")) != -1) {
            vector<int> sk = hey(v.assign(a, trg, Size - trg));
            sk[0] += trg;
            sk[1] += trg;
            p.assign(a, 0, trg);
            s.assign(a, sk[0] + 1, sk[1] - sk[0] - 1);
            v.assign(a, sk[1] + 1, Size - sk[1]);
            znach = exp(calc(s));
            a = p + to_string(znach) + v;
            Size = size(a);
        } else trg = 0;
    }
    vector<int> sk = hey(a);
    if (sk[1]) {
        p.assign(a, 0, sk[0]);
        s.assign(a, sk[0] + 1, sk[1] - sk[0] - 1);
        v.assign(a, sk[1] + 1, Size - sk[1]);
        a = p + to_string(calc(s)) + v;
        return calc(a);
    }
    for (int i = Size - 1; i > -1; i--) {
        if (a[i] == '+') {
            p.assign(a, 0, i);
            v.assign(a, i + 1, Size - i - 1);
            return (calc(p) + calc(v));
        } else if (a[i] == '-') {
            if (i != 0 && isdigit(a[i - 1]) == 0)
                continue;
            p.assign(a, 0, i);
            v.assign(a, i + 1, Size - i - 1);
            return (calc(p) - calc(v));
        }
    }
    for (int i = Size - 1; i > -1; i--) {
        if (a[i] == '*') {
            p.assign(a, 0, i);
            v.assign(a, i + 1, Size - i - 1);
            return (calc(p) * calc(v));
        } else if (a[i] == '/') {
            p.assign(a, 0, i);
            v.assign(a, i + 1, Size - i - 1);
            double t = calc(v);
            if (t == 0) {
                cout << "/0 zapresheno" << endl;
                system("pause");
            }
            return (calc(p) / t);
        }
    }
    if (a == "") {
        return 0;
    }
    return stod(a);
}

int main() {
    setlocale(LC_CTYPE, "rus");
    string ur;
    cout << "Vvedite vyraghenie: ";
    getline(cin, ur);
    int q;
    mspace(ur);
    bool x = false;
    if (check_correct(ur, x)) {
        if (x) {
            double x;
            cout << "Vvedite x = ";
            cin >> x;
            for (int q = 0; q < size(ur); q++)
                if (ur[q] == 'x' && ur[q - 1] != 'e') {
                    if (isdigit(ur[q - 1])) ur.replace(q, 1, '*' + to_string(x));
                    else ur.replace(q, 1, to_string(x));
                }
        }
        cout << "Otvet: " << calc(ur) << endl;
    }
}
