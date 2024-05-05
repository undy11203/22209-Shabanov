package com.shabanov.lab2.Module.Enemy;

import com.shabanov.lab2.Module.Types.EnemyType;
import com.shabanov.lab2.Module.Utils.Vector2D;

import java.util.ArrayList;

public class Goblin extends Enemy{
    public Goblin(Vector2D coords, ArrayList<Vector2D> way) {
        super(100, 100, 10, 0.05, coords, EnemyType.GOBLIN, way, false, 0, 0);
    }

}
