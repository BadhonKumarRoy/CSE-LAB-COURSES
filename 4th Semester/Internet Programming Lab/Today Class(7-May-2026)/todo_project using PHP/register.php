<?php
include 'includes/db.php';
if (!isset($conn)) {
    die("conn not found");
}
if(isset($_POST['register'])){
    $username = $_POST['username'];
    $password = md5($_POST['password']);

    $sql = "INSERT INTO users(username,password)
            VALUES('$username','$password')";

    mysqli_query($conn,$sql);

    header("Location: login.php");
}
?>

<link rel="stylesheet" href="css/style.css">

<div class="container">
<h2>Register</h2>

<form method="POST">
    <input type="text" name="username" placeholder="Username" required>

    <input type="password" name="password" placeholder="Password" required>

    <button name="register">Register</button>
</form>

<a href="login.php">Login Here</a>
</div>