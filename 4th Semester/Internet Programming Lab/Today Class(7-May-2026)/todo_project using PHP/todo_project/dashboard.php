<?php
session_start();
include 'includes/db.php';

if(!isset($_SESSION['user_id'])){
    header("Location: login.php");
}

$user_id = $_SESSION['user_id'];

$result = mysqli_query($conn,
"SELECT * FROM tasks WHERE user_id='$user_id'");
?>

<!DOCTYPE html>
<html>
<head>

    <title>Dashboard</title>

    <link rel="stylesheet" href="css/style.css">

    <script src="js/script.js"></script>

</head>

<body>

<div class="container">

    <h2>Task Manager Dashboard</h2>

    <!-- Add Task Form -->

    <form action="add_task.php" method="POST">

        <input type="text"
        name="task_name"
        placeholder="Enter New Task"
        required>

        <button type="submit"
        onclick="taskAdded()">
        Add Task
        </button>

    </form>

    <br>

    <!-- Task Table -->

    <table>

        <tr>
            <th>ID</th>
            <th>Task Name</th>
            <th>Status</th>
            <th>Actions</th>
        </tr>

        <?php while($row = mysqli_fetch_assoc($result)){ ?>

        <tr>

            <td>
                <?php echo $row['id']; ?>
            </td>

            <td>
                <?php echo $row['task_name']; ?>
            </td>

            <td>
                <?php echo $row['status']; ?>
            </td>

            <td>

                <!-- Complete Task -->

                <a href="complete_task.php?id=<?php echo $row['id']; ?>">
                    Complete
                </a>

                |

                <!-- Edit Task -->

                <a href="edit_task.php?id=<?php echo $row['id']; ?>">
                    Edit
                </a>

                |

                <!-- Delete Task -->

                <a href="delete_task.php?id=<?php echo $row['id']; ?>"
                onclick="return confirmDelete()">
                    Delete
                </a>

            </td>

        </tr>

        <?php } ?>

    </table>

    <br>

    <!-- Logout -->

    <a href="logout.php">
        Logout
    </a>

</div>

</body>
</html>