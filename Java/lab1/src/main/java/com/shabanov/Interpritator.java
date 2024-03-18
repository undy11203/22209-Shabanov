package com.shabanov;

import com.shabanov.commands.Command;
import com.shabanov.commands.CommandFactory;
import com.shabanov.commands.Context;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.stream.Stream;

public class Interpritator {
    private BufferedReader reader;
    private Logger logger = Logger.getLogger(getClass().getName());
    private String[] CommandWithParams = null;

    private String getNextCommand() throws IOException {
        try{
            String line = reader.readLine();
            while(line.contains("#")){
                line = reader.readLine();
            }
            CommandWithParams = line.split(" ");
        }catch (NullPointerException e){
            return null;
        }

        return  CommandWithParams[0];
    }

    private String[] getCommandParams(){
        Stream<String> parametrsStream = Arrays.stream(CommandWithParams).skip(1);
        String[] parametrsArray = parametrsStream.toArray(String[]::new);
        return parametrsArray;
    }

    public Interpritator(BufferedReader reader){
        this.reader = reader;
    }
    public void start(InputStream commands){
        Context ctx = new Context();
        logger.log(Level.INFO, "Created context");
        CommandFactory commandFactory = null;
        try{
            commandFactory = new CommandFactory(commands);
        }catch (NullPointerException | IOException e){
            e.printStackTrace();
            return;
        }
        logger.log(Level.INFO, "Created command factory");

        while (true) {
            try {
                String commandName = getNextCommand();
                if(commandName == null){
                    break;
                }
                logger.log(Level.INFO, "Read line");

                Command command = commandFactory.createCommand(commandName);
                logger.log(Level.INFO, "Create current command");
               command.execute(getCommandParams(), ctx);
                logger.log(Level.INFO, "Current command is executed");
            } catch (Exception e){
                e.printStackTrace();
            }
        }
    }
}
