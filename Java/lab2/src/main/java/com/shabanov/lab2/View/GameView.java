package com.shabanov.lab2.View;

import com.shabanov.lab2.Controller.GameController;
import com.shabanov.lab2.Controller.MenuController;
import com.shabanov.lab2.Module.Enemy.Enemy;
import com.shabanov.lab2.Module.ProjectTiles.ProjectTile;
import com.shabanov.lab2.Module.Tower.Tower;
import com.shabanov.lab2.Module.Types.BlockType;
import com.shabanov.lab2.Module.Types.TowerType;
import com.shabanov.lab2.Module.Utils.Vector2D;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.util.Duration;

import java.io.IOException;
import java.net.URL;
import java.time.Instant;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class GameView implements Initializable {
    @FXML Canvas mainCanvas;
    @FXML Pane Game;
    @FXML Pane Menu;
    @FXML Text gold;
    @FXML Text live;
    @FXML Text time;
    @FXML Pane currentTowerMenu;
    @FXML Button upgrade;
    @FXML Button remove;
    @FXML ArrayList<Button> priorityEnemy = new ArrayList<>();

    private int mouseX;
    private int mouseY;
    private int clickMouseX;
    private int clickMouseY;


    GameController gameController = new GameController();
    MenuController menuController = new MenuController();

    private double timerEndGame = 0;
    private double timeEndGame = 2000;
    private double timerGame = 0;
    private Instant lastUpdateInstant = Instant.now();

    private String towerButtonText = null;
    private boolean isClicked = false;

    @Override
    public void initialize(URL location, ResourceBundle resource){
        Game.setStyle("-fx-background-color: #232323");

        try {
            gameController.init();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        Timeline timeline = new Timeline(new KeyFrame(
                Duration.millis(40),
                this::onTimerTick
        ));
        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.play();
        
        RenderStaticUI();
    }

    private void RenderStaticUI() {
        ArrayList<Button> towers = new ArrayList<>();
        towers.add(new Button("Musketeer"));
        towers.add(new Button("Piromant"));
        for (int i = 0; i < towers.size(); i++){
            Button tower = towers.get(i);
            tower.setLayoutX(20);
            tower.setLayoutY(10 + i*40);
            tower.setOnAction(e -> {
                Menu.getChildren().removeIf(node -> node instanceof ImageView);

                towerButtonText = tower.getText();
                Image image = new Image(getClass().getResource("/assets/" + tower.getText() + ".png").toString());
                ImageView imageView = new ImageView(image);
                imageView.setFitHeight(60);
                imageView.setFitWidth(60);
                imageView.setLayoutX(150);
                imageView.setLayoutY(20);
                Menu.getChildren().add(imageView);
            });
        }
        Menu.getChildren().addAll(towers);
        currentTowerMenu = new Pane();
        currentTowerMenu.setPrefWidth(Menu.getPrefWidth() / 2);
        currentTowerMenu.setLayoutX(Menu.getPrefWidth() / 2);
        Menu.getChildren().add(currentTowerMenu);
    }

    private void onTimerTick(ActionEvent actionEvent) {
        Instant now = Instant.now();
        double delta = (double) java.time.Duration.between(lastUpdateInstant, now).toMillis();
        timerGame += delta;

        if(gameController.isGameWin(timerGame)){
            timerEndGame += delta;
            if(timerEndGame >= timeEndGame){
                try{
                    menuController.viewSwitch(Game, "/fxml/Menu.fxml");
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            RenderGameWin();
        } else if(gameController.isGameOver()){
            timerEndGame += delta;
            if(timerEndGame >= timeEndGame){
                try{
                    menuController.viewSwitch(Game, "/fxml/Menu.fxml");
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            RenderGameOver();
        }else{
            gameController.UpdateState(delta);

            RenderMap();
            RenderTower();
            RenderEnemy();
            RenderProjectile();
            RenderDynamicUI();
        }

        lastUpdateInstant = now;
    }

    private void RenderGameWin() {
        Game.getChildren().clear();
        Game.setStyle("-fx-background-color: black;");

        Font font = Font.loadFont(String.valueOf(getClass().getResource("/assets/Silkscreen.ttf")), 20);

        Text gameOverText = new Text("Game win!!!");
        gameOverText.setFont(font);
        gameOverText.setFill(Color.GREEN);
        gameOverText.setLayoutX((Game.getWidth() - gameOverText.getBoundsInLocal().getWidth()) / 2);
        gameOverText.setLayoutY(Game.getHeight() / 2);

        Game.getChildren().add(gameOverText);
    }

    private void RenderGameOver() {
        Game.getChildren().clear();
        Game.setStyle("-fx-background-color: black;");

        Font font = Font.loadFont(String.valueOf(getClass().getResource("/assets/Silkscreen.ttf")), 20);

        Text gameOverText = new Text("Game over");
        gameOverText.setFont(font);
        gameOverText.setFill(Color.RED);
        gameOverText.setLayoutX((Game.getWidth() - gameOverText.getBoundsInLocal().getWidth()) / 2);
        gameOverText.setLayoutY(Game.getHeight() / 2);

        Game.getChildren().add(gameOverText);

    }

    private void RenderDynamicUI() {
        GraphicsContext context2D = mainCanvas.getGraphicsContext2D();

        Vector2D sizeTileMap = gameController.getStaticMapSize();
        Vector2D tileSize = new Vector2D(mainCanvas.getWidth()/sizeTileMap.x,
                mainCanvas.getHeight()/sizeTileMap.y);

        mainCanvas.setOnMouseClicked(event -> {
            gameController.UpdateTowersArray(towerButtonText, new Vector2D((int)(event.getX() / tileSize.x), (int)(event.getY() / tileSize.y)));
            clickMouseX = (int) (event.getX() / tileSize.x);
            clickMouseY = (int) (event.getY() / tileSize.y);
            System.out.println(clickMouseX + " " + clickMouseY);
            if(gameController.isExistTowerInCoord(new Vector2D(clickMouseX, clickMouseY))){
                currentTowerMenu.getChildren().clear();
                Font font = Font.loadFont(String.valueOf(getClass().getResource("/assets/Silkscreen.ttf")), 20);
                Text priorityText = new Text("Get priority");
                priorityText.setFont(font);
                priorityText.setFill(Color.WHITE);
                priorityText.setLayoutX(currentTowerMenu.getWidth() - 250);
                priorityText.setLayoutY(15);
                currentTowerMenu.getChildren().add(priorityText);

                Button priorityButton1 = new Button("Orc");
                priorityButton1.setLayoutX(currentTowerMenu.getWidth() - 250);
                priorityButton1.setLayoutY(23);
                priorityEnemy.add(priorityButton1);

                Button priorityButton2 = new Button("Goblin");
                priorityButton2.setLayoutX(currentTowerMenu.getWidth() - 250);
                priorityButton2.setLayoutY(38);
                priorityEnemy.add(priorityButton2);

                Button priorityButton3 = new Button("Wizard");
                priorityButton3.setLayoutX(currentTowerMenu.getWidth() - 250);
                priorityButton3.setLayoutY(52);
                priorityEnemy.add(priorityButton3);

                Button priorityButton4 = new Button("none");
                priorityButton4.setLayoutX(currentTowerMenu.getWidth() - 250);
                priorityButton4.setLayoutY(70);
                priorityEnemy.add(priorityButton4);
                currentTowerMenu.getChildren().addAll(priorityEnemy);

                upgrade = new Button("Upgrade");
                upgrade.setLayoutX(currentTowerMenu.getWidth() - 70);
                upgrade.setLayoutY(20);
                currentTowerMenu.getChildren().add(upgrade);

                remove = new Button("Remove");
                remove.setLayoutX(currentTowerMenu.getWidth() - 70);
                remove.setLayoutY(50);

                TowerType type = gameController.getTowerTypeInCoord(new Vector2D(clickMouseX, clickMouseY));
                if(type != null){
                    String name = "";
                    switch (type) {
                        case PIROMANT -> name = "Piromant";
                        case MUSKETEER -> name = "Musketeer";
                    }
                    Image image = new Image(getClass().getResource("/assets/" + name + ".png").toString());
                    ImageView imageView = new ImageView(image);
                    imageView.setFitHeight(60);
                    imageView.setFitWidth(60);
                    imageView.setLayoutX(currentTowerMenu.getWidth() - 170);
                    imageView.setLayoutY(20);
                    currentTowerMenu.getChildren().add(imageView);
                }

                currentTowerMenu.getChildren().add(remove);
            }else if(gameController.isExistTowerInCoord(new Vector2D(clickMouseX, clickMouseY))){
                currentTowerMenu.getChildren().clear();
            }
        });

        if(priorityEnemy.size() > 0){
            for (Button priority: priorityEnemy){
                priority.setOnAction(event -> {
                    gameController.changePriority(new Vector2D(clickMouseX, clickMouseY), priority.getText());
                });
            }
        }

        if(upgrade != null){
            upgrade.setOnAction(event -> {
                gameController.towerUpgrade(new Vector2D(clickMouseX, clickMouseY));
            });
        }

        if(remove != null){
            remove.setOnAction(event -> {
                gameController.towerRemove(new Vector2D(clickMouseX, clickMouseY));
                currentTowerMenu.getChildren().clear();
            });
        }

        mainCanvas.setOnMouseMoved(event -> {
            mouseX = (int) ((int) (event.getX() / tileSize.x) * tileSize.x);
            mouseY = (int) ((int) (event.getY() / tileSize.y) * tileSize.y);
        });
        context2D.setStroke(Color.WHITE);
        context2D.strokeRect(mouseX, mouseY, tileSize.x, tileSize.y);

        Font font = Font.loadFont(String.valueOf(getClass().getResource("/assets/Silkscreen.ttf")), 20);

        int goldCount = gameController.getGold();
        gold.setFill(Color.rgb(228, 155, 15));
        gold.setFont(font);
        gold.setText("Gold: " + goldCount);

        int liveCount = gameController.getLifeBase();
        live.setFill(Color.rgb(220, 20, 60));
        live.setFont(font);
        live.setText("Live: " + liveCount);

        time.setFill(Color.rgb(0, 0, 0));
        time.setFont(font);
        time.setText("Time: " + (int)timerGame/1000 + "/" + gameController.getTimeToWin() + " sec");
    }

    private void RenderProjectile() {
        GraphicsContext context2D = mainCanvas.getGraphicsContext2D();
        ArrayList<ProjectTile> projectTiles = gameController.getProjectTiles();
        ArrayList<ArrayList<BlockType>> blocks = gameController.getStaticMap();
        Vector2D tileSize = new Vector2D();
        tileSize.x = mainCanvas.getWidth() / blocks.get(0).size();
        tileSize.y = mainCanvas.getHeight() / blocks.size();

        if(projectTiles.size() > 0){
            for (ProjectTile projectTile: projectTiles){
                Vector2D coords = projectTile.getCoord();

                String imgPath = "/assets/";
                switch (projectTile.getType()){
                    case BULLET -> imgPath += "Bullet.png";
                    case FIREBALL -> imgPath += "Fireball.png";
                    case WIZARD_BULLET -> imgPath += "wizerdBullet.png";
                }

                Image projectTileImage = new Image(getClass().getResource(imgPath).toString());

                if(projectTileImage != null){
                    double imgX = coords.x * tileSize.x;
                    double imgY = coords.y * tileSize.y;
                    context2D.drawImage(projectTileImage, imgX, imgY, 10, 10);
                }
            }
        }
    }

    private void RenderTower() {
        GraphicsContext context2D = mainCanvas.getGraphicsContext2D();

        Vector2D sizeTileMap = gameController.getStaticMapSize();
        Vector2D tileSize = new Vector2D(mainCanvas.getWidth()/sizeTileMap.x,
                mainCanvas.getHeight()/sizeTileMap.y);

        ArrayList<Tower> towers = gameController.getTowers();

        if(towers.size() > 0){
            for (Tower tower: towers){
                double life = tower.getLife();
                double maxLife = tower.getMaxLife();
                double currentCent = life/maxLife;

                Vector2D coords = tower.getCoord();

                String imgPath = "/assets/";
                switch (tower.getTowerType()){
                    case MUSKETEER -> imgPath += "Musketeer.png";
                    case PIROMANT -> imgPath += "Piromant.png";
                }

                Image towerImage = new Image(getClass().getResource(imgPath).toString());

                if (towerImage != null) {
                    double imgX = coords.x * tileSize.x;
                    double imgY = coords.y * tileSize.y;
                    context2D.drawImage(towerImage, imgX, imgY, tileSize.x, tileSize.y);
                    context2D.setStroke(Color.BLUE);
                    context2D.strokeRect(imgX+10, imgY + tileSize.y - tileSize.y/10, tileSize.x-20, 10);
                    context2D.setFill(Color.WHITE);
                    context2D.fillRect(imgX+10, imgY + tileSize.y - tileSize.y/10+2, (tileSize.x-20)*currentCent, 8);
                }
            }
        }
    }

    private void RenderEnemy() {
        GraphicsContext context2D = mainCanvas.getGraphicsContext2D();
        ArrayList<Enemy> enemies = gameController.getEnemies();

        ArrayList<ArrayList<BlockType>> blocks = gameController.getStaticMap();
        Vector2D tileSize = new Vector2D();
        tileSize.x = mainCanvas.getWidth() / blocks.get(0).size();
        tileSize.y = mainCanvas.getHeight() / blocks.size();

        if(enemies.size() > 0){
            for (Enemy enemy: enemies){
                Vector2D coords = enemy.getCoord();
                double life = enemy.getLife();
                double maxLife = enemy.getMaxLife();
                double currentCent = life/maxLife;

                String imgPath = "/assets/";
                switch (enemy.getType()){
                    case GOBLIN -> imgPath += "Goblin.png";
                    case ORC -> imgPath += "Orc.png";
                    case WIZARD -> imgPath += "Wizard.png";
                }

                Image enemyImage = new Image(getClass().getResource(imgPath).toString());

                if (enemyImage != null) {
                    double imgX = coords.x * tileSize.x;
                    double imgY = coords.y * tileSize.y;

                    context2D.drawImage(enemyImage, imgX, imgY, tileSize.x/4, tileSize.y/4);
                    context2D.setStroke(Color.RED);
                    context2D.strokeRect(imgX, imgY + tileSize.y/4 + 10, 10, 2);
                    context2D.setFill(Color.WHITE);
                    context2D.fillRect(imgX, imgY + tileSize.y/4 + 10, 10*currentCent, 2);

                }

            }
        }

    }

    private void RenderMap() {
        GraphicsContext context2D = mainCanvas.getGraphicsContext2D();

        ArrayList<ArrayList<BlockType>> blocks = gameController.getStaticMap();
        Vector2D tileSize = new Vector2D();
        tileSize.x = mainCanvas.getWidth() / blocks.get(0).size();
        tileSize.y = mainCanvas.getHeight() / blocks.size();
        for(int y = 0; y < blocks.size(); y++){
            for (int x = 0; x < blocks.get(0).size(); x++){
                context2D.drawImage(gameController.getTile(blocks.get(y).get(x)),
                        x * tileSize.x, y * tileSize.y);
            }
        }
    }


}