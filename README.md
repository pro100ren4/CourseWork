Вариант 18
Дан файл с информацией о сотрудниках НИИ. Структура записи: номер от-
дела; табельный номер; фамилия; номер темы, над которой работает сотрудник;
продолжительность работы над данной темой (*в месяцах*); код должности; размер
заработной платы (*в рублях*). **Определить перечень тем, разрабатываемых в НИИ,
количество сотрудников, занятых в каждой теме, а также фонд заработной платы
по каждой теме.** Результаты напечатать в виде соответствующей таблицы.

## Notes:
- Добавить шутку про сокращение R.I.P.(Research Institute Programm)

## Методы Работника НИИ:
- [x] Геттеры 
- [x] Сеттеры  
- [x] Создание
- [x] Создание из консоли
- [ ] Тесты

## Методы Связанног списка: 
- [x] Создание списка
- [x] Удаление списка
- [ ] Добавление элемента в список
- [ ] Удаление элемента из списка
- [ ] Запись списка в файл
- [ ] Чтение списка из файла
- [x] Вывод списка на дисплей
- [x] Редактирование элемента списка
- [ ] Тесты 

## TODO:
- [ ] main.c:9 Добавить запуск тестов
- [x] utils.h:65 Макросы для тестов
- [x] Тесты для управления терминалом
- [ ] Тест PAUSE на WIN
- [x] utils.h:78 Макросы для тестов

## FIXME:
- [ ] main.c:147 Проверить корректноти использования памяти menu_t 
- [ ] LinkedList.h:12 Исправить прототипы функций
- [x] ReseatchWorker.c:27 Исправить функцию получения фамилии
- [ ] utils.h:31 Исправить не рабочий режим отображения BLINK
- [ ] utils.h:32 Исправить не рабочий режим отображения FAST_BLINK
- [ ] utils.h:17 Исправить ошибку с PAUSE
- [ ] Исправить вывод несуществующих страниц
- [ ] Исправить редактирование несущестующих элементов

## Полезные ссылки
### Консольная графика
1. https://habr.com/ru/articles/325082/
2. https://linuxdoc.ru/console_codes.html
3. https://misc.flogisoft.com/bash/tip_colors_and_formatting
4. https://xakep.ru/2022/02/15/terminal-anatomy/
5. https://www.bdbd.ru/likbez/samostoyatelnoe-prodvizhenie/tablitsa_simvolov_yunikoda_dlya_saytov/
