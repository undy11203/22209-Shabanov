package com.shabanov.lab2.Module.ProjectTiles;

import com.shabanov.lab2.Module.Enemy.Enemy;
import com.shabanov.lab2.Module.Tower.Tower;
import com.shabanov.lab2.Module.Types.BulletType;

public class Fireball extends ProjectTile{
    public Fireball(Tower tower, Enemy enemy, boolean isFromTowerToEnemy) {
        super(tower, enemy, BulletType.FIREBALL, 0.08, isFromTowerToEnemy);
    }
}