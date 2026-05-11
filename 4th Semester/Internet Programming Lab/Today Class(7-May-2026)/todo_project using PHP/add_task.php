<?php
session_start();
include 'includes/db.php';

if (!isset($conn)) {
    die("conn not found");
}
$user_id = $_SESSION['user_id'];
$task_name = $_POST['task_name'];

$sql = "INSERT INTO tasks(user_id,task_name)
VALUES('$user_id','$task_name')";

mysqli_query($conn,$sql);

header("Location: dashboard.php");
?>