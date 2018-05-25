#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

string g[50][50];
string drp[50];
int p, nrp;

string unire(string x, string y) {
    unsigned int i;
    string t = x;
    for (i = 0; i < y.length(); i++)
        if (t.find(y[i]) > t.length())
            t = t + y[i];
    return t;
}

void separare(string x) {
    unsigned int i;
    p = 0;
    while (x.length()) {
        i = x.find("|");
        if (i > x.length()) {
            drp[p++] = x;
            x = "";
        } else {
            drp[p++] = x.substr(0, i);
            x = x.substr(i + 1, x.length());
        }
    }
}

int verificare1(string x) {
    if (x.length() == 1 && x[0] >= 'A' && x[0] <= 'Z')
        return 1;
    return 0;
}

int verificare2(string x) {
    if (x.length() == 1 && x[0] >= 'a' && x[0] <= 'z')
        return 1;
    if (x.length() == 2 && x[0] >= 'A' && x[0] <= 'Z' && x[1] >= 'A' && x[1] <= 'Z')
        return 1;
    return 0;
}

string cautare(string p) {
    int j, k;
    string t = "";
    for (j = 0; j < nrp; j++) {
        k = 1;
        while (g[j][k] != "") {
            if (g[j][k] == p) {
                t = unire(t, g[j][0]);
            }
            k++;
        }
    }
    return t;
}

string combinatii(string x, string y) {
    unsigned int i, j;
    string temp = x, t = "";
    for (i = 0; i < x.length(); i++) {
        for (j = 0; j < y.length(); j++) {
            temp = "";
            temp = temp + x[i] + y[j];
            t = t + cautare(temp);
        }
    }
    return t;
}


int main() {
    int l, t, k;
    string x, cuvant, r, pr, start;
    ifstream f("cyk.txt");
    f >> start;
    f >> nrp;
    for (int i = 0; i < nrp; i++) {
        f >> x;
        t = x.find("->");
        g[i][0] = x.substr(0, t);
        if (verificare1(g[i][0]) == 0) {
            cout << "Gramatica nu este in CNF" << endl;
            return 0;
        }
        x = x.substr(t + 2, x.length());
        separare(x);
        for (int j = 0; j < p; j++) {
            g[i][j + 1] = drp[j];
            if (verificare2(drp[j]) == 0) {
                cout << "Cuvantul nu este in CNF" << endl;
                return 0;
            }
        }
    }
    string m[100][100], st;
    f >> cuvant;
    for (unsigned int i = 0; i < cuvant.length(); i++) {
        r = "";
        st = "";
        st = st + cuvant[i];
        for (int j = 0; j < nrp; j++) {
            k = 1;
            while (g[j][k] != "") {
                if (g[j][k] == st)
                    r = unire(r, g[j][0]);
                k++;
            }
        }
        m[i][i] = r;
    }
    for (unsigned int k = 1; k < cuvant.length(); k++) {
        for (unsigned int j = k; j < cuvant.length(); j++) {
            r = "";
            for (l = j - k; l < j; l++) {
                pr = combinatii(m[j - k][l], m[l + 1][j]);
                r = unire(r, pr);
            }
            m[j - k][j] = r;
        }
    }

    for (unsigned int i = 0; i < cuvant.length(); i++) {
        k = 0;
        l = cuvant.length() - i - 1;
        for (unsigned int j = l; j < cuvant.length(); j++)
            cout << setw(3) << m[k++][j] << " ";
        cout << endl;
    }
    for (unsigned int i = 0; i < start.length(); i++)
        if (m[0][cuvant.length() - 1].find(start[i]) <= m[0][cuvant.length() - 1].length()) {
            cout << "Cuvantul '" << cuvant << "' apartine limbajului!" << endl;
            return 0;
        }
    cout << "Cuvantul '" << cuvant << "' nu apartine limbajului!" << endl;
    return 0;
}
