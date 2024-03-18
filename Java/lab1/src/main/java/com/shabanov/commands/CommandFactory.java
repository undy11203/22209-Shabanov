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
    private Properties commandsProp = new Properties();

    public CommandFactory(InputStream inputStream) throws IOException {
        commandsProp.load(inputStream);
        logger.log(Level.INFO, "Connect with commands.properties file");
    }

    public Command createCommand(String commandName) {
        try {
            String className = commandsProp.getProperty(commandName);
            logger.log(Level.INFO, "Get className command " + className);
            Class classCommand = Class.forName(className);
            logger.log(Level.INFO, "Get class by its className");
            return (Command) classCommand.newInstance();
        }catch (ClassNotFoundException | InstantiationException | IllegalAccessException | NullPointerException e){
            e.printStackTrace();
        }
        return null;
    }
}
