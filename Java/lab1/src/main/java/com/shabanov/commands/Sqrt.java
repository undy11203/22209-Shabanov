package com.shabanov.commands;

public class Sqrt implements Command {
    @Override
    public void execute(String[] paramentrs, Context ctx){
        Double first = ctx.getElement();
        ctx.removeLastElement();

        ctx.putElement(Math.sqrt(first));
    }
}
