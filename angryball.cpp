/*Вариант 5, день 3

Разработать программу для моделирования полета брошенного с  со скоростью vx (горизонтальная составляющая) и vx (горизонтальная составляющая) шарика массой m.
При соударении с землей шарик теряет определенный процент кинетической энергии (задается параметром функции)  и отскакивает (угол падения равен углу отражения).  


Программа должна иметь функции:
- Вычисления положения (h) и параметров движения шарика (v, a) через заданный промежуток времени
- Позволять записывать параметы движения шарика и метку времении в односвязный списко
- Печатать на экран информацию о траектории движения шарика за заданный промежуток времени
*/




#include <iostream>
#include <cmath>
#include <clocale>
#include <tuple>
#include <list>

using namespace std;

const float g = 9.81;
const float dt = 0.01;

float rt(float t, float v0) {
    return v0 * t - g * t * t / 2;
}

float xt(float t, float vx) {
    return vx * t - g * t * t / 2;
}

float yt(float t, float vy) {
    return vy * t - g * t * t / 2;
}
float at(float t, float vy, float vx) {
    float xt1 = xt(t, vx);
    float yt1 = yt(t, vy);
    float ax = 2 * (xt1 - vx * t) / (t * t);
    float ay = 2 * (yt1 - vy * t) / (t * t);
    return sqrt(ax * ax + ay * ay);
}

float vt(float t, float v0, float sina) {
    return sqrt(v0 * v0 - 2 * v0 * sina * g * t + g * g * t * t);
}
int main()
{
    float vx, vy, v0;

    cin >> vx >> vy;
    v0 = sqrt(vx * vx + vy * vy);
    float alpha;
    alpha = acos(vx / v0);
    float cosa = (vx / v0);
    float sina = (vy / v0);

    float m;
    cin >> m;

    float percentE;
    cin >> percentE;

    float tf;
    cin >> tf;

    float rmax = 2 * v0 * v0 * sina * cosa / g;
    float Ek = (m * v0 * v0 / 2;

    float t = dt;
    tuple <float, float> tupleav;
    list<tuple <float, float>> listav;
    tupleav = make_tuple(v0, 0);
    listav.push_back(tupleav);

    float ht = -1, atf = -1, vtf = -1; //ошибка

    while (xt(t, vx) >= rmax and xt(t, vx) <= rmax) {
        float xt1 = xt(t, vx);
        float yt1 = yt(t, vy);
        float at1 = at(t, vy, vx);
        float vt1 = vt(t, v0, sina);
        tupleav = make_tuple(vt1, at1);
        listav.push_back(tupleav);
        if (t == tf or (t >= tf and t <= tf)) { ht = yt1; atf = at1; vtf = vt1; }
        cout << "t= " << t << " xt= " << xt1 << " yt1= " << yt1 << " at1= " << at1 << " vt1= " << vt1 << endl;
        t += dt;
    }


    float newEk = (percentE / 100) * Ek;
    while (newEk <= 0) {
        float v0new = sqrt(2 * newEk / m);
        float vynew = v0new * cosa;
        float vxnew = v0new * sina;
        rmax = 2 * v0new * v0new * sina * cosa / g;
        while (xt(t, vxnew) >= rmax and xt(t, vxnew) <= rmax) {
            float xt1 = xt(t, vxnew);
            float yt1 = yt(t, vynew);
            float at1 = at(t, vynew, vxnew);
            float vt1 = vt(t, v0, sina);
            tupleav = make_tuple(vt1, at1);
            listav.push_back(tupleav);
            if (t == tf or (t >= tf and t <= tf)) { ht = yt1; atf = at1; vtf = vt1; }
            cout << "t= " << t << " xt= " << xt1 << " yt1= " << yt1 << " at1= " << at1 << " vt1= " << vt1 << endl;
            t += dt;
        }
    }

    return 0;
}