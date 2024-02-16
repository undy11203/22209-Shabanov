package com.shabanov.commands;

import com.shabanov.exceptions.NotExistsConstantException;

public class Push implements Command{
    private boolean isNumeric(String str){
        try{
            Double.parseDouble(str);
            return true;
        }catch (NumberFormatException e){
            return false;
        }
    }

    @Override
    public void execute(String[] paramentrs, Context ctx) throws NotExistsConstantException{
        if(isNumeric(paramentrs[0])){
            ctx.putElement(Double.parseDouble(paramentrs[0]));
        }else{
            if(ctx.getConstant(paramentrs[0]) == null){
                throw new NotExistsConstantException("Not exists constant with this name");
            }
            ctx.putElement(ctx.getConstant(paramentrs[0]));
        }
    }
}
