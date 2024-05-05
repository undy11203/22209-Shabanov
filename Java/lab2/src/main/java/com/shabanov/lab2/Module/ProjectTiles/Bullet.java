package com.shabanov.lab2.Module.ProjectTiles;

import com.shabanov.lab2.Module.Enemy.Enemy;
import com.shabanov.lab2.Module.Tower.Tower;
import com.shabanov.lab2.Module.Types.BulletType;

public class Bullet extends ProjectTile {
    public Bullet(Tower tower, Enemy enemy, boolean isFromTowerToEnemy) {
        super(tower, enemy, BulletType.BULLET, 0.15, isFromTowerToEnemy);
    }
}
