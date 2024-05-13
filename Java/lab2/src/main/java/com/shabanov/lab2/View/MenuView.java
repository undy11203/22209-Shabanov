package com.shabanov.lab2.View;

import com.shabanov.lab2.Controller.MenuController;
import com.shabanov.lab2.Module.Utils.LevelsFileManager;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Menu;
import javafx.scene.layout.Pane;

import java.io.IOException;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class MenuView implements Initializable {
    @FXML private Pane Menu;
    @FXML private ArrayList<Button> levels = new ArrayList<>();

    MenuController menuController = new MenuController();
    LevelsFileManager levelsFileManager = new LevelsFileManager();
    @Override
    public void initialize(URL location, ResourceBundle resource){
        for (int i = 0; i< levelsFileManager.getCountLevels(); i++){
            Button level = new Button("Level " + (i + 1));
            int levelNumber = i;
            level.setOnAction(event -> {
                menuController.setLevel(levelNumber+1);
                switchToNewView();
            });
            levels.add(level);
        }

        Platform.runLater(() -> {
            double spacing = 10.0;
            double buttonWidth = 90;
            double buttonHeight = 20;
            double posY = (Menu.getHeight() - (levels.size() * (buttonHeight + spacing))) / 2.0;

            for (Button levelButton : levels) {
                levelButton.setPrefHeight(buttonHeight);
                levelButton.setPrefWidth(buttonWidth);
                double posX = (Menu.getWidth() - buttonWidth) / 2.0;
                levelButton.setLayoutX(posX);
                levelButton.setLayoutY(posY);

                posY += buttonHeight + spacing;

                Menu.getChildren().add(levelButton);
            }
        });

    }

    public void switchToNewView() {
        try {
            menuController.viewSwitch(Menu, "/fxml/Game.fxml");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
