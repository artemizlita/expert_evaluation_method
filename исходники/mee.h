#ifndef MEE_H
#define MEE_H
#include<QtCore>

#include <vector>
#include <algorithm>

using namespace std;

class mee {
public:
    int d = 0, m = 0;
    float mr, s, tc;
    vector<vector<int> > e_o;
    vector<float> e_c, e_d, r, t;

    float find_kc() {
        r.resize(m);
        for (int i = 0; i < m; ++i) {
            r[i] = 0;
            for (int j = 0; j < d; ++j) {
                r[i] += e_o[i][j];
            }
        }
        mr = 0;
        for (int i = 0; i < m; ++i) {
            mr += r[i];
        }
        mr /= m;
        s = 0;
        for (int i = 0; i < m; ++i) {
            float a = 0;
            for (int j = 0; j < d; ++j) {
                a += e_o[i][j];
            }
            a -= mr;
            a = pow(a, 2);
            s += a;
        }
        t.resize(d);
        int tk = 0;
        for (int i = 0; i < d; ++i) {
            vector<int> mark;
            mark.resize(6);
            for (int j = 0; j < 6; ++j) {
                mark[j] = 0;
            }
            for (int j = 0; j < m; ++j) {
                mark[e_o[j][i]] += 1;
            }
            t[i] = 0;
            for (int j = 0; j < 6; ++j) {
                if (mark[j] > 1) {
                    t[i] += pow(mark[j], 3) - mark[j];
                }
            }
            tk += t[i];
        }
        return 12 * s / (pow(d, 2) * (pow(m, 3) - m) - d * tk);
    }

    bool readMatrOutFile(QString &fName) {
        QFile file(fName);
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug()<<"File not open";   return false;
        }
        e_o.clear();
        e_c.clear();
        QString str = file.readLine();
        QStringList lst = str.split(" ");
        m = lst[0].toInt();
        d = lst[1].toInt();
        e_o.resize(m);
        e_c.resize(d);
        e_d.resize(d);
        str = file.readLine();
        lst = str.split(" ");
        for (int i = 0; i < d; ++i) {
            e_c[i] = lst[i].toFloat();
        }
        str = file.readLine();
        lst = str.split(" ");
        for (int i = 0; i < d; ++i) {
            e_d[i] = lst[i].toFloat();
        }
        for(int i = 0; i < m; ++i) {
            str = file.readLine();
            lst = str.split(" ");
            e_o[i].resize(d);
            for (int j = 0; j < d; ++j) {
                e_o[i][j] = lst[j].toInt();
            }
        }
        file.close ();
        return true;
    }

    bool writeMatrInFile(QString &fName) {
        QFile file(fName);
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug()<<"File not open";
            return false;
        }
        QTextStream out(&file);
        out.setRealNumberPrecision(2);
        out<<m;
        out<<' ';
        out<<d;
        out<<endl;
        for(int i = 0; i < d; ++i) {
            out<<e_c[i];
            out<<' ';
        }
        out<<endl;
        for(int i = 0; i < d; ++i) {
            out<<e_d[i];
            out<<' ';
        }
        out<<endl;
        for(int i = 0; i < m; ++i) {
             for(int j = 0; j < d; ++j) {
                 out<<e_o[i][j];
                 out<<' ';
             }
             out<<endl;
        }
        file.close ();
        return true;
    }
};

#endif // MEE_H
