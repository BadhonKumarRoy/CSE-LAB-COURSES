<?php
include 'includes/db.php';

$id = $_GET['id'];

$sql = "UPDATE tasks
SET status='Completed'
WHERE id='$id'";

mysqli_query($conn,$sql);

header("Location: dashboard.php");
?>