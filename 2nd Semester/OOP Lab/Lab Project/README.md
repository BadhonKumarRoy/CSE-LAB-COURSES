# Course Management System

## Group Information
- **Group Roll's**: 04324205101006, 04324205101007, 04324205101042

## Overview
This is a Java-based Course Management System that allows managing teachers, students, and courses. The system provides functionality to add, edit, and view information about teachers, students, and courses, as well as assign courses to teachers and register courses for students.

## Features

### Teacher Management
- Add new teachers with details (name, age, ID, department, designation)
- Edit existing teacher information
- View all teachers with their assigned courses
- Assign courses to teachers

### Student Management
- Add new students with details (name, age, ID, department, batch, semester, grade)
- Edit existing student information
- View all students with their registered courses
- Register courses for students

### Course Management
- Add new courses with details (course ID, title, credit hours)
- Edit existing course information
- View all courses

## Class Structure

### Person (Abstract Base Class)
- `id`: Person's ID
- `name`: Person's name
- `age`: Person's age

### Course
- `c_id`: Course ID (unique)
- `c_title`: Course title
- `credit_hour`: Credit hours
- Methods for adding, editing, and listing courses

### Teacher (extends Person)
- `department`: Teacher's department
- `designation`: Teacher's designation
- `assignedCourses`: List of assigned courses
- Methods for adding, editing, and listing teachers
- Course assignment functionality

### Student (extends Person)
- `department`: Student's department
- `semester`: Current semester
- `batch`: Batch number
- `grade`: Grade level
- `registeredCourses`: List of registered courses
- Methods for adding, editing, and listing students
- Course registration functionality

### Menu
- Displays the main menu options

## How to Use

1. Run the `Main` class
2. Select options from the menu by entering the corresponding number:

### Menu Options
| Option | Description |
|--------|-------------|
| 1 | Add Teacher |
| 2 | Edit Teacher Info |
| 3 | View Teacher List |
| 4 | Add Student |
| 5 | Edit Student Info |
| 6 | View Student List |
| 7 | Add Course |
| 8 | Edit Course Info |
| 9 | View Course List |
| 10 | Assign Course to Teacher |
| 11 | Register Course for Student |
| 0 | Exit |

## Key Features

### Unique ID Validation
- Teacher IDs, Student IDs, and Course IDs are checked for duplicates during creation and editing

### Edit Functionality
- Edit existing records by ID
- Maintains data integrity during edits

### Course Assignment
- Assign courses to teachers by ID
- Teachers can have multiple courses

### Course Registration
- Register courses for students by ID
- Students can register for multiple courses

## Sample Usage

```java
// Adding a new course
// Option 7 from menu
Enter Course ID: CS101
Enter Course Title: Introduction to Programming
Enter Credit Hour: 3.0

// Assigning a course to a teacher
// Option 10 from menu
Enter Teacher ID: 1001
Enter Course ID: CS101
Course assigned successfully.
```

## Limitations
- Maximum of 10 teachers, 10 students, and 10 courses (array-based implementation)
- Data is not persisted between program runs (in-memory only)
- Input validation is basic

## Future Improvements
- Implement database persistence
- Increase storage capacity using dynamic data structures
- Enhanced input validation
- GUI interface
- Reporting features