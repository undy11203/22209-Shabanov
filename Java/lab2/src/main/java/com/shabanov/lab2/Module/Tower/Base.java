package com.shabanov.lab2.Module.Tower;

public class Base {
    private int maxLife;
    private int currentLife;

    public Base(int maxLife) {
        this.maxLife = maxLife;
        this.currentLife = maxLife;
    }

    public int getMaxLife() {
        return maxLife;
    }

    public int getCurrentLife() {
        return currentLife;
    }

    public void setCurrentLife(int currentLife) {
        this.currentLife = currentLife;
    }
}
