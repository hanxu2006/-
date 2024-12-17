#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string str[21];

string copy(const int N, const int X, const int L) {
    return str[N - 1].substr(X, L);
}

string add(string str1, string str2) {
    bool isint = true;
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] < '0' || str1[i] > '9') {
            isint = false;
        }
    }
    for (int i = 0; i < str2.length(); i++) {
        if (str2[i] < '0' || str2[i] > '9') {
            isint = false;
        }
    }
    if (isint) {
        int num1 = 0, num2 = 0;
        for (char c: str1) {
            num1 = num1 * 10 + (c - '0');
        }
        for (char c: str2) {
            num2 = num2 * 10 + (c - '0');
        }
        return to_string(num1 + num2);
    }
    return str1 + str2;
}

int find(const string &s, const int N) {
    const int pos = str[N - 1].find(s);
    if (pos != string::npos) {
        return pos;
    } else {
        return s.length();
    }
}

int rfind(const string &s, const int N) {
    const int pos = str[N - 1].rfind(s);
    if (pos != string::npos) {
        return pos;
    } else {
        return s.length();
    }
}

void insert(const string &s, const int N, const int X) {
    str[N - 1].insert(X, s);
}

void reset(const string &s, const int N) {
    str[N - 1].clear();
    str[N - 1] = s;
}

void print(const int N) {
    cout << str[N - 1] << endl;
}

void printall() {
    for (const auto &i: str) {
        if (!i.empty()) {
            cout << i << endl;
        }
    }
}

bool haveorder(const string &order) {
    istringstream iss(order);
    string cmd;
    while (iss >> cmd) {
        if (cmd == "copy"
            || cmd == "add"
            || cmd == "find"
            || cmd == "rfind"
            || cmd == "insert"
            || cmd == "reset"
            || cmd == "print"
            || cmd == "printall"
            || cmd == "over") {
            return true;
        }
    }
    return false;
}

bool isdigit(const char &c) {
    return c >= '0' && c <= '9';
}

bool isnumber(const string &str) {
    for (const auto &c: str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void putback(istringstream &iss, const string &word) {
    string remaining;
    getline(iss, remaining);

    remaining = word + " " + remaining;

    iss.clear();
    iss.str(remaining);
}

int main() {
    int count;
    cin >> count;
    cin.ignore();
    for (int i = 0; i < count; i++) {
        getline(cin, str[i]);
    }
    string order;
    while (getline(cin, order)) {
    remake:
        istringstream iss(order);
        string cmd;
        while (haveorder(order) && iss >> cmd) {
            if (haveorder(cmd)) {
                if (cmd == "over") {
                    return 0;
                }

                if (cmd == "printall") {
                    printall();
                    string c = "printall";
                    size_t pos = order.find(c);
                    if (pos != string::npos) {
                        order.replace(order.find(c), c.length(), "");
                        break;
                    }
                }

                if (cmd == "copy") {
                    string n;
                    iss >> n;
                    if (isnumber(n)) {
                        string x;
                        iss >> x;
                        if (isnumber(x)) {
                            string l;
                            iss >> l;
                            if (isnumber(l)) {
                                int N = stoi(n);
                                int X = stoi(x);
                                int L = stoi(l);
                                string cpy = copy(N, X, L);
                                string c = "copy " + n + " " + x + " " + l;
                                size_t pos = order.find(c);
                                if (pos != string::npos) {
                                    order.replace(order.find(c), c.length(), cpy);
                                    goto remake;
                                }
                            } else {
                                putback(iss, l);
                                putback(iss, x);
                                putback(iss, n);
                            }
                        } else {
                            putback(iss, x);
                            putback(iss, n);
                        }
                    } else {
                        putback(iss, n);
                    }
                }

                if (cmd == "add") {
                    string s1;
                    iss >> s1;
                    if (!haveorder(s1)) {
                        string s2;
                        iss >> s2;
                        if (!haveorder(s2)) {
                            string s;
                            s = add(s1, s2);
                            string c = "add " + s1 + " " + s2;
                            size_t pos = order.find(c);
                            if (pos != string::npos) {
                                order.replace(order.find(c), c.length(), s);
                                goto remake;
                            }
                        } else {
                            putback(iss, s2);
                            putback(iss, s1);
                        }
                    } else {
                        putback(iss, s1);
                    }
                }

                if (cmd == "find") {
                    string s1;
                    iss >> s1;
                    if (!haveorder(s1)) {
                        string n;
                        iss >> n;
                        if (isnumber(n)) {
                            int lenth = find(s1, stoi(n));
                            string c = "find " + s1 + " " + n;
                            size_t pos = order.find(c);
                            if (pos != string::npos) {
                                order.replace(order.find(c), c.length(), to_string(lenth));
                                goto remake;
                            }
                        } else {
                            putback(iss, n);
                            putback(iss, s1);
                        }
                    } else {
                        putback(iss, s1);
                    }
                }

                if (cmd == "rfind") {
                    string s1;
                    iss >> s1;
                    if (!haveorder(s1)) {
                        string n;
                        iss >> n;
                        if (isnumber(n)) {
                            int lenth = rfind(s1, stoi(n));
                            string c = "rfind " + s1 + " " + n;
                            size_t pos = order.find(c);
                            if (pos != string::npos) {
                                order.replace(order.find(c), c.length(), to_string(lenth));
                                goto remake;
                            }
                        } else {
                            putback(iss, n);
                            putback(iss, s1);
                        }
                    } else {
                        putback(iss, s1);
                    }
                }

                if (cmd == "insert") {
                    string s;
                    iss >> s;
                    if (!haveorder(s)) {
                        string n;
                        iss >> n;
                        if (isnumber(n)) {
                            string x;
                            iss >> x;
                            if (isnumber(x)) {
                                insert(s, stoi(n), stoi(x));
                                string c = "insert " + s + " " + n + " " + x + " ";
                                size_t pos = order.find(c);
                                if (pos != string::npos) {
                                    order.replace(order.find(c), c.length(), "");
                                    goto remake;
                                }
                            } else {
                                putback(iss, x);
                                putback(iss, n);
                                putback(iss, s);
                            }
                        } else {
                            putback(iss, n);
                            putback(iss, s);
                        }
                    } else {
                        putback(iss, s);
                    }
                }

                if (cmd == "reset") {
                    string s;
                    iss >> s;
                    if (!haveorder(s)) {
                        string n;
                        iss >> n;
                        if (isnumber(n)) {
                            reset(s, stoi(n));
                            string c = "reset " + s + " " + n + " ";
                            size_t pos = order.find(c);
                            if (pos != string::npos) {
                                order.replace(order.find(c), c.length(), "");
                                goto remake;
                            }
                        } else {
                            putback(iss, n);
                            putback(iss, s);
                        }
                    } else {
                        putback(iss, s);
                    }
                }

                if (cmd == "print") {
                    string n;
                    iss >> n;
                    if (isnumber(n)) {
                        print(stoi(n));
                        string c = "print " + n + " ";
                        size_t pos = order.find(c);
                        if (pos != string::npos) {
                            order.replace(order.find(c), c.length(), "");
                            goto remake;
                        }
                    } else {
                        putback(iss, n);
                    }
                }
            }
        }
    }
}