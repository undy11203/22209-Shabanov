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

    public ProjectTile(Tower tower, Enemy enemy, BulletType type, Double speed) {
        this.tower = tower;
        this.enemy = enemy;
        this.type = type;
        this.speed = speed;
        this.coord = new Vector2D(tower.getCoord());
    }

    public BulletType getType() {
        return type;
    }

    public Vector2D getFinish() {
        if(enemy == null){
            return null;
        }
        return enemy.getCoord();
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
}
