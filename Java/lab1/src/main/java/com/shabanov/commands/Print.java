package com.shabanov.commands;

import com.shabanov.exceptions.VoidStackException;

public class Print implements Command {
    @Override
    public void execute(String[] paramentrs, Context ctx) throws VoidStackException {
        Double value = ctx.getElement();
        if(value == null){
            throw new VoidStackException("Stack is void");
        }

        System.out.println(value);
    }
}
