package com.shabanov.commands;

public class Print implements Command {
    @Override
    public void execute(String[] paramentrs, Context ctx){
        Double value = ctx.getElement();

        System.out.println(value);
    }
}
