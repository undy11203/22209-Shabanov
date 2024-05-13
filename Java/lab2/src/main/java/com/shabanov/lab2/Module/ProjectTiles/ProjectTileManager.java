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

    public void addProjectTile(Tower tower, Enemy enemy, BulletType type, boolean isFromTowerToEnemy) {
        switch (type) {
            case FIREBALL -> projectTiles.add(new Fireball(tower, enemy, isFromTowerToEnemy));
            case BULLET -> projectTiles.add(new Bullet(tower, enemy, isFromTowerToEnemy));
            case WIZARD_BULLET -> projectTiles.add(new WizardBullet(tower, enemy, isFromTowerToEnemy));
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

                double distance = Math.sqrt(dy * dy + dx * dx);

                now.y += dy*speed/distance;
                now.x += dx*speed/distance;
            }
        });
    }

    public void destroyProjectTiles(){
        ArrayList<ProjectTile> remainingProjectTiles = new ArrayList<>();

        for (ProjectTile projectTile : projectTiles) {
            if (projectTile.getFinish() != null && projectTile.getCoord().distance(projectTile.getFinish()) > projectTile.getSpeed()) {
                remainingProjectTiles.add(projectTile);
            } else {
                if(projectTile.isFromTowerToEnemy()){
                    enemyManager.takeDamage(projectTile.getEnemy(), projectTile.getTower().getPower());
                }else {
                    towerManager.takeDamage(projectTile.getTower(), projectTile.getEnemy().getPower());
                }
                projectTiles = null;
            }
        }

        projectTiles = remainingProjectTiles;
    }

    public ArrayList<ProjectTile> getProjectTiles() {
        return projectTiles;
    }
}