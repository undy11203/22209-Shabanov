package com.shabanov.commands;

import com.shabanov.exceptions.VoidStackException;
public class Pop implements Command {
    @Override
    public void execute(String[] paramentrs, Context ctx) throws VoidStackException{
        if(ctx.getElement() == null){
            throw new VoidStackException("Stack is void");
        }
        if(paramentrs == null){
            ctx.removeLastElement();
        }else if(paramentrs.length == 1){
            Double elem = ctx.getElementAndRemove();
            ctx.putConstant(paramentrs[0], elem);
        }
    }
}
