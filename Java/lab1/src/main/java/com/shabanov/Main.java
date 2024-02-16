package com.shabanov;

import com.shabanov.commands.Command;
import com.shabanov.commands.CommandFactory;
import com.shabanov.commands.Context;

import java.io.*;
import java.util.Arrays;
import java.util.stream.Stream;
import java.util.logging.*;

public class Main {
    private static Logger logger = Logger.getLogger(Main.class.getName());

    public static void main(String[] args) {
        Context ctx = new Context();
        logger.log(Level.INFO, "Created context");
        CommandFactory commandFactory = new CommandFactory();
        logger.log(Level.INFO, "Created command factory");
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
        String line;
        while (true) {
            try {
                if((line = reader.readLine()) == null){
                    break;
                }
                logger.log(Level.INFO, "Read line");
                if (line.contains("#")) {
                    continue;
                }
                String[] formulationCommand = line.split(" ");
                Command command = commandFactory.createCommand(formulationCommand[0]);
                logger.log(Level.INFO, "Create current command");
                Stream<String> parametrsStream = Arrays.stream(formulationCommand).skip(1);
                String[] parametrsArray = parametrsStream.toArray(String[]::new);
                command.execute(parametrsArray, ctx);
                logger.log(Level.INFO, "Current command is executed");
            } catch (Exception e){
                e.printStackTrace();
            }
        }
    }
}