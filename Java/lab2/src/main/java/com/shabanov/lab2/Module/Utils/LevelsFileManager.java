package com.shabanov.lab2.Module.Utils;

import com.shabanov.lab2.Module.Types.BlockType;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.Comparator;

public class LevelsFileManager {
    private String level;
    private int countLevels;
    public LevelsFileManager() {
        try {
            countLevels = new File(getClass().getResource("/levels/").getFile()).listFiles().length;
        }catch (NullPointerException e){
            e.printStackTrace();
        }
        level = new String("/levels/level" + LevelSelect.level + ".txt");
    }

    public int getCountLevels(){
        return countLevels;
    }

    public Vector2D getInfo(String name){
        try(BufferedReader br = new BufferedReader(new FileReader(getClass().getResource(level).getPath()))){
            while(br.ready()){
                String line = br.readLine();
                if(line.contains(name)){
                    String[] content = line.split(" ");
                    return new Vector2D(Integer.parseInt(content[1]), Integer.parseInt(content[2]));
                }
            }
        }catch (IOException e){
            e.printStackTrace();
        }
        return null;
    }
    public ArrayList<ArrayList<BlockType>> getMap(){
        try(BufferedReader br = new BufferedReader(new FileReader(getClass().getResource(level).getPath()))){
            while (br.ready()){
                String line = br.readLine();
                if(line.contains("┏")){
                    break;
                }

            }
            ArrayList<ArrayList<BlockType>> map = new ArrayList<>();
            while (br.ready()){
                String line = br.readLine();
                ArrayList<BlockType> row = new ArrayList<>();
                for(int i = 0; i < line.length(); i++){
                    if(line.charAt(i) == ' '){
                        row.add(BlockType.GROW);
                    }else if(line.charAt(i) == '╔'){
                        row.add(BlockType.ROAD);
                    }else if(line.charAt(i) == '═'){
                        row.add(BlockType.ROAD);
                    }else if(line.charAt(i) == '║'){
                        row.add(BlockType.ROAD);
                    }else if(line.charAt(i) == '╗'){
                        row.add(BlockType.ROAD);
                    }else if(line.charAt(i) == '╚'){
                        row.add(BlockType.ROAD);
                    }else if(line.charAt(i) == '╝'){
                        row.add(BlockType.ROAD);
                    }
                }
                if(row.size() == 0){
                    continue;
                }
                map.add(row);
            }
            return map;
        }catch (IOException e){
            e.printStackTrace();
        }
        return null;
    }

    public ArrayList<Vector2D> getRoad(){
        try(BufferedReader br = new BufferedReader(new FileReader(getClass().getResource(level).getPath()))){
            while (br.ready()){
                String line = br.readLine();
                if(line.contains("┏")){
                    break;
                }

            }
            ArrayList<Vector2D> road = new ArrayList<>();
            int y = 0;
            while (br.ready()){
                String line = br.readLine();
                for(int i = 0; i < line.length(); i++){
                    if(line.charAt(i) == '╔'){
                        road.add(new Vector2D(i-1, y));
                    }else if(line.charAt(i) == '═'){
                        road.add(new Vector2D(i-1, y));
                    }else if(line.charAt(i) == '║'){
                        road.add(new Vector2D(i-1, y));
                    }else if(line.charAt(i) == '╗'){
                        road.add(new Vector2D(i-1, y));
                    }else if(line.charAt(i) == '╚'){
                        road.add(new Vector2D(i-1, y));
                    }else if(line.charAt(i) == '╝'){
                        road.add(new Vector2D(i-1, y));
                    }
                }
                y++;
            }

            Vector2D start = getInfo("Spawn");
            ArrayList<Vector2D> resRoad = new ArrayList<>();
            int i = 0;
            for(i = 0; i< road.size(); i++){
                if(Double.compare(start.x, road.get(i).x) == 0 && Double.compare(start.y, road.get(i).y) == 0){
                    break;
                }
            }
            Vector2D minPoint = road.get(i);
            road.remove(i);
            resRoad.add(minPoint);
            while (!road.isEmpty()) {
                for (Vector2D point : road) {
                    if (Math.abs(minPoint.x - point.x) < 1 && Math.abs(minPoint.y - point.y) <= 1) {
                        minPoint = point;
                        break;
                    }else if(Math.abs(minPoint.x - point.x) <= 1 && Math.abs(minPoint.y - point.y) < 1){
                        minPoint = point;
                        break;
                    }
                }
                resRoad.add(minPoint);
                road.remove(minPoint);
            }
            return resRoad;
        }catch (IOException e){
            e.printStackTrace();
        }
        return null;
    }
}
