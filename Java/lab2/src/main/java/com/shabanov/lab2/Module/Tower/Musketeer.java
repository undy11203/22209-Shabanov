package com.shabanov.lab2.Module.Tower;

import com.shabanov.lab2.Module.Types.BulletType;
import com.shabanov.lab2.Module.Types.TowerType;
import com.shabanov.lab2.Module.Utils.Vector2D;

public class Musketeer extends Tower{
    public Musketeer(Vector2D coords) {
        super(20, coords, TowerType.MUSKETEER, BulletType.BULLET, 3.0, 1000.0, 0.0, 50);
    }
}
