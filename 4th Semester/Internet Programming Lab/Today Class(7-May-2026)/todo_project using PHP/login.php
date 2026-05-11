<?php
session_start();
include 'includes/db.php';
if (!isset($conn)) {
    die("conn not found");
}
if(isset($_POST['login'])){
    $username = $_POST['username'];
    $password = md5($_POST['password']);

    $sql = "SELECT * FROM users
            WHERE username='$username'
            AND password='$password'";

    $result = mysqli_query($conn,$sql);

    if(mysqli_num_rows($result) > 0){
        $row = mysqli_fetch_assoc($result);

        $_SESSION['user_id'] = $row['id'];

        header("Location: dashboard.php");
    }else{
        echo "Invalid Login!";
    }
}
?>

<link rel="stylesheet" href="css/style.css">

<div class="container">
<h2>Login</h2>

<form method="POST">
    <input type="text" name="username" placeholder="Username" required>

    <input type="password" name="password" placeholder="Password" required>

    <button name="login">Login</button>
</form>

<a href="register.php">Register Here</a>
</div>