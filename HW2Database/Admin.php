<?php 

$logged_in = false;

if (isset($_POST["username"]) && isset($_POST["password"])) {  
    if ($_POST["username"] && $_POST["password"]) {  
        $username = $_POST["username"];
        $password = $_POST["password"];

        // Connect to dtabase
        $conn = mysqli_connect("localhost", "root", "", "Users");

        if (!$conn) { 
            die("Connection failed: " . mysqli_connect_error());
        }

        
        $sql = "SELECT password FROM logins WHERE username = '$username'";
        $results = mysqli_query($conn, $sql);

        if ($results) {
            $row = mysqli_fetch_assoc($results);
            if ($row && $row["password"] === $password) {  // Password matches
                $logged_in = true;
                echo "Login successful";  // login is successful
                
            } else {
                echo "Password Incorrect";
            }
        } else {
            echo "Error: " . mysqli_error($conn);
        }

        mysqli_close($conn);
    } else {
        echo "Please enter both username and password.";
    }
} else {
    echo "Nothing was submitted.";
}
?>
