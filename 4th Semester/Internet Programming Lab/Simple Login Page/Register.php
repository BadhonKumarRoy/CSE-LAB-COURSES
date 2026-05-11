<div>
    <h1>Register</h1>
    <form method="POST">
        <input type="text" name="username" placeholder="Username"> <br>
        <input type="password" name="password" placeholder="Password"><br>
        <input type="password" name="confirm_password" placeholder="Confirm Password"><br>
        <button name="register">Register</button>
        <a href="./Login.php">Login</a>
    </form>
</div>

<?php
    include 'db.php';
    if (!isset($conn)) {
        die("conn not found");
    }
    // check password empty
    if(empty($_POST['password']) || empty($_POST['confirm_password'])){
        die("<script>alert('Password cannot be empty!');</script>");
    }
    if($_POST['password'] !== $_POST['confirm_password']){
        die("<script>alert('Passwords do not match!');</script>");
    }
    // check username is available or not
    if(isset($_POST['username'])){
        $username = $_POST['username'];
        $sql = "SELECT * FROM users WHERE username='$username'";
        $result = mysqli_query($conn, $sql);
        if(mysqli_num_rows($result) > 0){
            die("<script>alert('Username already taken!');</script>");
        }
    }
    if(isset($_POST['username']) && isset($_POST['password']) && isset($_POST['confirm_password'])){
        $username = $_POST['username'];
        $password = $_POST['password'];
        $confirm_password = $_POST['confirm_password'];

        if($password === $confirm_password){
            $sql = "INSERT INTO users (username, password) VALUES ('$username', '$password')";
            if(mysqli_query($conn, $sql)){
                echo "Registration Successful!";
                header("Location: Login.php");
            } else {
                echo "Error: " . mysqli_error($conn);
            }
        } else {
            echo "Passwords do not match!";
        }
    }