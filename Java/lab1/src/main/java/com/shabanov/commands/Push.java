package com.shabanov.commands;

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
    public void execute(String[] paramentrs, Context ctx){
        if(isNumeric(paramentrs[0])){
            ctx.putElement(Double.parseDouble(paramentrs[0]));
        }else{
            ctx.putElement(ctx.getConstant(paramentrs[0]));
        }
    }
}
