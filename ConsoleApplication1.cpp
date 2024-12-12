#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

void printMenu()
{
    cout << "Что сделать?" << endl
        << "1.Заполнить матрицу порядка N" << endl
        << "2.Переставить блоки матрицы" << endl
        << "3.Отсортировать матрицу" << endl
        << "4.Изменить элементы матрицы" << endl
        << "5.Вывести матрицу" << endl
        << "0.Выйти из программы" << endl;
    cout << ">";
}
void writeMatrix(int* Matrix, int N)
{
    system("cls");
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD destCoord;
    for (int* i = Matrix; i < Matrix + N * N; i++) {
        destCoord.X = ((i - Matrix) % N) * 4;
        destCoord.Y = ((i - Matrix) / N) * 2;
        SetConsoleCursorPosition(hStdout, destCoord);
        cout << *i << " ";
        Sleep(100);
    }
    Sleep(2000);
}

void fillSnake(int* Matrix, int N)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD destCoord;
    for (int col = 0, value = 0; col < N; ++col) {
        if (col % 2 == 0) {
            for (int row = 0; row < N; ++row) {
                *(Matrix + row * N + col) = rand() % (N * N) + 1;
                destCoord.X = col * 4;
                destCoord.Y = row * 2;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << *(Matrix + row * N + col);
                Sleep(100);
            }
        }
        else {
            for (int row = N - 1; row >= 0; --row) {
                *(Matrix + row * N + col) = rand() % (N * N) + 1;
                destCoord.X = col * 4;
                destCoord.Y = row * 2;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << *(Matrix + row * N + col);
                Sleep(100);
            }
        }
    }
}
void fillSpiral(int* Matrix, int N)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD destCoord;
    int top = 0, left = 0, bottom = N - 1, right = N - 1;
    int value = 0;
    while (value < N * N) {
        for (int i = left; i <= right; ++i) {
            *(Matrix + top * N + i) = rand() % (N * N) + 1;
            destCoord.X = i * 4;
            destCoord.Y = top * 2;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << *(Matrix + top * N + i);
            Sleep(100);
            value++;
        }
        top++;

        for (int i = top; i <= bottom; ++i) {
            *(Matrix + i * N + right) = rand() % (N * N) + 1;
            destCoord.X = right * 4;
            destCoord.Y = i * 2;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << *(Matrix + i * N + right);
            Sleep(100);
            value++;
        }
        right--;

        for (int i = right; i >= left; --i) {
            *(Matrix + bottom * N + i) = rand() % (N * N) + 1;
            destCoord.X = i * 4;
            destCoord.Y = bottom * 2;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << *(Matrix + bottom * N + i);
            Sleep(100);
            value++;
        }
        bottom--;

        for (int i = bottom; i >= top; --i) {
            *(Matrix + i * N + left) = rand() % (N * N) + 1;
            destCoord.X = left * 4;
            destCoord.Y = i * 2;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << *(Matrix + i * N + left);
            Sleep(100);
            value++;
        }
        left++;
    }
}

void shakerSort(int* Arr, int N)
{

    bool swapped = 1;
    int* start = Arr;
    int* end = Arr + N * N;

    while (swapped) {
        swapped = 0;

        for (int* i = start; i < end; i++)
        {
            if (*i > *(i + 1)) {
                swap(*i, *(i + 1));
                swapped = 1;
            }
        }

        if (!swapped)
            break;

        for (int* i = end - 1; i >= start; i--)
        {
            if (*i > *(i + 1)) {
                swap(*i, *(i + 1));
                swapped = 1;
            }
        }

        start++;
    }


}
void combSort(int* Arr, int N)
{

    float k = 1.247;
    int s = N * N;
    int* end = Arr + N * N;
    bool swapped = true;

    while (s >= 1) {
        for (int* i = Arr; i + s < end; i++)
        {
            if (*i > *(i + 1))
                swap(*i, *(i + 1));
        }

        s /= k;
    }

    while (swapped)
    {
        swapped = false;
        for (int* j = Arr; j < end; j++)
        {
            if (*j > *(j + 1))
            {
                swap(*j, *(j + 1));
                swapped = true;
            }
        }
    }
}
void insertSort(int* Arr, int N)
{

    int j, key;

    for (int* i = Arr + 1; i < Arr + N * N; i++) {
        key = *i;
        int* j = i - 1;

        while (j >= Arr && *j > key) {
            *(j + 1) = *j;
            --j;
        }
        *(j + 1) = key;
    }
}
void quickSort(int* Arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int* i = (Arr + left), * j = (Arr + right);
    int pivot = *(i + (j - i) / 2);

    while (i <= j) {
        while (*i < pivot) i++;
        while (*j > pivot) j--;

        if (i <= j) {
            swap(*i, *j);
            i++;
            j--;
        }
    }
    quickSort(Arr, left, j - Arr);
    quickSort(Arr, i - Arr, right);
}

void task1(int* M, int N)
{
    srand(time(NULL));
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "Выберите схему заполнения матрицы:" << endl
        << "1. Змейкой" << endl
        << "2. Спиралью" << endl
        << ">";
    int ans;
    cin >> ans;

    system("cls");

    switch (ans) {
    case 1:
        fillSnake(M, N);
        break;
    case 2:
        fillSpiral(M, N);
        break;
    default:
        cout << "Неверный выбор." << endl;
        return;
    }

    Sleep(2000);
}
void task2(int* M, int N)
{
    int answer;
    cout << endl << "Как переставить блоки матрицы?" << endl <<
        "1.По часовой стрелке" << endl <<
        "2.По диагонали" << endl <<
        "3.По вертикали" << endl <<
        "4.По горизонтали" << endl <<
        ">";
    cin >> answer;

    system("cls");
    cout << "Матрица перед перестановками" << endl;
    Sleep(2000);
    writeMatrix(M, N);

    switch (answer) {
    case 1://по часовой стрелке
    {
        for (int x = 0; x < N / 2; x++)
        {
            for (int y = 0; y < N / 2; y++)
            {
                swap(*(M + x + y * N), *(M + x + y * N + N * (N / 2)));//1 блок на место 4
                swap(*(M + x + y * N + N * (N / 2)), *(M + x + y * N + N * (N / 2) + (N / 2)));//4 блок на место 3
                swap(*(M + x + y * N + N * (N / 2) + (N / 2)), *(M + x + y * N + (N / 2)));//3 блок на место 2
            }
        }
        break;

    }
    case 2://по диагонали
    {
        for (int x = 0; x < N / 2; x++)
        {
            for (int y = 0; y < N / 2; y++)
            {
                swap(*(M + x + y * N), *(M + x + y * N + N * (N / 2) + (N / 2)));
                swap(*(M + x + y * N + (N / 2)), *(M + x + y * N + N * (N / 2)));
            }
        }
        break;
    }
    case 3://по вертикали
    {
        for (int x = 0; x < N / 2; x++)
        {
            for (int y = 0; y < N / 2; y++)
            {
                swap(*(M + x + y * N), *(M + x + y * N + N * (N / 2)));
                swap(*(M + x + y * N + (N / 2)), *(M + x + y * N + N * (N / 2) + (N / 2)));
            }
        }
        break;
    }
    case 4://по горизонтали
    {
        for (int x = 0; x < N / 2; x++)
        {
            for (int y = 0; y < N / 2; y++)
            {
                swap(*(M + x + y * N), *(M + x + y * N + (N / 2)));
                swap(*(M + x + y * N + N * (N / 2)), *(M + x + y * N + N * (N / 2)));
            }
        }
        break;
    }

    }

    system("cls");
    cout << "Матрица после перестановок" << endl;
    Sleep(2000);
    writeMatrix(M, N);
}
void task3(int* M, int N)
{
    int answer;
    cout << endl << "Задание 2. Выберете сортировку: " << endl;
    cout << "1. Shaker Sort" << endl;
    cout << "2. Comb Sort" << endl;
    cout << "3. Insert Sort" << endl;
    cout << "4. Quick Sort" << endl;
    cout << ">";
    cin >> answer;

    switch (answer) {
    case 1:
        shakerSort(M, N);
        break;
    case 2:
        combSort(M, N);
        break;
    case 3:
        insertSort(M, N);
        break;
    case 4:
        quickSort(M, 0, N * N - 1);
        break;
    default:
        cout << "Неверный выбор сортировки." << endl;
        Sleep(1500);
        return;
    }
    system("cls");
    cout << "Матрица после сортировки" << endl;
    Sleep(2000);
    writeMatrix(M, N);
}
void task4(int* M, int N)
{
    int answer, number;

    cout << "Какое действие выполнить?" << endl
        << "1.Умножение" << endl
        << "2.Деление" << endl
        << "3.Сложение" << endl
        << "4.Вычитание" << endl
        << ">";
    cin >> answer;

    cout << endl << "На какое число выполнить действие?" << endl << ">";
    cin >> number;

    system("cls");
    cout << "Матрица перед изменениями" << endl;
    Sleep(2000);
    writeMatrix(M, N);

    for (int* i = M; i < M + N * N; i++)
    {
        switch (answer)
        {
        case 1:
            *i *= number;
            break;
        case 2:
            if (number == 0)
            {
                cout << endl << "Ошибка: деление на ноль!" << endl;
                Sleep(2000);
                return;
            }
            else
            {
                *i /= number;
            }
            break;
        case 3:
            *i += number;
            break;
        case 4:
            *i -= number;
            break;
        }
    }
    system("cls");
    cout << "Матрица после изменений" << endl;
    Sleep(2000);
    writeMatrix(M, N);
}

int main()
{
    setlocale(LC_ALL, "");
    int menuAnswer, nAnswer, n;
    int matrix[10][10] = { 0 };

    cout << "Выберите порядок матрицы:" << endl
        << "1.6" << endl
        << "2.8" << endl
        << "3.10" << endl;
    cout << ">";
    cin >> nAnswer;

    switch (nAnswer)
    {
    case 1:
    {
        n = 6;
        break;
    }
    case 2:
    {
        n = 8;
        break;
    }
    case 3:
    {
        n = 10;
        break;
    }
    default:
    {
        n = 6;
        break;
    }
    }

    do {
        system("cls");
        printMenu();
        cin >> menuAnswer;

        switch (menuAnswer) {
        case 1:
            task1(&matrix[0][0], n);
            break;
        case 2:
            task2(&matrix[0][0], n);
            break;
        case 3:
            task3(&matrix[0][0], n);
            break;
        case 4:
            task4(&matrix[0][0], n);
            break;
        case 5:
            writeMatrix(&matrix[0][0], n);
            break;
        case 0:
            break;
        default:
            cout << "Некорректный ввод, попробуйте снова..." << endl;
            Sleep(1500);
        }
    } while (menuAnswer != 0);

    return 0;
}