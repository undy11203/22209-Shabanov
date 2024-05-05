module com.shabanov.lab2 {
    requires javafx.controls;
    requires javafx.fxml;
            
                            
    opens com.shabanov.lab2 to javafx.fxml;
    exports com.shabanov.lab2;
    opens com.shabanov.lab2.View to javafx.fxml;
    exports com.shabanov.lab2.View;
    exports com.shabanov.lab2.Module.Pages;
    opens com.shabanov.lab2.Module.Pages to javafx.fxml;
}