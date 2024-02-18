package com.shabanov;

import com.shabanov.commands.Command;
import com.shabanov.commands.CommandFactory;
import com.shabanov.commands.Context;

import java.io.BufferedReader;
import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.stream.Stream;

public class Interpritator {
    private BufferedReader reader;
    private Logger logger = Logger.getLogger(getClass().getName());

    public Interpritator(BufferedReader reader){
        this.reader = reader;
    }
    public void start(){
        Context ctx = new Context();
        logger.log(Level.INFO, "Created context");
        CommandFactory commandFactory = new CommandFactory();
        logger.log(Level.INFO, "Created command factory");

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
