package com.shabanov.lab2.Module.Tower;

import com.shabanov.lab2.Module.Types.BulletType;
import com.shabanov.lab2.Module.Types.TowerType;
import com.shabanov.lab2.Module.Utils.Vector2D;

public class Piromant extends Tower{
    public Piromant(Vector2D coords) {
        super(50, coords, TowerType.PIROMANT, BulletType.FIREBALL, 3.0, 500.0, 0.0);
    }
}
