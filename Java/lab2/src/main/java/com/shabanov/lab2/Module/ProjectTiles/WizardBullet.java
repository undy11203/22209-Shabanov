package com.shabanov.lab2.Module.ProjectTiles;

import com.shabanov.lab2.Module.Enemy.Enemy;
import com.shabanov.lab2.Module.Tower.Tower;
import com.shabanov.lab2.Module.Types.BulletType;

public class WizardBullet extends ProjectTile {
    public WizardBullet(Tower tower, Enemy enemy, boolean isFromTowerToEnemy) {
        super(tower, enemy, BulletType.WIZARD_BULLET, 0.05, isFromTowerToEnemy);
    }
}
