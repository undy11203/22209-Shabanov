package com.shabanov.commands;

import com.shabanov.exceptions.NotEnoughStackValueException;
import com.shabanov.exceptions.NotExistsConstantException;
import com.shabanov.exceptions.UncorrectValue;
import com.shabanov.exceptions.VoidStackException;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

public class CommandTest {
    private Context ctx;
    private CommandFactory commandFactory;
    @BeforeEach
    void setUp(){
        ctx = new Context();
        commandFactory = new CommandFactory();
    }

    @Test
    void addCorrect() throws Exception {
        Command command = commandFactory.createCommand("+");
        ctx.putElement(10.0);
        ctx.putElement(20.0);
        command.execute(null, ctx);
        Assertions.assertEquals(30, ctx.getElement());
    }

    @Test
    void addNotEnoughParametr() throws Exception {
        Command command = commandFactory.createCommand("+");
        ctx.putElement(10.0);
        Assertions.assertThrowsExactly(NotEnoughStackValueException.class,
                                        () -> command.execute(null, ctx));
    }

    @Test
    void subCorrect() throws Exception {
        Command command = commandFactory.createCommand("-");
        ctx.putElement(10.0);
        ctx.putElement(20.0);
        command.execute(null, ctx);
        Assertions.assertEquals(-10.0, ctx.getElement());
    }

    @Test
    void subNotEnoughParametr() throws Exception {
        Command command = commandFactory.createCommand("-");
        ctx.putElement(10.0);
        Assertions.assertThrowsExactly(NotEnoughStackValueException.class,
                                        () -> command.execute(null, ctx));
    }

    @Test
    void divCorrect() throws Exception {
        Command command = commandFactory.createCommand("/");
        ctx.putElement(10.0);
        ctx.putElement(20.0);
        command.execute(null, ctx);
        Assertions.assertEquals(0.5, ctx.getElement());
    }

    @Test
    void divNotEnoughParametr() throws Exception {
        Command command = commandFactory.createCommand("/");
        ctx.putElement(10.0);
        Assertions.assertThrowsExactly(NotEnoughStackValueException.class,
                                        () -> command.execute(null, ctx));
    }

    @Test
    void divByZero(){
        Command command = commandFactory.createCommand("/");
        ctx.putElement(0.0);
        ctx.putElement(10.0);
        Assertions.assertThrows(UncorrectValue.class,
                                () -> command.execute(null, ctx));
    }

    @Test
    void mulCorrect() throws Exception {
        Command command = commandFactory.createCommand("*");
        ctx.putElement(20.0);
        ctx.putElement(2.0);
        command.execute(null, ctx);
        Assertions.assertEquals(40.0, ctx.getElement());
    }

    @Test
    void mulNotEnoughParametr() throws Exception {
        Command command = commandFactory.createCommand("+");
        ctx.putElement(10.0);
        Assertions.assertThrows(NotEnoughStackValueException.class,
                                () -> command.execute(null, ctx));
    }

    @Test
    void sqrtCorrect() throws Exception {
        Command command = commandFactory.createCommand("sqrt");
        ctx.putElement(4.0);
        command.execute(null, ctx);
        Assertions.assertEquals(2.0, ctx.getElement());
    }

    @Test
    void sqrtNotEnoughParametr() throws Exception {
        Command command = commandFactory.createCommand("sqrt");
        Assertions.assertThrowsExactly(VoidStackException.class,
                () -> command.execute(null, ctx));
    }

    @Test
    void sqrtWithNegativeValue(){
        Command command = commandFactory.createCommand("sqrt");
        ctx.putElement(-10.0);
        Assertions.assertThrows(UncorrectValue.class,
                () -> command.execute(null, ctx));
    }

    @Test
    void defineCorrect() throws Exception {
        Command command = commandFactory.createCommand("define");
        String[] p = {"a","3"};
        command.execute(p, ctx);
        Assertions.assertEquals(3, ctx.getConstant("a"));
    }

    @Test
    void defineUncorrectValue(){
        Command command = commandFactory.createCommand("define");
        String[] p = {"a", "pi"};
        Assertions.assertThrows(UncorrectValue.class, () -> command.execute(p, ctx));
    }

    @Test
    void pushCorrect() throws Exception {
        Command command = commandFactory.createCommand("push");
        String[] p = {"10"};
        command.execute(p, ctx);
        Assertions.assertEquals(10.0, ctx.getElement());
    }

    @Test
    void pushNotExistsConstant(){
        Command command = commandFactory.createCommand("push");
        String[] p = {"a"};
        Assertions.assertThrows(NotExistsConstantException.class, () -> command.execute(p, ctx));
    }

    @Test
    void popCorrect() throws Exception {
        Command command = commandFactory.createCommand("pop");
        ctx.putElement(10.0);
        ctx.putElement(20.0);
        command.execute(null, ctx);
        Assertions.assertEquals(10.0, ctx.getElement());
        command.execute(new String[]{"a"}, ctx);
        Assertions.assertEquals(10.0, ctx.getConstant("a"));
    }

    @Test
    void popVoidStack(){
        Command command = commandFactory.createCommand("pop");
        Assertions.assertThrows(VoidStackException.class, ()-> command.execute(null, ctx));
    }

    @Test
    void printCorrect() throws Exception {
        Command command = commandFactory.createCommand("print");
        ctx.putElement(10.0);
        ByteArrayOutputStream stream = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(stream);
        System.setOut(ps);
        command.execute(null, ctx);
        String output = stream.toString().replace("\r\n", "");
        Assertions.assertEquals("10.0", output);
    }

    @Test
    void printVoidStack(){
        Command command = commandFactory.createCommand("print");
        Assertions.assertThrows(VoidStackException.class, () -> command.execute(null, ctx));
    }
}
