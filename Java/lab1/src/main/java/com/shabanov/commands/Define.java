package com.shabanov.commands;

public class Define implements Command {
    @Override
    public void execute(String[] paramentrs, Context ctx){
        ctx.putConstant(paramentrs[0], Double.parseDouble(paramentrs[1]));
    }
}
