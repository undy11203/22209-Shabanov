package com.shabanov.lab2.Module;

import com.shabanov.lab2.Module.Types.BlockType;
import com.shabanov.lab2.Module.Utils.LevelsFileManager;
import com.shabanov.lab2.Module.Utils.Vector2D;
import javafx.scene.image.Image;
import javafx.scene.image.WritableImage;

import java.net.URISyntaxException;
import java.util.ArrayList;

public class TileManager {
    private ArrayList<Image> tiles = new ArrayList<>();
    private LevelsFileManager fileManager = new LevelsFileManager();
    private ArrayList<ArrayList<BlockType>> map;

    private Vector2D size;

    public TileManager() {
        size = fileManager.getInfo("Size");
        CreateMap();
        CreateTiles();
    }

    private void CreateMap() {
        map = fileManager.getMap();
    }

    private void CreateTiles() {
        Image atlasRoad = new Image(getClass().getResourceAsStream("/assets/road.jfif"));

        Image grow = new WritableImage(atlasRoad.getPixelReader(), 0, 0, (int)atlasRoad.getWidth()/6, (int)atlasRoad.getHeight()/3);
        tiles.add(grow);
        Image road = new WritableImage(atlasRoad.getPixelReader(), (int)atlasRoad.getWidth()/6 * 3, 0, (int)atlasRoad.getWidth()/6, (int)atlasRoad.getHeight()/3);
        tiles.add(road);
    }

    public ArrayList<ArrayList<BlockType>> getMapInTypes() {
        return map;
    }
    public Image getTileFromTypes(BlockType type){
        return tiles.get(type.ordinal());
    }

    public Vector2D getMapSize() {
        return size;
    }
}
