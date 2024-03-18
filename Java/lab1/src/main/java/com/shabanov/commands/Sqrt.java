package com.shabanov.commands;

import com.shabanov.exceptions.UncorrectValue;
import com.shabanov.exceptions.VoidStackException;

public class Sqrt implements Command {
    @Override
    public void execute(String[] paramentrs, Context ctx) throws UncorrectValue, VoidStackException {
        Double value = ctx.getElementAndRemove();
        if(value == null){
            throw new VoidStackException("Stack is void");
        }
        if(value < 0){
            throw new UncorrectValue("Value is negative");
        }

        ctx.putElement(Math.sqrt(value));
    }
}
