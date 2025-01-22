# Морской Бой

## Задачи

Реализовать программу на с++, которая бы:
1. **Загружала данные из файла**
2. **Проверяла, что корабли расставлены в соответствии с правилами игры Морской бой:**
   *  есть 1 четырехпалубный корабль, 2 трехпалубных, 3 двухпалубных. 4 однопалубных
   *  корабли не изгибаются, не соприкасаются друг с другом
3. **Выводила на экран результат анализа: поле заполнено корректно/некорректно**
  
## Выполненые требования

Программа выполняет следующие действия:

1.  **Загрузка данных:** Считывает игровое поле из текстового файла `field.txt`. Поле представляется в виде сетки 10x10, где символ `0` обозначает пустое поле, а символ `*` - часть корабля.
2.  **Проверка корректности:** Проверяет, что корабли на поле расставлены в соответствии с правилами игры "Морской бой":
    *   Присутствует 1 четырехпалубный корабль, 2 трехпалубных, 3 двухпалубных и 4 однопалубных.
    *   Корабли не изгибаются (расположены только по горизонтали или вертикали).
    *   Корабли не касаются друг друга, даже по диагонали.
3.  **Вывод результата:** Выводит на экран сообщение о том, является ли поле заполненным корректно или нет.


## Структура кода

*   **`sea_battle.cpp`:** Основной файл программы.
*   **`loadField(const string& filename)`:** Функция, загружающая игровое поле из файла.
   ```cpp
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
```
*   **`checkShips(const vector<string>& field)`:** Функция, проверяющая, что корабли не касаются друг друга согласно правилам морского боя, а также длину строк и столбцов поля и наличия в них посторонних символов.
  ```cpp
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
```
*   **`isValidBattlefield(vector<string>& field)`:** Функция, проверяющая количество кораблей каждого размера и размерность не привышающую 4.
```cpp
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
```
*   **`main()`:** Главная функция, выполняющая загрузку, проверку и вывод результата.
```cpp
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
```
## Примеры результатов работы
**Корректное заполнение**

![Корректное поле](https://github.com/ne1zvest3n/sea_battle/blob/main/correct.PNG)

**Некорректное заполнение - недостаточное количество кораблей**

![Недостаточное количество кораблей](https://github.com/ne1zvest3n/sea_battle/blob/main/noncorrect2.PNG)

**Некорректное заполнение - неверное расположение кораблей**

![Неверное расположение кораблей](https://github.com/ne1zvest3n/sea_battle/blob/main/noncorrect1.PNG).

**Некорректное заполнение - неверное создание поля**

![Неверная размерность](https://github.com/ne1zvest3n/sea_battle/blob/main/noncorrect3.PNG).

**Некорректное заполнение - неизвестный символ в поле**

![Неизвестный символ](https://github.com/ne1zvest3n/sea_battle/blob/main/noncorrect4.PNG).
