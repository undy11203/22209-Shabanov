package com.shabanov.lab2.Module.Pages;

import com.shabanov.lab2.Game;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Objects;

public class SceneSwitch {
    public SceneSwitch(Pane currentPane, String fxml) throws IOException {
        Parent root = FXMLLoader.load(Objects.requireNonNull(Game.class.getResource(fxml)));
        Stage stage = (Stage) currentPane.getScene().getWindow();
        if(stage != null) {
            stage.close();
            stage.setScene(new Scene(root));
            stage.show();
        }
    }
}
