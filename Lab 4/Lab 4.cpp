#include <iostream>
#include <cmath>
#include <time.h>
#include <random>
#include <math.h>

using namespace std;

double func(double x)
{
    double y = 0;
    if (x >= 0 && x <= 2)    // [0;2]
        return y = 0.25 * x;
    else if (x > 2 && x <= 4)  // (2;4]
        return y = 0.25;
    else
        return 0;
}

double expectation(double* mass, int size)  // Математичне сподівання
{
    double probality = 1.0 / (double)size;
    double res = 0;
    for (int i = 0; i < size; i++)
        res += mass[i] * probality;
    return res;
}

double vib_ser(double* mass, int size)  // Математичне вибіркове середнє
{
    double result = 0;
    double probality = 1.0 / (double)size;
    for (int i = 0; i < size; i++)
        result += pow(mass[i], 2) * probality;
    return result;
}

double variacy(double* mass, int size)  // Математична дисперсія
{
    double result;
    double probality = 1.0 / (double)size;
    result = (vib_ser(mass, size) - pow(expectation(mass, size), 2));
    return result;
}

int main()
{
    srand(time(NULL));
    const int size = 100000;
    double arr[size] = {};
    double r1, r2;
    double X0 = 0;
    double n = 0;
    int idx = 0;
    double M = 0.5; // y - Максимум
    double a = 0; // x Є [0;4]
    double b = 4; // x Є [0;4]

    //Інтервали
    int count_of_intervals = ceil((1.0 + 3.332 * log10(size)));
    double distance = (b - a) / count_of_intervals; // розмір кожного інтервала
    double* interval = new double[count_of_intervals];
    for (int i = 0; i < count_of_intervals; i++) // заповнюємо масив значеннями інтервалів
        interval[i] = 0;

	//Заповнення масиву
    for (int i = 0; i < size; i++)
    {
        r1 = (double)rand() / RAND_MAX;
        r2 = (double)rand() / RAND_MAX;  
        X0 = a + r1 * (b - a);
        n = r2 * M;
        if (n <= func(X0))  // Якщо випадкове число менше за значення функції в даному інтервалі
        {
            arr[i] = X0;
            idx = floor((X0 - a) / distance); // позиція в масиві
            interval[idx]++;
        }
        else // Якщо випадкове число більше за значення функції в даному інтервалі
            i--;
    }

    // Виведення масиву
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }

    // Виведення результатів
    cout << "\n\n\n";
    cout << "Expecation = " << expectation(arr, size) << "\t-\tTheoretical expecation = 2.16" << endl;
    cout << "Viborochne serednye = " << vib_ser(arr, size) << "\t-\tTheoretical viborochne serednye = 5.7" << endl;
    cout << "Variacy = " << variacy(arr, size) << "\t-\tTheoretical Variacy = 1"<<endl;

    cout << endl << "[Interval]     [Frequency]      [Relative frequency]" << endl;
    for (int i = 0; i < count_of_intervals; i++)
    {
        cout << i << "\t\t  " << interval[i] << "\t\t  " << (double)interval[i] / (double)count_of_intervals << endl;
    }



}
