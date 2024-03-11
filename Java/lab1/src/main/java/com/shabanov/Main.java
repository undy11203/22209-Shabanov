package com.shabanov;

import java.io.*;
import java.util.logging.*;

public class Main {
    private static Logger logger = Logger.getLogger(Main.class.getName());

    public static void main(String[] args) {
        InputStream inputStream = Main.class.getClassLoader().getResourceAsStream("commands.properties");
        if(args.length == 1){
            logger.log(Level.INFO, "Select file input");
            try(InputStream input = new FileInputStream(args[0]);
                BufferedReader reader = new BufferedReader(new InputStreamReader(input))){
                new Interpritator(reader).start(inputStream);
            }catch(IOException e){
                e.printStackTrace();
            }
        }else{
            InputStream input = System.in;
            logger.log(Level.INFO, "Select console input");
            try(BufferedReader reader = new BufferedReader(new InputStreamReader(input))){
                new Interpritator(reader).start(inputStream);
            }catch(IOException e){
                e.printStackTrace();
            }
        }
    }
}