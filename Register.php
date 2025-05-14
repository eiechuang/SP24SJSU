<html>
    <head>
        <title> File Processing... </title>
    </head>
    <body>
        <h1> Processing... </h1>
        <?php
        if (isset($_POST["username"]) && isset($_POST["password"])) {  
            if ($_POST["username"] && $_POST["password"]) {  
                $username = $_POST["username"];
                $password = $_POST["password"];

                $conn = mysqli_connect("localhost", "root", "", "users");

                if (!$conn) { 
                    die("Connection failed: " . mysqli_connect_error());
                }

                
                
                $sql = "INSERT INTO users (username, password) VALUES ('$username', '$password')";

                if (mysqli_query($conn, $sql)) {
                    echo "User has been successfully added.";
                } else {
                    echo "Error: " . mysqli_error($conn);
                }

                mysqli_close($conn);
            } else {
                echo "Username or Password is empty";
            } 
        } else {
            echo "Form not submitted.";
        }
        ?>
    </body>
</html>
