#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
using namespace std;

struct WrongIndexDiv {
    string err = "delenie na 0";
};

struct WrongIndexException {
    string err = " wrong index ";
};

struct Ceil {
    int index;
    int number;
};

class Array
{
private:

    Ceil* ceils;
    int capacity;


public:

    Array()
    {
        this->capacity = 1;
        this->ceils = new Ceil[1];
    }

    Array(int n)
    {
        this->capacity = n;
        this->ceils = new Ceil[n];
    }

    Array(int n, Ceil* ceils)
    {
        this->capacity = n;
        this->ceils = ceils;
    }

    Array& InputData(int temp)
    {
        for (int i = 0; i < this->capacity; i++)
        {
            this->ceils[i].index = temp;
            cin >> this->ceils[i].number;
            temp++;
        }

        return *this;
    }

    int GetIndexOfCeil(int index)
    {
        return this->ceils[index].index;
    }

    int GetNumberOfCeil(int index)
    {
        return this->ceils[index].number;
    }

    int GetCapacity()
    {
        return this->capacity;
    }

    Array operator + (Array secondArray) 
    {
        Ceil* newCeils = new Ceil[this->capacity];
        for (int i = 0; i < this->capacity; i++) {
            newCeils[i].index = this->GetIndexOfCeil(i);
            newCeils[i].number = this->GetNumberOfCeil(i) + secondArray.GetNumberOfCeil(i);
        }

        Array newArray = Array(this->capacity, newCeils);
        return newArray;
    }

    Array operator - (Array secondArray)
    {
        Ceil* newCeils = new Ceil[this->capacity];
        for (int i = 0; i < this->capacity; i++) {
            newCeils[i].index = this->GetIndexOfCeil(i);
            newCeils[i].number = this->GetNumberOfCeil(i) - secondArray.GetNumberOfCeil(i);
        }

        Array newArray = Array(this->capacity, newCeils);
        return newArray;
    }

    Array operator * (Array secondArray)
    {
        Ceil* newCeils = new Ceil[this->capacity];
        for (int i = 0; i < this->capacity; i++) {
            newCeils[i].index = this->GetIndexOfCeil(i);
            newCeils[i].number = this->GetNumberOfCeil(i) * secondArray.GetNumberOfCeil(i);
        }

        Array newArray = Array(this->capacity, newCeils);
        return newArray;
    }

    Array operator / (Array secondArray)
    {
        Ceil* newCeils = new Ceil[this->capacity];
        for (int i = 0; i < this->capacity; i++) {

            if (secondArray.GetNumberOfCeil(i) == 0)
                throw WrongIndexDiv();

            newCeils[i].index = this->GetIndexOfCeil(i);
            newCeils[i].number = this->GetNumberOfCeil(i) / secondArray.GetNumberOfCeil(i);
        }

        Array newArray = Array(this->capacity, newCeils);
        return newArray;
    }

    Array operator = (Array secondArray)
    {
        this->capacity = secondArray.capacity;
        this->ceils = secondArray.ceils;
        return *this;
    }

    Array PlusConst (int constanta)
    {
        Ceil* newCeils = new Ceil[this->capacity];
        for (int i = 0; i < this->capacity; i++)
        {
            newCeils[i].index = this->GetIndexOfCeil(i);
            newCeils[i].number = this->GetNumberOfCeil(i) + constanta;
        }

        Array newArray = Array(this->capacity, newCeils);
        return newArray;
    }

    Array MultConst(int constanta)
    {
        Ceil* newCeils = new Ceil[this->capacity];
        for (int i = 0; i < this->capacity; i++)
        {
            newCeils[i].index = this->GetIndexOfCeil(i);
            newCeils[i].number = this->GetNumberOfCeil(i) * constanta;
        }

        Array newArray = Array(this->capacity, newCeils);
        return newArray;
    }

    int SearchIndex(int searchIndex) 
    {
        for (int i = 0; i < this->capacity; i++)
        {
            if (this->GetIndexOfCeil(i) == searchIndex)
                return this->GetNumberOfCeil(i);
        }

        throw WrongIndexException();
    }

    void Print()
    {
        for (int i = 0; i < this->capacity; i++)
            cout << this->GetNumberOfCeil(i) << " ";

        cout << endl;
    }

};

int main()
{
    const int n = 2;
    int first = 0, last = 0;
    cin >> first >> last;
    int k = abs(last - first) + 1;

    Array arr1 = Array(k);
    Array arr2 = Array(k);

    int temp = first;
    arr1.InputData(temp);

    temp = first;
    arr2.InputData(temp);

    int constanta = 0;
    cin >> constanta;

    cout << "Array1= ";
    arr1.Print();
    cout << "Array1+const= ";
    arr1.PlusConst(constanta).Print();
    cout << "Array1*const= ";
    arr1.MultConst(constanta).Print();

    cout << "Array2= ";
    arr2.Print();
    cout << "Array2+const= ";
    arr2.PlusConst(constanta).Print();
    cout << "Array2*const= ";
    arr2.MultConst(constanta).Print();

    cout << "summa= ";
    Array sumArr = arr1 + arr2;
    sumArr.Print();
    cout << "raznost= ";
    Array diffArr = arr1 - arr2;
    diffArr.Print();
    cout << "proizv = ";
    Array multArr = arr1 * arr2;
    multArr.Print();

    try
    {
        Array divArray = arr1 / arr2;
        cout << "delenie= ";
        divArray.Print();
    }
    catch (const WrongIndexDiv& ex) {
        cout << ex.err << endl;
    }

    int m, searchIndex;
    cin >> m;
    while (m != 0)
    {
        cin >> searchIndex;

        try
        {
            int result = 0;

            if (m == 1)
            {
                result = arr1.SearchIndex(searchIndex);
            }
            else
            {
                result = arr2.SearchIndex(searchIndex);
            }

            cout << "Array" << m << "[" << searchIndex << "] = " << result << endl;
        }
        catch(const WrongIndexException& ex)
        {
            cout << "Array" << m << ex.err << searchIndex << endl;
        }

        cin >> m;  
    }
}
