package com.shabanov.commands;


import com.shabanov.exceptions.NotEnoughStackValueException;

public class Add implements Command{
    @Override
    public void execute(String[] paramentrs, Context ctx) throws NotEnoughStackValueException {
        Double first = ctx.getElementAndRemove();
        Double second = ctx.getElementAndRemove();
        if(first == null || second == null){
            throw new NotEnoughStackValueException("Not enough value");
        }

        ctx.putElement(first + second);
    }
}
