package com.shabanov.lab2.Module.Enemy;

import com.shabanov.lab2.Module.ProjectTiles.ProjectTileManager;
import com.shabanov.lab2.Module.Tower.Tower;
import com.shabanov.lab2.Module.Tower.TowerManager;
import com.shabanov.lab2.Module.Types.BlockType;
import com.shabanov.lab2.Module.Types.BulletType;
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

    private TowerManager towerManager;
    private ProjectTileManager projectTileManager;
    private int bigRate;
    private LevelsFileManager levelsFileManager = new LevelsFileManager();
    private ArrayList<Vector2D> road;
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

    public void setProjectTileManager(ProjectTileManager projectTileManager) {
        this.projectTileManager = projectTileManager;
    }

    public void createWave(double delta){
        timeFromLastWave += delta;
        if(timeFromLastWave > bigRate){
            timeFromLastWave = 0;

            Vector2D coords = levelsFileManager.getInfo("Spawn");
            int random = new Random().nextInt();
            if(random%2 == 0){
                enemies.add(new Goblin(new Vector2D(coords), new ArrayList<>(road)));
                coords.x += 0.5;
                coords.y += 0.3;
                enemies.add(new Orc(new Vector2D(coords), new ArrayList<>(road)));
            }else {
                enemies.add(new Orc(new Vector2D(coords), new ArrayList<>(road)));
                coords.x += 0.5;
                coords.y += 0.3;
                enemies.add(new Goblin(new Vector2D(coords), new ArrayList<>(road)));
            }
            coords.x -= 0.5;
            coords.y += 0.2;
            enemies.add(new Wizard(new Vector2D(coords), new ArrayList<>(road)));
        }
    }

    public void setTowerManager(TowerManager towerManager) {
        this.towerManager = towerManager;
    }

    public void attack(double delta) {
        for (Enemy enemy : enemies){
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
    }

    public void moveEnemies(){
        enemies.stream().forEach(Enemy -> {
            if(!Enemy.isStop()){
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
            }
        });
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
