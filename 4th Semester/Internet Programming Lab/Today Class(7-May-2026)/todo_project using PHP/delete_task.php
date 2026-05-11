<?php
include 'includes/db.php';
if (!isset($conn)) {
    die("conn not found");
}
$id = $_GET['id'];

$sql = "DELETE FROM tasks WHERE id='$id'";

mysqli_query($conn,$sql);

header("Location: dashboard.php");
?>