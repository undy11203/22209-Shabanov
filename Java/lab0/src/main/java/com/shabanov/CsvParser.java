package com.shabanov;

import javax.xml.crypto.Data;
import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

class DataWord implements Comparable<DataWord> {
    private String word;
    private Integer count;

    public DataWord(String w, Integer c){
        word = w;
        count = c;
    }

    @Override
    public int compareTo(DataWord o) {
        return getCount() - o.getCount();
    }

    public Integer getCount() {
        return count;
    }

    public String getWord() {
        return word;
    }
}

public class CsvParser {
    private String path;
    private Integer allWords;
    private ArrayList<DataWord> words;

    public CsvParser(String path) {
        this.path = path;
        this.allWords = 0;
        this.words = new ArrayList<DataWord>();
    }

    public void writeWordStatistic() {
        try (InputStreamReader reader = new InputStreamReader(new FileInputStream(path))){
            collectingStatistic(reader);
            writeInFile();
        } catch(IOException e){
            System.out.println("\u001B[31mError while reading: " + e.getMessage() + "\u001B[31m");
        }
    }

    private void writeInFile() throws IOException {
        String outputPath = path.substring(0, path.lastIndexOf('/') > 0
                                                ? path.lastIndexOf('/') + '/'
                                                : 0
                                            ) + "output.csv";
        try(OutputStreamWriter writer = new OutputStreamWriter(new FileOutputStream(outputPath))){
            for (DataWord word : words) {
                String entry = word.getWord() + ',' +
                        word.getCount() + ',' +
                        (double)word.getCount()/allWords*100 + '%' + '\n';
                writer.write(entry);
            }
        }catch (IOException e){
            System.out.println("\u001B[31mError while writing: " + e.getMessage() + "\u001B[31m");
        }
    }

    private void collectingStatistic(InputStreamReader reader) throws IOException {
        StringBuilder word = new StringBuilder();
        Character c;
        Map<String, Integer> statistic = new HashMap<>();
        while(reader.ready()){
            c = (char)reader.read();
            if (!(Character.isDigit(c) || Character.isLetter(c) || Character.isWhitespace(c))) {
                continue;
            }
            if(Character.isWhitespace(c)) {
                if(word.length()>0) {
                    allWords++;
                    int value = statistic.get(word.toString()) != null ? statistic.get(word.toString()) + 1 : 1;
                    statistic.put(word.toString(), value);
                    word.delete(0, word.length());
                }
            }else{
                word.append(c);
            }
        }

        if (word.length() > 0) {
            allWords++;
            int value = statistic.containsKey(word.toString()) ? statistic.get(word.toString()) + 1 : 1;
            statistic.put(word.toString(), value);
        }

        sortAndGetStatisticValue(statistic);
    }

    private void sortAndGetStatisticValue(Map<String, Integer> statistic) {
        for (Map.Entry<String, Integer> entry : statistic.entrySet()) {
            words.add(new DataWord(entry.getKey(), entry.getValue()));
        }
        Collections.sort(words);
        Collections.reverse(words);
    }
}
