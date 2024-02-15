package com.shabanov.commands;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Context {
    private Logger logger = Logger.getLogger(getClass().getName());
    private ArrayList<Double> stack;
    private Map<String, Double> constant;

    public Context(){
        this.stack = new ArrayList<Double>();
        this.constant = new HashMap<String, Double>();
    }

    public Double getElement(){
        Double res = stack.get(stack.size()-1);
        logger.log(Level.INFO, "Get last element " + res);
        return res;
    }

    public void putElement(Double value){
        stack.add(value);
        logger.log(Level.INFO, "put value = " + value);
    }

    public void removeLastElement(){
        stack.remove(stack.size()-1);
        logger.log(Level.INFO, "delete last element");
    }

    public Double getConstant(String name){
        Double res = constant.get(name);
        logger.log(Level.INFO, "get constant = " + res);
        return res;
    }

    public void putConstant(String name, Double value){
        constant.put(name, value);
        logger.log(Level.INFO, "put constant " + name + " with a value of " + value);
    }
}
