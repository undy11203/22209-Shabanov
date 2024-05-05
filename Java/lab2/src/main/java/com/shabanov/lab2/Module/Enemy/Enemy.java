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

    public Enemy(int life, int maxLife, int power, double speed, Vector2D coords, EnemyType type, ArrayList<Vector2D> way) {
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
    }

    public void setCoords(Vector2D coords){
        this.coords = coords;
    }

    public int getHealth() {
        return life;
    }

    public void setHealth(int life) { this.life = life; }

    public int getMaxHealth() {
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
}
