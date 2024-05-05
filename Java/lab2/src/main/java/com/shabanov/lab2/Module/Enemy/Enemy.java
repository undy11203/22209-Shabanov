package com.shabanov.lab2.Module.Enemy;

import com.shabanov.lab2.Module.Types.EnemyType;
import com.shabanov.lab2.Module.Utils.Vector2D;

import java.util.ArrayList;

public abstract class Enemy {
    private int life;
    private int maxLife;
    private int power;
    private double speed;
    private Vector2D coords;
    private Vector2D offsetCoord;
    private EnemyType type;
    private ArrayList<Vector2D> way;
    private boolean isTowerAttackingEnemy;

    private int attackRate;

    private double radius;

    private  boolean isStop = false;

    private double lastTimeToAttack = 0;

    public Enemy(int life, int maxLife, int power, double speed, Vector2D coords, EnemyType type, ArrayList<Vector2D> way, boolean isTowerAttackingEnemy, double radius, int attackRate) {
        this.life = life;
        this.maxLife = maxLife;
        this.power = power;
        this.speed = speed;
        this.coords = coords;
        this.type = type;
        this.way = way;
        this.offsetCoord = new Vector2D();
        this.offsetCoord.x = this.coords.x - (int)this.coords.x;
        this.offsetCoord.y = this.coords.y - (int)this.coords.y;
        this.isTowerAttackingEnemy = isTowerAttackingEnemy;
        if(isTowerAttackingEnemy){
            this.radius = radius;
            this.attackRate = attackRate;
        }
    }

    public void setCoords(Vector2D coords){
        this.coords = coords;
    }

    public int getLife() {
        return life;
    }

    public void setLife(int life) { this.life = life; }

    public int getMaxLife() {
        return maxLife;
    }

    public int getPower() {
        return power;
    }

    public double getSpeed() {
        return speed;
    }

    public Vector2D getCoord() {
        return coords;
    }

    public EnemyType getType() {
        return type;
    }

    public ArrayList<Vector2D> getWay() {
        return way;
    }

    public void setWay(ArrayList<Vector2D> way) {
        this.way = way;
    }

    public double getOffsetX() {
        return offsetCoord.x;
    }

    public double getOffsetY(){
        return offsetCoord.y;
    }

    public boolean isTowerAttackingEnemy() {
        return isTowerAttackingEnemy;
    }

    public void setTowerAttackingEnemy(boolean towerAttackingEnemy) {
        isTowerAttackingEnemy = towerAttackingEnemy;
    }

    public double getRadius() {
        return radius;
    }


    public int getAttackRate() {
        return attackRate;
    }

    public boolean isStop() {
        return isStop;
    }

    public void setStop(boolean stop) {
        isStop = stop;
    }

    public double getLastTimeToAttack() {
        return lastTimeToAttack;
    }

    public void setLastTimeToAttack(double lastTimeToAttack) {
        this.lastTimeToAttack = lastTimeToAttack;
    }
}
