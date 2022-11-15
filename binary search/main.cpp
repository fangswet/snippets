#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

int binary_search(double element, double array[], int array_size)
{
    int result = -1;
    int number_of_iterations = 0;
    int i = 0;
    int j = array_size - 1;
    
    while (i <= j)
    {
        number_of_iterations++;
        int m = i + (j - i) / 2;
        
        if (array[m] == element)
        {
            result = m;
            break;
        }
        
        if (array[m] < element)
            i = m + 1;
        else 
            j = m - 1;
    }
    
    cout << number_of_iterations << endl;
    return result;
}

int inter_search(double element, double array[], int array_size)
{
    int result = -1;
    int number_of_iterations = 0;
    int l = 0;
    int h = array_size - 1;
    
    while (l <= h && element >= array[l] && element <= array[h])
    {
        number_of_iterations++;
        
        if (l == h)
        {
            if (array[l] == element) result = l;
            break;
        }
        
        int pos = l + (double)(h - l) / (array[h] - array[l]) * (element - array[l]);
        
        if (array[pos] == element)
        {
            result = pos;
            break;
        }
        
        if (array[pos] < element)
            l = pos + 1;
        else
            h = pos - 1;
    }
    
    cout << number_of_iterations << endl;
    return result;
}

int main()
{
    constexpr int sz = 10000;
    double array[sz];
    uniform_real_distribution<double> unif(0, 1);
    default_random_engine re;
    
    for (int i = 0; i < sz - 1; i++)
        array[i] = unif(re);
        
    sort(array, array + sz);
    
    uniform_real_distribution<double> unif2(0, sz - 1);
    double element = array[(int)unif2(re)];
    cout << element << ": " << endl;
    cout << binary_search(element, array, sz) << endl;
    cout << inter_search(element, array, sz) << endl;
    
    return 0;
}
