<div class="container">
    <h1>Login</h1>
    <form method="POST">
        <input type="text" name="username" placeholder="Username"><br>
        <input type="password" name="password" placeholder="Password"><br>
        <button type="submit">Login</button>
        <a href="./Register.php">Register</a>
    </form>
</div>

<?php
    session_start();
    include 'db.php';
    if (!isset($conn)) {
        die("conn not found");
    }
    if(isset($_POST['username']) && isset($_POST['password'])){
        $username = $_POST['username'];
        $password = $_POST['password'];

        $sql = "SELECT * FROM users WHERE username='$username' AND password='$password'";
        $result = mysqli_query($conn, $sql);

        if(mysqli_num_rows($result) > 0){
            echo "Login Successful!";
            header("Location: demo.php");
        } else {
            echo "Invalid Credentials!";
        }
    }