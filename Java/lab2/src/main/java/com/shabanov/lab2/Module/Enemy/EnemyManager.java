package com.shabanov.lab2.Module.Enemy;

import com.shabanov.lab2.Module.Types.BlockType;
import com.shabanov.lab2.Module.Utils.LevelsFileManager;
import com.shabanov.lab2.Module.Utils.Vector2D;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URISyntaxException;
import java.time.Instant;
import java.util.ArrayList;
import java.util.Properties;
import java.util.Random;

public class EnemyManager {
    private ArrayList<Enemy> enemies = new ArrayList<>();
    private int bigRate;
    private int smallRate;
    private LevelsFileManager levelsFileManager = new LevelsFileManager();
    private ArrayList<Vector2D> road = new ArrayList<>();
    private Vector2D finish;
    private double timeFromLastWave = 0;

    private int damageBase = 0;

    public EnemyManager() throws IOException {
        Properties info = new Properties();
        info.load(getClass().getClassLoader().getResourceAsStream("app.properties"));
        bigRate = Integer.parseInt(info.getProperty("enemyWaveRate"));
        finish = levelsFileManager.getInfo("Base");
        road = levelsFileManager.getRoad();
        road.remove(0);
    }

    public void createWave(double delta){
        timeFromLastWave += delta;
        if(timeFromLastWave > bigRate){
            timeFromLastWave = 0;

            Vector2D coords = levelsFileManager.getInfo("Spawn");
            enemies.add(new Goblin(new Vector2D(coords), new ArrayList<>(road)));
            coords.x += 0.5;
            coords.y += 0.3;
            enemies.add(new Orc(new Vector2D(coords), new ArrayList<>(road)));
        }
    }

    public void moveEnemies(){
        enemies.stream().forEach(Enemy -> {
            ArrayList<Vector2D> way = Enemy.getWay();
            Vector2D cellCoord = new Vector2D(way.get(0));
            Vector2D nowCoord = Enemy.getCoord();

            cellCoord.x += Enemy.getOffsetX();
            cellCoord.y += Enemy.getOffsetY();

            double speed = Enemy.getSpeed();

            double dy = cellCoord.y - nowCoord.y;
            double dx = cellCoord.x - nowCoord.x;

            nowCoord.y += (dy > 0? 1: -1)*speed;
            nowCoord.x += (dx > 0? 1: -1)*speed;

            dy = cellCoord.y - nowCoord.y;
            dx = cellCoord.x - nowCoord.x;

            nowCoord.y += (dy > 0? 1: -1)*speed;
            nowCoord.x += (dx > 0? 1: -1)*speed;


            if(Math.abs(dy) < speed+speed/2 && Math.abs(dx) < speed+speed/2){
                way.remove(0);
                Enemy.setWay(way);
            }
        });
    }

    public void destroyEnemyes(){
        Vector2D finish = levelsFileManager.getInfo("Base");
        enemies.removeIf(Enemy -> {
            if(Enemy.getWay().size() == 0) damageBase++;

            if(Enemy.getWay().size() == 0) return true;
            if(Enemy.getHealth() <= 0) return true;
            return false;
        });
    }

    public ArrayList<Enemy> getEnemies() {
        return enemies;
    }

    public int destroyInBase() {
        int res = damageBase;
        damageBase = 0;
        return res;
    }

    public void takeDamage(Enemy enemy, int damage) {
        enemy.setHealth(enemy.getHealth() - damage);
    }
}
