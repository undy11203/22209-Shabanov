package com.shabanov.lab2.Module.ProjectTiles;

import com.shabanov.lab2.Module.Enemy.Enemy;
import com.shabanov.lab2.Module.Enemy.EnemyManager;
import com.shabanov.lab2.Module.Tower.Tower;
import com.shabanov.lab2.Module.Tower.TowerManager;
import com.shabanov.lab2.Module.Types.BulletType;
import com.shabanov.lab2.Module.Utils.Vector2D;

import java.util.ArrayList;

public class ProjectTileManager {
    ArrayList<ProjectTile> projectTiles = new ArrayList<>();
    EnemyManager enemyManager;
    TowerManager towerManager;

    public ProjectTileManager(EnemyManager enemyManager, TowerManager towerManager) {
        this.enemyManager = enemyManager;
        this.towerManager = towerManager;
    }

    public void addProjectTile(Tower tower, Enemy enemy, BulletType type) {
        switch (type) {
            case FIREBALL -> projectTiles.add(new Fireball(tower, enemy));
            case BULLET -> projectTiles.add(new Bullet(tower, enemy));
        }
    }

    public void moveProjectTile() {
        projectTiles.stream().forEach(ProjectTile -> {
            Vector2D finishCoord = ProjectTile.getFinish();
            if(finishCoord != null){
                Vector2D now = ProjectTile.getCoord();
                double speed = ProjectTile.getSpeed();
                double dy = finishCoord.y - now.y;
                double dx = finishCoord.x - now.x;

                now.y += (dy > 0? 1: -1)*speed;
                now.x += (dx > 0? 1: -1)*speed;

                dy = finishCoord.y - now.y;
                dx = finishCoord.x - now.x;

                now.y += (dy > 0? 1: -1)*speed;
                now.x += (dx > 0? 1: -1)*speed;
            }
        });
    }

    public void destroyProjectTiles(){
        projectTiles.removeIf(ProjectTile -> {
            if(ProjectTile.getFinish() == null || ProjectTile.getEnemy() == null) return true;
            if(ProjectTile.getCoord().distance(ProjectTile.getEnemy().getCoord()) < 0.1) {
                enemyManager.takeDamage(ProjectTile.getEnemy(), ProjectTile.getTower().getPower());
                return true;
            }
            return false;
        });
    }

    public ArrayList<ProjectTile> getProjectTiles() {
        return projectTiles;
    }
}