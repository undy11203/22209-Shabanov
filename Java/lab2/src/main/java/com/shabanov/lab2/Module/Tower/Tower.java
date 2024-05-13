package com.shabanov.lab2.Module.Tower;

import com.shabanov.lab2.Module.Types.BulletType;
import com.shabanov.lab2.Module.Types.EnemyType;
import com.shabanov.lab2.Module.Types.TowerType;
import com.shabanov.lab2.Module.Utils.Vector2D;

public abstract class Tower {
    private int maxLife;
    private int life;
    private int power;
    private Vector2D coords;
    private TowerType towerType;
    private BulletType bulletType;
    private double radius;
    private double attackRate;
    private double lastAttackTime;

    private EnemyType priority = null;

    public Tower(int power, Vector2D coords, TowerType towerType, BulletType bulletType, double radius, double attackRate, double lastAttackTime, int maxLife) {
        this.power = power;
        this.coords = new Vector2D(coords);
        this.towerType = towerType;
        this.bulletType = bulletType;
        this.radius = radius;
        this.attackRate = attackRate;
        this.lastAttackTime = lastAttackTime;
        this.maxLife = maxLife;
        this.life = maxLife;
    }

    public Vector2D getCoord() {
        return coords;
    }

    public int getPower() {
        return power;
    }

    public void setPower(int i) {
        power = i;
    }

    public double getRadius() {
        return radius;
    }

    public void setRadius(double v) {
        radius = v;
    }

    public double getAttackRate() {
        return attackRate;
    }

    public double getLastAttackTime() {
        return lastAttackTime;
    }
    public void setLastAttackTime(double lastAttackTime) {
        this.lastAttackTime = lastAttackTime;
    }

    public TowerType getTowerType() {
        return towerType;
    }

    public BulletType getBulletType() {
        return bulletType;
    }

    public EnemyType getPriority() {
        return priority;
    }

    public void setPriority(EnemyType priority) {
        this.priority = priority;
    }

    public int getMaxLife() {
        return maxLife;
    }

    public void setMaxLife(int maxLife) {
        this.maxLife = maxLife;
    }

    public int getLife() {
        return life;
    }

    public void setLife(int life) {
        this.life = life;
    }

}
