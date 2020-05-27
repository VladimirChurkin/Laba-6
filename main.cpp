#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int summ = 0;
double x[100000];
double y[100000];
double z[100000];
int arr[10];

void iDP() {
    for (int i = 0; i < 5; i++) {
        cout << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::milliseconds(100));

    }
}

double f(double x, double y) {
    return x * x * y * 100 + y * y / x * y / x / x;
}

void calc(double* x, double* y, double* z, int a, int b) {
    for (int i = a; i < b; i++) {
        for (int j = 0; j < 100; j++) {
            z[i] = f(x[i], y[i]);
        }
    }
}


void arrElements() {
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }
}

mutex mtx;
void arraySum(int a, int b) {

    lock_guard < mutex> guard(mtx);

    for (int i = a; i < b; i++) {
        summ += arr[i];
    }
    this_thread::sleep_for(chrono::milliseconds(100));

}



int main() {
    //-----------------пункт 1--------------------
    //thread th1(iDP);
    //iDP();
    //th1.join();

    //-----------------пункт 2--------------------
    for (int i = 0; i < 100000; i++) {
        x[i] = i;
        y[i] = 100000 - i;
        z[i] = 0;
    }

    unsigned int start = clock();
    thread t1(calc, x, y, z, 0, 25000);

    thread t2(calc, x, y, z, 25000, 50000);
    thread t3(calc, x, y, z, 50000, 75000);
    thread t4(calc, x, y, z, 75000, 100000);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    unsigned int end = clock();
    cout << "threads = " << end - start << std::endl;

    cout << endl << endl << endl;

    unsigned int start1 = clock();
    calc(x, y, z, 0, 100000);
    unsigned int end1 = clock();
    cout << "one thread = " << end1 - start1 << std::endl;
    //--------------------пункт 3---------------
    /*arrElements();

    thread t1(arraySum, 0, 4);
    thread t2(arraySum, 4, 10);
    t1.join();
    t2.join();

    cout << summ << endl;*/

    return 0;
}