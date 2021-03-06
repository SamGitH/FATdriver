Целью лабораторной работы является изучение классической архитектуры
файловой системы FAT.

# Теоретические сведения

FAT (англ. File Allocation Table — «таблица размещения файлов») — классическая
архитектура файловой системы, которая из-за своей простоты всё ещё широко
используется для флеш-накопителей.
Задачей файловой системы является хранение файлов на диске и доступ к ним по
требованию пользователя. При форматировании диск разбивается на блоки
определенного пользователем размера. Размер блока представляет собой минимальный
объем дискового пространства, который может использоваться для хранения файла. Если
размер файла не кратен кратен размеру блока, необходимо использовать дополнительное
пространство для хранения файла (кратное размеру блока).
Отслеживание соответствия файлов блокам на диске файловая система ведет с
помощью таблицы, хранящей указатель на следующий блок текущего файла. В таблице 1
показано, как выглядит таблица для двух файлов: файл А использует в указанном
порядке дисковые блоки 4, 7, 2, 10 и 12, а файл В использует в указанном порядке блоки
6, 3, 11 и 14. Используя таблицу 2, можно пройти всю цепочку от начального блока 4 и
до самого конца. То же самое может быть проделано начиная с блока 6. Обе цепочки
заканчиваются специальным маркером (например, -1), который не является допустимым
номером блока. Такая таблица, находящаяся в оперативной памяти, называется FAT (File
Allocation Table — таблица размещения файлов).
При использовании такой организации для данных доступен весь блок. Так же
прост произвольный доступ к файлу. Хотя для поиска заданного смещения в файле
нужно идти по цепочке, эта цепочка целиком находится в памяти, поэтому проход по ней
может осуществляться без обращений к диску. В записи каталога достаточно хранить
одно целое число (номер начального блока) и по-прежнему получать возможность
определения местоположения всех блоков независимо от того, насколько большим будет
размер файла.
В таблице 2 представлено расположение файлов A и B на диске в соответствии с
представленной выше таблице FAT.

```
1 Пустой блок
2 10
3 11
4 7 Файл A начинается здесь
5
6 3 Файл B начинается здесь
7 1
8
9
10 12
11 14
12 -1
13
14 -1
15


Таблица 1. Таблица FAT
```
Файл - A B A - B A - - A B A - B - -

Номер блока 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16
_Таблица 2. Расположение файлов в файловой системе_


# Описание учебной файловой системы

Заданная файловая система НЕ соответствует спецификации файловых систем от
Microsoft FAT12, FAT16, FAT32.

Каждому студенту выдается файл, содержащий образ файловой системы. Задачей
студента является написать программу на языке C, читающую файловую систему из
образа и предоставляющую пользователю интерфейс для выполнения следующих
действий над файловой системой:

1. Вывести информацию о файловой системе из суперблока.
2. Вывести содержимое корневого каталога.
3. По требованию пользователя вывести содержимое таблицы FAT.
4. Реализовать поиск файлов и каталогов по имени или части имени.
5. По требованию пользователя вывести дерево всей файловой системы включая
    атрибуты файлов и каталогов.
6. По требованию пользователя сохранить содержимое выбранного файла из образа
    файловой системы на диск. Путь к файлу задается как абсолютный путь от
    корневой директории.
7. По требованию пользователя вывести содержимое текстовых
    файлов(расширение .txt) из образа файловой системы на экран.

# Файловая система

В учебной файловой системе дисковое пространство раздела делится на две
области – системную и область данных. Системная область создается и
инициализируется при форматировании, а впоследствии обновляется при
манипулировании файловой структурой. Системная область файловой системы состоит
из следующих компонентов:

1. суперблок
2. таблицы размещения файлов (FAT)
3. область корневого каталога

Схема файловой системы:

# Суперблок

Суперблок — это наиболее ответственная область файловой системы, содержащая
информацию, которая необходима для работы с файловой системой в целом. Структура

```
суперблок таблица FAT
```
```
корневой каталог
данные
данные
данные
данные
```

суперблока содержит следующие поля:

1. Размер блока файловой системы. (unsigned, 4 байта)
2. Размер таблицы FAT в байтах. (unsigned, 4 байта)
3. Размер корневого каталога — количество файловых записей в корневом каталоге.
    (unsigned, 4 байта).

# Таблица FAT

Представляет собой двумерный массив четырехбайтных элементов (int) из двух
столбцов, содержащий в первом столбце номер блока, а во втором — одно из следующих
значений:

- блок занят файлом и не является последним блоком файла — значение содержит
    номер следующего блока файла;
- блок свободен — значение обнулено ( **0** );
- блок является последним блоком файла — содержит метку EOC (End Of
    Clusterchain), значение которой равно **0xFF** ;
- блок поврежден — содержит специальную метку, значение которой **0x0FE**.
    Поврежденный блок не может использоваться файловой системой для хранения
    данных;

# Область данных

Область данных логического диска содержит файлы и каталоги, подчиненные
корневому, и разделена на участки одинакового размера – блоки.

# Корневой каталог

Содержит определенное в суперблоке (поле «Размер корневого каталога»)
количество записей о файлах или каталогах. Длину корневого каталога в байтах можно
вычислить, умножив размер корневого каталога на длину файловой записи в байтах.

**_Файл в файловой системе, описывается следующей структурой:_**

1. Имя файла — 12 байт (1 байт на символ).
2. Номер первого блока файла (unsigned, 4 байта).
3. Атрибуты (int, 4 байта). Значение 1 — каталог, 0 — файл.

# Образ файловой системы для тестирования приложения:

# http://13633.mooo.com/files/unix/v12.dat

# Список литературы

1. Таненбаум Э. «Современные операционные системы» ISBN 978-5-496-00301-8,
    978-0136006633; 2013 г.


