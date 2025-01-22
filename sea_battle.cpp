#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> loadField(const string& filename)
{
    vector<string> field;

    ifstream file(filename);

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            field.push_back(line);
        }
        for (int i = 0; i < field.size(); i++)
        {
            cout << field[i] << endl;
        }
        file.close();
    }
    else
    {
        cout << "Не удалось открыть файл: " << filename << endl;
    }
    return field;
}

bool checkShips(const vector<string>& field)
{
    if (field.size() != 10)
    {
        cout << "Поля не соответствуют требованиям: неверное количество строк" << endl;
        return false;
    }

    for (int i = 0; i < field.size(); ++i)
    {
        if (field[i].size() != 10)
        {
            cout << "Поля не соответствуют требованиям: пустой или лишний символ в строке " << i + 1 << endl;
            return false;
        }
        for (int j = 0; j < field[i].size(); ++j)
        {
            if (field[i][j] != '0' && field[i][j] != '*')
            {
                cout << "Поля не соответствуют требованиям: недопустимый символ '" << field[i][j] << "' в строке " << i + 1 << ", позиции " << j + 1 << endl;
                return false;
            }
        }
    }

    for (int row = 0; row < 10; ++row)
    {
        for (int col = 0; col < 10; ++col)
        {
            if (field[row][col] == '*')
            {
                if ((row > 0 && col > 0 && field[row - 1][col - 1] == '*') ||
                    (row > 0 && col < 9 && field[row - 1][col + 1] == '*') ||
                    (row < 9 && col > 0 && field[row + 1][col - 1] == '*') ||
                    (row < 9 && col < 9 && field[row + 1][col + 1] == '*'))
                {
                    cout << "Ошибка: Обнаружено диагональное касание кораблей в координатах (" << row + 1 << ", " << col + 1 << ")." << endl;
                    return false;
                }
            }
        }
    }
    return true;
}
bool isValidBattlefield(vector<string>& field)
{
    vector<int> shipCounts(5, 0);

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (field[i][j] == '*')
            {
                int length = 0;
                if (j + 1 < 10 && field[i][j + 1] == '*')
                {
                    while (j + length < 10 && field[i][j + length] == '*')
                    {
                        field[i][j + length] = '.';
                        length++;
                    }
                }
                else
                {
                    while (i + length < 10 && field[i + length][j] == '*')
                    {
                        field[i + length][j] = '.';
                        length++;
                    }
                }

                if (length > 4)
                {
                    cout << "Ошибка: Корабль слишком длинный." << endl;
                    return false;
                }
                shipCounts[length]++;
            }
        }
    }
    cout << "Четырехпалубных кораблей - " << shipCounts[4] << endl << "Трёхпалубных кораблей - " << shipCounts[3] << endl << "Двухпалубных кораблей - " << shipCounts[2] << endl << "Однопалубных кораблей - " << shipCounts[1] << endl;
    return (shipCounts[4] == 1 && shipCounts[3] == 2 && shipCounts[2] == 3 && shipCounts[1] == 4);
}

int main()
{
    setlocale(LC_ALL, "rus");
    string filename = "field.txt";
    vector<string> field = loadField(filename);


    if (checkShips(field) && isValidBattlefield(field))
    {
        cout << "Заполнено корректно" << endl;
    }
    else
    {
        cout << "Заполнено некорректно" << endl;
    }
    return 0;
}
