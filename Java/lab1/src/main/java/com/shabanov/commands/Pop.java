package com.shabanov.commands;

public class Pop implements Command {
    @Override
    public void execute(String[] paramentrs, Context ctx){
        ctx.removeLastElement();
    }
}
