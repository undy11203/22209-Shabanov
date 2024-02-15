package com.shabanov;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        CsvParser parser = new CsvParser(args[0]);
        parser.writeWordStatistic();
    }
}