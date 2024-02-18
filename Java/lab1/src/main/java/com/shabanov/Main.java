package com.shabanov;

import java.io.*;
import java.util.logging.*;

public class Main {
    private static Logger logger = Logger.getLogger(Main.class.getName());

    public static void main(String[] args) {
        InputStream input = System.in;
        logger.log(Level.INFO, "Select console input");

        try {
            if (args.length == 1) {
                input = new FileInputStream(args[0]);
                logger.log(Level.INFO, "Change on file input");
            }
        }catch(FileNotFoundException e){
            e.printStackTrace();
        }
        BufferedReader reader = new BufferedReader(new InputStreamReader(input));
        new Interpritator(reader).start();
    }
}