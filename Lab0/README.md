## О чём проект
Подсчёт слов из текстового документа и вывод их в csv-фаил

## Инструкция сборки
1). открыть cmd в данной папке
2). Прописать сначала
```
cmake -S . -B build
```
Затем
```
 cmake --build build
```
Создаться папка bin и exe-фаил будет лежать в ней

## Инструкция использование
Lab0.exe [файл1.txt] [файл2.csv] \
файл1.txt - путь до файл1.txt из которого считаем слова \
файл2.csv - путь до файл2.csv куда записываем данные