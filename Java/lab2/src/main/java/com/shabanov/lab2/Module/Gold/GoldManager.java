package com.shabanov.lab2.Module.Gold;

import java.io.IOException;
import java.util.Properties;

public class GoldManager {
    private int gold = 0;
    private double goldRate;
    private double timeFromLastGold;
    public GoldManager() throws IOException {
        Properties info = new Properties();
        info.load(getClass().getClassLoader().getResourceAsStream("app.properties"));
        goldRate = Integer.parseInt(info.getProperty("goldRate"));
    }

    public void updateGold(double delta){
        timeFromLastGold += delta;
        if(timeFromLastGold > goldRate){
            timeFromLastGold = 0;
            gold += 1;
        }
    }

    public int getGold() {
        return gold;
    }
    public void changeGold(int delta) {
        gold += delta;
    }
}
