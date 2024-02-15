package com.shabanov.commands;

public interface Command {
    public void execute(String[] parametrs, Context ctx);
}
