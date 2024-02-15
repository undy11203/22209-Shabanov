package com.shabanov.commands;

public class Mul implements Command {
    @Override
    public void execute(String[] paramentrs, Context ctx){
        Double first = ctx.getElement();
        Double second = ctx.getElement();
        ctx.removeLastElement();
        ctx.removeLastElement();

        ctx.putElement(first * second);
    }
}
