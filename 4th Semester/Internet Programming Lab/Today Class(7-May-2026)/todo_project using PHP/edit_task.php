<?php
session_start();
include 'includes/db.php';
if (!isset($conn)) {
    die("conn not found");
}
$id = $_GET['id'];

$result = mysqli_query($conn,
"SELECT * FROM tasks WHERE id='$id'");

$row = mysqli_fetch_assoc($result);

if(isset($_POST['update'])){

    $task_name = $_POST['task_name'];

    $sql = "UPDATE tasks
            SET task_name='$task_name'
            WHERE id='$id'";

    mysqli_query($conn,$sql);

    header("Location: dashboard.php");
}
?>

<link rel="stylesheet" href="css/style.css">

<div class="container">

<h2>Edit Task</h2>

<form method="POST">

    <input type="text"
    name="task_name"
    value="<?php echo $row['task_name']; ?>"
    required>

    <button name="update">Update Task</button>

</form>

</div>