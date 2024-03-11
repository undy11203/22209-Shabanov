package com.shabanov.commands;

import com.shabanov.exceptions.NotEnoughStackValueException;
import com.shabanov.exceptions.UncorrectValue;

public class Div implements Command {
    @Override
    public void execute(String[] paramentrs, Context ctx) throws NotEnoughStackValueException, UncorrectValue {
        Double first = ctx.getElementAndRemove();
        Double second = ctx.getElementAndRemove();
        if(first == null || second == null){
            throw new NotEnoughStackValueException("Not enough value");
        }
        if(first == 0){
            throw new UncorrectValue("Divide by 0");
        }

        ctx.putElement(second / first);
    }
}
