package com.shabanov.commands;

import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Context {
    private Logger logger = Logger.getLogger(getClass().getName());
    private ArrayDeque<Double> stack = new ArrayDeque<Double>();
    private Map<String, Double> constant = new HashMap<String, Double>();

    public Double getElement(){
        try {
            Double res = stack.getLast();
            logger.log(Level.INFO, "Get last element " + res);
            return res;
        }catch (NoSuchElementException e){
            return null;
        }
    }

    public Double getElementAndRemove(){
        logger.log(Level.INFO, "Use getElementAndRemove method:\n");
        Double elem = getElement();
        removeLastElement();
        return elem;
    }

    public void putElement(Double value){
        stack.add(value);
        logger.log(Level.INFO, "put value = " + value);
    }

    public void removeLastElement(){
        try{
            stack.removeLast();
            logger.log(Level.INFO, "delete last element");
        }catch (NoSuchElementException e){

        }
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
