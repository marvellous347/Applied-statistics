#include <iostream>
#include <time.h>


using namespace std;

double frequency(int* mass, int k, int size) // Обрахунок частоти входження елементів в масив
{
    int count_of_k = 0;
	
    for (int i = 0; i < size; i++)
    {
        if (mass[i] == k) { count_of_k++; }
    }
    return double(count_of_k) / double(size);
}
double vib_ser(int* mass, int size) // Математичне вибіркове середнє
{
    double result = 0;
	
    for (int i = 1; i <= 6; i++)
    {
        result += i * (frequency(mass, i, size) * size);
    }
    return result / size;
}
double variacy(int* mass, int size) //Вибіркова дисперсія елементів масиву
{
    double temp = 0;
    double result = 0;
    double total = 0;
	
    for (int i = 1; i <= 6; i++)
    {
        result += pow(i, 2) * (frequency(mass, i, size) * size);
    }
    result = result / size;
    total = result - pow(vib_ser(mass, size), 2);
    return total;
}
int main()
{
    const int size = 10000;
    int mass[size];
    int k = 0;
    double freq = 0;
    int count_of_k = 0;
	
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        mass[i] = 1 + rand() % 6;
    }

    for (int i = 0; i < size; i++) {

        cout << mass[i] << " ";
    }
	
    cout << "\n\n" << endl;
    cout << "Enter k: ";
    cin >> k;
    
    for (int i = 0; i < size; i++) // Обрахунок частоти входження елемента k в масив
    {
        if (mass[i] == k) { count_of_k++; }
    }
    freq = (double)count_of_k / (double)size;
	
    cout << "Frequency of k = " << freq << "|" << 1.0 / 6.0 << endl;
    cout << endl;
    
    double expectation = 0; //Математичне сподівання
    for (int i = 1; i <= 6; i++)
    {
        expectation += frequency(mass, i, size) * i;
    }

	
	
    cout << "Mathematical expactation = " << expectation << " | " << "3.5" << endl; //Математичне сподівання
    cout << "Sampling Variacy = " << variacy(mass, size) << " | " << "2.91" << endl; //Вибіркова дисперсія
    cout << "Standard deviation = " << sqrt(variacy(mass, size)) << " | " << "1.7" << endl; //Середньоквадратичне відхилення
}
