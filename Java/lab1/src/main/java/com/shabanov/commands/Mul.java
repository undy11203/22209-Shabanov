package com.shabanov.commands;

import com.shabanov.exceptions.NotEnoughStackValueException;

public class Mul implements Command {
    @Override
    public void execute(String[] paramentrs, Context ctx) throws NotEnoughStackValueException {
        Double first = ctx.getElement();
        ctx.removeLastElement();
        Double second = ctx.getElement();
        ctx.removeLastElement();
        if(first == null || second == null){
            throw new NotEnoughStackValueException("Not enough value");
        }

        ctx.putElement(first * second);
    }
}
