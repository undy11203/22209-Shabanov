package com.shabanov.commands;

public interface Command {
    void execute(String[] parametrs, Context ctx) throws Exception;
}
