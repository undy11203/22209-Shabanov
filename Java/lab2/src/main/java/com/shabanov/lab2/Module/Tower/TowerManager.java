package com.shabanov.lab2.Module.Tower;

import com.shabanov.lab2.Module.Enemy.EnemyManager;
import com.shabanov.lab2.Module.Enemy.Enemy;
import com.shabanov.lab2.Module.ProjectTiles.ProjectTileManager;
import com.shabanov.lab2.Module.Types.EnemyType;
import com.shabanov.lab2.Module.Types.TowerType;
import com.shabanov.lab2.Module.Utils.Vector2D;

import java.util.ArrayList;

public class TowerManager {
    private Base base;
    private EnemyManager enemyManager;
    private ProjectTileManager projectTileManager;
    private ArrayList<Tower> towers = new ArrayList<>();
    public TowerManager() {
        this.base = new Base(100);
    }

    public void updateState(double delta){
        for(Tower tower: towers){
            attack(tower, delta);
        }
    }

    private void attack(Tower tower, double delta){
        tower.setLastAttackTime(tower.getLastAttackTime()+delta);
        if(tower.getLastAttackTime() > tower.getAttackRate()){
            tower.setLastAttackTime(0);

            ArrayList<Enemy> enemies = enemyManager.getEnemies();
            Vector2D towerCoord = tower.getCoord();
            double radius = tower.getRadius();
            Enemy target = null;
            EnemyType towerPriority = tower.getPriority();

            double lastDistance = 100;
            for (Enemy enemy : enemies) {
                Vector2D enemyCoord = enemy.getCoord();
                double distance = Math.sqrt(Math.pow(enemyCoord.x - towerCoord.x, 2) + Math.pow(enemyCoord.y - towerCoord.y, 2));

                if (towerPriority == enemy.getType()) {
                    if (distance <= radius && distance < lastDistance) {
                        lastDistance = distance;
                        target = enemy;
                    }
                }
            }

            if (target == null) {
                for (Enemy enemy : enemies) {
                    Vector2D enemyCoord = enemy.getCoord();
                    double distance = Math.sqrt(Math.pow(enemyCoord.x - towerCoord.x, 2) + Math.pow(enemyCoord.y - towerCoord.y, 2));
                    if (distance <= radius && distance < lastDistance) {
                        lastDistance = distance;
                        target = enemy;
                    }
                }
            }

            if(target != null){
                projectTileManager.addProjectTile(tower, target, tower.getBulletType(), true);
            }
        }
    }

    public void addTower(TowerType tower, Vector2D coords) {

        switch (tower){
            case MUSKETEER -> towers.add(new Musketeer(coords));
            case PIROMANT -> towers.add(new Piromant(coords));
        }
    }

    public ArrayList<Tower> getTowers(){
        return towers;
    }

    public int towerCost(TowerType type) {
        switch (type){
            case MUSKETEER -> {
                return 10;
            }
            case PIROMANT -> {
                return 20;
            }
        }
        return 0;
    }

    public int getLifeBase() {
        return base.getCurrentLife();
    }

    public void calcDamage(int damageToBase) {
        base.setCurrentLife(base.getCurrentLife()-damageToBase);
    }

    public void setEnemyManager(EnemyManager enemyManager) {
        this.enemyManager = enemyManager;
    }

    public void setProjectTileManager(ProjectTileManager projectTileManager) {
        this.projectTileManager = projectTileManager;
    }

    public boolean isExistTower(Vector2D vector2D) {
        for(Tower tower : towers){
            Vector2D coord = tower.getCoord();
            if (coord.equals(vector2D)) return true;
        }
        return false;
    }

    public TowerType getTowerTypeInCoord(Vector2D vector2D){
        TowerType type = null;
        for(Tower tower : towers){
            Vector2D coord = tower.getCoord();
            if (coord.x == vector2D.x && coord.y == vector2D.y) {
                type = tower.getTowerType();
            }
        }
        return type;
    }

    public void upgradeTower(Vector2D vector2D) {
        for(Tower tower : towers){
            Vector2D coord = tower.getCoord();
            if (coord.x == vector2D.x && coord.y == vector2D.y) {
                tower.setPower(tower.getPower()+5);
                break;
            }
        }
    }

    public TowerType removeTower(Vector2D vector2D) {
        TowerType type = null;
        for(Tower tower : towers){
            Vector2D coord = tower.getCoord();
            if (coord.x == vector2D.x && coord.y == vector2D.y) {
                type = tower.getTowerType();
                towers.remove(tower);
                break;
            }
        }
        return type;
    }

    public void ChangePriority(Vector2D vector2D, EnemyType type){
        for(Tower tower : towers){
            Vector2D coord = tower.getCoord();
            if (coord.equals(vector2D)) tower.setPriority(type);
        }
    }

    public void destroyTower() {
        ArrayList<Tower> remainingTowers = new ArrayList<>();

        for (Tower tower : towers) {
            if (tower.getLife() > 0) {
                remainingTowers.add(tower);
            } else {
                tower = null;
            }
        }

        towers = remainingTowers;
    }


    public void takeDamage(Tower tower, int damage) {
        tower.setLife(tower.getLife() - damage);
    }
}
