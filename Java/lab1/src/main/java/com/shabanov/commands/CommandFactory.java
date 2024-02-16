package com.shabanov.commands;

import com.shabanov.Main;

import java.io.IOException;
import java.io.InputStream;
import java.util.Map;
import java.util.HashMap;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

public class CommandFactory {
    private Logger logger = Logger.getLogger(getClass().getName());
    private Map<String, String> commandMap = new HashMap<String, String>();

    public CommandFactory() {
        try {
            InputStream inputStream = getClass().getClassLoader().getResourceAsStream("commands.properties");
            Properties prop = new Properties();
            prop.load(inputStream);
            logger.log(Level.INFO, "Connect with commands.properties file");
            for (String commandName: prop.stringPropertyNames()){
                String className = prop.getProperty(commandName);
                commandMap.put(commandName, className);
                logger.log(Level.INFO, "Read command " + commandName);
            }
        }catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Command createCommand(String commandName) {
        try {
            String className = commandMap.get(commandName);
            logger.log(Level.INFO, "Get className command " + className);
            Class classCommand = Class.forName(className);
            logger.log(Level.INFO, "Get class by its className");
            return (Command) classCommand.newInstance();
        }catch (ClassNotFoundException | InstantiationException | IllegalAccessException e){
            e.printStackTrace();
        }
        return null;
    }
}
