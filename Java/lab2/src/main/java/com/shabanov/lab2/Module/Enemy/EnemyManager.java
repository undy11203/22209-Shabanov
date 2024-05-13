package com.shabanov.lab2.Module.Enemy;

import com.shabanov.lab2.Module.ProjectTiles.ProjectTileManager;
import com.shabanov.lab2.Module.Tower.Tower;
import com.shabanov.lab2.Module.Tower.TowerManager;
import com.shabanov.lab2.Module.Types.BlockType;
import com.shabanov.lab2.Module.Types.BulletType;
import com.shabanov.lab2.Module.Utils.LevelSelect;
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
    private int level;
    private ArrayList<Enemy> enemies = new ArrayList<>();
    private TowerManager towerManager;
    private ProjectTileManager projectTileManager;
    private int bigRate;
    private LevelsFileManager levelsFileManager = new LevelsFileManager();
    private ArrayList<Vector2D> road;
    private Vector2D finish;
    private Vector2D spawn;
    private double timeFromLastWave = 0;
    private int damageBase = 0;

    public EnemyManager() throws IOException {
        Properties info = new Properties();
        info.load(getClass().getClassLoader().getResourceAsStream("app.properties"));
        bigRate = Integer.parseInt(info.getProperty("enemyWaveRate"));
        finish = levelsFileManager.getInfo("Base");
        spawn = levelsFileManager.getInfo("Spawn");
        level = LevelSelect.level;
        road = levelsFileManager.getRoad();
        road.remove(0);
    }

    public void setProjectTileManager(ProjectTileManager projectTileManager) {
        this.projectTileManager = projectTileManager;
    }


    public void UpdateState(double delta) {
        createWave(delta);
        for (Enemy enemy: enemies){
            attack(delta, enemy);
            moveEnemies(enemy);
        }
        destroyEnemyes();
    }

    public void createWave(double delta){
        timeFromLastWave += delta;
        if(timeFromLastWave > bigRate) {
            timeFromLastWave = 0;

            for (int i = 0; i < level; i++) {
                int random = (new Random().nextInt()) % 3;
                Vector2D newVec = new Vector2D(spawn);
                newVec.x += 0.1 + (new Random()).nextDouble() * 0.4;
                newVec.y += 0.1 + (new Random()).nextDouble() * 0.4;
                switch (random) {
                    case 0 -> enemies.add(new Goblin(newVec, new ArrayList<>(road)));
                    case 1 -> enemies.add(new Orc(newVec, new ArrayList<>(road)));
                    case 2 -> enemies.add(new Wizard(newVec, new ArrayList<>(road)));
                }
            }
        }
    }

    public void setTowerManager(TowerManager towerManager) {
        this.towerManager = towerManager;
    }

    public void attack(double delta, Enemy enemy) {
        enemy.setLastTimeToAttack(enemy.getLastTimeToAttack()+delta);
        if(enemy.getLastTimeToAttack() > enemy.getAttackRate() && enemy.isTowerAttackingEnemy()){
            enemy.setLastTimeToAttack(0);
            double radius = enemy.getRadius();
            double lastDistance = 100;
            Vector2D enemyCoord = enemy.getCoord();
            Tower target = null;

            ArrayList<Tower> towers = towerManager.getTowers();
            for (Tower tower: towers){
                Vector2D towerCoord = tower.getCoord();
                double distance = Math.sqrt(Math.pow(towerCoord.x - enemyCoord.x, 2) + Math.pow(towerCoord.y - enemyCoord.y, 2));

                if (distance <= radius && distance < lastDistance) {
                    lastDistance = distance;
                    target = tower;
                }
            }

            if(target != null){
                enemy.setStop(true);
                projectTileManager.addProjectTile(target, enemy, BulletType.WIZARD_BULLET, false);
            }else{
                enemy.setStop(false);
            }
        }else if(enemy.getLastTimeToAttack() <= enemy.getAttackRate() && enemy.isTowerAttackingEnemy()) {
            enemy.setLastTimeToAttack(enemy.getLastTimeToAttack()+delta);
        }
    }

    public void moveEnemies(Enemy enemy){
        if(!enemy.isStop()){
            ArrayList<Vector2D> way = enemy.getWay();
            Vector2D cellCoord = new Vector2D(way.get(0));
            Vector2D nowCoord = enemy.getCoord();

            cellCoord.x += enemy.getOffsetX();
            cellCoord.y += enemy.getOffsetY();

            double speed = enemy.getSpeed();

            double dy = cellCoord.y - nowCoord.y;
            double dx = cellCoord.x - nowCoord.x;

            double distance = Math.sqrt(dy * dy + dx * dx);

            nowCoord.y += dy*speed/distance;
            nowCoord.x += dx*speed/distance;

            if(Math.abs(dy) < speed+speed/2 && Math.abs(dx) < speed+speed/2){
                way.remove(0);
                enemy.setWay(way);
            }
        }
    }

    public void destroyEnemyes(){
        ArrayList<Enemy> remainingEnemies = new ArrayList<>();


        for (Enemy enemy : enemies) {
            if (enemy.getLife() > 0 && enemy.getWay().size() > 0) {
                remainingEnemies.add(enemy);
            } else {
                if(enemy.getWay().size() == 0){
                    damageBase++;
                }
                enemy = null;
            }
        }

        enemies = remainingEnemies;
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
        enemy.setLife(enemy.getLife() - damage);
    }

}
