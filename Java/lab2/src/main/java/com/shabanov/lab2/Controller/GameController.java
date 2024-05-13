package com.shabanov.lab2.Controller;

import com.shabanov.lab2.Module.Enemy.EnemyManager;
import com.shabanov.lab2.Module.Enemy.Enemy;
import com.shabanov.lab2.Module.Gold.GoldManager;
import com.shabanov.lab2.Module.ProjectTiles.ProjectTile;
import com.shabanov.lab2.Module.ProjectTiles.ProjectTileManager;
import com.shabanov.lab2.Module.TileManager;
import com.shabanov.lab2.Module.Tower.Tower;
import com.shabanov.lab2.Module.Tower.Tower;
import com.shabanov.lab2.Module.Tower.TowerManager;
import com.shabanov.lab2.Module.Types.BlockType;
import com.shabanov.lab2.Module.Types.BulletType;
import com.shabanov.lab2.Module.Types.EnemyType;
import com.shabanov.lab2.Module.Types.TowerType;
import com.shabanov.lab2.Module.Utils.LevelsFileManager;
import com.shabanov.lab2.Module.Utils.Vector2D;
import javafx.scene.image.Image;

import java.io.IOException;
import java.net.URISyntaxException;
import java.time.Instant;
import java.util.ArrayList;
import java.util.Properties;

public class GameController {
    private TileManager map;
    private EnemyManager enemyManager;
    private GoldManager goldManager;
    private TowerManager towerManager;
    private ProjectTileManager projectTileManager;
    private double timeToWin;

    public void UpdateState(double delta) {
        projectTileManager.moveProjectTile();
        projectTileManager.destroyProjectTiles();

        enemyManager.UpdateState(delta);
        int damageToBase = enemyManager.destroyInBase();
        if(damageToBase > 0){
            towerManager.calcDamage(damageToBase);
        }
        towerManager.updateState(delta);
        towerManager.destroyTower();

        goldManager.updateGold(delta);


    }

    public void init() throws IOException {
        map = new TileManager();
        goldManager = new GoldManager();
        enemyManager = new EnemyManager();
        towerManager = new TowerManager();
        projectTileManager = new ProjectTileManager(enemyManager, towerManager);
        towerManager.setEnemyManager(enemyManager);
        towerManager.setProjectTileManager(projectTileManager);
        enemyManager.setTowerManager(towerManager);
        enemyManager.setProjectTileManager(projectTileManager);

        Properties info = new Properties();
        try {
            info.load(getClass().getClassLoader().getResourceAsStream("app.properties"));
            timeToWin = Integer.parseInt(info.getProperty("timeToWin"))*1000;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public ArrayList<ArrayList<BlockType>> getStaticMap() {
        return map.getMapInTypes();
    }

    public Image getTile(BlockType type) {
        return map.getTileFromTypes(type);
    }


    public ArrayList<ProjectTile> getProjectTiles() {
        return projectTileManager.getProjectTiles();
    }

    public ArrayList<Enemy> getEnemies() {
        return enemyManager.getEnemies();
    }

    public ArrayList<Tower> getTowers() {
        return towerManager.getTowers();
    }

    public Vector2D getStaticMapSize() {
        return map.getMapSize();
    }

    public int getGold() { return goldManager.getGold(); }

    public void UpdateTowersArray(String towerType, Vector2D vector2D) {
        if(towerType == null) return;
        TowerType type;
        switch (towerType){
            case "Piromant" -> type = TowerType.PIROMANT;
            case "Musketeer" -> type = TowerType.MUSKETEER;
            default -> {
                return;
            }
        }

        if(getGold() >= towerManager.towerCost(type) && !towerManager.isExistTower(vector2D)){
            towerManager.addTower(type, vector2D);
            goldManager.changeGold(-towerManager.towerCost(type));
        }
    }

    public int getLifeBase() {
        return towerManager.getLifeBase();
    }

    public boolean isGameOver() {
        if(towerManager.getLifeBase() <= 0) return true;
        return false;
    }

    public void towerUpgrade(Vector2D vector2D) {
        TowerType type = towerManager.getTowerTypeInCoord(vector2D);
        if(type != null){
            towerManager.upgradeTower(vector2D);
            switch (type){
                case MUSKETEER -> {
                    if(goldManager.getGold() >= 5){
                        goldManager.changeGold(-5);
                    }
                }
                case PIROMANT -> {
                    if(goldManager.getGold() >= 10){
                        goldManager.changeGold(-10);
                    }
                }
            }
        }
    }

    public void towerRemove(Vector2D vector2D) {
        TowerType type = towerManager.removeTower(vector2D);
        if(type != null){
            switch (type){
                case MUSKETEER -> goldManager.changeGold(5);
                case PIROMANT -> goldManager.changeGold(10);
            }
        }
    }

    public boolean isExistTowerInCoord(Vector2D vector2D){
        return towerManager.isExistTower(vector2D);
    }

    public TowerType getTowerTypeInCoord(Vector2D vector2D) { return  towerManager.getTowerTypeInCoord(vector2D); }

    public void changePriority(Vector2D vector2D, String enemyName) {
        switch (enemyName) {
            case "Goblin" -> towerManager.ChangePriority(vector2D, EnemyType.GOBLIN);
            case "Orc" -> towerManager.ChangePriority(vector2D, EnemyType.ORC);
            case "Wizard" -> towerManager.ChangePriority(vector2D, EnemyType.WIZARD);
            case "none" -> towerManager.ChangePriority(vector2D, null);
        }
    }

    public boolean isGameWin(double timerGame) {
        if (timerGame > timeToWin) return true;
        return false;
    }

    public int getTimeToWin(){
        return (int) timeToWin/1000;
    }
}
