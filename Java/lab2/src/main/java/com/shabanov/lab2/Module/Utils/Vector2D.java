package com.shabanov.lab2.Module.Utils;

import java.util.Objects;

public class Vector2D {
    public double x = 0;
    public double y = 0;

    public Vector2D() {
    }

    public Vector2D(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public Vector2D(Vector2D oldCoord) {
        this.x = oldCoord.x;
        this.y = oldCoord.y;
    }


    @Override
    public boolean equals(Object obj){
        if (this == obj) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Vector2D other = (Vector2D) obj;
        return Double.compare(other.x, x) == 0 && Double.compare(other.y, y) == 0;
    }

    public double distance(Vector2D other){
        return Math.sqrt(Math.pow(this.x - other.x, 2) + Math.pow(this.y - other.y, 2));
    }
}
