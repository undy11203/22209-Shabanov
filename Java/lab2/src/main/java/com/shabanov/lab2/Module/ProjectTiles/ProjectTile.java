package com.shabanov.lab2.Module.ProjectTiles;

import com.shabanov.lab2.Module.Enemy.Enemy;
import com.shabanov.lab2.Module.Tower.Tower;
import com.shabanov.lab2.Module.Types.BulletType;
import com.shabanov.lab2.Module.Utils.Vector2D;

public abstract class ProjectTile {
    private Tower tower;
    private Enemy enemy;
    private BulletType type;
    private Double speed;
    private Vector2D coord;

    private boolean isFromTowerToEnemy;

    public ProjectTile(Tower tower, Enemy enemy, BulletType type, Double speed, boolean isFromTowerToEnemy) {
        this.tower = tower;
        this.enemy = enemy;
        this.type = type;
        this.speed = speed;
        this.isFromTowerToEnemy = isFromTowerToEnemy;
        if(isFromTowerToEnemy){
            this.coord = new Vector2D(tower.getCoord());
        }else {
            this.coord = new Vector2D(enemy.getCoord());
        }
    }

    public BulletType getType() {
        return type;
    }

    public Vector2D getFinish() {
        if(isFromTowerToEnemy){
            if(enemy == null){
                return null;
            }
            return enemy.getCoord();
        }else{
            if(tower == null){
                return null;
            }
            return tower.getCoord();
        }
    }

    public void setType(BulletType type) {
        this.type = type;
    }

    public Double getSpeed() {
        return speed;
    }

    public void setSpeed(Double speed) {
        this.speed = speed;
    }


    public Vector2D getCoord() {
        return coord;
    }

    public void setCoord(Vector2D coord) {
        this.coord = coord;
    }

    public Tower getTower(){
        return tower;
    }

    public Enemy getEnemy(){
        return enemy;
    }


    public boolean isFromTowerToEnemy() {
        return isFromTowerToEnemy;
    }
}
