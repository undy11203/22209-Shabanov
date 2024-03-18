package com.shabanov.commands;

import com.shabanov.exceptions.UncorrectValue;

public class Define implements Command {
    private boolean isNumeric(String str){
        try{
            Double.parseDouble(str);
            return true;
        }catch (NumberFormatException e){
            return false;
        }
    }

    @Override
    public void execute(String[] paramentrs, Context ctx) throws UncorrectValue {
        if(!isNumeric(paramentrs[1])){
            throw new UncorrectValue("is not double: " + paramentrs[1]);
        }
        ctx.putConstant(paramentrs[0], Double.parseDouble(paramentrs[1]));
    }
}
